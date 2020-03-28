
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/ecs/common.h>
#include <unnecessary/rendering/lighting/lights.h>
#include <unnecessary/rendering/ecs/components.h>

namespace un {
    DrawingSystem::DrawingSystem(GLFWwindow *wnd) : wnd(wnd) {}

    void DrawingSystem::update(
            entityx::EntityManager &entities,
            entityx::EventManager &events,
            entityx::TimeDelta dt
    ) {
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
                Geometry *geometry = drawable.geometry;
                auto &material = geometry->getMaterial();
                auto *program = material.getShaderProgram();
                auto &indices = program->getIndices();
                auto pid = program->getId();

                auto mvp = camera.projection * viewMatrix * modelM;
                glCall(glUseProgram(pid));
                glCall(glUniformMatrix4fv(indices.mvp, 1, GL_FALSE, reinterpret_cast<float *>(&mvp)));
                glCall(glUniformMatrix4fv(indices.model, 1, GL_FALSE, reinterpret_cast<float *>(&modelM)));

                geometry->bind();
                glCall(glBindBufferBase(GL_UNIFORM_BUFFER, 0, drawable.pointLights.getId()));
                glCall(
                        glDrawElements(
                                GL_TRIANGLES,
                                geometry->getIndicesCount(),
                                GL_UNSIGNED_INT,
                                nullptr
                        )
                );
                //glDrawArrays(GL_TRIANGLES, 0, 4);
            }
        }
    }


}