#version 330 core

struct PointLight {
    vec3 position;
    float range;
    float intensity;
};

out vec3 color;

in vec3 normal;
uniform PointLight lights[4];

void main() {
    vec3 baseColor = (normal + vec3(1, 1, 1)) / 2;
    color = baseColor;
}