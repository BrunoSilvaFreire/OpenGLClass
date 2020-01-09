#ifndef UNNECESSARYENGINE_LIGHTS_H
#define UNNECESSARYENGINE_LIGHTS_H

#include <glm/glm.hpp>

namespace un {
#define ALIGN_4F alignas(4 * sizeof(float))

    struct Lighting {
        glm::vec3 color;
        float intensity;

        explicit Lighting(
                const glm::vec3 &color = glm::vec3(),
                float intensity = 1.0F
        ) : color(color), intensity(intensity) {}

    };

    struct PointLight {
    public:
        Lighting lighting;
        float range;

        PointLight() : range(1), lighting() {};

        explicit PointLight(
                const Lighting &lighting,
                float range
        ) : lighting(lighting), range(range) {}

    };

    struct PositionedPointLight {
        PointLight light;
        ALIGN_4F glm::vec4 pos;

        PositionedPointLight() : pos(), light() {}

        PositionedPointLight(const PointLight &light, const glm::vec4 &pos) : light(light), pos(pos) {}
    };

    struct DirectionalLight {
    public:
        ALIGN_4F glm::vec3 direction;
        Lighting lighting;

        DirectionalLight() : lighting(), direction() {};

        DirectionalLight(
                const glm::vec3 &direction,
                const Lighting &light
        ) : direction(direction), lighting(light) {}
    };

#define POINT_LIGHTS_COUNT 4
#define DIRECTIONAL_LIGHTS_COUNT 2

    struct EntityLighting {

        PositionedPointLight points[POINT_LIGHTS_COUNT];
        DirectionalLight directionals[DIRECTIONAL_LIGHTS_COUNT];
        ALIGN_4F glm::vec3 ambient;

        EntityLighting() : points(), directionals(), ambient() {};

    };
}
#endif
