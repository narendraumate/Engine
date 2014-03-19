#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fColor;

void main()
{
	//fColor = vec4(1.0, 0.0, 0.0, 1.0);
	fColor = clamp(dot(vec3(1.0, 1.0, 1.0), normalize(vNormal)), 0.0, 1.0) * vec4(0.5, 0.5, 0.5, 1.0);
}
