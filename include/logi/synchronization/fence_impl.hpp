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

#ifndef LOGI_SYNCHRONIZATION_FENCE_IMPL_HPP
#define LOGI_SYNCHRONIZATION_FENCE_IMPL_HPP

#include "logi/base/common.hpp"
#include <optional>
#include "logi/base/vulkan_object.hpp"
#include "logi/structures/extension.hpp"

namespace logi {

class VulkanInstanceImpl;
class PhysicalDeviceImpl;
class LogicalDeviceImpl;

class FenceImpl : public VulkanObject, public std::enable_shared_from_this<FenceImpl> {
 public:
  FenceImpl(LogicalDeviceImpl& logicalDevice, const vk::FenceCreateInfo& createInfo,
            const std::optional<vk::AllocationCallbacks>& allocator = {});

  FenceImpl(LogicalDeviceImpl& logicalDevice, const vk::DeviceEventInfoEXT& eventInfo,
            const std::optional<vk::AllocationCallbacks>& allocator = {});

  FenceImpl(LogicalDeviceImpl& logicalDevice, const vk::DisplayKHR& display, const vk::DisplayEventInfoEXT& eventInfo,
            const std::optional<vk::AllocationCallbacks>& allocator = {});

  // region Vulkan Declarations

  vk::Result getStatus() const;

  vk::Result wait(const std::vector<vk::Fence>& fences, vk::Bool32 waitAll, uint64_t timeout) const;

  vk::Result wait(uint64_t timeout) const;

  vk::ResultValueType<void>::type reset(const std::vector<vk::Fence>& fences) const;

  vk::ResultValueType<void>::type reset() const;

  vk::ResultValueType<void>::type importFdKHR(const vk::FenceImportFlags& flags,
                                              vk::ExternalFenceHandleTypeFlagBits handleType, int fd,
                                              const ConstVkNextProxy<vk::ImportFenceFdInfoKHR>& next = {}) const;

#ifdef VK_USE_PLATFORM_WIN32_KHR

  vk::ResultValueType<void>::type
    importWin32HandleKHR(const vk::FenceImportFlags& flags, vk::ExternalFenceHandleTypeFlagBits handleType,
                         HANDLE handle, LPCWSTR name,
                         const ConstVkNextProxy<vk::ImportFenceWin32HandleInfoKHR>& next = {}) const;

#endif

  vk::ResultValueType<int>::type getFdKHR(vk::ExternalFenceHandleTypeFlagBits handleType,
                                          const ConstVkNextProxy<vk::FenceGetFdInfoKHR>& next = {}) const;

  // endregion

  // region Logi Declarations

  VulkanInstanceImpl& getInstance() const;

  PhysicalDeviceImpl& getPhysicalDevice() const;

  LogicalDeviceImpl& getLogicalDevice() const;

  const vk::DispatchLoaderDynamic& getDispatcher() const;

  void destroy() const;

  operator const vk::Fence&() const;

 protected:
  void free() override;

  // endregion

 private:
  LogicalDeviceImpl& logicalDevice_;
  std::optional<vk::AllocationCallbacks> allocator_;
  vk::Fence vkFence_;
};

} // namespace logi

#endif // LOGI_SYNCHRONIZATION_FENCE_IMPL_HPP
