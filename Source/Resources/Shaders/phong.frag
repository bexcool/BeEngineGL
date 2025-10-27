#version 330 core

#define MAX_LIGHTS 16

struct light
{
    vec4 position;
    vec3 spotDirection;
    vec4 color;
};

uniform light lights[MAX_LIGHTS];
uniform int lightCount;

in vec3 vert_normal;
in vec4 vert_worldPosition;
in vec3 vert_worldNormal;
in vec3 vert_cameraWorldLocation;

out vec4 fragColor;

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main(void)
{
    // Material
    vec4 modelColor = vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec4 finalSpecular = vec4(0, 0, 0, 1);
    vec4 finalDiffuse = vec4(0, 0, 0, 1);
    vec4 finalAmbient = vec4(0, 0, 0, 1);

    // Camera view direction
    vec3 viewDirection = normalize(vert_cameraWorldLocation - vert_worldPosition.xyz);

    for (int i = 0; i < lightCount; i++)
    {
        vec3 lightPosition = vec3(lights[i].position.xyz);
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);
        float lightDistance = map(length(lightPosition - vert_worldPosition.xyz), 0, 10, 1, 0);

        float normalLightDirDotProduct = max(dot(lightDirection, vert_worldNormal), 0.0);
        vec4 diffuse = normalLightDirDotProduct * (modelColor);

        vec3 reflectDirection = reflect(-lightDirection, vert_worldNormal);
        float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

        float finalSpot = 1;
        if (lights[i].spotDirection != vec3(0))
        {
            finalSpot = 0;
            
            float spot = dot(normalize(lights[i].spotDirection), -lightDirection);
            float cutoff = 0.9;          // Inner cone
            float outerCutoff = 0.8;     // Outer cone
            finalSpot = clamp((spot - outerCutoff) / (cutoff - outerCutoff), 0, 1);
        }

        finalAmbient += ambient * lightDistance;
        finalSpecular += specular * lights[i].color * lightDistance * finalSpot;
        finalDiffuse += diffuse * lightDistance * finalSpot;
    }

    fragColor = clamp(finalAmbient, 0, 0.1) + (finalSpecular + finalDiffuse);
}