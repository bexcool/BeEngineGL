#version 330 core

#define MAX_LIGHTS 16

struct light
{
    vec4 position;
    vec4 color;
};

uniform light lights[MAX_LIGHTS];
uniform int lightCount;

in vec3 vert_normal;
in vec4 vert_worldPosition;
in vec3 vert_worldNormal;
in vec3 vert_cameraWorldLocation;

out vec4 fragColor;

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(void)
{
    // Material
    vec4 modelColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 finalSpecular = vec4(0, 0, 0, 1);
    vec4 finalDiffuse = vec4(0, 0, 0, 1);

    // Camera view direction
    vec3 viewDirection = normalize(vert_cameraWorldLocation - vert_worldPosition.xyz);

    for (int i = 0; i < lightCount; i++)
    {
        vec3 lightPosition = vec3(lights[i].position.xyz);
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);
        float lightDistance = map(length(lightPosition - vert_worldPosition.xyz), 0, 10, 1, 0);

        float normalLightDirDotProduct = max(dot(normalize(lightDirection), normalize(vert_normal)), 0.0);
        vec4 diffuse = normalLightDirDotProduct * modelColor;

        finalDiffuse += diffuse * lightDistance;

        vec3 halfDir = normalize(lightDirection + viewDirection);
        float specular = pow(max(dot(vert_normal, halfDir), 0.0), 32);

        finalSpecular += specular * lights[i].color * lightDistance;
    }

    fragColor = ambient + finalSpecular + finalDiffuse;
}