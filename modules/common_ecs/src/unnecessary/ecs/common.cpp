#include <unnecessary/ecs/common.h>

namespace un {
    glm::vec3 forward(const Rotation &rotation) {
        return glm::vec3(0, 0, 1) * rotation.value;
    }

    glm::vec3 right(const Rotation &rotation) {
        return glm::vec3(1, 0, 0) * rotation.value;
    }

    glm::vec3 up(const Rotation &rotation) {
        return glm::vec3(0, 1, 0) * rotation.value;
    }

    glm::vec3 forward(entityx::Entity &e) {
        auto rot = e.component<Rotation>();
        if (rot) {
            return forward(*rot);
        }
        return glm::vec3(0, 0, 1);
    }

    void
    TransformSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

        entityx::ComponentHandle<ModelToWorld> hMatrix;
        for (entityx::Entity entity : entities.entities_with_components(hMatrix)) {
            ModelToWorld &m = *hMatrix;
            auto mat = glm::identity<glm::mat4>();
            auto translation = entity.component<Translation>();
            if (translation) {
                mat *= glm::translate(glm::identity<glm::mat4>(), (*translation).value);
            }

            auto rotation = entity.component<Rotation>();
            if (rotation) {
                mat *= glm::toMat4((*rotation).value);
            }
            auto scale = entity.component<Scale>();
            if (scale) {
                mat *= glm::scale(mat, (*scale).value);
            }

            m.value = mat;
        }
    }

    void ViewSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
        entityx::ComponentHandle<WorldToView> hMatrix;
        for (entityx::Entity entity : entities.entities_with_components(hMatrix)) {
            WorldToView &m = *hMatrix;
            glm::vec3 fwd(0, 0, 1);
            glm::vec3 pos(0, 0, 0);
            glm::vec3 up(0, 1, 0);
            auto rotation = entity.component<Rotation>();
            if (rotation) {
                glm::quat quat = (*rotation).value;
                up = up * quat;
                fwd = fwd * quat;

            }
            auto translation = entity.component<Translation>();
            if (translation) {
                pos = (*translation).value;
            }
            m.value = glm::lookAt(pos, pos + fwd, up);
        }
    }


    double NavigationSystem::getInput(GLFWwindow *window, int32_t positive, int32_t negative) {
        return (glfwGetKey(window, positive) - glfwGetKey(window, negative));
    }

    void
    NavigationSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
        entityx::ComponentHandle<Navigator> hNav;
        entityx::ComponentHandle<Translation> hTrans;
        for (entityx::Entity e : entities.entities_with_components(hNav, hTrans)) {
            un::Navigator &nav = *hNav;
            auto speed = nav.speed;
            glm::vec3 fwd(0, 0, 1);
            glm::vec3 up(0, 1, 0);
            glm::vec3 right(1, 0, 0);
            auto &trans = *hTrans;
            auto hRot = e.component<Rotation>();
            bool reset = glfwGetKey(wnd, GLFW_KEY_R);
            if (reset) {
                trans.value = glm::vec3(0, 0, -10);
            }
            if (hRot) {
                auto &rot = *hRot;
                if (reset) {
                    rot.value = glm::quat(glm::vec3(0, 0, 0));
                }
                double newMouseX, newMouseY;
                glfwGetCursorPos(wnd, &newMouseX, &newMouseY);
                auto dX = newMouseX - lastMouseX;
                auto dY = newMouseY - lastMouseY;
                lastMouseX = newMouseX;
                lastMouseY = newMouseY;

                auto yaw = (dY + getInput(wnd, GLFW_KEY_LEFT, GLFW_KEY_RIGHT)) * nav.angularSpeed * dt;
                auto pitch = (dX + getInput(wnd, GLFW_KEY_UP, GLFW_KEY_DOWN)) * nav.angularSpeed * dt;

                rot.value = glm::quat(glm::vec3(-yaw, 0, 0)) * rot.value * glm::quat(glm::vec3(0, pitch, 0));

                fwd = un::forward(rot);
                up = un::up(rot);
                right = un::right(rot);
            }
            float fwdM = getInput(wnd, GLFW_KEY_W, GLFW_KEY_S) * speed * dt;
            float sideM = getInput(wnd, GLFW_KEY_A, GLFW_KEY_D) * speed * dt;
            float upDownM = getInput(wnd, GLFW_KEY_E, GLFW_KEY_Q) * speed * dt;
            fwd *= fwdM;
            right *= sideM;
            up *= upDownM;
            // Normalize
            auto dir = fwd + right + up;
            trans.value += dir;
        }
    }

    void ecs::register_default_systems(un::Application &app) {
        auto &systems = app.getSystems();
        systems.add<TransformSystem>();
        systems.add<ViewSystem>();
        auto window = app.getWindow();
        systems.add<NavigationSystem>(window);
    }

    Scale::Scale(const glm::vec3 &value) : value(value) {}

    Rotation::Rotation(const glm::quat &value) : value(value) {}

    Translation::Translation(const glm::vec3 &value) : value(value) {}
}