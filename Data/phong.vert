//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C5E2v_fragmentLighting
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

uniform sampler2D normalTextureSampler;

out vec4 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

void main()
{
	vPosition = perspective * modelView * vec4(position, 1.0);
	gl_Position = vPosition;

	mat3 vTangentToWorld = mat3(normalize(norm * tangent), normalize(norm * bitangent), normalize(norm * normal));
	vNormal = normalize(vTangentToWorld * ((texture(normalTextureSampler, texcoord)).rgb * 2.0 - 1.0));

	vTexcoord = texcoord;
}
