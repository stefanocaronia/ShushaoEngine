#version 430

/*
    In questo shader il colore è deciso dall'array di vertex colors
*/

in vec4 rendered_color;
out vec4 frag_color;

void main() {
    frag_color = rendered_color;
}
