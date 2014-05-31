#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;
in vec3 vTangent;
in vec3 vBitangent;
in mat3 vTangentToWorld;

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
	fColor = vec4(vTangent, 1.0);
	fColor = vec4(vBitangent, 1.0);

	fColor = vec4(normalize(vTangentToWorld * ((texture(normalTextureSampler, vTexcoord)).rgb * 2.0 - 1.0)), 1.0);
}
