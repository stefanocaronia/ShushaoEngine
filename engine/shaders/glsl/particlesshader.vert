#version 430

layout(location=1) in vec3 particle_position;
layout(location=3) in vec4 particle_color;
layout(location=7) in vec2 particle_size;
layout(location=5) uniform mat4 MVP;

out vec4 color;
out vec2 size;

void main() {
    gl_Position = MVP * vec4(particle_position, 1.0);

    color = particle_color;
    size = particle_size;
}