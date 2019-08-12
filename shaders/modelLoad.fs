#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D texture_diffuse1;

void main()
{
    fragColor = vec4(2.2f,2.2f,2.2f,1.0f) * texture(texture_diffuse1,texCoords);
}