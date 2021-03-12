#version 330

in vec2 frag_UV;

out vec4 out_color;

uniform sampler2D img;

void main()
{
	out_color = vec4(1, 1, 1, 1) - texture(img, vec2(frag_UV.x, 1 - frag_UV.y));
}