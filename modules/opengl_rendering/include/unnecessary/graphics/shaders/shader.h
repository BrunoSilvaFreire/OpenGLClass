#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <streambuf>
#include <filesystem>
#include <fstream>
#include <unnecessary/utility/layout.h>
#include <GL/glew.h>
#include <ostream>
#include <unnecessary/utility/debugging.h>

namespace gl {
    class ShaderElement : LayoutElement {
    private:
        GLenum type;
    public:
        ShaderElement(
                uint8_t elementLength,
                uint8_t elementCount,
                GLenum type
        );

        GLenum getType() const;

        friend std::ostream &operator<<(std::ostream &os, const ShaderElement &element);
    };

    typedef Layout <gl::ShaderElement> ShaderLayout;

    class ShaderSource {
    private:
        std::string source;
        gl::ShaderLayout layout;

        static bool checkCompileStatus(uint32_t id);

        static void showCompileError(uint32_t id);

    public:
        ShaderSource(
                std::string source,
                ShaderLayout layout
        );

        static ShaderSource from(
                const std::filesystem::path &path,
                const ShaderLayout &layout
        );

        uint32_t exportShader(GLenum type) const;
    };

    class Shader {
    private:
        ShaderSource vertex, fragment;
    public:
        Shader(ShaderSource vertex, ShaderSource fragment) : vertex(std::move(vertex)), fragment(std::move(fragment)) {}

        const ShaderSource &getVertex() const;

        const ShaderSource &getFragment() const;

        static Shader from(
                const std::filesystem::path &vertexPath,
                const ShaderLayout &vertexLayout,
                const std::filesystem::path &fragmentPath,
                const ShaderLayout &fragmentLayout
        );

    };
}
#endif
