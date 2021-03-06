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

#include "logi/memory/device_memory_impl.hpp"
#include "logi/device/logical_device_impl.hpp"

namespace logi {

DeviceMemoryImpl::DeviceMemoryImpl(LogicalDeviceImpl& logicalDevice, const vk::MemoryAllocateInfo& allocateInfo,
                                   const std::optional<vk::AllocationCallbacks>& allocator)
  : logicalDevice_(logicalDevice), allocator_(allocator) {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);
  vkDeviceMemory_ = vkDevice.allocateMemory(allocateInfo, allocator_ ? &allocator_.value() : nullptr, getDispatcher());
}

// region Vulkan Definitions

vk::DeviceSize DeviceMemoryImpl::getCommitment() const {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);
  return vkDevice.getMemoryCommitment(vkDeviceMemory_, getDispatcher());
}

vk::ResultValueType<void*>::type DeviceMemoryImpl::mapMemory(vk::DeviceSize offset, vk::DeviceSize size,
                                                             const vk::MemoryMapFlags& flags) const {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);
  return vkDevice.mapMemory(vkDeviceMemory_, offset, size, flags, getDispatcher());
}

void DeviceMemoryImpl::unmapMemory() const {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);
  vkDevice.unmapMemory(vkDeviceMemory_, getDispatcher());
}

uint64_t DeviceMemoryImpl::getOpaqueCaptureAddress(const ConstVkNextProxy<vk::DeviceMemoryOpaqueCaptureAddressInfo>& next) const {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);

  vk::DeviceMemoryOpaqueCaptureAddressInfo addressInfo(vkDeviceMemory_);
  addressInfo.pNext = next;

  return vkDevice.getMemoryOpaqueCaptureAddress(addressInfo, getDispatcher());
}

// endregion

// region Logi Definitions

VulkanInstanceImpl& DeviceMemoryImpl::getInstance() const {
  return logicalDevice_.getInstance();
}

PhysicalDeviceImpl& DeviceMemoryImpl::getPhysicalDevice() const {
  return logicalDevice_.getPhysicalDevice();
}

LogicalDeviceImpl& DeviceMemoryImpl::getLogicalDevice() const {
  return logicalDevice_;
}

const vk::DispatchLoaderDynamic& DeviceMemoryImpl::getDispatcher() const {
  return logicalDevice_.getDispatcher();
}

void DeviceMemoryImpl::destroy() const {
  logicalDevice_.freeMemory(id());
}

DeviceMemoryImpl::operator const vk::DeviceMemory&() const {
  return vkDeviceMemory_;
}

void DeviceMemoryImpl::free() {
  auto vkDevice = static_cast<vk::Device>(logicalDevice_);
  vkDevice.freeMemory(vkDeviceMemory_, allocator_ ? &allocator_.value() : nullptr, getDispatcher());
  VulkanObject::free();
}

// endregion

} // namespace logi
