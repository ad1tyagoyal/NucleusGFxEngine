#shader vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextCoor;

uniform mat4 u_TransformMat;
uniform mat4 u_ViewProjectionMatrix;
out vec2 v_TextCoor;

void main() {
	gl_Position = u_ViewProjectionMatrix * u_TransformMat * vec4(a_Position, 1.0);
	v_TextCoor = a_TextCoor;
}


#shader fragment
#version 330 core

uniform sampler2D u_Texture;
uniform vec4 u_TintColor;

out vec4 color;
in vec2 v_TextCoor;


void main() {
	color = texture(u_Texture, v_TextCoor) * vec4(u_TintColor);
}