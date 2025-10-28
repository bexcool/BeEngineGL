#version 330 core

#define MAX_LIGHTS 16

struct light
{
    vec4 position;
    vec3 spotDirection;
    float radius;
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
    vec4 ambient = vec4(vec3(0.05), 1.0);

    vec4 finalSpecular = vec4(0, 0, 0, 1);
    vec4 finalDiffuse = vec4(0, 0, 0, 1);
    vec4 finalAmbient = vec4(0, 0, 0, 1);

    // Camera view direction
    vec3 viewDirection = normalize(vert_cameraWorldLocation - vert_worldPosition.xyz);

    for (int i = 0; i < lightCount; i++)
    {
        if (lights[i].color == vec4(vec3(0), 1)) continue;

        vec3 lightPosition = vec3(lights[i].position.xyz);
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);
        float lightDistance = length(lightPosition - vert_worldPosition.xyz);

        float attenuation = clamp(1.0 - smoothstep(lights[i].radius * 0.5, lights[i].radius, lightDistance), 0.0, 1.0);

        float normalLightDirDotProduct = max(dot(lightDirection, vert_worldNormal), 0.0);
        vec4 diffuse = normalLightDirDotProduct * modelColor * lights[i].color;

        vec3 reflectDirection = reflect(-lightDirection, vert_worldNormal);
        float specular = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);

        float finalSpot = 1;
        if (lights[i].spotDirection != vec3(0))
        {
            float spot = dot(normalize(lights[i].spotDirection), -lightDirection);
            float cutoff = 0.9;          // Inner cone
            float outerCutoff = 0.8;     // Outer cone
            finalSpot = clamp((spot - outerCutoff) / (cutoff - outerCutoff), 0, 1);
        }

        finalAmbient += ambient * attenuation;
        finalSpecular += specular * lights[i].color * attenuation * finalSpot;
        finalDiffuse += diffuse * attenuation * finalSpot;
    }

    fragColor = clamp(clamp(finalAmbient, 0, ambient.x) + finalSpecular + finalDiffuse, 0, 1);
}
/*
#version 330 core

#define MAX_LIGHTS 16

struct light
{
    vec4 position;
    vec3 spotDirection;
    float radius;
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

    vec4 finalSpecular = vec4(0);
    vec4 finalDiffuse = vec4(0);
    vec4 finalAmbient = ambient;

    vec3 viewDirection = normalize(vert_cameraWorldLocation - vert_worldPosition.xyz);

    for (int i = 0; i < lightCount; i++)
    {
        if (lights[i].color.a == 0.0) continue;

        vec3 lightPosition = lights[i].position.xyz;
        vec3 lightDirection = normalize(lightPosition - vert_worldPosition.xyz);

        float dist = length(lightPosition - vert_worldPosition.xyz);
        float attenuation = clamp(1.0 - smoothstep(lights[i].radius * 0.5, lights[i].radius, dist), 0.0, 1.0);

        // Diffuse
        float diff = max(dot(lightDirection, vert_worldNormal), 0.0);
        vec4 diffuse = diff * modelColor * lights[i].color;

        // Specular
        vec3 reflectDir = reflect(-lightDirection, vert_worldNormal);
        float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 32);
        vec4 specular = spec * lights[i].color;

        // Spotlight
        float finalSpot = 1.0;
        if (length(lights[i].spotDirection) > 0.001)
        {
            float spot = dot(normalize(lights[i].spotDirection), -lightDirection);
            float cutoff = 0.9;
            float outerCutoff = 0.8;
            finalSpot = clamp((spot - outerCutoff) / (cutoff - outerCutoff), 0.0, 1.0);
        }

        finalDiffuse += diffuse * attenuation * finalSpot;
        finalSpecular += specular * attenuation * finalSpot;
    }

    fragColor = clamp(finalAmbient + finalDiffuse + finalSpecular, 0.0, 1.0);
}
*/