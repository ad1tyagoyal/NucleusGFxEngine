#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(Location = 2) in vec2 a_TextCoordinate;

uniform mat4 u_Model;

out vec3 v_Normal;
out vec3 v_FragPos;
out vec2 v_TextCoordinate;

void main() {
	gl_Position = u_Model * vec4(a_Position, 1.0);
	v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
	v_Normal = a_Normal;
	v_TextCoordinate = a_TextCoordinate;
}


#shader fragment
#version 330 core

struct Material {
	float ambientStrength;
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;


	float constantValue;
	float linearValue;
	float quadraticValue;
};

out vec4 color;

uniform vec3 u_LightColor;
uniform vec3 u_LightPos;
//uniform vec3 u_ObjectColor;
uniform vec3 u_CamPos;

uniform Material u_Material;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight[] u_PointLights;

in vec3 v_Normal;
in vec3 v_FragPos;
in vec2 v_TextCoordinate;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	//ambient
	//float amberStrength = 0.5f;
	vec3 amberLighting = u_Material.ambientStrength * u_LightColor;

	//diffuse
	vec3 fragNormal = normalize(v_Normal);
	vec3 lightRayDir = normalize(u_LightPos - v_FragPos);
	float diffuseStrength = max(dot(fragNormal, lightRayDir), 0.0f);
	vec3 diffuseLighting = diffuseStrength * u_LightColor * vec3(texture(u_Material.diffuse, v_TextCoordinate));

	//specular
	vec3 viewerDir = normalize(u_CamPos - v_FragPos);
	vec3 reflectedLightRayDir = normalize(reflect(-1.0 * lightRayDir, fragNormal));
	float specularStrength = pow(max(dot(reflectedLightRayDir, viewerDir), 0.0f), u_Material.shininess);
	vec3 specularLighting =  specularStrength * u_LightColor * vec3(texture(u_Material.specular, v_TextCoordinate));

	//result
	vec3 result = (amberLighting + diffuseLighting + specularLighting);
	color = vec4(result, 1.0);
}

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-1.0 * light.direction);
	float diff = max(dot(lightDir, normal), 0.0);

	vec3 reflectRayDir = reflect(-1.0 * light.direction, normal);
	float spec = pow(max(dot(reflectRayDir, viewDir), 0.0), u_Material.shininess);

	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TextCoordinate));
	vec3 diffuse = diff * light.diffuse * vec3(texture(u_Material.diffuse, v_TextCoordinate));
	vex3 specular = spec * light.specular * vec3(texture(u_Material.specular, v_TextCoordinate));

	return(ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(-1.0 * light.direction);
	float diff = max(dot(lightDir, normal), 0.0);

	vec3 reflectRayDir = reflect(-1.0 * light.direction, normal);
	float spec = pow(max(dot(reflectRayDir, viewDir), 0.0), u_Material.shininess);

	float distance = length(light.position - v_FragPos);
	float attenuation = 1.0 / (light.constantValue + light.linearValue * distance +
						light.quadraticValue * pow(distance, 2.0));

	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TextCoordinate));
	vec3 diffuse = diff * light.diffuse * vec3(texture(u_Material.diffuse, v_TextCoordinate));
	vex3 specular = spec * light.specular * vec3(texture(u_Material.specular, v_TextCoordinate));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return(ambient + diffuse + specular);
}
