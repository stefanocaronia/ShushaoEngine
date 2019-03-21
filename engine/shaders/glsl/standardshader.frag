#version 430

in vec2 UV;

layout(location=6) uniform vec4 render_color;

uniform sampler2D diffuse_map;
uniform bool enabled_sliced;
uniform bool enabled_tiled;
uniform vec4 border; // X=left, Y=bottom, Z=right, W=top
uniform vec2 size;

out vec4 frag_color;

void main() {

    vec4 uvBorder;

    uvBorder.x = border.x / size.x;
    uvBorder.y = border.y / size.y;
    uvBorder.z = border.z / size.x;
    uvBorder.w = border.w / size.y;

    if (enabled_sliced && UV.x > uvBorder.x) {
        frag_color = vec4(1,1,1,1);
        return;
    }

    frag_color = texture(diffuse_map, UV) * vec4(render_color);
}