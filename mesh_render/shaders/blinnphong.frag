#version 460

in vec3 ex_pos;
in vec2 ex_uv;
in vec3 ex_normal;

uniform sampler2D tex;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

out vec4 color;

const float lightPower = 50000000.0;
const vec3 specColor = vec3(0.3, 0.3, 0.3);

void main() 
{
	// get object color from texture
	vec3 objectColor = vec3(texture(tex, ex_uv).rgb);

	// ambient
	vec3 ambient = 0.05 * objectColor;

    // diffuse
    vec3 lightDir = normalize(lightPos - ex_pos);
    vec3 normal = normalize(ex_normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * objectColor;

    // specular
    vec3 viewDir = normalize(viewPos - ex_pos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color

    color = vec4(ambient + diffuse + specular, 1.0);
}