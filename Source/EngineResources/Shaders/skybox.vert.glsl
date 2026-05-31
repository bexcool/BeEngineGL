#version 330 core

layout (location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vert_normal;
out vec2 vert_uv;
out vec3 vert_texDir;

void main() {
    mat4 viewNoTranslation = mat4(mat3(viewMatrix));

    vert_texDir = vp;
    gl_Position = projectionMatrix * viewNoTranslation * vec4(vp, 1.0);
}