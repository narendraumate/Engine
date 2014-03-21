#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

uniform sampler2D diffuseTextureSampler;

out vec4 fColor;

void main()
{	
	//fColor = vec4(vNormal, 1.0);
	fColor = texture(diffuseTextureSampler, vTexCoord);
}
