#version 330 core

layout (location = 0) in vec3 vp;
layout (location = 1) in vec3 vn;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraWorldLocation;
out vec3 normal;
out vec4 worldPosition;
out vec3 worldNormal;
out vec3 worldCameraLocation;

void main() {
    worldCameraLocation = cameraWorldLocation;
    worldPosition = vec4(vp, 1.0) * modelMatrix;
    worldNormal = vn;

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    normal = vn;
}