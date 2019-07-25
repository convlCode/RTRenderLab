#version 330 core

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    float ambient = 0.1f;
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    
    float diffuse = max(dot(norm,lightDir),0.0f);
    
    vec3 result = (ambient + diffuse) * lightColor * objectColor;

    fragColor = vec4(result, 1.0f);
}