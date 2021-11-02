#version 460

in vec3 ex_pos;
in vec2 ex_uv;
in vec3 ex_normal;

out vec4 color;

uniform sampler2D tex;
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

void main()
{
	vec3 objectColor = vec3(texture(tex, ex_uv).rgb);

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(ex_normal);
    vec3 lightDir = normalize(lightPos - ex_pos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - ex_pos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
} 