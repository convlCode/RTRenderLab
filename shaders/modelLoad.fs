#version 330 core

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

out vec4 fragColor;

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform Light light;
uniform vec3 viewPos;

uniform bool isOpenLighting;

void main()
{
    vec3 ambient = light.ambient*texture(texture_diffuse1, texCoords).rgb;
    
    if(isOpenLighting){
        vec3 norm = normalize(normal);
        vec3 lightDir = normalize(light.position - fragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = light.diffuse*diff*texture(texture_diffuse1, texCoords).rgb;
    
        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0) , 32);
        vec3 specular = light.specular * spec * texture(texture_specular1, texCoords).rgb;
    
        vec3 result = ambient + diffuse + specular;
    
        fragColor = vec4(result, 1.0f);
    }else{
        fragColor = vec4(ambient, 1.0f);
    }
    
    //fragColor = texture(texture_diffuse1,texCoords);
}