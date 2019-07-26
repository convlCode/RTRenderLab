#version 330 core

struct Material{
    vec3 ambientCol;
    vec3 diffuseCol;
    vec3 specularCol;
    
    float shininess;
};

struct Light{
    vec3 position;
    
    vec3 ambientVol;
    vec3 diffuseVol;
    vec3 specularVol;
};


out vec4 fragColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
    vec3 ambient = light.ambientVol * material.ambientCol;
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = light.diffuseVol * (diff * material.diffuseCol);
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir ,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = light.specularVol *(spec*material.specularCol);
    
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}