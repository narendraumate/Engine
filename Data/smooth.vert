#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;
layout( location = 3 ) in vec3 tangent;
layout( location = 4 ) in vec3 bitangent;

uniform mat3 norm;
uniform mat4 modelViewPerspective;
//uniform mat4 modelViewOrthographic;

uniform sampler2D normalTextureSampler;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

void main()
{
	gl_Position = modelViewPerspective * vec4(position, 1.0);
	vPosition = gl_Position.xyz;
	vTexcoord = texcoord;

//#if defined (USE_NORMALS)
	vNormal = normalize(norm * normal);
//#else
//	mat3 vTangentToWorld = mat3(normalize(norm * tangent), normalize(norm * bitangent), normalize(norm * normal));
//	vNormal = normalize(vTangentToWorld * ((texture(normalTextureSampler, texcoord)).rgb * 2.0 - 1.0));
//#endif defined // (USE_NORMALS)

}
