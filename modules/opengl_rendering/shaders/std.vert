#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUv;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;

out vec3 fragPos;
out vec3 vPos;
out vec2 uv;

void main() {
    vPos= (modelMatrix * vec4(vertexPosition, 1)).xyz;
    uv = vertexUv;
    gl_Position = mvpMatrix * vec4(vertexPosition, 1);
}