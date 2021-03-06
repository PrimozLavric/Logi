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

#ifndef LOGI_QUEUE_QUEUE_FAMILY_HPP
#define LOGI_QUEUE_QUEUE_FAMILY_HPP

#include "logi/base/handle.hpp"
#include "logi/queue/queue_family_impl.hpp"
#include "logi/structures/extension.hpp"

namespace logi {

class VulkanInstance;
class PhysicalDevice;
class LogicalDevice;
class Queue;
class CommandPool;

class QueueFamily : public Handle<QueueFamilyImpl> {
 public:
  using Handle::Handle;

  /**
   * @brief Reference: <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCreateCommandPool.html">vkCreateCommandPool</a>
   */
  CommandPool createCommandPool(const vk::CommandPoolCreateFlags& flags = {},
                                const ConstVkNextProxy<vk::CommandPoolCreateInfo>& next = {},
                                const std::optional<vk::AllocationCallbacks>& allocator = {}) const;

  /**
   * @brief Reference: <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkDestroyCommandPool.html">vkDestroyCommandPool</a>
   */
  void destroyCommandPool(const CommandPool& commandPool) const;

  /**
   * @brief Reference: <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkGetDeviceQueue.html">vkGetDeviceQueue</a>
   */
  Queue getQueue(uint32_t queueIndex) const;

  /**
   * @brief Reference: <a href="https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkGetDeviceQueue2.html">vkGetDeviceQueue2</a>
   */
  Queue getQueue2(uint32_t queueIndex, const vk::DeviceQueueCreateFlags& flags = {},
                  const ConstVkNextProxy<vk::DeviceQueueInfo2>& next = {}) const;

  // region Logi Declarations

  VulkanInstance getInstance() const;

  PhysicalDevice getPhysicalDevice() const;

  LogicalDevice getLogicalDevice() const;

  const vk::DispatchLoaderDynamic& getDispatcher() const;

  uint32_t queueCount() const;

  uint32_t getIndex() const;

  operator uint32_t() const;

  // endregion
};

} // namespace logi

#endif // LOGI_QUEUE_QUEUE_FAMILY_HPP