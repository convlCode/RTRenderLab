#version 330 core

struct Material{
    sampler2D diffuseCol;
    sampler2D specularCol;
    
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
in vec2 texCoords;

void main()
{
    vec3 ambient = light.ambientVol * vec3(texture2D(material.diffuseCol,texCoords));
    
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm,lightDir),0.0f);
    vec3 diffuse = light.diffuseVol * (diff * vec3(texture2D(material.diffuseCol,texCoords)));
    
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir ,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f), material.shininess);
    vec3 specular = light.specularVol *(spec * vec3(texture2D(material.specularCol,texCoords)));
    
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0f);
}