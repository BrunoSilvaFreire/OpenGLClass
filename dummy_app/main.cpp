#include <unnecessary/application.h>
#include <unnecessary/graphics/graphics.h>
#include <unnecessary/ecs/common.h>
#include <array>
#include <entityx/entityx.h>
#include <cmath>
#include <filesystem>
#include <glm/gtx/string_cast.hpp>
#include <unnecessary/graphics/ecs/rendering.h>
#include <tiny_obj_loader.h>

#define FLOOR_WIDTH 10
#define FLOOR_HEIGHT 5
#define FLOOR_SIZE 1.0F

un::Geometry createFloor(
        un::Shader *shader
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
                            un::VertexElement(sizeof(float), 3, GL_FLOAT, false)
                    }
            ),
            vertices.data(), vertices.size(),
            indices.data(), indices.size(),
            un::Material(shader)
    );
}

un::Geometry createTriangle(
        un::Shader *shader
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
            un::Material(shader)
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
        tr.value.z = -10 + std::sin(time) * 5;

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
    auto *shader = new un::Shader(
            un::Shader::from(
                    resDir / "std.vert",
                    un::ShaderLayout({}),
                    resDir / "std.frag",
                    un::ShaderLayout({}),
                    resDir / "std.geom",
                    un::ShaderLayout({})
            )
    );
    un::ecs::register_default_systems(application);
    un::gl_rendering::register_default_systems(application);
    auto &systems = application.getSystems();
    auto camera = application.getEntities().create();
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
    auto material = un::Material(shader);

    auto e = application.getEntities().create();
    //systems.add<Sine>(t, 0.01);
    e.assign<un::ModelToWorld>();
    auto tri = createTriangle(shader);
    auto pid = tri.getProgram().getId();

    auto mvpLocation = glGetUniformLocation(pid, "mvpMatrix");
    auto lightsLocation = glGetUniformLocation(pid, "lights");

    e.assign_from_copy<un::Drawable>(
            {
                    un::DrawableIndices(
                            mvpLocation,
                            lightsLocation
                    ),
                    tri
            }
    );
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
        auto e = application.getEntities().create();
        e.assign<un::ModelToWorld>();
        e.assign<un::WorldToView>();
        e.assign_from_copy<un::Drawable>(
                {
                        "mvpMatrix",
                        un::Geometry::from(
                                vLayout,
                                model.verts.data(), model.verts.size(),
                                model.indices.data(), model.indices.size(),
                                material
                        )
                }
        );
        e.assign_from_copy<un::Translation>(
                {
                        glm::vec3(2, 1, 0)
                }
        );
    }
    for (Model &model : import_obj(bunnyFile)) {
        auto e = application.getEntities().create();
        e.assign<un::ModelToWorld>();
        e.assign<un::WorldToView>();
        e.assign_from_copy<un::Drawable>(
                {
                        "mvpMatrix",
                        un::Geometry::from(
                                vLayout,
                                model.verts.data(), model.verts.size(),
                                model.indices.data(), model.indices.size(),
                                material
                        )
                }
        );
        e.assign<un::Scale>(glm::vec3(20, 20, 20));
        e.assign<un::Translation>(
                glm::vec3(-1, 1, 0)
        );
    }
    /*auto floorE = application.getEntities().create();
    floorE.assign<un::ModelToWorld>();
    floorE.assign_from_copy<un::Drawable>(
            {
                    "mvpMatrix",
                    createFloor(shader)
            }
    );*/
    systems.add<Closer>(&application);
    application.show();
    application.run();
}