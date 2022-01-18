#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;


void main() {
	gl_Position = u_Model * vec4(a_Position/2.0, 1.0);
}


#shader fragment
#version 330 core

out vec4 color;

uniform vec3 u_LightColor;

void main() {
	color = vec4(u_LightColor, 1.0);
}