//
// Created by qvx on 29.10.2024.
//

#include <stdexcept>
#include <array>
#include "first_app.h"

namespace qve {

    FirstApp::FirstApp() {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }
    FirstApp::~FirstApp() {
        vkDestroyPipelineLayout(qveDevice.device(), pipelineLayout, nullptr);
    }

    void FirstApp::run() {
        while (!qveWindow.shouldClose()){
            glfwPollEvents();
            drawFrame();
        }
        vkDeviceWaitIdle(qveDevice.device());
    }

    void FirstApp::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if(vkCreatePipelineLayout(qveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS){
            throw std::runtime_error("Failed to create pipeline layout");
        }
    }

    void FirstApp::createPipeline() {
        auto pipelineConfig = QvePipeline::defaultPipelineConfigInfo(qveSwapChain.width(), qveSwapChain.height());
        pipelineConfig.renderPass = qveSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        qvePipeline = std::make_unique<QvePipeline>(
                qveDevice,
                "..\\shaders\\simple_shaders.vert.spv",
                "..\\shaders\\simple_shaders.frag.spv",
                pipelineConfig);
    }

    void FirstApp::createCommandBuffers() {
        commandBuffers.resize(qveSwapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = qveDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t >(commandBuffers.size());
        if(vkAllocateCommandBuffers(qveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS){
            throw std::runtime_error("Failed to allocate command buffers");
        }

        for (int i = 0 ; i < commandBuffers.size() ; i++){
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
                throw std::runtime_error("Failed to begin recording command buffer");
            }
            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = qveSwapChain.getRenderPass();
            renderPassInfo.framebuffer = qveSwapChain.getFrameBuffer(i);
            renderPassInfo.renderArea.offset = {0,0};
            renderPassInfo.renderArea.extent = qveSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f,0.1f,0.1f,0.1f};
            clearValues[1].depthStencil = {1.0f,0};
            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            qvePipeline->bind(commandBuffers[i]);
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
                throw std::runtime_error("Failed to record command buffer");
            }
        }
    }
    void FirstApp::drawFrame() {
        uint32_t  imageIndex;
        auto result = qveSwapChain.acquireNextImage(&imageIndex);
        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
            throw std::runtime_error("Failed to acquire swap chain image");
        }
        result = qveSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
        if(result != VK_SUCCESS){
            throw std::runtime_error("Failed to present swap chain image");
        }
    }

} // qve