#version 410 core

in vec3 vN;
in vec3 vL;
in vec3 vV;
in vec3 vR;
in vec2 vT;

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
	vec3 emission_ = emission;

	vec3 ambient_ = ambient * texture(ambientTextureSampler, vT).rgb;

	float diffuseLight = max(dot(vN, vL), 0.0);

	vec3 diffuse_ = diffuseLight * diffuse * texture(diffuseTextureSampler, vT).rgb;

	float specularLight = 0.0;

	if (diffuseLight <= 0)
	{
		specularLight = 0.0;
	}
	else
	{
		specularLight = pow(max(dot(vR, vV), 0.0), shininess);
	}

	vec3 specular_ = specularLight * specular * texture(specularTextureSampler, vT).rgb;

	fColor = (vec4(emission_ + ambient_ + diffuse_ + specular_, 1.0));
}
