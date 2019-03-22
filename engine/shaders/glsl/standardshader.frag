#version 430

in vec2 UV;

layout(location=6) uniform vec4 render_color;

uniform sampler2D diffuse_map;

uniform bool enabled_sliced;
uniform bool enabled_tiled;
uniform vec4 sprite_border; // X=left, Y=bottom, Z=right, W=top
uniform vec4 image_border; // X=left, Y=bottom, Z=right, W=top
uniform vec2 texture_size;
uniform vec2 image_size;
uniform bool sliced_fill;

out vec4 frag_color;

float map(float value, float originalMin, float originalMax, float newMin, float newMax) {
    return (value - originalMin) / (originalMax - originalMin) * (newMax - newMin) + newMin;
}

void main() {

    vec4 uvSpriteBorder;
    vec4 uvImageBorder;

    // sprite borders in uv coords
    uvSpriteBorder.x = sprite_border.x / texture_size.x;
    uvSpriteBorder.y = sprite_border.y / texture_size.y;
    uvSpriteBorder.z = sprite_border.z / texture_size.x;
    uvSpriteBorder.w = sprite_border.w / texture_size.y;

    // image borders in uv coords
    uvImageBorder.x = image_border.x / image_size.x;
    uvImageBorder.y = image_border.y / image_size.y;
    uvImageBorder.z = image_border.z / image_size.x;
    uvImageBorder.w = image_border.w / image_size.y;


    vec2 newUV = UV;
    bool inContentX = false;
    bool inContentY = false;

    if (enabled_sliced) {

        if (UV.x <= uvImageBorder.x) {
            newUV.x = map(UV.x, 0, uvImageBorder.x, 0, uvSpriteBorder.x);
        } else if (UV.x < 1 - uvImageBorder.z) {
            newUV.x = map(UV.x, uvImageBorder.z, 1 - uvImageBorder.z, uvSpriteBorder.z, 1 - uvSpriteBorder.z);
            inContentX = true;
        } else {
            newUV.x = map(UV.x, 1 - uvImageBorder.z, 1, 1 - uvSpriteBorder.z, 1);
        }

        if (UV.y <= uvImageBorder.w) {
            newUV.y = map(UV.y, 0, uvImageBorder.w, 0, uvSpriteBorder.w);
        } else if (UV.y < 1 - uvImageBorder.y) {
            newUV.y = map(UV.y, uvImageBorder.y, 1 - uvImageBorder.y, uvSpriteBorder.y, 1 - uvSpriteBorder.y);
            inContentY = true;
        } else {
            newUV.y = map(UV.y, 1 - uvImageBorder.y, 1, 1 - uvSpriteBorder.y, 1);
        }

        if (!sliced_fill && inContentX && inContentY) {
            discard;
        }

        frag_color = texture(diffuse_map, newUV) * vec4(render_color);
        return;

    } else if (enabled_tiled) {

        // TOPLEFT CORNER
        if (UV.x <= uvImageBorder.x && UV.y <= uvImageBorder.w) {
            newUV.x = map(UV.x, 0, uvImageBorder.x, 0, uvSpriteBorder.x);
            newUV.y = map(UV.y, 0, uvImageBorder.w, 0, uvSpriteBorder.w);

        // TOPRIGHT CORNER
        } else if (UV.x >= 1 - uvImageBorder.z && UV.y <= uvImageBorder.w) {
            newUV.x = map(UV.x, 1 - uvImageBorder.z, 1, 1 - uvSpriteBorder.z, 1);
            newUV.y = map(UV.y, 0, uvImageBorder.w, 0, uvSpriteBorder.w);

        // BOTTOMLEFT CORNER
        } else if (UV.x <= uvImageBorder.x && UV.y >= 1 - uvImageBorder.y) {
            newUV.x = map(UV.x, 0, uvImageBorder.x, 0, uvSpriteBorder.x);
            newUV.y = map(UV.y, 1 - uvImageBorder.y, 1, 1 - uvSpriteBorder.y, 1);

        // BOTTOMRIGHT CORNER
        } else if (UV.x >= 1 - uvImageBorder.z && UV.y >= 1 - uvImageBorder.y) {
            newUV.x = map(UV.x, 1 - uvImageBorder.z, 1, 1 - uvSpriteBorder.z, 1);
            newUV.y = map(UV.y, 1 - uvImageBorder.y, 1, 1 - uvSpriteBorder.y, 1);

        // MIDDLE AREA
        } else  if (UV.x > uvImageBorder.x && UV.y < 1 - uvImageBorder.y && UV.x < 1 - uvImageBorder.z && UV.y > uvImageBorder.w) {
            inContentX = inContentY = true;
            frag_color = vec4(0,0,1,1);return; // blue

        // LEFT SIDE
        } else if (UV.x <= uvImageBorder.x && UV.y < 1 - uvImageBorder.y && UV.y > uvImageBorder.w) {

            newUV.x = map(UV.x, 0, uvImageBorder.x, 0, uvSpriteBorder.x);

            float textureSide = texture_size.y - sprite_border.w - sprite_border.y;
            float imageSide = image_size.y - image_border.w - image_border.y;

            vec2 imageCoord = image_size * UV;
            vec2 textureCoord = texture_size * UV;

            //newUV.y = int(pixelCoord.y) % int(texture_size.y) / float(texture_size.y);
            //newUV.y = (int(imageCoord.y) % int(textureSide) + sprite_border.w) / texture_size.y;
            newUV.y = fract(UV.y / 0.5f) + uvSpriteBorder.x;
            //frag_color = vec4(1,0,0,1);return; // red

        // RIGHT SIDE
        } else if (UV.x >= 1 - uvImageBorder.z && UV.y < 1 - uvImageBorder.y && UV.y > uvImageBorder.w) {
            frag_color = vec4(0,1,0,1);return; // green

        // TOP SIDE
        } else if (UV.x > uvImageBorder.x && UV.x < 1 - uvImageBorder.z && UV.y <= uvImageBorder.w) {
            frag_color = vec4(1,1,0,1);return; //  brown

        // BOTTOM SIDE
        } else if (UV.x > uvImageBorder.x && UV.x < 1 - uvImageBorder.z && UV.y >= 1 - uvImageBorder.y) {
             frag_color = vec4(0,1,1,1);return; //cyan
        }

        if (!sliced_fill && inContentX && inContentY) {
            discard;
        }

        frag_color = texture(diffuse_map, newUV) * vec4(render_color);
        return;

    }

    frag_color = texture(diffuse_map, UV) * vec4(render_color);
}