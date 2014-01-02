#version 330
out vec4 outputColor;
void main()
{
    float lerpValue = (gl_FragCoord.y) / 1000.0f;

    vec4 white      = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    vec4 darkgray   = vec4(0.2f, 0.2f, 0.2f, 1.0f);
	vec4 red		= vec4(1.0f, 0.0f, 0.0f, 0.0f);
	vec4 green		= vec4(0.0f, 1.0f, 0.0f, 0.0f);
	vec4 blue		= vec4(0.0f, 0.0f, 1.0f, 0.0f);

    outputColor = mix(white, blue, lerpValue);
}
