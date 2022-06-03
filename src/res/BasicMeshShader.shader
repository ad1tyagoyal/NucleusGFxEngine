#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;


uniform mat4 v_View;
out vec3 u_Color;

void main() {
	gl_Position = v_View * vec4(a_Position, 1.0);
	u_Color = a_Color;
}


#shader fragment
#version 330 core

in vec3 u_Color;
out vec4 color;
void main() {
	color = vec4(u_Color, 1.0f);
}