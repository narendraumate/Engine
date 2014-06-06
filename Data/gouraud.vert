//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C5E1v_basicLight
//

#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;
layout( location = 3 ) in vec3 tangent;
layout( location = 4 ) in vec3 bitangent;

//uniform mat4 model;
//uniform mat4 view;
uniform mat4 modelView;
uniform mat3 norm;
uniform mat4 perspective;
//uniform mat4 orthographic;

out vec4 vColor;

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
	vec3 eyePosition = vec3(0.0, 0.0, 30.0);

	vec4 vPosition = perspective * modelView * vec4(position, 1.0);
	gl_Position = vPosition;

	vec3 P = vPosition.xyz;

#if defined (USE_NORMALS)
	vec3 N = normalize(norm * normal);
#else
	mat3 vTangentToWorld = mat3(normalize(norm * tangent), normalize(norm * bitangent), normalize(norm * normal));
	vec3 N = normalize(vTangentToWorld * ((texture(normalTextureSampler, texcoord)).rgb * 2.0 - 1.0));
#endif defined // (USE_NORMALS)

	vec3 emission_ = emission;

	vec3 ambient_ = ambient * texture(ambientTextureSampler, texcoord).rgb;

	vec3 L = normalize(eyePosition - P);

	float diffuseLight = max(dot(N, L), 0);

	vec3 diffuse_ = diffuse * texture(diffuseTextureSampler, texcoord).rgb * diffuseLight;

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

	vec3 specular_ = specular * texture(specularTextureSampler, texcoord).rgb * specularLight;

	vColor = vec4(emission_ + ambient_ + diffuse_ + specular_, 1);
}
