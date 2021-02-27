#version 330

in vec3 frag_color;
in vec2 frag_UV;

out vec4 out_color;

uniform sampler2D img;

void main()
{
	out_color = texture(img, vec2(frag_UV.x, 1 - frag_UV.y)) * vec4(frag_color, 1);
}