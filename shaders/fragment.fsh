#version 330

in vec2 frag_UV;

out vec3 out_color;

uniform vec4 color;
uniform sampler2D img;

void main()
{
	out_color = texture(img, vec2(frag_UV.x, 1 - frag_UV.y)).rgb * color.rgb;
}