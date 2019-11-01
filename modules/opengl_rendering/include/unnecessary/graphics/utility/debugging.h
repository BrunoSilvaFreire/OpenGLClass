#ifndef OPENGL_DEBUGGING_H
#define OPENGL_DEBUGGING_H

#include <GL/glew.h>
#include <iostream>

namespace un {

    void print_bound_target(uint32_t pName, const std::string &desc);

    void print_bound_elements();
}

void glClearErrors();


void glCheckErrors(const std::string &functionName);

#define glCall(x) glClearErrors();\
                  x;\
                  glCheckErrors(#x);

#define glDeclare(var, x)  glClearErrors();\
                  auto var = x;\
                  glCheckErrors(#x);

#endif