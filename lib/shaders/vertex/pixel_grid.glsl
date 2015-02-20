#version 430

/*
    EXPERIMENTAL CODE!

    This shader was created with pixel-aligned ("grid-fitted") 2D drawing in mind.

    TODO: The use of a floating-point 3x3 transformation matrix is somewhat in conflict with
        the idea of pixel-aligned drawing. It may be more productive to simply define an
        offset uniform, plus maybe a scaling uniform (perhaps as a rational number?)
 */

layout(location = 0) uniform ivec2 vp_size;
layout(location = 1) uniform mat3  model_view; // TODO: the name "model/view" may be misleading - there is no "camera"

in ivec2 coordinates;
in ivec2 texture_coords;

void main()
{
    vec3 coords = vec3(coordinates, 1);

    coords = model_view * coords;
    
    gl_Position = vec4(2 * coords.x / vp_size.x - 1, 2 * coords.y / vp_size.y - 1, 0, 1);
}
