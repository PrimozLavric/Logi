/**
 * Project Logi source code
 * Copyright (C) 2019 Lana Besevic
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "logi/program/pipeline.hpp"
#include "logi/device/logical_device.hpp"
#include "logi/device/physical_device.hpp"
#include "logi/instance/vulkan_instance.hpp"
#include "logi/program/pipeline_impl.hpp"

namespace logi {

// region Vulkan Definitions

vk::DeviceSize Pipeline::getRayTracingShaderGroupStackSizeKHR(uint32_t group, 
                                                              vk::ShaderGroupShaderKHR groupShader) const {
  return object_->getRayTracingShaderGroupStackSizeKHR(group, groupShader);
}

vk::ResultValueType<void>::type Pipeline::compileDeferredNV(uint32_t shader) const {
  return object_->compileDeferredNV(shader);
}

typename vk::ResultValueType<std::vector<uint8_t>>::type
  Pipeline::getShaderInfoAMD(vk::ShaderStageFlagBits shaderStage, vk::ShaderInfoTypeAMD infoType) const {
  return object_->getShaderInfoAMD(shaderStage, infoType);
}

// endregion

// region Logi Definitions

VulkanInstance Pipeline::getInstance() const {
  return VulkanInstance(object_->getInstance().shared_from_this());
}

PhysicalDevice Pipeline::getPhysicalDevice() const {
  return PhysicalDevice(object_->getPhysicalDevice().shared_from_this());
}

LogicalDevice Pipeline::getLogicalDevice() const {
  return LogicalDevice(object_->getLogicalDevice().shared_from_this());
}

const vk::DispatchLoaderDynamic& Pipeline::getDispatcher() const {
  return object_->getDispatcher();
}

void Pipeline::destroy() const {
  if (object_) {
    object_->destroy();
  }
}

Pipeline::operator const vk::Pipeline&() const {
  static vk::Pipeline nullHandle(nullptr);
  return (object_) ? object_->operator const vk::Pipeline&() : nullHandle;
}

// endregion

} // namespace logi