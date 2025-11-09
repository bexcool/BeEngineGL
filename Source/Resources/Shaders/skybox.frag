#version 330 core

uniform sampler2D texture2D;

in vec3 vert_normal;
in vec2 vert_uv;

out vec4 fragColor;

void main() {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = ambient + texture(texture2D, vert_uv);
}