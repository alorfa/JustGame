#version 330

layout (location = 0) in vec2 in_vertex;
layout (location = 1) in vec2 in_UV;

out vec2 TexCoords;

uniform mat3 transform;

void main()
{
	vec3 out_pos = transform * vec3(in_vertex, 1.0);
    gl_Position = vec4(out_pos.xy, 0, 1);
    TexCoords = vec2(in_UV.x, in_UV.y);
}