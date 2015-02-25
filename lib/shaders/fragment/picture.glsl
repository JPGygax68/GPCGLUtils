#version 430

layout(location = 2) uniform sampler2DRect picture;

in  vec2 frag_coord;

in  vec2 _coords;
in float _flag;

out vec4 color;

void main()
{
    //color = vec4(1, 1, 1, 1);

    color = texture(picture, vec2(frag_coord.x, textureSize(picture).y - frag_coord.y));
    //color = texelFetch(picture, ivec2(frag_coord));
    //color = vec4(0.5, 0.5, 0.5, 1) + vec4(frag_coord.x / 1920, frag_coord.y / 1080, 0, 1);
}
