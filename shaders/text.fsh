#version 330

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    color = vec4(textColor, texture(text, TexCoords).r);
    //vec4(0.5, 0.6, 0.2, 1);
}  