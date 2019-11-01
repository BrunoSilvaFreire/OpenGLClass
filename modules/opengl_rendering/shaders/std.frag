#version 330 core

out vec3 color;
in vec3 normal;
void main() {
    color = (normal + vec3(1, 1, 1)) / 2;
    color.b=1;
}