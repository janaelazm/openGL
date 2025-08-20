#version 330 core
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

void main()
{
    // 3D models are usually not rendered in a vaccum, different objects around can affect lighting
    // the light can bounce off walls or other objects, we can simulate this ambient lighting 
    // by setting a base value for "brightness", otherwise surfaces not facing the light source directly
    // will appear too dark
    float ambient = 0.20f;

    // Diffuse light
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    // Specular lighting
    float specularLight = 0.5f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmount * specularLight;
    
    // Ouputs final color
    FragColor = texture(tex0, texCoor) * lightColor * (diffuse + ambient + specular);
}