//
// Created by qvx on 29.10.2024.
//

#ifndef QVE_QVE_PIPELINE_H
#define QVE_QVE_PIPELINE_H

#include "qve_device.h"

#include <string>
#include <vector>

namespace qve {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class QvePipeline {
        public:
            QvePipeline(QveDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);
            ~QvePipeline();
            QvePipeline(const QvePipeline&) = delete;
            void operator=(const QvePipeline&) = delete;

            void bind(VkCommandBuffer commandBuffer);
            static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

        private:
            static std::vector<char> readFile(const std::string& filePath);

            void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo &configInfo);
            void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        QveDevice &qveDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };

} // qve

#endif //QVE_QVE_PIPELINE_H
