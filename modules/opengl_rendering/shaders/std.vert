#version 330 core

layout(location = 0) in vec3 vertexPosition;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;
out vec3 fragPos;
out vec3 vPos;
void main() {
    vPos= (modelMatrix * vec4(vertexPosition, 1)).xyz;
    gl_Position = mvpMatrix * vec4(vertexPosition, 1);
}