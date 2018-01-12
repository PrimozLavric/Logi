/*
* Vulkan Renderer base class.
*
* Copyright (C) 2017 by Primoz Lavric
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "examples/ExampleA.h"
#include "program_management/ProgramManager.h"
#include <vector>
#include <iostream>
#include "base/VulkanDevice.h"
#include "util/helpers.h"
#include "base/Types.h"

namespace vkr {

const int WIDTH = 3200;
const int HEIGHT = 2400;
const int WORKGROUP_SIZE = 32;

ExampleA::ExampleA(std::vector<char *>& global_extensions, std::vector<char *>& device_extensions, vk::PhysicalDeviceFeatures& features) : RendererBase(global_extensions), gpu_(nullptr) {

	auto scoreDevice = [&device_extensions, &features](const VulkanDevice* device) {
		// Device must support all requested extensions.
		for (char* extension : device_extensions) {
			if (!device->extensionSupported(extension)) {
				return -1;
			}
		}

		// Check if the device supports all requested features.
		if (!hasRequestedFeatures(device->features(), features)) {
			return -1;
		}

		int32_t score = 0;
		// Prefer discrete gpu-s.
		if (device->properties().deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
			score += 100000;
		}

		// Score based on the device memory.
		std::vector<vk::MemoryHeap> heaps = std::vector<vk::MemoryHeap>(device->memoryProperties().memoryHeaps, device->memoryProperties().memoryHeaps + device->memoryProperties().memoryHeapCount);

		for (const vk::MemoryHeap& heap : heaps) {
			if (heap.flags & vk::MemoryHeapFlagBits::eDeviceLocal) {
				score += heap.size / 1048576;
				break;
			}
		}

		return score;
	};

	// Retrieve devices that match the scoring function criteria.
	std::vector<std::pair<int32_t, VulkanDevice*>> devices = retrieveDevices(scoreDevice);

	// Make user select the device.
	std::cout << "Select the device: " << std::endl;
	for (size_t i = 0; i < devices.size(); i++) {
		std::cout << i << ": " << devices[i].second->properties().deviceName << std::endl;
	}

	size_t selection;
	while (true) {
		std::cin >> selection;

		if (selection < devices.size()) {
			break;
		}
	}

	// Select and initialize the device.
	gpu_ = devices[selection].second;
	gpu_->initialize(features, device_extensions, QueueConfig(0, 1, 0));
	gpu_->getComputeFamily()->createCommandPool(false, false);
}

void ExampleA::runExample() {
	std::vector<char*> global_extensions;
	std::vector<char*> device_extensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	vk::PhysicalDeviceFeatures features;

	ExampleA example(global_extensions, device_extensions, features);
	ProgramManager* pm = example.gpu_->getProgramManager();
	pm->loadPrograms("./resources/shaders");

	example.gpu_->createDescriptorPool(pm->getDescriptorsCount());
	DescriptorPool* dp = example.gpu_->getDescriptorPool();
	
	ComputePipeline* compute_pipeline = pm->getComputePipeline(pm->getComputePipelineId("compute_test"));

	dp->createDescriptorSet(compute_pipeline->getPipelineLayout())

	Buffer* buffer = example.gpu_->getAllocationManager()->allocateBuffer(BufferConfiguration(WIDTH * HEIGHT, vk::BufferUsageFlagBits::eStorageBuffer));
	

	std::cout << "success" << std::endl;
}

}