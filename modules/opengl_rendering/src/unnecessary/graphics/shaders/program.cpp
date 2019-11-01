#include <unnecessary/graphics/shaders/program.h>

namespace un {

    ShaderProgram::ShaderProgram(const un::Shader &shader) {
        id = glCreateProgram();
        vShader = shader.getVertex().exportShader(GL_VERTEX_SHADER);
        fShader = shader.getFragment().exportShader(GL_FRAGMENT_SHADER);
        glAttachShader(id, vShader);
        glAttachShader(id, fShader);
        auto g = shader.getGeometry();
        if (g != nullptr) {
            gShader = g->exportShader(GL_GEOMETRY_SHADER);
            glAttachShader(id, gShader);
        }
        glCall(glLinkProgram(id));
        int32_t result;
        glCall(glGetProgramiv(id, GL_LINK_STATUS, &result));
        if (result == GL_FALSE) {
            int32_t length;
            glCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));
            if (length <= 0) {
                std::cerr << "Error while linking program @ " << id << ", no message given";
            } else {
                char *linkError = new char[length];
                glCall(glGetProgramInfoLog(id, length, &length, linkError));
                std::cerr << "Error while linking program @ " << id << ": \"" << linkError << "\"";
                delete[] linkError;
                glCall(glDeleteProgram(id));
                throw std::runtime_error("Program linking failed!");
            }


        }
        glCall(glValidateProgram(id));
        /*glCall(glDeleteShader(fragmentShaderID));
        glCall(glDeleteShader(vertexShaderID));*/
    }

    uint32_t ShaderProgram::getId() const {
        return id;
    }

    uint32_t ShaderProgram::getVShader() const {
        return vShader;
    }

    uint32_t ShaderProgram::getFShader() const {
        return fShader;
    }
}