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

#ifndef LOGI_MEMORY_VMA_IMAGE_HPP
#define LOGI_MEMORY_VMA_IMAGE_HPP

#include "logi/base/common.hpp"
#include "logi/base/handle.hpp"
#include "logi/memory/image.hpp"

namespace logi {

class VMAImageImpl;
class MemoryAllocator;

/**
 * @brief VMA allocation of an image 
 * @see <a href="https://gpuopen-librariesandsdks.github.io/VulkanMemoryAllocator/html/index.html">VMA(Vulkan Memory Allocator)</a> 
 */
class VMAImage : public Image {
 public:
  explicit VMAImage() = default;

  explicit VMAImage(const std::shared_ptr<VMAImageImpl>& vmaImageImpl);

  explicit VMAImage(const Image& image);

  void* mapMemory() const;

  void unmapMemory() const;

  size_t size() const;

  void writeToImage(const void* data, size_t size, size_t offset = 0) const;

  bool isMappable() const;

  MemoryAllocator getMemoryAllocator() const;
};

} // namespace logi

#endif // LOGI_MEMORY_VMA_IMAGE_HPP
