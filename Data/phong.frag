#version 410 core

in vec3 vN;
in vec3 vL;
in vec3 vV;
in vec2 vT;

out vec4 fColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
//uniform vec3 transmittance;
//uniform vec3 emission;
uniform float shininess;
//uniform float ior;
uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;

void main()
{
	// Light Properties
	float specular_power = 128.0;	//	Same as shininess?

	vec3 R = reflect(-vL, vN);

	vec3 ambient_ = ambient + texture(ambientTextureSampler, vT).rgb;

	vec3 diffuse_ = max(dot(vN, vL), 0.0) * (diffuse + texture(diffuseTextureSampler, vT).rgb);

	vec3 specular_ = pow(max(dot(R, vV), 0.0), specular_power) * (specular + texture(specularTextureSampler, vT).rgb);

	fColor = vec4(ambient_ + diffuse_ + specular_, 1.0);
}
