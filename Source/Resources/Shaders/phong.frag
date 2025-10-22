#version 330 core

#define MAX_LIGHTS 4

struct light
{
    vec4 position;
    vec4 diffuse;
};

uniform light lights[MAX_LIGHTS];
uniform uint lightCount;

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
    vec4 finalColor = vec4(0, 0, 0, 1);
    
    vec3 viewDirection = normalize(vert_cameraWorldLocation - vert_worldPosition.xyz);

    vec3 lightPosition = vec3(lights[0].position.xyz); //Point Light position
    //vec3 lightPosition = vec3(0, 0, 0); //Point Light position
    vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);

    float normalLightDirDotProduct = max(dot(lightDirection, vert_worldNormal), 0.0);
    vec4 diffuse = normalLightDirDotProduct * modelColor;

    vec3 reflectDirection = reflect(-lightDirection, vert_worldNormal);
    float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 8);

    fragColor = ambient + diffuse + (specular * vec4(0.7, 0.7, 0.7, 1.0));
}