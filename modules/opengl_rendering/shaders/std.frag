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
uniform PointLight lights[4];

void main() {
    vec3 baseColor = vec3(1, 1, 1);
    PointLight fLights[2];
    fLights[0] = PointLight(
    vec3(10, 10, 10),
    vec3(0.012, 0.663, 0.957),
    1,
    0
    );
    fLights[1] = PointLight(
    vec3(-10, -10, 10),    vec3(0.914, 0.118, 0.388),
    1,
    0
    );
    color= vec3(0, 0, 0);
    for (int i =0; i< 2;i++){
        PointLight light = fLights[i];
        vec3 lightDir = normalize(light.position - fragPos);
        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse  = light.color  * diff * light.intensity;
        diffuse  *= light.intensity;

        color += diffuse* baseColor;
    }
}