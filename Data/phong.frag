//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C5E3f_basicLight
//

#version 410 core

in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;

out vec4 fColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
//uniform vec3 transmittance;
uniform vec3 emission;
uniform float shininess;
//uniform float ior;
uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;

void main()
{
	vec3 eyePosition = vec3(0.0, 0.0, 30.0);

	vec3 P = vPosition.xyz;

	vec3 N = normalize(vNormal);

	vec3 emission_ = emission;

	vec3 ambient_ = ambient * texture(ambientTextureSampler, vTexcoord).rgb;

	vec3 L = normalize(eyePosition - P);

	float diffuseLight = max(dot(N, L), 0);

	vec3 diffuse_ = diffuse * texture(diffuseTextureSampler, vTexcoord).rgb * diffuseLight;

	vec3 V = normalize(eyePosition - P);

	vec3 H = normalize(L + V);

	float specularLight = 0.0;

	if (diffuseLight <= 0.0)
	{
		specularLight = 0.0;
	}
	else
	{
		specularLight = pow(max(dot(N, H), 0), shininess);
	}

	vec3 specular_ = specular * texture(specularTextureSampler, vTexcoord).rgb * specularLight;

	fColor = vec4(emission_ + ambient_ + diffuse_ + specular_, 1);
}
