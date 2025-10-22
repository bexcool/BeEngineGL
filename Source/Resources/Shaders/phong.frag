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
        vec3 lightPosition = vec3(lights[i].position.xyz); //Point Light position
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);

        float normalLightDirDotProduct = max(dot(lightDirection, vert_worldNormal), 0.0);
        vec4 diffuse = normalLightDirDotProduct * (modelColor);

        finalDiffuse += diffuse;

        vec3 reflectDirection = reflect(-lightDirection, vert_worldNormal);
        float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 16);

        finalSpecular += (specular * lights[i].color);
    }

    fragColor = ambient + finalSpecular + finalDiffuse;
}