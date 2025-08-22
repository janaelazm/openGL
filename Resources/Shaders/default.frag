#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Exports color in RGBA
out vec4 FragColor;

// Inputs texture coordinates from vertex shader
in vec2 texCoor;
// Inputs normals from vertex shader
in vec3 Normal;
// inputs current position from vertex shader
in vec3 crntPos;
// Gets camera position from main function
uniform vec3 camPos;

uniform Light light;
uniform Material material;

void main()
{
    // 3D models are usually not rendered in a vaccum, different objects around can affect lighting
    // the light can bounce off walls or other objects, we can simulate this ambient lighting 
    // by setting a base value for "brightness", otherwise surfaces not facing the light source directly
    // will appear too dark
    vec3 ambient =  texture(material.diffuse, texCoor).rgb * light.ambient;

    // Diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(light.position - crntPos);
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = diff * light.diffuse * texture(material.diffuse, texCoor).rgb;

    // Specular lighting
    vec3 specularLight = vec3(1.0f);
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
    vec3 specular = specAmount * light.specular * texture(material.specular, texCoor).rgb;
   
    
    // Ouputs final color
    FragColor =   vec4(light.color * (diffuse + ambient + specular), 1.0f);
}