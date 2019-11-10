#ifndef UNNECESSARY_ECS_COMMON_H
#define UNNECESSARY_ECS_COMMON_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <entityx/System.h>
#include <glm/gtx/string_cast.hpp>
#include <unnecessary/application.h>
namespace un {
    struct Translation {
        Translation(const glm::vec3 &value);

        glm::vec3 value;
    };
    struct Rotation {
        Rotation(const glm::quat &value);

        glm::quat value;
    };
    struct Scale {
        Scale(const glm::vec3 &value);

        glm::vec3 value;
    };
    struct ModelToWorld {
        glm::mat4 value;
    };
    struct WorldToView {
        glm::mat4 value;
    };


    glm::vec3 forward(const un::Rotation &rotation);

    glm::vec3 right(const un::Rotation &rotation);

    glm::vec3 up(const un::Rotation &rotation);

    glm::vec3 forward(entityx::Entity &e);


    struct TransformSystem : entityx::System<TransformSystem> {

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };

    struct ViewSystem : entityx::System<ViewSystem> {
        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };


    struct Navigator {
    public:
        float speed;
        float angularSpeed;
    };

    struct NavigationSystem : entityx::System<NavigationSystem> {
    private:
        GLFWwindow *wnd;
        double lastMouseX = 0, lastMouseY = 0;

        double getInput(GLFWwindow *window, int32_t positive, int32_t negative);

    public:
        explicit NavigationSystem(GLFWwindow *wnd) : wnd(wnd) {}

        void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };
    namespace ecs {
        void register_default_systems(un::Application &app);
    }
}

#endif
