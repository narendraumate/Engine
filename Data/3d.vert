#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 perspective;
uniform mat4 orthographic;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

void main()
{
	vPosition = position;
	vNormal = normal;
	vTexCoord = texCoord;
	
	gl_Position = perspective * view * model * vec4(position, 1.0);
}
