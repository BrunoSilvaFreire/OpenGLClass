#ifndef OPENGL_DEBUGGING_H
#define OPENGL_DEBUGGING_H

#include <GL/glew.h>
#include <iostream>

void glClearErrors() {
    while (glGetError() != GLEW_NO_ERROR);
}


void glCheckErrors(const std::string &functionName) {
    uint32_t error;
    while ((error = glGetError()) != GLEW_NO_ERROR) {
        std::cout << "Error while calling function " << functionName << ": " << error << std::endl;
    }
}

void glPrintBoundTarget(uint32_t pName, const std::string &desc) {
    int result;
    glGetIntegerv(pName, &result);
    std::cout << "Target '" << desc << "' bound @ " << result << std::endl;
}

void glPrintBoundTargets() {
    std::cout << "Currently bound targets are:" << std::endl;
    glPrintBoundTarget(GL_VERTEX_ARRAY_BUFFER_BINDING, "Vertex Array");
    glPrintBoundTarget(GL_ARRAY_BUFFER_BINDING, "Vertex Buffer");
    glPrintBoundTarget(GL_ELEMENT_ARRAY_BUFFER_BINDING, "Index Buffer");

}

#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#define glDeclare(var, x)  glClearErrors();\
                  auto var = x;\
                  glCheckErrors(#x);

#endif