#version 330 core

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float range;
};

out vec3 color;

in vec3 fragPos;
in vec3 normal;

#define LIGHT_COUNT 4

uniform Lighting {
    PointLight pointLights[LIGHT_COUNT];
};

void main() {
    vec3 baseColor = vec3(1, 1, 1);
    color= vec3(0, 0, 0);
    for (int i = 0; i < LIGHT_COUNT; i++){
        PointLight light = pointLights[i];
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse  = light.color  * diff * light.intensity;
        diffuse  *= light.intensity;

        color += diffuse* baseColor;
    }
}