/**
 * Project Logi source code
 * Copyright (C) 2019 Primoz Lavric
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

#ifndef LOGI_BASE_PHYSICAL_DEVICE_HPP
#define LOGI_BASE_PHYSICAL_DEVICE_HPP

#include "logi/base/handle.hpp"
#include "logi/device/logical_device.hpp"
#include "logi/device/physical_device_impl.hpp"

namespace logi {

class VulkanInstance;

class PhysicalDevice : public Handle<PhysicalDeviceImpl> {
 public:
  using Handle::Handle;

  // region Vulkan Declarations

  typename vk::ResultValueType<std::vector<vk::ExtensionProperties>>::type
    enumerateDeviceExtensionProperties(const std::string* layer = nullptr) const;

  typename vk::ResultValueType<std::vector<vk::LayerProperties>>::type enumerateDeviceLayerProperties() const;

  vk::ExternalBufferProperties
    getExternalBufferProperties(const vk::PhysicalDeviceExternalBufferInfo& external_buffer_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalBufferProperties(const vk::PhysicalDeviceExternalBufferInfo& external_buffer_info) const;

  vk::ExternalBufferPropertiesKHR
    getExternalBufferPropertiesKHR(const vk::PhysicalDeviceExternalBufferInfoKHR& external_buffer_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalBufferPropertiesKHR(const vk::PhysicalDeviceExternalBufferInfoKHR& external_buffer_info) const;

  vk::ExternalFenceProperties
    getExternalFenceProperties(const vk::PhysicalDeviceExternalFenceInfo& external_fence_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalFenceProperties(const vk::PhysicalDeviceExternalFenceInfo& external_fence_info) const;

  vk::ExternalFencePropertiesKHR
    getExternalFencePropertiesKHR(const vk::PhysicalDeviceExternalFenceInfoKHR& external_fence_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalFencePropertiesKHR(const vk::PhysicalDeviceExternalFenceInfoKHR& external_fence_info) const;

  vk::ExternalSemaphoreProperties
    getExternalSemaphoreProperties(const vk::PhysicalDeviceExternalSemaphoreInfo& external_semaphore_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalSemaphoreProperties(const vk::PhysicalDeviceExternalSemaphoreInfo& external_semaphore_info) const;

  vk::ExternalSemaphorePropertiesKHR
    getExternalSemaphorePropertiesKHR(const vk::PhysicalDeviceExternalSemaphoreInfoKHR& external_semaphore_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getExternalSemaphorePropertiesKHR(const vk::PhysicalDeviceExternalSemaphoreInfoKHR& external_semaphore_info) const;

  vk::PhysicalDeviceFeatures getFeatures() const;

  vk::PhysicalDeviceFeatures2 getFeatures2() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getFeatures2() const;

  vk::PhysicalDeviceFeatures2KHR getFeatures2KHR() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getFeatures2KHR() const;

  vk::FormatProperties getFormatProperties(vk::Format format) const;

  vk::FormatProperties2 getFormatProperties2(vk::Format format) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getFormatProperties2(vk::Format format) const;

  vk::FormatProperties2KHR getFormatProperties2KHR(vk::Format format) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getFormatProperties2KHR(vk::Format format) const;

  vk::ImageFormatProperties getImageFormatProperties(vk::Format format, vk::ImageType type, vk::ImageTiling tiling,
                                                     const vk::ImageUsageFlags& usage,
                                                     const vk::ImageCreateFlags& flags) const;

  vk::ImageFormatProperties2 getImageFormatProperties2(const vk::PhysicalDeviceImageFormatInfo2& format_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getImageFormatProperties2(const vk::PhysicalDeviceImageFormatInfo2& format_info) const;

  vk::ImageFormatProperties2KHR
    getImageFormatProperties2KHR(const vk::PhysicalDeviceImageFormatInfo2& format_info) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getImageFormatProperties2KHR(const vk::PhysicalDeviceImageFormatInfo2KHR& format_info) const;

  vk::PhysicalDeviceMemoryProperties getMemoryProperties() const;

  vk::PhysicalDeviceMemoryProperties2 getMemoryProperties2() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getMemoryProperties2() const;

  vk::PhysicalDeviceMemoryProperties2KHR getMemoryProperties2KHR() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getMemoryProperties2KHR() const;

  vk::PhysicalDeviceProperties getProperties() const;

  vk::PhysicalDeviceProperties2 getProperties2() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getProperties2() const;

  vk::PhysicalDeviceProperties2KHR getProperties2KHR() const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...> getProperties2KHR() const;

  std::vector<vk::QueueFamilyProperties> getQueueFamilyProperties() const;

  std::vector<vk::QueueFamilyProperties2> getQueueFamilyProperties2() const;

  template <typename X, typename Y, typename... Z>
  std::vector<vk::StructureChain<X, Y, Z...>> getQueueFamilyProperties2() const;

  std::vector<vk::QueueFamilyProperties2KHR> getQueueFamilyProperties2KHR() const;

  template <typename X, typename Y, typename... Z>
  std::vector<vk::StructureChain<X, Y, Z...>> getQueueFamilyProperties2KHR() const;

  std::vector<vk::SparseImageFormatProperties> getSparseImageFormatProperties(vk::Format format, vk::ImageType type,
                                                                              vk::SampleCountFlagBits samples,
                                                                              const vk::ImageUsageFlags& usage,
                                                                              vk::ImageTiling tiling) const;

  std::vector<vk::SparseImageFormatProperties2> getSparseImageFormatProperties2(
    const vk::PhysicalDeviceSparseImageFormatInfo2& sparse_image_format_properties) const;

  template <typename X, typename Y, typename... Z>
  std::vector<vk::StructureChain<X, Y, Z...>> getSparseImageFormatProperties2(
    const vk::PhysicalDeviceSparseImageFormatInfo2& sparse_image_format_properties) const;

  std::vector<vk::SparseImageFormatProperties2KHR> getSparseImageFormatProperties2KHR(
    const vk::PhysicalDeviceSparseImageFormatInfo2KHR& sparse_image_format_properties) const;

  template <typename X, typename Y, typename... Z>
  std::vector<vk::StructureChain<X, Y, Z...>> getSparseImageFormatProperties2KHR(
    const vk::PhysicalDeviceSparseImageFormatInfo2KHR& sparse_image_format_properties) const;

  vk::ResultValueType<std::vector<vk::Rect2D>>::type getPresentRectanglesKHR(vk::SurfaceKHR surface) const;

  vk::ResultValueType<vk::SurfaceCapabilitiesKHR>::type getSurfaceCapabilitiesKHR(vk::SurfaceKHR surface) const;

  template <typename X, typename Y, typename... Z>
  typename vk::ResultValueType<vk::StructureChain<X, Y, Z...>>::type
    getSurfaceCapabilities2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const;

  vk::ResultValueType<vk::SurfaceCapabilities2KHR>::type
    getSurfaceCapabilities2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const;

  vk::ResultValueType<std::vector<vk::SurfaceFormatKHR>>::type getSurfaceFormatsKHR(vk::SurfaceKHR surface) const;

  template <typename X, typename Y, typename... Z>
  typename vk::ResultValueType<vk::StructureChain<X, Y, Z...>>::type
    getSurfaceFormats2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const;

  vk::ResultValueType<std::vector<vk::SurfaceFormat2KHR>>::type
    getSurfaceFormats2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const;

  vk::ResultValueType<std::vector<vk::PresentModeKHR>>::type getSurfacePresentModesKHR(vk::SurfaceKHR surface) const;

  vk::ResultValueType<vk::Bool32>::type getSurfaceSupportKHR(uint32_t queue_index, vk::SurfaceKHR surface) const;

  vk::ExternalImageFormatPropertiesNV
    getExternalImageFormatPropertiesNV(vk::Format format, vk::ImageType type, vk::ImageTiling tiling,
                                       const vk::ImageUsageFlags& usage, const vk::ImageCreateFlags& flags,
                                       const vk::ExternalMemoryHandleTypeFlagsNV& external_handle_type) const;

  vk::DeviceGeneratedCommandsLimitsNVX
    getGeneratedCommandsPropertiesNVX(vk::DeviceGeneratedCommandsFeaturesNVX& features) const;

  template <typename X, typename Y, typename... Z>
  vk::StructureChain<X, Y, Z...>
    getGeneratedCommandsPropertiesNVX(vk::DeviceGeneratedCommandsFeaturesNVX& features) const;

  // endregion Vulkan Declarations

  // region Logi Declarations

  LogicalDevice createLogicalDevice(const vk::DeviceCreateInfo& create_info,
                                    const std::optional<vk::AllocationCallbacks>& allocator = {});

  void destroyLogicalDevice(const LogicalDevice& device);

  VulkanInstance getInstance() const;

  const vk::DispatchLoaderDynamic& getDispatcher() const;

  operator vk::PhysicalDevice() const;

  // endregion
};

// region Template Definitions

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...>
  PhysicalDevice::getExternalBufferProperties(const vk::PhysicalDeviceExternalBufferInfo& external_buffer_info) const {
  return object_->getExternalBufferProperties<X, Y, Z...>(external_buffer_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getExternalBufferPropertiesKHR(
  const vk::PhysicalDeviceExternalBufferInfoKHR& external_buffer_info) const {
  return object_->getExternalBufferPropertiesKHR<X, Y, Z...>(external_buffer_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...>
  PhysicalDevice::getExternalFenceProperties(const vk::PhysicalDeviceExternalFenceInfo& external_fence_info) const {
  return object_->getExternalFenceProperties<X, Y, Z...>(external_fence_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getExternalFencePropertiesKHR(
  const vk::PhysicalDeviceExternalFenceInfoKHR& external_fence_info) const {
  return object_->getExternalFencePropertiesKHR<X, Y, Z...>(external_fence_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getExternalSemaphoreProperties(
  const vk::PhysicalDeviceExternalSemaphoreInfo& external_semaphore_info) const {
  return object_->getExternalSemaphoreProperties<X, Y, Z...>(external_semaphore_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getExternalSemaphorePropertiesKHR(
  const vk::PhysicalDeviceExternalSemaphoreInfoKHR& external_semaphore_info) const {
  return object_->getExternalSemaphorePropertiesKHR<X, Y, Z...>(external_semaphore_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getFeatures2() const {
  return object_->getFeatures2<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getFeatures2KHR() const {
  return object_->getFeatures2KHR<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getFormatProperties2(vk::Format format) const {
  return object_->getFormatProperties2<X, Y, Z...>(format);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getFormatProperties2KHR(vk::Format format) const {
  return object_->getFormatProperties2KHR<X, Y, Z...>(format);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...>
  PhysicalDevice::getImageFormatProperties2(const vk::PhysicalDeviceImageFormatInfo2& format_info) const {
  return object_->getImageFormatProperties2<X, Y, Z...>(format_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...>
  PhysicalDevice::getImageFormatProperties2KHR(const vk::PhysicalDeviceImageFormatInfo2KHR& format_info) const {
  return object_->getImageFormatProperties2KHR<X, Y, Z...>(format_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getMemoryProperties2() const {
  return object_->getMemoryProperties2<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getMemoryProperties2KHR() const {
  return object_->getMemoryProperties2KHR<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getProperties2() const {
  return object_->getProperties2<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...> PhysicalDevice::getProperties2KHR() const {
  return object_->getProperties2KHR<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
std::vector<vk::StructureChain<X, Y, Z...>> PhysicalDevice::getQueueFamilyProperties2() const {
  return object_->getQueueFamilyProperties2<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
std::vector<vk::StructureChain<X, Y, Z...>> PhysicalDevice::getQueueFamilyProperties2KHR() const {
  return object_->getQueueFamilyProperties2KHR<X, Y, Z...>();
}

template <typename X, typename Y, typename... Z>
std::vector<vk::StructureChain<X, Y, Z...>> PhysicalDevice::getSparseImageFormatProperties2(
  const vk::PhysicalDeviceSparseImageFormatInfo2& sparse_image_format_properties) const {
  return object_->getSparseImageFormatProperties2<X, Y, Z...>(sparse_image_format_properties);
}

template <typename X, typename Y, typename... Z>
std::vector<vk::StructureChain<X, Y, Z...>> PhysicalDevice::getSparseImageFormatProperties2KHR(
  const vk::PhysicalDeviceSparseImageFormatInfo2KHR& sparse_image_format_properties) const {
  return object_->getSparseImageFormatProperties2KHR<X, Y, Z...>(sparse_image_format_properties);
}

template <typename X, typename Y, typename... Z>
typename vk::ResultValueType<vk::StructureChain<X, Y, Z...>>::type
  PhysicalDevice::getSurfaceCapabilities2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const {
  return object_->getSurfaceCapabilities2KHR(surface_info);
}

template <typename X, typename Y, typename... Z>
typename vk::ResultValueType<vk::StructureChain<X, Y, Z...>>::type
  PhysicalDevice::getSurfaceFormats2KHR(const vk::PhysicalDeviceSurfaceInfo2KHR& surface_info) const {
  return object_->getSurfaceFormats2KHR(surface_info);
}

template <typename X, typename Y, typename... Z>
vk::StructureChain<X, Y, Z...>
  PhysicalDevice::getGeneratedCommandsPropertiesNVX(vk::DeviceGeneratedCommandsFeaturesNVX& features) const {
  return object_->getGeneratedCommandsPropertiesNVX<X, Y, Z...>(features);
}

// endregion

} // namespace logi

#endif // LOGI_BASE_PHYSICAL_DEVICE_HPP