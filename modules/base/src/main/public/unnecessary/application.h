#ifndef UNNECESSARYENGINE_APPLICATION_H
#define UNNECESSARYENGINE_APPLICATION_H

#define GLEW_NO_GLU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>
#include <entityx/entityx.h>

namespace gl {

    class Application {
    private:
        GLFWwindow *window;
        bool running;
        entityx::EntityX ecs;
    public:
        entityx::EntityManager &getEntities();

        entityx::SystemManager &getSystems();

        explicit Application(glm::u32vec2 size, const std::string &title);

        void show();

        bool isRunning() const;

        GLFWwindow *getWindow() const {
            return window;
        }

        void setRunning(bool running);

        void run();
    };
}

#endif
