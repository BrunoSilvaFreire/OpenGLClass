#include <application.h>
#include <graphics/graphics.h>
#include <array>
#include <entityx/entityx.h>
#include <filesystem>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

gl::Geometry createTriangle() {

    std::array<glm::vec3, 3> triangle = {
            glm::vec3(-0.5, -0.5, 0),
            glm::vec3(0.5, -0.5, 0),
            glm::vec3(0, 0.5, 0)
    };
    std::array<uint32_t, 3> indices = {
            0, 1, 2
    };
    std::filesystem::path workingDir = "/home/bruno/CLionProjects/OpenGL";
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
    return gl::Geometry::from(
            gl::VertexLayout(
                    {
                            gl::VertexElement(sizeof(float), 3, GL_FLOAT)
                    }
            ),
            triangle.data(), sizeof(triangle),
            indices.data(), sizeof(indices),
            gl::Material(shader)
    );
}

class DummySystem : public entityx::System<DummySystem> {
private:
    gl::Geometry geometry;
public:
    DummySystem() : geometry(createTriangle()) {

    }

private:
    void update(entityx::EntityManager &entities, entityx::EventManager &events, entityx::TimeDelta dt) override {
        auto mvpLocation = glGetUniformLocation(geometry.getProgram().getId(), "mvp");
        auto mvp = glm::identity<glm::mat4>();
        //std::cout << glm::to_string(mvp) << std::endl;
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, reinterpret_cast<float *>(&mvp));

        geometry.draw();
    }
};

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

int main() {
    gl::Application application(glm::u32vec2(600, 400), "OpenGL");
    auto &systems = application.getSystems();
    systems.add<DummySystem>();
    systems.add<Closer>(&application);
    application.show();
    application.run();
}