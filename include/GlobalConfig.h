/*
* Vulkan Renderer global configuration variables
*
* Copyright (C) 2017 by Primoz Lavric
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#ifndef _VKR_GLOBAL_CONFIG_H_
#define _VKR_GLOBAL_CONFIG_H_

#include <cstdint>
#include <vulkan/vulkan.hpp>
#include <vector>

namespace vkr {
namespace global_config {

	// Application meta data:
	constexpr char* kEngineName{ "Vulkan Renderer" };
	constexpr uint32_t kEngineVersion{ VK_MAKE_VERSION(0, 0, 1) };

	constexpr char* kAppName{ "Med3D" };
	constexpr uint32_t kAppVersion{ VK_MAKE_VERSION(0, 0, 1) };

}
}

#endif  // _VKR_GLOBAL_CONFIG_H_