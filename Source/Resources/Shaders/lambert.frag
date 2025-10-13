#version 330 core

in vec3 normal;
in vec4 worldPosition;
in vec3 worldNormal;
out vec4 fragColor;

void main(void) {
    vec3 lightPosition = vec3(10.0, 10.0, 10.0); //Point Light position
    vec3 lightDirection = vec3(0, 1, 0);

    float dotProduct = max(dot(normalize(lightDirection), normalize(worldNormal)), 0.0);
    vec4 diffuse = dotProduct * vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    fragColor = ambient + diffuse;
}