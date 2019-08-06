#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include <cstdint>
#include <utility>
#include <vector>
#include <streambuf>
#include <filesystem>
#include <fstream>
#include <utility/layout.h>
#include <GL/glew.h>
#include <ostream>
#include <utility/debugging.h>

namespace gl {
    class ShaderElement : LayoutElement {
    private:
        GLenum type;
    public:
        ShaderElement(
                uint8_t elementLength,
                uint8_t elementCount,
                GLenum type
        ) : LayoutElement(
                elementLength,
                elementCount
        ), type(type) {

        }

        GLenum getType() const {
            return type;
        }

        friend std::ostream &operator<<(std::ostream &os, const ShaderElement &element) {
            return os << static_cast<const LayoutElement &>(element) << " type: " << element.type;
        }
    };

    typedef Layout <gl::ShaderElement> ShaderLayout;

    class ShaderSource {
    private:
        std::vector<char> source;
        gl::ShaderLayout layout;

        static bool checkCompileStatus(uint32_t id) {
            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            return result == GL_TRUE;
        }

        static void showCompileError(uint32_t id) {
            int32_t length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

            if (length <= 0) {
                std::cerr << "Error while compiling shader @ " << id << ", no message given" << std::endl;
            } else {
                char *message = new char[length];
                glGetShaderInfoLog(id, length, &length, message);
                std::cerr << "Error while compiling shader @ " << id << ": \"" << message << "\"" << std::endl;
                delete[] message;
            }
        }

    public:
        ShaderSource(
                std::vector<char> source,
                ShaderLayout layout
        ) : source(std::move(source)), layout(std::move(layout)) {}

        static ShaderSource from(
                const std::filesystem::path &path,
                const ShaderLayout &layout
        ) {
            std::cout << path << std::endl;
            std::vector<char> result;
            std::ifstream stream(path.string());
            char currentByte;
            stream.seekg(0, std::ios::end);
            size_t length = stream.tellg();
            stream.seekg(0, std::ios::beg);
            //result.reserve(length);
            while (stream.get(currentByte)) {
                result.emplace_back(currentByte);
            }
            stream.close();
            return ShaderSource(result, layout);
        }

        uint32_t exportShader(GLenum type) const {
            uint32_t id = glCreateShader(type);
            auto ptr = source.data();
            glCall(glShaderSource(id, 1, &ptr, nullptr));
            glCall(glCompileShader(id));
            auto status = checkCompileStatus(id);
            if (!status) {
                showCompileError(id);
                glCall(glDeleteShader(id));
            }
            return id;
        }
    };

    class Shader {
    private:
        ShaderSource vertex, fragment;
    public:
        Shader(ShaderSource vertex, ShaderSource fragment) : vertex(std::move(vertex)), fragment(std::move(fragment)) {}

        const ShaderSource &getVertex() const {
            return vertex;
        }

        const ShaderSource &getFragment() const {
            return fragment;
        }

        static Shader from(
                const std::filesystem::path &vertexPath,
                const ShaderLayout &vertexLayout,
                const std::filesystem::path &fragmentPath,
                const ShaderLayout &fragmentLayout
        ) {
            return Shader(
                    ShaderSource::from(vertexPath, vertexLayout),
                    ShaderSource::from(fragmentPath, fragmentLayout)
            );
        }

    };
}
#endif
