#include <unnecessary/graphics/ecs/gl.h>
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/graphics/ecs/lighting.h>

namespace un {
    void gl_rendering::register_default_systems(un::Application &app, glm::vec3 ambient) {
        auto &systems = app.getSystems();
        auto window = app.getWindow();
        systems.add<LightingSystem>(ambient);
        systems.add<DrawingSystem>(window);

    }
}