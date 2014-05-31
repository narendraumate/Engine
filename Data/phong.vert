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

uniform sampler2D normalTextureSampler;

out vec3 vN;
out vec3 vL;
out vec3 vV;
out vec2 vT;

void main()
{
	// Light Properties
	vec3 light_position = vec3(0.0, 0.0, 5.0);

	vec4 P = modelView * vec4(position, 1.0);

	//vN = normalize(mat3(modelView) * normal);
	// OR
	//vN = normalize(norm * normal);

	vec3 vNormal = normalize(mat3(model) * normal);
	vec3 vTangent = normalize(mat3(model) * tangent);
	vec3 vBitangent = normalize(mat3(model) * bitangent);
	mat3 vTangentToWorld = mat3(vTangent, vBitangent, vNormal);
	vN = normalize(vTangentToWorld * ((texture(normalTextureSampler, texcoord)).rgb * 2.0 - 1.0));

	vL = normalize(light_position - P.xyz);

	vV = normalize(-P.xyz);

	vT = texcoord;

	gl_Position = perspective * P;
}
