#version 330 core

out vec4 fragColor;
in vec2 TexCoords;

uniform sampler2D ambientMap;

void main()
{
    fragColor = texture2D(ambientMap,TexCoords);
}