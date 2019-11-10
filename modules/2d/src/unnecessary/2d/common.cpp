#include <unnecessary/2d/common.h>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

namespace un {
    Scale2D::Scale2D(
            float x,
            float y
    ) : x(x), y(y) {}

    Rotation2D::Rotation2D(float angle) : angle(angle) {}

    Translation2D::Translation2D(float x, float y) : x(x), y(y) {}

    void Transform2DSystem::update(
            entityx::EntityManager &entities,
            entityx::EventManager &events,
            entityx::TimeDelta dt
    ) {
        entityx::ComponentHandle<ModelToWorld2D> hMatrix;
        for (entityx::Entity entity : entities.entities_with_components(hMatrix)) {
            ModelToWorld2D &m = *hMatrix;
            auto mat = glm::identity<glm::mat3>();
            auto translation = entity.component<ModelToWorld2D>();
            if (translation) {
                mat *= glm::translate(
                        glm::mat3(),
                        m.value
                )
            }

            auto rotation = entity.component<Rotation2D>();
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
}
