#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;
layout( location = 3 ) in vec3 tangent;
layout( location = 4 ) in vec3 bitangent;


uniform mat4 model;
uniform mat4 view;
uniform mat4 modelView;
uniform mat3 norm;

uniform mat4 perspective;
uniform mat4 orthographic;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;
out vec3 vTangent;
out vec3 vBitangent;
out mat3 vTangentToWorld;

void main()
{
	gl_Position = perspective * modelView * vec4(position, 1.0);
	vPosition = gl_Position.xyz;
	vTexcoord = texcoord;
	vNormal = normalize(mat3(model) * normal);
	vTangent = normalize(mat3(model) * tangent);
	vBitangent = normalize(mat3(model) * bitangent);
	vTangentToWorld = mat3(vTangent, vBitangent, vNormal);
}
