//
// Created by qvx on 29.10.2024.
//

#ifndef QVE_FIRST_APP_H
#define QVE_FIRST_APP_H

#include "qve_window.h"
#include "qve_pipeline.h"
#include "qve_device.h"
#include "qve_swap_chain.h"

#include <memory>

namespace qve {

    class FirstApp {
        public:
            static constexpr int WIDTH = 800;
            static constexpr int HEIGHT = 600;

            FirstApp();
            ~FirstApp();
            FirstApp(const FirstApp &) = delete;
            FirstApp &operator=(const FirstApp &) = delete;

            void run();

        private:
            void createPipelineLayout();
            void createPipeline();
            void createCommandBuffers();
            void drawFrame();

            QveWindow qveWindow{WIDTH,HEIGHT,"Qvx Vulkan Engine"};
            QveDevice qveDevice{qveWindow};
            QveSwapChain qveSwapChain{qveDevice,qveWindow.getExtent()};
            std::unique_ptr<QvePipeline> qvePipeline;
            VkPipelineLayout  pipelineLayout;
            std::vector<VkCommandBuffer> commandBuffers;
    };

} // qve

#endif //QVE_FIRST_APP_H
