#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texCoord;

//uniform mat4 model;
//uniform mat4 view;
uniform mat4 modelView;
uniform mat3 norm;
uniform mat4 perspective;
//uniform mat4 orthographic;

out vec3 vColor;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
//uniform vec3 transmittance;
//uniform vec3 emission;
uniform float shininess;
//uniform float ior;
uniform sampler2D diffuseTextureSampler;

void main()
{
	// Light Properties
	vec3 light_position = vec3(10.0, 10.0, 10.0);
	float specular_power = 128.0;	//	Same as shininess?

	vec4 P = modelView * vec4(position, 1.0);

	//vec3 N = normalize(mat3(modelView) * normal);
	// OR
	vec3 N = normalize(norm * normal);

	vec3 L = normalize(light_position - P.xyz);

	vec3 V = normalize(-P.xyz);

	vec3 R = reflect(-L, N);

	vec3 ambient_ = ambient;

	vec3 diffuse_ = max(dot(N, L), 0.0) * diffuse;

	vec3 specular_ = pow(max(dot(R, V), 0.0), specular_power) * specular;

	vColor = ambient_ + diffuse_ + specular_;

	gl_Position = perspective * P;
}
