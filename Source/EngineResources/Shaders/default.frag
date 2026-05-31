#version 330 core

in vec3 vert_normal;
out vec4 fragColor;

void main() {
    vec4 modelColor = vec4(0.385, 0.647, 0.812, 1.0);

    fragColor = modelColor;
    //fragColor = vec4(vert_normal.x + 0.8, vert_normal.x + 0.8, vert_normal.x + 0.8, 1.0);
}