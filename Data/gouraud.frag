//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C2E2f_passthrough
//

#version 410 core

in vec4 vColor;

out vec4 fColor;

void main()
{
	fColor = vColor;
}
