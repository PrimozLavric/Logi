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

#ifndef LOGI_STRUCTURES_VK_STRUCTURE_HPP
#define LOGI_STRUCTURES_VK_STRUCTURE_HPP

#include <vulkan/vulkan.hpp>
#include "logi/base/exception.hpp"
#include "logi/structures/structure.hpp"

namespace logi {

class BindBufferMemoryDeviceGroupInfo : public Structure<vk::BindBufferMemoryDeviceGroupInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(deviceIndices, pDeviceIndices, deviceIndexCount);
  }

  std::vector<uint32_t> deviceIndices;
};

class BindBufferMemoryInfo : public Structure<vk::BindBufferMemoryInfo> {
 public:
  using VkType::buffer;
  using VkType::memory;
  using VkType::memoryOffset;
};

using BindBufferMemoryInfoChain = StructureChain<BindBufferMemoryInfo, BindBufferMemoryDeviceGroupInfo>;

class BindImagePlaneMemoryInfo : public Structure<vk::BindImagePlaneMemoryInfo> {
 public:
  using VkType::planeAspect;
};

class BindImageMemorySwapchainInfoKHR : public Structure<vk::BindImageMemorySwapchainInfoKHR> {
 public:
  using VkType::imageIndex;
  using VkType::swapchain;
};

class BindImageMemoryDeviceGroupInfo : public Structure<vk::BindImageMemoryDeviceGroupInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(deviceIndices, pDeviceIndices, deviceIndexCount);
    vecToCArr(splitInstanceBindRegions, pSplitInstanceBindRegions, splitInstanceBindRegionCount);
  }

  std::vector<uint32_t> deviceIndices;
  std::vector<vk::Rect2D> splitInstanceBindRegions;
};

class BindImageMemoryInfo : public Structure<vk::BindImageMemoryInfo> {
 public:
  using VkType::image;
  using VkType::memory;
  using VkType::memoryOffset;
};

using BindImageMemoryInfoChain = StructureChain<BindImageMemoryInfo, BindImageMemoryDeviceGroupInfo,
                                                BindImageMemorySwapchainInfoKHR, BindImagePlaneMemoryInfo>;

class DeviceGroupBindSparseInfo : public Structure<vk::DeviceGroupBindSparseInfo> {
 public:
  using VkType::memoryDeviceIndex;
  using VkType::resourceDeviceIndex;
};

class SparseBufferMemoryBindInfo : public Structure<vk::SparseBufferMemoryBindInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(binds, pBinds, bindCount);
  }

  using VkType::buffer;
  std::vector<vk::SparseMemoryBind> binds;
};

class SparseImageOpaqueMemoryBindInfo : public Structure<vk::SparseImageOpaqueMemoryBindInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(binds, pBinds, bindCount);
  }

  using VkType::image;
  std::vector<vk::SparseMemoryBind> binds;
};

class SparseImageMemoryBindInfo : public Structure<vk::SparseImageMemoryBindInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(binds, pBinds, bindCount);
  }

  using VkType::image;
  std::vector<vk::SparseImageMemoryBind> binds;
};

class BindSparseInfo : public Structure<vk::BindSparseInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(waitSemaphores, pWaitSemaphores, waitSemaphoreCount);
    vecLogiToVk(bufferBinds, vkBufferBinds);
    vecToCArr(vkBufferBinds, pBufferBinds, bufferBindCount);
    vecLogiToVk(imageOpaqueBinds, vkImageOpaqueBinds);
    vecToCArr(vkImageOpaqueBinds, pImageOpaqueBinds, imageOpaqueBindCount);
    vecLogiToVk(imageBinds, vkImageBinds);
    vecToCArr(vkImageBinds, pImageBinds, imageBindCount);
    vecToCArr(signalSemaphores, pSignalSemaphores, signalSemaphoreCount);
  }

  std::vector<vk::Semaphore> waitSemaphores;
  std::vector<SparseBufferMemoryBindInfo> bufferBinds;
  std::vector<SparseImageOpaqueMemoryBindInfo> imageOpaqueBinds;
  std::vector<SparseImageMemoryBindInfo> imageBinds;
  std::vector<vk::Semaphore> signalSemaphores;

 private:
  std::vector<vk::SparseBufferMemoryBindInfo> vkBufferBinds;
  std::vector<vk::SparseImageOpaqueMemoryBindInfo> vkImageOpaqueBinds;
  std::vector<vk::SparseImageMemoryBindInfo> vkImageBinds;
};

using BindSparseInfoChain = StructureChain<BindSparseInfo, SparseImageMemoryBindInfo, SparseImageOpaqueMemoryBindInfo,
                                           SparseBufferMemoryBindInfo, DeviceGroupBindSparseInfo>;

class ExternalMemoryBufferCreateInfo : public Structure<vk::ExternalMemoryBufferCreateInfo> {
 public:
  using VkType::handleTypes;
};

class DedicatedAllocationBufferCreateInfoNV : public Structure<vk::DedicatedAllocationBufferCreateInfoNV> {
 public:
  using VkType::dedicatedAllocation;
};

class BufferDeviceAddressCreateInfoEXT : public Structure<vk::BufferDeviceAddressCreateInfoEXT> {
 public:
  using VkType::deviceAddress;
};

class BufferCreateInfo : public Structure<vk::BufferCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(queueFamilyIndices, pQueueFamilyIndices, queueFamilyIndexCount);
  }

  using VkType::flags;
  using VkType::sharingMode;
  using VkType::size;
  using VkType::usage;
  std::vector<uint32_t> queueFamilyIndices;
};

using BufferCreateInfoChain = StructureChain<BufferCreateInfo, BufferDeviceAddressCreateInfoEXT,
                                             DedicatedAllocationBufferCreateInfoNV, ExternalMemoryBufferCreateInfo>;

class CommandBufferInheritanceConditionalRenderingInfoEXT
  : public Structure<vk::CommandBufferInheritanceConditionalRenderingInfoEXT> {
 public:
  using VkType::conditionalRenderingEnable;
};

class CommandBufferInheritanceInfo : public Structure<vk::CommandBufferInheritanceInfo> {
 public:
  using VkType::framebuffer;
  using VkType::occlusionQueryEnable;
  using VkType::pipelineStatistics;
  using VkType::queryFlags;
  using VkType::renderPass;
  using VkType::subpass;
};

using CommandBufferInheritanceInfoChain =
  StructureChain<CommandBufferInheritanceInfo, CommandBufferInheritanceConditionalRenderingInfoEXT>;

class DescriptorPoolInlineUniformBlockCreateInfoEXT
  : public Structure<vk::DescriptorPoolInlineUniformBlockCreateInfoEXT> {
 public:
  using VkType::maxInlineUniformBlockBindings;
};

class DescriptorPoolCreateInfo : public Structure<vk::DescriptorPoolCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(poolSizes, pPoolSizes, poolSizeCount);
  }

  using VkType::flags;
  using VkType::maxSets;
  std::vector<vk::DescriptorPoolSize> poolSizes;
};

using DescriptorPoolCreateInfoChain =
  StructureChain<DescriptorPoolCreateInfo, DescriptorPoolInlineUniformBlockCreateInfoEXT>;

class DescriptorSetVariableDescriptorCountAllocateInfoEXT
  : public Structure<vk::DescriptorSetVariableDescriptorCountAllocateInfoEXT> {
 public:
  void updateVkStructure() override {
    vecToCArr(descriptorCounts, pDescriptorCounts, descriptorSetCount);
  }

  std::vector<uint32_t> descriptorCounts;
};

class DescriptorSetAllocateInfo : public Structure<vk::DescriptorSetAllocateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(setLayouts, pSetLayouts, descriptorSetCount);
  }

  using VkType::descriptorPool;
  std::vector<vk::DescriptorSetLayout> setLayouts;
};

using DescriptorSetAllocateInfoChain =
  StructureChain<DescriptorSetAllocateInfo, DescriptorSetVariableDescriptorCountAllocateInfoEXT>;

class DescriptorSetVariableDescriptorCountLayoutSupportEXT
  : public Structure<vk::DescriptorSetVariableDescriptorCountLayoutSupportEXT> {
 public:
  using VkType::maxVariableDescriptorCount;
};

class DescriptorSetLayoutSupport : public Structure<vk::DescriptorSetLayoutSupport> {
 public:
  using VkType::supported;
};

using DescriptorSetLayoutSupportChain =
  StructureChain<DescriptorSetLayoutSupport, DescriptorSetVariableDescriptorCountLayoutSupportEXT>;

class PhysicalDeviceVulkanMemoryModelFeaturesKHR : public Structure<vk::PhysicalDeviceVulkanMemoryModelFeaturesKHR> {
 public:
  using VkType::vulkanMemoryModel;
  using VkType::vulkanMemoryModelAvailabilityVisibilityChains;
  using VkType::vulkanMemoryModelDeviceScope;
};

class PhysicalDeviceVertexAttributeDivisorFeaturesEXT
  : public Structure<vk::PhysicalDeviceVertexAttributeDivisorFeaturesEXT> {
 public:
  using VkType::vertexAttributeInstanceRateDivisor;
  using VkType::vertexAttributeInstanceRateZeroDivisor;
};

class PhysicalDeviceVariablePointerFeatures : public Structure<vk::PhysicalDeviceVariablePointerFeatures> {
 public:
  using VkType::variablePointers;
  using VkType::variablePointersStorageBuffer;
};

class PhysicalDeviceTransformFeedbackFeaturesEXT : public Structure<vk::PhysicalDeviceTransformFeedbackFeaturesEXT> {
 public:
  using VkType::geometryStreams;
  using VkType::transformFeedback;
};

class PhysicalDeviceShadingRateImageFeaturesNV : public Structure<vk::PhysicalDeviceShadingRateImageFeaturesNV> {
 public:
  using VkType::shadingRateCoarseSampleOrder;
  using VkType::shadingRateImage;
};

class PhysicalDeviceShaderImageFootprintFeaturesNV
  : public Structure<vk::PhysicalDeviceShaderImageFootprintFeaturesNV> {
 public:
  using VkType::imageFootprint;
};

class PhysicalDeviceShaderDrawParameterFeatures : public Structure<vk::PhysicalDeviceShaderDrawParameterFeatures> {
 public:
  using VkType::shaderDrawParameters;
};

class PhysicalDeviceShaderAtomicInt64FeaturesKHR : public Structure<vk::PhysicalDeviceShaderAtomicInt64FeaturesKHR> {
 public:
  using VkType::shaderBufferInt64Atomics;
  using VkType::shaderSharedInt64Atomics;
};

class PhysicalDeviceScalarBlockLayoutFeaturesEXT : public Structure<vk::PhysicalDeviceScalarBlockLayoutFeaturesEXT> {
 public:
  using VkType::scalarBlockLayout;
};

class PhysicalDeviceSamplerYcbcrConversionFeatures
  : public Structure<vk::PhysicalDeviceSamplerYcbcrConversionFeatures> {
 public:
  using VkType::samplerYcbcrConversion;
};

class PhysicalDeviceRepresentativeFragmentTestFeaturesNV
  : public Structure<vk::PhysicalDeviceRepresentativeFragmentTestFeaturesNV> {
 public:
  using VkType::representativeFragmentTest;
};

class PhysicalDeviceProtectedMemoryFeatures : public Structure<vk::PhysicalDeviceProtectedMemoryFeatures> {
 public:
  using VkType::protectedMemory;
};

class PhysicalDeviceMultiviewFeatures : public Structure<vk::PhysicalDeviceMultiviewFeatures> {
 public:
  using VkType::multiview;
  using VkType::multiviewGeometryShader;
  using VkType::multiviewTessellationShader;
};

class PhysicalDeviceMeshShaderFeaturesNV : public Structure<vk::PhysicalDeviceMeshShaderFeaturesNV> {
 public:
  using VkType::meshShader;
  using VkType::taskShader;
};

class PhysicalDeviceMemoryPriorityFeaturesEXT : public Structure<vk::PhysicalDeviceMemoryPriorityFeaturesEXT> {
 public:
  using VkType::memoryPriority;
};

class PhysicalDeviceInlineUniformBlockFeaturesEXT : public Structure<vk::PhysicalDeviceInlineUniformBlockFeaturesEXT> {
 public:
  using VkType::descriptorBindingInlineUniformBlockUpdateAfterBind;
  using VkType::inlineUniformBlock;
};

class PhysicalDeviceFragmentShaderBarycentricFeaturesNV
  : public Structure<vk::PhysicalDeviceFragmentShaderBarycentricFeaturesNV> {
 public:
  using VkType::fragmentShaderBarycentric;
};

class PhysicalDeviceFragmentDensityMapFeaturesEXT : public Structure<vk::PhysicalDeviceFragmentDensityMapFeaturesEXT> {
 public:
  using VkType::fragmentDensityMap;
  using VkType::fragmentDensityMapDynamic;
  using VkType::fragmentDensityMapNonSubsampledImages;
};

class PhysicalDeviceFloat16Int8FeaturesKHR : public Structure<vk::PhysicalDeviceFloat16Int8FeaturesKHR> {
 public:
  using VkType::shaderFloat16;
  using VkType::shaderInt8;
};

class PhysicalDeviceExclusiveScissorFeaturesNV : public Structure<vk::PhysicalDeviceExclusiveScissorFeaturesNV> {
 public:
  using VkType::exclusiveScissor;
};

class PhysicalDeviceDescriptorIndexingFeaturesEXT : public Structure<vk::PhysicalDeviceDescriptorIndexingFeaturesEXT> {
 public:
  using VkType::descriptorBindingPartiallyBound;
  using VkType::descriptorBindingSampledImageUpdateAfterBind;
  using VkType::descriptorBindingStorageBufferUpdateAfterBind;
  using VkType::descriptorBindingStorageImageUpdateAfterBind;
  using VkType::descriptorBindingStorageTexelBufferUpdateAfterBind;
  using VkType::descriptorBindingUniformBufferUpdateAfterBind;
  using VkType::descriptorBindingUniformTexelBufferUpdateAfterBind;
  using VkType::descriptorBindingUpdateUnusedWhilePending;
  using VkType::descriptorBindingVariableDescriptorCount;
  using VkType::runtimeDescriptorArray;
  using VkType::shaderInputAttachmentArrayDynamicIndexing;
  using VkType::shaderInputAttachmentArrayNonUniformIndexing;
  using VkType::shaderSampledImageArrayNonUniformIndexing;
  using VkType::shaderStorageBufferArrayNonUniformIndexing;
  using VkType::shaderStorageImageArrayNonUniformIndexing;
  using VkType::shaderStorageTexelBufferArrayDynamicIndexing;
  using VkType::shaderStorageTexelBufferArrayNonUniformIndexing;
  using VkType::shaderUniformBufferArrayNonUniformIndexing;
  using VkType::shaderUniformTexelBufferArrayDynamicIndexing;
  using VkType::shaderUniformTexelBufferArrayNonUniformIndexing;
};

class PhysicalDeviceDepthClipEnableFeaturesEXT : public Structure<vk::PhysicalDeviceDepthClipEnableFeaturesEXT> {
 public:
  using VkType::depthClipEnable;
};

class PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV
  : public Structure<vk::PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV> {
 public:
  using VkType::dedicatedAllocationImageAliasing;
};

class PhysicalDeviceCornerSampledImageFeaturesNV : public Structure<vk::PhysicalDeviceCornerSampledImageFeaturesNV> {
 public:
  using VkType::cornerSampledImage;
};

class PhysicalDeviceCooperativeMatrixFeaturesNV : public Structure<vk::PhysicalDeviceCooperativeMatrixFeaturesNV> {
 public:
  using VkType::cooperativeMatrix;
  using VkType::cooperativeMatrixRobustBufferAccess;
};

class PhysicalDeviceConditionalRenderingFeaturesEXT
  : public Structure<vk::PhysicalDeviceConditionalRenderingFeaturesEXT> {
 public:
  using VkType::conditionalRendering;
  using VkType::inheritedConditionalRendering;
};

class PhysicalDeviceComputeShaderDerivativesFeaturesNV
  : public Structure<vk::PhysicalDeviceComputeShaderDerivativesFeaturesNV> {
 public:
  using VkType::computeDerivativeGroupLinear;
  using VkType::computeDerivativeGroupQuads;
};

class PhysicalDeviceBufferAddressFeaturesEXT : public Structure<vk::PhysicalDeviceBufferAddressFeaturesEXT> {
 public:
  using VkType::bufferDeviceAddress;
  using VkType::bufferDeviceAddressCaptureReplay;
  using VkType::bufferDeviceAddressMultiDevice;
};

class PhysicalDeviceBlendOperationAdvancedFeaturesEXT
  : public Structure<vk::PhysicalDeviceBlendOperationAdvancedFeaturesEXT> {
 public:
  using VkType::advancedBlendCoherentOperations;
};

class PhysicalDeviceASTCDecodeFeaturesEXT : public Structure<vk::PhysicalDeviceASTCDecodeFeaturesEXT> {
 public:
  using VkType::decodeModeSharedExponent;
};

class PhysicalDevice8BitStorageFeaturesKHR : public Structure<vk::PhysicalDevice8BitStorageFeaturesKHR> {
 public:
  using VkType::storageBuffer8BitAccess;
  using VkType::storagePushConstant8;
  using VkType::uniformAndStorageBuffer8BitAccess;
};

class PhysicalDevice16BitStorageFeatures : public Structure<vk::PhysicalDevice16BitStorageFeatures> {
 public:
  using VkType::storageBuffer16BitAccess;
  using VkType::storageInputOutput16;
  using VkType::storagePushConstant16;
  using VkType::uniformAndStorageBuffer16BitAccess;
};

class PhysicalDeviceFeatures2 : public Structure<vk::PhysicalDeviceFeatures2> {
 public:
  using VkType::features;
};

using PhysicalDeviceFeatures2Chain =
  StructureChain<PhysicalDeviceFeatures2, PhysicalDevice16BitStorageFeatures, PhysicalDevice8BitStorageFeaturesKHR,
                 PhysicalDeviceASTCDecodeFeaturesEXT, PhysicalDeviceBlendOperationAdvancedFeaturesEXT,
                 PhysicalDeviceBufferAddressFeaturesEXT, PhysicalDeviceComputeShaderDerivativesFeaturesNV,
                 PhysicalDeviceConditionalRenderingFeaturesEXT, PhysicalDeviceCooperativeMatrixFeaturesNV,
                 PhysicalDeviceCornerSampledImageFeaturesNV, PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV,
                 PhysicalDeviceDepthClipEnableFeaturesEXT, PhysicalDeviceDescriptorIndexingFeaturesEXT,
                 PhysicalDeviceExclusiveScissorFeaturesNV, PhysicalDeviceFloat16Int8FeaturesKHR,
                 PhysicalDeviceFragmentDensityMapFeaturesEXT, PhysicalDeviceFragmentShaderBarycentricFeaturesNV,
                 PhysicalDeviceInlineUniformBlockFeaturesEXT, PhysicalDeviceMemoryPriorityFeaturesEXT,
                 PhysicalDeviceMeshShaderFeaturesNV, PhysicalDeviceMultiviewFeatures,
                 PhysicalDeviceProtectedMemoryFeatures, PhysicalDeviceRepresentativeFragmentTestFeaturesNV,
                 PhysicalDeviceSamplerYcbcrConversionFeatures, PhysicalDeviceScalarBlockLayoutFeaturesEXT,
                 PhysicalDeviceShaderAtomicInt64FeaturesKHR, PhysicalDeviceShaderDrawParameterFeatures,
                 PhysicalDeviceShaderImageFootprintFeaturesNV, PhysicalDeviceShadingRateImageFeaturesNV,
                 PhysicalDeviceTransformFeedbackFeaturesEXT, PhysicalDeviceVariablePointerFeatures,
                 PhysicalDeviceVertexAttributeDivisorFeaturesEXT, PhysicalDeviceVulkanMemoryModelFeaturesKHR>;

class DeviceMemoryOverallocationCreateInfoAMD : public Structure<vk::DeviceMemoryOverallocationCreateInfoAMD> {
 public:
  using VkType::overallocationBehavior;
};

class DeviceGroupDeviceCreateInfo : public Structure<vk::DeviceGroupDeviceCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(physicalDevices, pPhysicalDevices, physicalDeviceCount);
  }

  uint32_t physicalDeviceCount;
  std::vector<vk::PhysicalDevice> physicalDevices;
};

class DescriptorSetLayoutBinding : public SimpleStructure<vk::DescriptorSetLayoutBinding> {
 public:
  vk::DescriptorSetLayoutBinding build() const override {
    return vk::DescriptorSetLayoutBinding(binding, descriptorType, descriptorCount, stageFlags,
                                          immutableSamplers.data());
  }

  uint32_t binding;
  vk::DescriptorType descriptorType;
  uint32_t descriptorCount;
  vk::ShaderStageFlags stageFlags;
  std::vector<vk::Sampler> immutableSamplers;
};

class DescriptorSetLayoutBindingFlagsCreateInfoEXT
  : public Structure<vk::DescriptorSetLayoutBindingFlagsCreateInfoEXT> {
 public:
  void updateVkStructure() override {
    vecToCArr(bindingFlags, pBindingFlags, bindingCount);
  }

  std::vector<vk::DescriptorBindingFlagsEXT> bindingFlags;
};

class DescriptorSetLayoutCreateInfo : public Structure<vk::DescriptorSetLayoutCreateInfo> {
 public:
  void updateVkStructure() override {
    vk_bindings_.clear();
    vk_bindings_.reserve(bindings.size());
    for (const auto& binding : bindings) {
      vk_bindings_.emplace_back(binding.build());
    }
    vecToCArr(vk_bindings_, pBindings, bindingCount);
  }

  using VkType::flags;
  std::vector<DescriptorSetLayoutBinding> bindings;

 private:
  std::vector<vk::DescriptorSetLayoutBinding> vk_bindings_;
};

using DescriptorSetLayoutCreateInfoChain =
  StructureChain<DescriptorSetLayoutCreateInfo, DescriptorSetLayoutBindingFlagsCreateInfoEXT>;

class PipelineLayoutCreateInfo : public Structure<vk::PipelineLayoutCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(setLayouts, pSetLayouts, setLayoutCount);
    vecToCArr(pushConstantRanges, pPushConstantRanges, pushConstantRangeCount);
  }

  using VkType::flags;
  std::vector<vk::DescriptorSetLayout> setLayouts;
  std::vector<vk::PushConstantRange> pushConstantRanges;
};

using PipelineLayoutCreateInfoChain = StructureChain<PipelineLayoutCreateInfo>;

class SpecializationInfo : public Structure<vk::SpecializationInfo> {
  void updateVkStructure() override {
    vecToCArr(mapEntries, pMapEntries, mapEntryCount);
    dataSize = data.size();
    pData = data.empty() ? nullptr : data.data();
  }

  std::vector<vk::SpecializationMapEntry> mapEntries;
  std::vector<std::byte> data;
};

class PipelineShaderStageCreateInfo : public Structure<vk::PipelineShaderStageCreateInfo> {
 public:
  void updateVkStructure() override {
    pName = name.data();
    pSpecializationInfo = &specializationInfo.build();
  }

  using VkType::flags;
  using VkType::module;
  using VkType::stage;
  std::string name = "main";
  SpecializationInfo specializationInfo;
};

using PipelineShaderStageCreateInfoChain = StructureChain<PipelineShaderStageCreateInfo>;

class ComputePipelineCreateInfo : public Structure<vk::ComputePipelineCreateInfo> {
 public:
  void updateVkStructure() override {
    VkType::stage = stage.build();
  }

  using VkType::basePipelineHandle;
  using VkType::basePipelineIndex;
  using VkType::flags;
  using VkType::layout;
  PipelineShaderStageCreateInfo stage;
};

using ComputePipelineCreateInfoChain = StructureChain<ComputePipelineCreateInfo>;

class PipelineRepresentativeFragmentTestStateCreateInfoNV
  : public Structure<vk::PipelineRepresentativeFragmentTestStateCreateInfoNV> {
 public:
  using VkType::representativeFragmentTestEnable;
};

class PipelineDiscardRectangleStateCreateInfoEXT : public Structure<vk::PipelineDiscardRectangleStateCreateInfoEXT> {
 public:
  void updateVkStructure() override {
    vecToCArr(discardRectangles, pDiscardRectangles, discardRectangleCount);
  }

  using VkType::discardRectangleMode;
  using VkType::flags;
  std::vector<vk::Rect2D> discardRectangles;
};

class PipelineVertexInputDivisorStateCreateInfoEXT
  : public Structure<vk::PipelineVertexInputDivisorStateCreateInfoEXT> {
 public:
  void updateVkStructure() override {
    vecToCArr(vertexBindingDivisors, pVertexBindingDivisors, vertexBindingDivisorCount);
  }

  std::vector<vk::VertexInputBindingDivisorDescriptionEXT> vertexBindingDivisors;
};

class PipelineVertexInputStateCreateInfo : public Structure<vk::PipelineVertexInputStateCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(vertexBindingDescription, pVertexBindingDescriptions, vertexBindingDescriptionCount);
    vecToCArr(vertexAttributeDescriptions, pVertexAttributeDescriptions, vertexAttributeDescriptionCount);
  }

  using VkType::flags;

  std::vector<vk::VertexInputBindingDescription> vertexBindingDescription;
  std::vector<vk::VertexInputAttributeDescription> vertexAttributeDescriptions;
};

using PipelineVertexInputStateCreateInfoChain =
  StructureChain<PipelineVertexInputStateCreateInfo, PipelineVertexInputDivisorStateCreateInfoEXT>;

class PipelineInputAssemblyStateCreateInfo : public Structure<vk::PipelineInputAssemblyStateCreateInfo> {
 public:
  using VkType::flags;
  using VkType::primitiveRestartEnable;
  using VkType::topology;
};

using PipelineInputAssemblyStateCreateInfoChain = StructureChain<PipelineInputAssemblyStateCreateInfo>;

class PipelineTessellationDomainOriginStateCreateInfo
  : public Structure<vk::PipelineTessellationDomainOriginStateCreateInfo> {
 public:
  using VkType::domainOrigin;
};

class PipelineTessellationStateCreateInfo : public Structure<vk::PipelineTessellationStateCreateInfo> {
 public:
  using VkType::flags;
  using VkType::patchControlPoints;
};

using PipelineTessellationStateCreateInfoChain =
  StructureChain<PipelineTessellationStateCreateInfo, PipelineTessellationDomainOriginStateCreateInfo>;

class PipelineViewportCoarseSampleOrderStateCreateInfoNV
  : public Structure<vk::PipelineViewportCoarseSampleOrderStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    vecToCArr(customSampleOrders, pCustomSampleOrders, customSampleOrderCount);
  }

  using VkType::sampleOrderType;
  std::vector<vk::CoarseSampleOrderCustomNV> customSampleOrders;
};

class PipelineViewportExclusiveScissorStateCreateInfoNV
  : public Structure<vk::PipelineViewportExclusiveScissorStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    vecToCArr(exclusiveScissors, pExclusiveScissors, exclusiveScissorCount);
  }

  std::vector<vk::Rect2D> exclusiveScissors;
};

class PipelineViewportShadingRateImageStateCreateInfoNV
  : public Structure<vk::PipelineViewportShadingRateImageStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    pShadingRatePalettes = shadingRatePalettes.empty() ? nullptr : shadingRatePalettes.data();
  }

  using VkType::shadingRateImageEnable;
  using VkType::viewportCount;
  std::vector<vk::ShadingRatePaletteNV> shadingRatePalettes;
};

class PipelineViewportSwizzleStateCreateInfoNV : public Structure<vk::PipelineViewportSwizzleStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    vecToCArr(viewportSwizzles, pViewportSwizzles, viewportCount);
  }

  using VkType::flags;
  std::vector<vk::ViewportSwizzleNV> viewportSwizzles;
};

class PipelineViewportWScalingStateCreateInfoNV : public Structure<vk::PipelineViewportWScalingStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    pViewportWScalings = viewportWScalings.empty() ? nullptr : viewportWScalings.data();
  }

  using VkType::viewportCount;
  using VkType::viewportWScalingEnable;
  std::vector<vk::ViewportWScalingNV> viewportWScalings;
};

class PipelineViewportStateCreateInfo : public Structure<vk::PipelineViewportStateCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(viewports, pViewports, viewportCount);
    vecToCArr(scissors, pScissors, scissorCount);
  }

  using VkType::flags;
  std::vector<vk::Viewport> viewports;
  std::vector<vk::Rect2D> scissors;
};

using PipelineViewportStateCreateInfoChain =
  StructureChain<PipelineViewportStateCreateInfo, PipelineViewportWScalingStateCreateInfoNV,
                 PipelineViewportSwizzleStateCreateInfoNV, PipelineViewportShadingRateImageStateCreateInfoNV,
                 PipelineViewportExclusiveScissorStateCreateInfoNV, PipelineViewportCoarseSampleOrderStateCreateInfoNV>;

class PipelineRasterizationStateStreamCreateInfoEXT
  : public Structure<vk::PipelineRasterizationStateStreamCreateInfoEXT> {
 public:
  using VkType::flags;
  using VkType::rasterizationStream;
};

class PipelineRasterizationStateRasterizationOrderAMD
  : public Structure<vk::PipelineRasterizationStateRasterizationOrderAMD> {
 public:
  using VkType::rasterizationOrder;
};

class PipelineRasterizationDepthClipStateCreateInfoEXT
  : public Structure<vk::PipelineRasterizationDepthClipStateCreateInfoEXT> {
 public:
  using VkType::depthClipEnable;
  using VkType::flags;
};

class PipelineRasterizationConservativeStateCreateInfoEXT
  : public Structure<vk::PipelineRasterizationConservativeStateCreateInfoEXT> {
 public:
  using VkType::conservativeRasterizationMode;
  using VkType::extraPrimitiveOverestimationSize;
  using VkType::flags;
};

class PipelineRasterizationStateCreateInfo : public Structure<vk::PipelineRasterizationStateCreateInfo> {
 public:
  using VkType::cullMode;
  using VkType::depthBiasClamp;
  using VkType::depthBiasConstantFactor;
  using VkType::depthBiasEnable;
  using VkType::depthBiasSlopeFactor;
  using VkType::depthClampEnable;
  using VkType::flags;
  using VkType::frontFace;
  using VkType::lineWidth;
  using VkType::polygonMode;
  using VkType::rasterizerDiscardEnable;
};

using PipelineRasterizationStateCreateInfoChain =
  StructureChain<PipelineRasterizationStateCreateInfo, PipelineRasterizationConservativeStateCreateInfoEXT,
                 PipelineRasterizationDepthClipStateCreateInfoEXT, PipelineRasterizationStateRasterizationOrderAMD,
                 PipelineRasterizationStateStreamCreateInfoEXT>;

class SampleLocationsInfoEXT : public Structure<vk::SampleLocationsInfoEXT> {
 public:
  void updateVkStructure() override {
    vecToCArr(sampleLocations, pSampleLocations, sampleLocationsCount);
  }

  using VkType::sampleLocationGridSize;
  using VkType::sampleLocationsPerPixel;
  std::vector<vk::SampleLocationEXT> sampleLocations;
};

class ImageMemoryBarrier : public Structure<vk::ImageMemoryBarrier> {
 public:
  using VkType::dstAccessMask;
  using VkType::dstQueueFamilyIndex;
  using VkType::image;
  using VkType::newLayout;
  using VkType::oldLayout;
  using VkType::srcAccessMask;
  using VkType::srcQueueFamilyIndex;
  using VkType::subresourceRange;
};

using ImageMemoryBarrierChain = StructureChain<ImageMemoryBarrier, SampleLocationsInfoEXT>;

class PipelineSampleLocationsStateCreateInfoEXT : public Structure<vk::PipelineSampleLocationsStateCreateInfoEXT> {
 public:
  void updateVkStructure() override {
    VkType::sampleLocationsInfo = sampleLocationsInfo.build();
  }

  using VkType::sampleLocationsEnable;
  SampleLocationsInfoEXT sampleLocationsInfo;
};

class PipelineCoverageModulationStateCreateInfoNV : public Structure<vk::PipelineCoverageModulationStateCreateInfoNV> {
 public:
  void updateVkStructure() override {
    vecToCArr(coverageModulationTable, pCoverageModulationTable, coverageModulationTableCount);
  }

  using VkType::coverageModulationMode;
  using VkType::coverageModulationTableEnable;
  using VkType::flags;
  std::vector<float> coverageModulationTable;
};

class PipelineCoverageToColorStateCreateInfoNV : public Structure<vk::PipelineCoverageToColorStateCreateInfoNV> {
 public:
  using VkType::coverageToColorEnable;
  using VkType::coverageToColorLocation;
  using VkType::flags;
};

class PipelineMultisampleStateCreateInfo : public Structure<vk::PipelineMultisampleStateCreateInfo> {
 public:
  void updateVkStructure() override {
    pSampleMask = sampleMask.empty() ? nullptr : sampleMask.data();
  }

  using VkType::alphaToCoverageEnable;
  using VkType::alphaToOneEnable;
  using VkType::flags;
  using VkType::minSampleShading;
  using VkType::rasterizationSamples;
  using VkType::sampleShadingEnable;

  std::vector<vk::SampleMask> sampleMask;
};

using PipelineMultisampleStateCreateInfoChain =
  StructureChain<PipelineMultisampleStateCreateInfo, PipelineCoverageToColorStateCreateInfoNV,
                 PipelineCoverageModulationStateCreateInfoNV, PipelineSampleLocationsStateCreateInfoEXT>;

class PipelineDepthStencilStateCreateInfo : public Structure<vk::PipelineDepthStencilStateCreateInfo> {
 public:
  using VkType::back;
  using VkType::depthBoundsTestEnable;
  using VkType::depthCompareOp;
  using VkType::depthTestEnable;
  using VkType::depthWriteEnable;
  using VkType::flags;
  using VkType::front;
  using VkType::maxDepthBounds;
  using VkType::minDepthBounds;
  using VkType::stencilTestEnable;
};

using PipelineDepthStencilStateCreateInfoChain = StructureChain<PipelineDepthStencilStateCreateInfo>;

class PipelineColorBlendAdvancedStateCreateInfoEXT
  : public Structure<vk::PipelineColorBlendAdvancedStateCreateInfoEXT> {
 public:
  using VkType::blendOverlap;
  using VkType::dstPremultiplied;
  using VkType::srcPremultiplied;
};

class PipelineColorBlendStateCreateInfo : public Structure<vk::PipelineColorBlendStateCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(attachments, pAttachments, attachmentCount);
  }

  using VkType::blendConstants;
  using VkType::flags;
  using VkType::logicOp;
  using VkType::logicOpEnable;

  std::vector<vk::PipelineColorBlendAttachmentState> attachments;
};

using PipelineColorBlendStateCreateInfoChain =
  StructureChain<PipelineColorBlendStateCreateInfo, PipelineColorBlendAdvancedStateCreateInfoEXT>;

class PipelineDynamicStateCreateInfo : public Structure<vk::PipelineDynamicStateCreateInfo> {
 public:
  void updateVkStructure() override {
    vecToCArr(dynamicStates, pDynamicStates, dynamicStateCount);
  }

  using VkType::flags;
  std::vector<vk::DynamicState> dynamicStates;
};

using PipelineDynamicStateCreateInfoChain = StructureChain<PipelineDynamicStateCreateInfo>;

class GraphicsPipelineCreateInfo : public Structure<vk::GraphicsPipelineCreateInfo> {
 public:
  void updateVkStructure() override {
    // todo
    // vecToCArr(dynamicStates, pDynamicStates, dynamicStateCount);
  }

  using VkType::basePipelineHandle;
  using VkType::basePipelineIndex;
  using VkType::flags;
  using VkType::layout;
  using VkType::renderPass;
  using VkType::subpass;

  std::vector<PipelineShaderStageCreateInfoChain> stages;
  PipelineVertexInputStateCreateInfoChain vertexInputState;
  PipelineInputAssemblyStateCreateInfoChain inputAssemblyState;
  PipelineTessellationStateCreateInfoChain tessellationState;
  PipelineViewportStateCreateInfoChain viewportState;
  PipelineRasterizationStateCreateInfoChain rasterizationState;
  PipelineMultisampleStateCreateInfoChain multisampleState;
  PipelineDepthStencilStateCreateInfoChain depthStencilState;
  PipelineColorBlendStateCreateInfoChain colorBlendState;
  PipelineDynamicStateCreateInfoChain dynamicState;

 private:
  std::vector<vk::PipelineShaderStageCreateInfo> vkStages_;
};

} // namespace logi

#endif // LOGI_STRUCTURES_VK_STRUCTURE_HPP