/*
* Vulkan Renderer base class.
*
* Copyright (C) 2017 by Primoz Lavric
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "base/VulkanInstance.h"
#include <algorithm>
#include "GlobalConfig.h"
#include "DebugUtils.h"

namespace logi {

ApplicationInfo::ApplicationInfo(const std::string& app_name, const uint32_t app_version, const std::string& engine_name, const uint32_t engine_version)
	: app_name(app_name), app_version(app_version), engine_name(engine_name), engine_version(engine_version) {}

InstanceConfiguration::InstanceConfiguration(const std::vector<const char*>& extensions, bool enable_validation, const std::vector<const char*>& validation_layers)
	: extensions(extensions), enable_validation(enable_validation), validation_layers(validation_layers) {}


VulkanInstance::VulkanInstance() : data_(nullptr), handle_manager_(nullptr) {}

VulkanInstance::VulkanInstance(const ApplicationInfo& application_info, const InstanceConfiguration& configuration)
	: data_(std::make_shared<InstanceData>(application_info, configuration)), handle_manager_(std::make_shared<HandleManager>()) {

	const ApplicationInfo& app_info = data_->application_info;
	InstanceConfiguration& config = data_->configuration;

	// Create ApplicationInfo using the global configuration.
	vk::ApplicationInfo vk_app_info{};

	vk_app_info.pApplicationName = app_info.app_name.c_str();
	vk_app_info.applicationVersion = app_info.app_version;
	vk_app_info.pEngineName = app_info.engine_name.c_str();
	vk_app_info.engineVersion = app_info.engine_version;
	vk_app_info.apiVersion = VK_API_VERSION_1_1;

	vk::InstanceCreateInfo instance_ci{};
	instance_ci.pApplicationInfo = &vk_app_info;



	// Initialize requested extensions.
	// Add debug report extension if the validation is enabled.
	if (config.enable_validation) {
		// Add debug report extension if not present.
		if (std::find(config.extensions.begin(), config.extensions.end(), VK_EXT_DEBUG_REPORT_EXTENSION_NAME) == config.extensions.end()) {
			config.extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}
	}

	instance_ci.enabledExtensionCount = static_cast<uint32_t>(config.extensions.size());
	instance_ci.ppEnabledExtensionNames = config.extensions.data();

	// Setup validation layers if validation is enabled.
	if (config.enable_validation) {
		std::vector<const char*>& layers = config.validation_layers;

		// Check if the requested validation layers are supported.
		if (config.enable_validation && !checkValidationLayerSupport(layers)) {
			throw std::runtime_error("Requested validation layers are not supported!");
		}

		instance_ci.ppEnabledLayerNames = layers.data();
		instance_ci.enabledLayerCount = static_cast<uint32_t>(layers.size());
	} else {
		instance_ci.enabledLayerCount = 0;
	}

	// Try to create instance.
	data_->vk_instance = vk::createInstance(instance_ci);


	// Fetch available physical devices.
	std::vector<vk::PhysicalDevice> physical_devices = data_->vk_instance.enumeratePhysicalDevices();

	// Create Vulkan device handles.
	for (vk::PhysicalDevice& p_dev : physical_devices) {
		data_->devices.emplace_back(handle_manager_->createHandle<VulkanDevice>(p_dev));
	}
}

void VulkanInstance::setupDebugCallback(const vk::DebugReportFlagsEXT& flags, PFN_vkDebugReportCallbackEXT callback) {
	// Validation must be enabled in order to setup a debug callback.
	if (!vkr::debug_utils::kEnableValidation) {
		return;
	}

	// Generate callback create info
	VkDebugReportCallbackCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = static_cast<VkDebugReportFlagsEXT>(flags);
	createInfo.pfnCallback = callback;

	// Setup callback.
	auto setup_callback_fn = reinterpret_cast<PFN_vkCreateDebugReportCallbackEXT>(data_->vk_instance.getProcAddr("vkCreateDebugReportCallbackEXT"));

	// Check if the setup callback function was successfully retrieved.
	if (setup_callback_fn == nullptr) {
		throw std::runtime_error("Failed to set up debug callback!");
	}

	data_->debug_callbacks.push_back({});
	setup_callback_fn(static_cast<VkInstance>(data_->vk_instance), &createInfo, nullptr, reinterpret_cast<VkDebugReportCallbackEXT*>(&data_->debug_callbacks.back()));
}

const ApplicationInfo& VulkanInstance::applicationInfo() const {
	return data_->application_info;
}

const InstanceConfiguration& VulkanInstance::configuration() const {
	return data_->configuration;
}

const std::vector<VulkanDevice>& VulkanInstance::devices() const {
	return data_->devices;
}

const vk::Instance& VulkanInstance::getVkHandle() const {
	return data_->vk_instance;
}

bool VulkanInstance::checkValidationLayerSupport(const std::vector<const char*>& layers) {
	uint32_t layerCount;
	vk::enumerateInstanceLayerProperties(&layerCount, nullptr);

	// Fetch validation layers
	std::vector<vk::LayerProperties> availableLayers(layerCount);
	vk::enumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	// Check if all requested validation layers are present among the available layers.
	for (const char* layerName : layers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

void VulkanInstance::free() {
	if (alive()) {
		handle_manager_->destroyAllHandles();

		if (vkr::debug_utils::kEnableValidation) {
			// Clear debug callbacks.
			const auto destroy_callback_fn = reinterpret_cast<PFN_vkDestroyDebugReportCallbackEXT>(data_->vk_instance.getProcAddr("vkDestroyDebugReportCallbackEXT"));

			// Check if the destroy callback function was successfully retrieved.
			if (destroy_callback_fn == nullptr) {
				throw std::runtime_error("Failed to destroy debug callbacks!");
			}

			for (auto& callback : data_->debug_callbacks) {
				destroy_callback_fn(static_cast<VkInstance>(data_->vk_instance), static_cast<VkDebugReportCallbackEXT>(callback), nullptr);
			}
		}

		Handle::free();
	}
}

VulkanInstance::InstanceData::InstanceData(const ApplicationInfo& application_info, const InstanceConfiguration& configuration)
	: application_info(application_info), configuration(configuration) {}


} /// !namespace logi