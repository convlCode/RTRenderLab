#version 330 core

struct Material{
    vec3 ambientCol;
    vec3 diffuseCol;
    vec3 specularCol;
    
    float shininess;
};


out vec4 fragColor;

uniform Material material;

uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    vec3 ambient = lightColor * material.ambientCol;
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = lightColor * (diff * material.diffuseCol);
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir ,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = lightColor*(spec*material.specularCol);
    
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}