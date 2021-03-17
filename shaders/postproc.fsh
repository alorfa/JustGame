#version 330

in vec2 frag_UV;

out vec4 out_color;

uniform sampler2D img;

void main()
{
	vec3 color;
	color.r = texture(img, frag_UV).r;
	color.g = texture(img, vec2(frag_UV.x - 0.01f, frag_UV.y - 0.01f)).g;
	color.b = texture(img, vec2(frag_UV.x - 0.02f, frag_UV.y)).b;
	out_color = vec4(color, 1.f);
}