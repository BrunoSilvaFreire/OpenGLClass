#ifndef OPENGL_DEBUGGING_H
#define OPENGL_DEBUGGING_H

#include <GL/glew.h>
#include <iostream>

namespace gl {

    void print_bound_target(uint32_t pName, const std::string &desc) {
        int result;
        glGetIntegerv(pName, &result);
        std::cout << "Target '" << desc << "' bound @ " << result << std::endl;
    }

    void print_bound_elements() {

        std::cout << "Currently bound targets are:" << std::endl;
        print_bound_target(GL_VERTEX_ARRAY_BUFFER_BINDING, "Vertex Array");
        print_bound_target(GL_ARRAY_BUFFER_BINDING, "Vertex Buffer");
        print_bound_target(GL_ELEMENT_ARRAY_BUFFER_BINDING, "Index Buffer");
    }
}

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}


void glCheckErrors(const std::string &functionName) {
    uint32_t error;

    //std::cout << "Calling function " << functionName << "..." << std::endl;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        std::cout << "Error while calling function " << functionName << ": " << error << std::endl;
    }
}

#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#define glDeclare(var, x)  glClearErrors();\
                  auto var = x;\
                  glCheckErrors(#x);

#endif