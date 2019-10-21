#include <unnecessary/graphics/shaders/shader.h>
namespace gl {

    ShaderElement::ShaderElement(uint8_t elementLength, uint8_t elementCount, GLenum type) : LayoutElement(
            elementLength,
            elementCount
    ), type(type) {

    }

    GLenum ShaderElement::getType() const {
        return type;
    }

    std::ostream &operator<<(std::ostream &os, const ShaderElement &element) {
        return os << static_cast<const LayoutElement &>(element) << " type: " << element.type;
    }

    bool ShaderSource::checkCompileStatus(uint32_t id) {
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        return result == GL_TRUE;
    }

    void ShaderSource::showCompileError(uint32_t id) {
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

    ShaderSource::ShaderSource(std::string source, ShaderLayout layout) : source(std::move(source)), layout(std::move(layout)) {}

    ShaderSource ShaderSource::from(const std::filesystem::path &path, const ShaderLayout &layout) {
        std::cout << path << std::endl;
        std::string result;
        std::ifstream stream(path.string());
        char currentByte;
        stream.seekg(0, std::ios::end);
        size_t length = stream.tellg();
        stream.seekg(0, std::ios::beg);
        //result.reserve(length);
        while (stream.get(currentByte)) {
            result += currentByte;
        }
        stream.close();
        return ShaderSource(result, layout);
    }

    uint32_t ShaderSource::exportShader(GLenum type) const {
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

    const ShaderSource &Shader::getVertex() const {
        return vertex;
    }

    const ShaderSource &Shader::getFragment() const {
        return fragment;
    }

    Shader Shader::from(
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
}