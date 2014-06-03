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
	vec4 ambient = texture(ambientTextureSampler, vTexcoord);
	vec4 diffuse = texture(diffuseTextureSampler, vTexcoord);
	vec4 specular = texture(specularTextureSampler, vTexcoord);
	vec4 normal = vec4(normalize(vTangentToWorld * ((texture(normalTextureSampler, vTexcoord)).rgb * 2.0 - 1.0)), 0.0);
	fColor = (ambient + diffuse + specular/* + normal*/);
}
