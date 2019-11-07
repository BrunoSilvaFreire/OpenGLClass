
#include <unnecessary/graphics/ecs/rendering.h>
#include <unnecessary/ecs/common.h>

namespace un {
    RenderingSystem::RenderingSystem(GLFWwindow *wnd) : wnd(wnd) {}

    void
    RenderingSystem::update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1F, 0.1F, 0.1F, 1);
        entityx::ComponentHandle<LightPoint> hPoint;
        std::vector<LightPoint &> points;
        for (entityx::Entity _ : entities.entities_with_components(points)) {
            points.emplace_back(*hPoint);
            if (points.size() >= MAX_LIGHTS) {
                break;
            }
        }

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

                auto mvp = camera.projection * viewMatrix * modelM;
                glCall(glUseProgram(pid));
                glCall(glUniformMatrix4fv(drawable.indices.mvp, 1, GL_FALSE, reinterpret_cast<float *>(&mvp)));
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

    void gl_rendering::register_default_systems(un::Application &app) {
        auto &systems = app.getSystems();
        auto window = app.getWindow();
        systems.add<RenderingSystem>(window);

    }

    DrawableIndices::DrawableIndices(
            uint32_t mvp,
            uint32_t lights
    ) : mvp(mvp), lights(lights) {}
}