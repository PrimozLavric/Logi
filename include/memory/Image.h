#ifndef MEMORY_IMAGE_H
#define MEMORY_IMAGE_H

#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>
#include <list>
#include "base/ManagedResource.h"
#include "memory/MemoryUsage.h"
#include "memory/ImageView.h"

namespace vkr {

struct ImageConfiguration {
	vk::ImageCreateFlags create_flags;
	vk::ImageType type;
	vk::Format format;
	vk::Extent3D extent;
	uint32_t mip_levels;
	uint32_t array_layers;
	vk::SampleCountFlagBits samples;
	vk::ImageTiling tiling;
	vk::ImageLayout initial_layout;
	MemoryUsage memory_usage;
	bool concurrent;
	std::vector<uint32_t> concurrent_queue_families;

	ImageConfiguration(vk::ImageCreateFlags create_flags = vk::ImageCreateFlags(), vk::ImageType type = vk::ImageType::e1D, vk::Format format = vk::Format::eUndefined, vk::Extent3D extent = vk::Extent3D(), uint32_t mip_levels = 0, uint32_t array_layers = 0,
									vk::SampleCountFlagBits samples = vk::SampleCountFlagBits::e1, vk::ImageTiling tiling = vk::ImageTiling::eOptimal, MemoryUsage memory_usage = MemoryUsage::GPU_ONLY, bool concurrent = false, std::vector<uint32_t> concurrent_queue_families = {});
};


class Image {
public:
	Image(const vk::Device& device, VmaAllocator allocator, const VmaAllocation& allocation, const vk::Image& image, const ImageConfiguration& configuration);

	/**
	 * @brief Create image view for this Image.
	 *
	 * @param component_mapping Specifies a remapping of color components.
	 * @param aspect_mask Specifies which aspect(s) of the image are included in the view.
	 * @param base_mip_level First mipmap level accessible to the view.
	 * @param mip_level_count Number of mipmap levels (starting from base_mip_level) accessible to the view.
	 * @param base_array_layer First array layer accessible to the view.
	 * @param layer_count Number of array layers (starting from base_array_layer) accessible to the view.
	 */
	ImageView createImageView(vk::Format format, const vk::ComponentMapping& component_mapping, const vk::ImageAspectFlags& aspect_mask, uint32_t base_mip_level, uint32_t mip_level_count, uint32_t base_array_layer, uint32_t layer_count);

	const vk::Image& getVkImage();

	const VmaAllocation& getAllocation() const;

	void destroy();

	~Image();
private:
	vk::Device device_;	///< Vulkan logical device handle.
	vk::Image image_;		///< Vulkan image handle.
	VmaAllocator allocator_;
	VmaAllocation allocation_;

	ImageConfiguration configuration_;	///< Vulkan image configuration.
	std::list<std::shared_ptr<ManagedVkImageView>> image_views_; ///< Allocated buffer views..
};

}

#endif // !MEMORY_BUFFER_H
