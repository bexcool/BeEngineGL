#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraWorldLocation;
out vec3 vert_normal;
out vec4 vert_worldPosition;
out vec3 vert_worldNormal;
out vec3 vert_cameraWorldLocation;

void main() {
    vert_cameraWorldLocation = cameraWorldLocation;
    vert_worldPosition = modelMatrix * vec4(vp, 1.0);
    vert_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * vn);
    vert_normal = vn;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
}