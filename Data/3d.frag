#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;

uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;
uniform sampler2D normalTextureSampler;

out vec4 fColor;

void main()
{	
	fColor = texture(ambientTextureSampler, vTexcoord);
	fColor = texture(diffuseTextureSampler, vTexcoord);
	fColor = texture(specularTextureSampler, vTexcoord);
	fColor = texture(normalTextureSampler, vTexcoord);
	fColor = vec4(vNormal, 1.0);
}
