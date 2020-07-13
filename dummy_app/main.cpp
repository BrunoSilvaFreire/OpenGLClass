#include <unnecessary/application.h>
#include <unnecessary/ecs/common.h>
#include <unnecessary/graphics/ecs/gl.h>
#include <unnecessary/graphics/graphics.h>
#include <array>
#include <entityx/entityx.h>
#include <cmath>
#include <filesystem>
#include <glm/gtx/string_cast.hpp>
#include <tiny_obj_loader.h>
#include <unnecessary/graphics/ecs/drawing.h>
#include <unnecessary/graphics/material.h>
#include <unnecessary/graphics/lighting/lights.h>
#include <unnecessary/graphics/gl_loaders.h>
#define FLOOR_WIDTH 10
#define FLOOR_HEIGHT 5
#define FLOOR_SIZE 1.0F

un::Geometry createFloor(
        un::Material &material
) {
    std::vector<glm::vec3> vertices;
    std::vector<uint32_t> indices;

    for (int i = 0; i < FLOOR_WIDTH; ++i) {
        for (int j = 0; j < FLOOR_HEIGHT; ++j) {
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
    return un::Geometry::from(
            un::VertexLayout(
                    {
                            un::VertexElement(sizeof(float), 3, GL_FLOAT, false),
                            un::VertexElement(sizeof(float), 2, GL_FLOAT, false),
                    }
            ),
            vertices.data(), vertices.size(),
            indices.data(), indices.size(),
            material
    );
}

un::Geometry createTriangle(
        un::Material &material
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

    return un::Geometry::from(
            un::VertexLayout(
                    {
                            un::VertexElement(sizeof(float), 3, GL_FLOAT, false)
                    }
            ),
            triangle.data(), triangle.size(),
            indices.data(), indices.size(),
            material
    );
}

struct Closer : entityx::System<Closer> {
private:
    un::Application *application;

public:
    explicit Closer(un::Application *application) : application(application) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        if (glfwGetKey(application->getWindow(), GLFW_KEY_ESCAPE)) {
            application->setRunning(false);
        }
    }
};

struct Sine : entityx::System<Sine> {
private:
    entityx::ComponentHandle<un::Translation> t;
    float time = 0;
    float speed;
public:
    Sine(const entityx::ComponentHandle<un::Translation> &t, float speed) : t(t), speed(speed) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        time += dt * speed;
        un::Translation &tr = *t;
        tr.value.z += std::sin(time);

    }
};

struct Rotator : entityx::System<Rotator> {
private:
    entityx::ComponentHandle<un::Rotation> t;
    float time = 0;
    float speed;
public:
    Rotator(const entityx::ComponentHandle<un::Rotation> &t, float speed) : t(t), speed(speed) {}

    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        time += dt * speed;
        un::Rotation &tr = *t;
        tr.value = glm::vec3(0, time, 0);

    }
};


struct Model {
    std::vector<glm::vec3> verts;
    std::vector<uint32_t> indices;
};

std::vector<Model> import_obj(std::filesystem::path file) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    tinyobj::LoadObj(
            &attrib,
            &shapes,
            &materials,
            &warn, &err, file.c_str()
    );

    std::vector<glm::vec3> vData;
    auto verts = attrib.vertices;
    auto count = verts.size();
    vData.reserve(count / 3);
    for (size_t i = 0; i < count; i += 3) {
        auto x = verts[i];
        auto y = verts[i + 1];
        auto z = verts[i + 2];
        vData.emplace_back(
                x,
                y,
                z

        );
    }
    std::vector<Model> models;
    for (auto &shape : shapes) {

        std::vector<uint32_t> i;
        auto &toTransform = shape.mesh.indices;
        std::transform(
                toTransform.begin(),
                toTransform.end(),
                std::back_inserter(i),
                [](const tinyobj::index_t &index) {
                    return index.vertex_index;
                }
        );
        models.push_back(
                {
                        vData,
                        i
                }
        );
    }
    return models;
}

int main() {
    un::Application application(glm::u32vec2(1920, 1080), "Unnecessary App");
    std::filesystem::path workingDir = std::filesystem::current_path();
    std::cout << "Executing at " << workingDir << std::endl;
    std::filesystem::path resDir = workingDir / "shaders";
    //Allocate on heap
    std::cout << "Using resources located @ " << resDir << std::endl;
    un::Shader shader(
            un::Shader::from(
                    resDir / "std.vert",
                    un::ShaderLayout({}),
                    resDir / "std.frag",
                    un::ShaderLayout(
                            {
                                    un::ShaderElement(
                                            1, 1, GL_TEXTURE_2D
                                    )
                            }
                    ),
                    resDir / "std.geom",
                    un::ShaderLayout({})
            )
    );
    un::ShaderProgram program(shader, "mvpMatrix", "EntityLighting", "modelMatrix");
    un::Material material(
            &program,
            std::vector<un::Material::FloatProperty>(),
            std::vector<un::Material::IntProperty>(),
            std::vector<un::Material::ColorProperty>(),
            {}
    );

    un::ecs::register_default_systems(application);
    un::gl_rendering::register_default_systems(application, glm::vec3(0.5, 0.5, 0.5));
    un::gl::register_default_loaders(application.getResources());
    auto &systems = application.getSystems();
    auto &entities = application.getEntities();
    auto camera = entities.create();
    camera.assign<un::WorldToView>();
    auto t = camera.assign_from_copy<un::Translation>(
            {
                    glm::vec3(0, 0, -10)
            }
    );
    camera.assign_from_copy<un::Rotation>(
            {
                    glm::quat_identity<float, glm::qualifier::defaultp>()
            }
    );
    camera.assign_from_copy<un::Navigator>(
            {
                    1.0F, .05F
            }
    );
    camera.assign_from_copy<un::Camera>(
            {
                    60.0F,
                    0.01F,
                    100.0F
            }
    );

    auto e = entities.create();
    //systems.add<Sine>(t, 0.01);
    e.assign<un::ModelToWorld>();
    auto tri = createTriangle(material);
    e.assign_from_copy(un::Drawable::create(&tri));
    std::filesystem::path assetsDir = workingDir / "assets";
    std::filesystem::path teapotFile = assetsDir / "teapot.obj";
    std::filesystem::path bunnyFile = assetsDir / "bunny.obj";
    std::cout << "Using teapot " << teapotFile << "." << std::endl;
    un::VertexLayout vLayout = un::VertexLayout(
            {
                    un::VertexElement(sizeof(float), 3, GL_FLOAT, false)
            }
    );
    for (Model &model : import_obj(teapotFile)) {
        auto e = entities.create();
        e.assign<un::ModelToWorld>();
        e.assign<un::WorldToView>();
        auto heo = new un::Geometry(
                un::Geometry::from(
                        vLayout,
                        model.verts.data(), model.verts.size(),
                        model.indices.data(), model.indices.size(),
                        material
                )
        );
        e.assign_from_copy(un::Drawable::create(heo));
        e.assign_from_copy<un::Translation>(
                {
                        glm::vec3(2, 1, 0)
                }
        );

    }
    for (Model &model : import_obj(bunnyFile)) {
        auto e = entities.create();
        e.assign<un::ModelToWorld>();
        e.assign<un::WorldToView>();
        e.assign_from_copy(
                un::Drawable::create(
                        new un::Geometry(
                                un::Geometry::from(
                                        vLayout,
                                        model.verts.data(), model.verts.size(),
                                        model.indices.data(), model.indices.size(),
                                        material
                                )
                        )
                )
        );
        e.assign<un::Scale>(glm::vec3(20, 20, 20));
        e.assign<un::Translation>(
                glm::vec3(-1, 1, 1)
        );
        auto tls = e.assign_from_copy<un::Rotation>(
                {
                        glm::vec3(0, 180 * DEG_TO_RAD, 0)
                }
        );
        systems.add<Rotator>(tls, 1);

    }
    std::vector<std::tuple<glm::vec3, glm::vec3>> lights = {
            {
                    glm::vec3(0, 1, 1),
                    glm::vec3(0, 1, 0),
            },
            {
                    glm::vec3(0, 1, 0),
                    glm::vec3(1, 1, 0),
            },
            {
                    glm::vec3(1, 0, 0),
                    glm::vec3(-1, -5, 0)
            }
    };
    for (std::tuple<glm::vec3, glm::vec3> l : lights) {
        auto c = std::get<0>(l);
        auto p = std::get<1>(l);
        auto light = entities.create();
        light.assign<un::Translation>(p);
        light.assign_from_copy(un::Drawable::create(&tri));
        light.assign<un::PointLight>(
                un::Lighting(
                        c,
                        1
                ),
                1
        );
    }
    auto dLight = entities.create();
    dLight.assign<un::DirectionalLight>(
            glm::vec3(-1, -1, -1),
            un::Lighting(glm::vec3(0.2, 0.2, 0.2), 0.3)
    );

//    systems.add<Sine>(lighting.component<un::Translation>(), 1);
    systems.add<Closer>(&application);
    application.show();
    application.run();
}