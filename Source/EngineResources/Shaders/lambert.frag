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

void main(void) {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 modelColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 finalDiffuse = vec4(0, 0, 0, 1);

    for (int i = 0; i < lightCount; i++)
    {
        vec3 lightPosition = vec3(lights[i].position.xyz);
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);

        float dotProduct = max(dot(normalize(lightDirection), normalize(vert_worldNormal)), 0.0);
        vec4 diffuse = dotProduct * modelColor;

        finalDiffuse += diffuse;
    }
    
    fragColor = ambient + finalDiffuse;
}