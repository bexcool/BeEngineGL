#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;
layout (location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraWorldLocation;
out vec3 vert_normal;
out vec4 vert_worldPosition;
out vec3 vert_worldNormal;
out vec3 vert_cameraWorldLocation;
out vec2 vert_uv;

void main() {
    vert_cameraWorldLocation = cameraWorldLocation;
    vert_worldPosition = modelMatrix * vec4(vp, 1.0);
    vert_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    vert_normal = vn;
    vert_uv = uv;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}