#version 330 core

in vec3 normal;
out vec4 fragColor;

void main() {
    fragColor = vec4(normal.x + 0.8, normal.x + 0.8, normal.x + 0.8, 1.0);
}