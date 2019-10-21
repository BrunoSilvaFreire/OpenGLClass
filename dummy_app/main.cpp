#include <unnecessary/application.h>
#include <unnecessary/graphics/graphics.h>
#include <unnecessary/ecs/common.h>
#include <array>
#include <entityx/entityx.h>
#include <cmath>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <unnecessary/graphics/ecs/rendering.h>

#define FLOOR_WIDTH 5
#define FLOOR_HEIGHT 5
#define FLOOR_SIZE 1.0F

gl::Geometry createFloor(
        gl::Shader *shader
) {
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;
    for (int i = -FLOOR_WIDTH; i < FLOOR_WIDTH; ++i) {
        for (int j = -FLOOR_HEIGHT; j < FLOOR_HEIGHT; ++j) {
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            vertices.emplace_back(
                    (float) i * FLOOR_SIZE,
                    r,
                    (float) j * FLOOR_SIZE
            );
        }
    }

    for (uint32_t i = 0; i < FLOOR_HEIGHT * FLOOR_WIDTH; ++i) {
        auto first = i;
        auto second = i + 1;
        auto third = i + (FLOOR_WIDTH * 2);
        auto fourth = i + (FLOOR_WIDTH * 2) + 1;
        // First triangle
        indices.push_back(first);
        indices.push_back(second);
        indices.push_back(third);
        // Second triangle
        indices.push_back(second);
        indices.push_back(third);
        indices.push_back(fourth);
    }
    return gl::Geometry::from(
            gl::VertexLayout(
                    {
                            gl::VertexElement(sizeof(float), 3, GL_FLOAT, false)
                    }
            ),
            vertices.data(), vertices.size(),
            indices.data(), indices.size(),
            gl::Material(shader)
    );
}

gl::Geometry createTriangle(
        gl::Shader *shader
) {

    std::vector<glm::vec3> triangle = {
            glm::vec3(1.0, -1.0, 1.0),
            glm::vec3(1.0, -1.0, 1.0),
            glm::vec3(1.0, 1.0, 1.0),
            glm::vec3(-1.0, 1.0, 1.0),
            // back
            glm::vec3(-1.0, -1.0, -1.0),
            glm::vec3(1.0, -1.0, -1.0),
            glm::vec3(1.0, 1.0, -1.0),
            glm::vec3(-1.0, 1.0, -1.0)
    };
    std::vector<uint32_t> indices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

    return gl::Geometry::from(
            gl::VertexLayout(
                    {
                            gl::VertexElement(sizeof(float), 3, GL_FLOAT, false)
                    }
            ),
            triangle.data(), triangle.size(),
            indices.data(), indices.size(),
            gl::Material(shader)
    );
}

struct Closer : entityx::System<Closer> {
private:
    gl::Application *application;

public:
    explicit Closer(gl::Application *application) : application(application) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        if (glfwGetKey(application->getWindow(), GLFW_KEY_ESCAPE)) {
            application->setRunning(false);
        }
    }
};

struct Sine : entityx::System<Sine> {
private:
    entityx::ComponentHandle<gl::Translation> t;
    float time = 0;
    float speed;
public:
    Sine(const entityx::ComponentHandle<gl::Translation> &t, float speed) : t(t), speed(speed) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        time += dt * speed;
        gl::Translation &tr = *t;
        tr.value.z = -10 + std::sin(time) * 5;

    }
};

int main() {
    gl::Application application(glm::u32vec2(1920, 1080), "Unnecessary App");
    std::filesystem::path workingDir = std::filesystem::current_path();
    std::cout << "Executing at " << workingDir << std::endl;
    std::filesystem::path resDir = workingDir / "shaders";
    //Allocate on heap
    std::cout << "Using resources located @ " << resDir << std::endl;
    auto *shader = new gl::Shader(
            gl::Shader::from(
                    resDir / "std.vert",
                    gl::ShaderLayout({}),
                    resDir / "std.frag",
                    gl::ShaderLayout({})
            )
    );
    gl::ecs::register_default_systems(application);
    gl::gl_rendering::register_default_systems(application);
    auto &systems = application.getSystems();
    auto camera = application.getEntities().create();
    camera.assign<gl::WorldToView>();
    auto t = camera.assign_from_copy<gl::Translation>(
            {
                    glm::vec3(0, 0, -10)
            }
    );
    camera.assign_from_copy<gl::Rotation>(
            {
                    glm::quat_identity<float, glm::qualifier::defaultp>()
            }
    );
    camera.assign_from_copy<gl::Navigator>(
            {
                    1.0F, .05F
            }
    );
    camera.assign_from_copy<gl::Camera>(
            {
                    60.0F,
                    0.01F,
                    100.0F
            }
    );
    auto e = application.getEntities().create();
    //systems.add<Sine>(t, 0.01);
    e.assign<gl::ModelToWorld>();
    e.assign_from_copy<gl::Drawable>(
            {
                    "mvpMatrix",
                    createTriangle(shader)
            }
    );
    auto floorE = application.getEntities().create();
    floorE.assign<gl::ModelToWorld>();
    floorE.assign_from_copy<gl::Drawable>(
            {
                    "mvpMatrix",
                    createFloor(shader)
            }
    );
    systems.add<Closer>(&application);
    application.show();
    application.run();
}