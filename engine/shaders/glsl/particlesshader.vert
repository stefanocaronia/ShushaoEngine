#version 430

layout(location=1) in vec3 particle_position;
layout(location=5) uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(particle_position, 1.0);
}