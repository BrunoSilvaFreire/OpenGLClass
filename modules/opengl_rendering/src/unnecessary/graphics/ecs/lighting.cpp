#include <unnecessary/graphics/ecs/lighting.h>
#include <cstring>

namespace un {
    LightingSystem::LightingSystem(const glm::vec3 &ambient) : ambient(ambient) {}

    void LightingSystem::update(
            entityx::EntityManager &entities,
            entityx::EventManager &events,
            entityx::TimeDelta dt
    ) {
        entityx::ComponentHandle<Drawable> drawableView;
        entityx::ComponentHandle<Translation> translationView;
        entityx::ComponentHandle<PointLight> pointLightView;
        for (entityx::Entity _ : entities.entities_with_components(drawableView, translationView)) {
            auto entityPos = (*translationView).value;
            Drawable &drawable = *drawableView;
            // Construct lighting data
            EntityLighting lighting;
            lighting.ambient = ambient;
            // Find POINT_LIGHTS_COUNT nearest point lights
            float pointScores[POINT_LIGHTS_COUNT];
            memset(pointScores, 0, sizeof(pointScores));
            entityx::ComponentHandle<PointLight> hPoint;
            for (entityx::Entity lightEntity : entities.entities_with_components(hPoint)) {
                const PointLight &light = *hPoint;
                auto lightTranslationView = lightEntity.component<Translation>();
                if (!lightTranslationView) {
                    //We require a translation component
                    continue;
                }
                auto pos = (*lightTranslationView).value;
                float distance = glm::distance(pos, entityPos);
                auto attempt = light.lighting.intensity * (1.0F / distance);
                for (int i = 0; i < POINT_LIGHTS_COUNT; ++i) {
                    auto bar = pointScores[i];
                    if (attempt > bar) {
                        pointScores[i] = attempt;
                        lighting.points[i] = un::PositionedPointLight(
                                light,
                                glm::vec4(pos, 0)
                        );
                        break;
                    }
                }
            }

            float directionScores[DIRECTIONAL_LIGHTS_COUNT];
            memset(directionScores, 0, sizeof(directionScores));
            entityx::ComponentHandle<DirectionalLight> hDirectional;
            for (entityx::Entity _ : entities.entities_with_components(hDirectional)) {
                auto &light = *hDirectional;
                auto attempt = light.lighting.intensity;
                for (int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; ++i) {
                    auto bar = directionScores[i];
                    if (attempt > bar) {
                        directionScores[i] = attempt;
                        lighting.directionals[i] = light;
                        break;
                    }
                }
            }
            drawable.pointLights.update(&lighting, sizeof(lighting));
        }
    }

}