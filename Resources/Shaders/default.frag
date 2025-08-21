#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

// Exports color in RGBA
out vec4 FragColor;

// Inputs color from vertex shader
in vec3 color;
// Inputs texture coordinates from vertex shader
in vec2 texCoor;
// Inputs normals from vertex shader
in vec3 Normal;
// inputs current position from vertex shader
in vec3 crntPos;

// Gets texture unit from main function
uniform sampler2D tex0;
// Gets light color from main function
uniform vec4 lightColor;
// Gets light position from main function
uniform vec3 lightPos;
// Gets camera position from main function
uniform vec3 camPos;

uniform vec3 materialDiffuse;
uniform vec3 materialAmbient;
uniform vec3 materialSpecular;

void main()
{
    // 3D models are usually not rendered in a vaccum, different objects around can affect lighting
    // the light can bounce off walls or other objects, we can simulate this ambient lighting 
    // by setting a base value for "brightness", otherwise surfaces not facing the light source directly
    // will appear too dark
    vec3 ambient =  materialAmbient * vec3(0.2f);

    // Diffuse light
    vec3 lightDiff = vec3(0.5f);
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diff = max(dot(normal, lightDirection), 0.0f);
    vec3 diffuse = (diff * materialDiffuse) * vec3(0.5f);

    // Specular lighting
    vec3 specularLight = vec3(1.0f);
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
    vec3 specular = (specAmount * materialSpecular) * vec3(1.0f);
    
    // Ouputs final color
    FragColor = texture(tex0, texCoor) * (lightColor * vec4((diffuse + ambient + specular), 1.0f));
}