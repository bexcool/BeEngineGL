#version 330 core

layout(location=0) in vec3 vp;
layout(location=1) in vec3 vn;

uniform mat4 modelMatrix;
out vec3 normal;

void main () {
     gl_Position = modelMatrix * vec4 (vp, 1.0);
     normal = vn;
}