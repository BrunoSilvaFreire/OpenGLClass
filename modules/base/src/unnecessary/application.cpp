#include <unnecessary/application.h>

namespace gl {
    Application::Application(glm::u32vec2 size, const std::string &title) : window(nullptr), running(false) {
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
        //glDepthMask(GL_FALSE);
        glDepthFunc(GL_LESS);
        glEnable(GL_DEPTH_TEST);
    }

    void Application::show() {
        ecs.systems.configure();
        glfwShowWindow(window);
    }

    bool Application::isRunning() const {
        return running;
    }

    entityx::SystemManager &Application::getSystems() {
        return ecs.systems;
    }

    entityx::EntityManager &Application::getEntities() {
        return ecs.entities;
    }

    void Application::setRunning(bool running) {
        Application::running = running;
    }

    void Application::run() {
        running = true;
        while (running) {

            ecs.systems.update_all(1 / 60.0F);
            glfwPollEvents();
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            if (glfwWindowShouldClose(window)) {
                running = false;
            }
            glfwSwapBuffers(window);
        }
    }

}