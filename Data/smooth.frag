#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;
in vec3 vTangent;
in vec3 vBitangent;

uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;

out vec4 fColor;

void main()
{
	vec4 ambient = texture(ambientTextureSampler, vTexcoord);
	vec4 diffuse = texture(diffuseTextureSampler, vTexcoord);
	vec4 specular = texture(specularTextureSampler, vTexcoord);

	fColor = (ambient + diffuse + specular);
	fColor = vec4(vNormal, 1.0);
}
