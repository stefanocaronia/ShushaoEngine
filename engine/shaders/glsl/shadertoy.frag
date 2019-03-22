void mainImage(out vec4 frag_color, in vec2 fragCoord) {

    // Normalized pixel coordinates (from 0 to 1)
    vec2 UV = fragCoord/iResolution.xy;

    bool enabled_sliced = true;
	bool enabled_tiled = false;

    vec4 sprite_border = vec4(10, 10, 10, 10); // X=left, Y=bottom, Z=right, W=top
    vec4 image_border = vec4(10, 10, 10, 10); // X=left, Y=bottom, Z=right, W=top
    vec2 texture_size = vec2(512, 512);
    vec2 image_size = vec2(iResolution);

    vec4 uvBorder;

    // sprite borders in uv coords
    uvBorder.x = sprite_border.x / texture_size.x;
    uvBorder.y = sprite_border.y / texture_size.y;
    uvBorder.z = sprite_border.z / texture_size.x;
    uvBorder.w = sprite_border.w / texture_size.y;

    if (enabled_sliced && UV.x < uvBorder.x) {
        frag_color = vec4(0,1,1,1);
        return;
    }

    // Output to screen
    frag_color = texture(iChannel0, UV);
}
