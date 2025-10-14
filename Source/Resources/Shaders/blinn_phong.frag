#version 330 core

in vec3 normal;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 fragColor;
in vec3 worldCameraLocation;

void main(void)
{
    vec3 lightPosition = vec3(0, 0, 0); //Point Light position
    vec3 lightDirection = vec3(0, 0, -1);

    vec3 viewDirection = normalize(worldCameraLocation - worldPosition.xyz);
    vec4 modelColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    float normalLightDirDotProduct = max(dot(normalize(lightDirection), normalize(worldNormal)), 0.0);
    vec4 diffuse = normalLightDirDotProduct * modelColor;

    vec3 halfDir = normalize(lightDirection + viewDirection);
    float specular = pow(max(dot(worldNormal, halfDir), 0.0), 2);

    fragColor = ambient + diffuse + (specular * vec4(0.7, 0.7, 0.7, 1.0));
}