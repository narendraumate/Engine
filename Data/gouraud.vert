#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;
layout( location = 3 ) in vec3 tangent;
layout( location = 4 ) in vec3 bitangent;

uniform mat4 model;
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
uniform vec3 emission;
uniform float shininess;
//uniform float ior;
uniform sampler2D ambientTextureSampler;
uniform sampler2D diffuseTextureSampler;
uniform sampler2D specularTextureSampler;
uniform sampler2D normalTextureSampler;

void main()
{
	vec3 eyePosition = vec3(0.0, 0.0, 0.0);

	//vec3 N = normalize(mat3(modelView) * normal);
	// OR
	//vec3 N = normalize(norm * normal);

	mat3 vTangentToWorld = mat3(normalize(norm * tangent), normalize(norm * bitangent), normalize(norm * normal));
	vec3 N = normalize(vTangentToWorld * ((texture(normalTextureSampler, texcoord)).rgb * 2.0 - 1.0));

	vec4 P = modelView * vec4(position, 1.0);

	vec3 L = normalize(eyePosition - P.xyz);

	vec3 V = normalize(-P.xyz);

	vec3 R = normalize(reflect(-L, N));

	vec3 emission_ = emission;

	vec3 ambient_ = ambient * texture(ambientTextureSampler, texcoord).rgb;

	float diffuseLight = max(dot(N, L), 0.0);

	vec3 diffuse_ = diffuseLight * diffuse * texture(diffuseTextureSampler, texcoord).rgb;

	float specularLight = 0.0;

	if (diffuseLight <= 0)
	{
		specularLight = 0.0;
	}
	else
	{
		specularLight = pow(max(dot(R, V), 0.0), shininess);
	}

	vec3 specular_ = specularLight * specular * texture(specularTextureSampler, texcoord).rgb;

	vColor = (emission_ + ambient_ + diffuse_ + specular_);

	gl_Position = perspective * P;
}
//http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
//Example 5-3. The C5E3f_basicLight Fragment Program