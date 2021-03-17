#version 330

in vec2 frag_UV;

out vec4 out_color;

uniform sampler2D img;

const float MAX_COMP = 8;

float to_8bit_comp(float in_comp)
{
	for (int i = 0; i < MAX_COMP; i++)
	{
		if (in_comp < (i + 1) / MAX_COMP)
			return i / MAX_COMP;
	}
}

void main()
{
	vec3 color = texture(img, frag_UV).rgb;
	color.r = to_8bit_comp(color.r);
	color.g = to_8bit_comp(color.g);
	color.b = to_8bit_comp(color.b);
	out_color = vec4(color, 1.f);
}