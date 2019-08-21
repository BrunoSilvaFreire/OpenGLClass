#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#define GLEW_NO_GLU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <entityx/entityx.h>
#include <ecs/common.h>

namespace gl {

    class Application {
    private:
        GLFWwindow *window;
        bool running;
        entityx::EntityX ecs;
    public:
        entityx::EntityManager &getEntities() {
            return ecs.entities;
        }

        entityx::SystemManager &getSystems() {
            return ecs.systems;
        }

        explicit Application(glm::u32vec2 size, const std::string &title) : window(nullptr), running(false) {
            auto glfwInitStatuss = glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            window = glfwCreateWindow(
                    size.x, size.y, title.c_str(), nullptr, nullptr
            );
            glfwMakeContextCurrent(window);
            auto glewInitCode = glewInit();
            if (glewInitCode != GLEW_OK) {
                std::cout << "An error occoured while initializing GLEW (" << glewInitCode << ") '"
                          << glewGetErrorString(glewInitCode) << "'" << std::endl;
                throw std::runtime_error("Error while initializing GLEW");
            }
            std::cout << "OpenGL '" << glGetString(GL_VERSION) << "' succesfully initialized (GLFW: "
                      << glfwGetVersionString()
                      << ")" << std::endl;
            ecs.systems.add<NavigationSystem>(window);
            ecs.systems.add<TransformSystem>();
            ecs.systems.add<ViewSystem>();
            ecs.systems.add<RenderingSystem>(window);
            ecs.systems.configure();
        }

        void show() {
            glfwShowWindow(window);
        }

        bool isRunning() const {
            return running;
        }

        GLFWwindow *getWindow() const {
            return window;
        }

        void setRunning(bool running) {
            Application::running = running;
        }

        void run() {
            running = true;
            while (running) {
                ecs.systems.update_all(1 / 60.0F);
                glfwPollEvents();
                if (glfwWindowShouldClose(window)) {
                    running = false;
                }
                glfwSwapBuffers(window);
            }
        }
    };
}
#endif //OPENGL_APPLICATION_H
