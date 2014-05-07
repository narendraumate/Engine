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

out vec3 vN;
out vec3 vL;
out vec3 vV;
out vec2 vT;

void main()
{
	// Light Properties
	vec3 light_position = vec3(0.0, 10.0, 10.0);

	vec4 P = modelView * vec4(position, 1.0);

	//vN = normalize(mat3(modelView) * normal);
	// OR
	vN = normalize(norm * normal);

	vL = normalize(light_position - P.xyz);

	vV = normalize(-P.xyz);

	vT = texCoord;

	gl_Position = perspective * P;
}
