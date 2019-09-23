#include <unnecessary/ecs/common.h>

namespace gl {
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

    void TransformSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {

        entityx::ComponentHandle<ModelToWorld> hMatrix;
        for (entityx::Entity entity : entities.entities_with_components(hMatrix)) {
            ModelToWorld &m = *hMatrix;
            auto mat = glm::identity<glm::mat4>();
            auto scale = entity.component<Scale>();
            if (scale) {
                mat *= glm::scale(mat, (*scale).value);
            }

            auto rotation = entity.component<Rotation>();
            if (rotation) {
                mat *= glm::toMat4((*rotation).value);
            }
            auto translation = entity.component<Translation>();
            if (translation) {
                mat *= glm::translate(glm::identity<glm::mat4>(), (*translation).value);
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

    RenderingSystem::RenderingSystem(GLFWwindow *wnd) : wnd(wnd) {}

    void RenderingSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1F, 0.1F, 0.1F, 1);
        entityx::ComponentHandle<Camera> hCamera;
        entityx::ComponentHandle<WorldToView> hView;
        for (entityx::Entity _ : entities.entities_with_components(hCamera, hView)) {
            entityx::ComponentHandle<ModelToWorld> hModelMatrix;
            entityx::ComponentHandle<Drawable> hDrawable;
            auto &camera = *hCamera;
            auto viewMatrix = (*hView).value;
            int32_t width, height;
            glfwGetWindowSize(wnd, &width, &height);
            auto aspect = (float) width / height;
            camera.projection = glm::perspective(
                    camera.fieldOfView * DEG_TO_RAD,
                    aspect,
                    camera.nearPlane,
                    camera.farPlane
            );
            for (entityx::Entity e : entities.entities_with_components(hModelMatrix, hDrawable)) {
                Drawable &drawable = *hDrawable;
                glm::mat4 modelM = hModelMatrix->value;
                Geometry &geometry = drawable.geometry;
                auto pid = geometry.getProgram().getId();

                auto mvpLocation = glGetUniformLocation(pid, drawable.mvpName.c_str());
                auto mvp = camera.projection * viewMatrix * modelM;
                glCall(glUseProgram(pid));
                glCall(glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, reinterpret_cast<float *>(&mvp)));
                geometry.bind();
                glDrawElements(
                        GL_TRIANGLES,
                        geometry.getIndexBuffer().getLength(),
                        GL_UNSIGNED_INT, nullptr
                );
                //glDrawArrays(GL_TRIANGLES, 0, 4);
            }
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
            auto eFwd = gl::forward(e);
            gl::Navigator &nav = *hNav;
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

                auto yaw = dY * nav.angularSpeed * dt +
                           getInput(wnd, GLFW_KEY_LEFT, GLFW_KEY_RIGHT) * nav.angularSpeed * dt * 5;
                auto pitch = dY * nav.angularSpeed * dt +
                             getInput(wnd, GLFW_KEY_UP, GLFW_KEY_DOWN) * nav.angularSpeed * dt * 5;
                glm::vec3 rotV(0, 0, 0);
                rotV.y += yaw;
                rotV.z = pitch;
                rot.value *= glm::quat(rotV);

                fwd = gl::forward(rot);
                up = gl::up(rot);
                right = gl::right(rot);
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
}