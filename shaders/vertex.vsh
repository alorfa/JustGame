#version 330

layout (location = 0) in vec2 in_position;
layout (location = 2) in vec2 in_UV;

uniform mat3 transform;

out vec2 frag_UV;

void main()
{
	gl_Position = vec4(transform * vec3(in_position, 1), 1);
	frag_UV = in_UV;
}