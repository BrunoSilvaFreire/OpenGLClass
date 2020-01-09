#version 330 core

struct Lighting {
    vec4 color;
};

struct PointLight {
    Lighting lighting;
    float range;
    vec4 position;
};

struct DirectionalLight {
    vec4 direction;
    Lighting lighting;
};

out vec3 color;

in vec3 fragPos;
in vec3 normal;

#define DIRECTIONAL_LIGHT_COUNT 2
#define POINT_LIGHT_COUNT 4

uniform EntityLighting {
    PointLight pointLights[POINT_LIGHT_COUNT];
    DirectionalLight directionalLights[DIRECTIONAL_LIGHT_COUNT];
    vec4 ambient;
};

vec3 diffuse(vec3 lightDir, Lighting light) {
    float diff = max(dot(normal, lightDir), 0.0);
    return (light.color.xyz  * diff * light.color.w);
}

void main() {
    color = vec3(0, 0, 0);
    for (int i = 0; i < POINT_LIGHT_COUNT; i++){
        PointLight point = pointLights[i];
        vec3 lightDir = normalize(fragPos-point.position.xyz);
        color += diffuse(lightDir, point.lighting);
    }
    for (int i = 0; i < DIRECTIONAL_LIGHT_COUNT; i++){
        DirectionalLight l = directionalLights[i];
        color += diffuse(l.direction.xyz, l.lighting);
    }
    color += ambient.xyz * ambient.w;

}