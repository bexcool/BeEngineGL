#version 330 core

uniform samplerCube cubeTexture;

in vec3 vert_texDir;

out vec4 fragColor;

void main() {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    fragColor = ambient + texture(cubeTexture, vert_texDir);
}