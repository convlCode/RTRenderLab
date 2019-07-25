#version 330 core

out vec4 fragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    float ambient = 0.1f;
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuse = max(dot(norm,lightDir),0.0f);
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir ,norm);
    float specularStrength = 0.8f;
    float specular = pow(max(dot(viewDir,reflectDir),0.0f), 64) * specularStrength;
    
    vec3 result = (ambient + diffuse + specular) * lightColor * objectColor;

    fragColor = vec4(result, 1.0f);
}