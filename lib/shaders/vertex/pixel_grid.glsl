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

layout(location = 0) in vec4 coordinates;
layout(location = 8) in vec4 texture_coords;

out vec2 frag_coord;

out vec2 _coords;
out float _flag;

void main()
{
    //vec3 coords = vec3(coordinates, 1);
    vec3 coords = model_view * vec3(coordinates.xy, 1);

    gl_Position = vec4(2 * coords.x / vp_size.x - 1, 2 * coords.y / vp_size.y - 1, 0, 1);

    //frag_coord = coordinates.xy; //vec2(texture_coords);
    frag_coord = texture_coords.xy;

    _coords = coordinates.xy;
    _flag = gl_Position.x;
}
