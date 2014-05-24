#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 modelView;
uniform mat3 norm;

uniform mat4 perspective;
uniform mat4 orthographic;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

void main()
{
	vPosition = position;
	vNormal = normal;
	vTexcoord = texcoord;

	gl_Position = perspective * modelView * vec4(position, 1.0);
}
