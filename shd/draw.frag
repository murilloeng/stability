#version 460 core

uniform int width;
uniform int height;

out vec4 fragment_color;

vec3 palette[] = vec3[](
	vec3(0.0, 0.0, 0.5),
	vec3(0.0, 0.0, 1.0),
	vec3(0.0, 0.5, 1.0),
	vec3(0.0, 1.0, 1.0),
	vec3(0.5, 1.0, 0.5),
	vec3(1.0, 1.0, 0.0),
	vec3(1.0, 0.5, 0.0),
	vec3(1.0, 0.0, 0.0),
	vec3(0.5, 0.0, 0.0)
);

vec3 color(float s)
{
	s = min(max(s, 0), 1);
	const int n = palette.length();
	const int i = int(floor(n * s));
	const float r = n * s - floor(n * s);
	return (1 - r) * palette[i] + r * palette[i + 1];
}

void main(void)
{
	//data
	const float w = float(width);
	const float h = float(height);
	const float x1 = (2 * gl_FragCoord.x - w) / min(w, h);
	const float x2 = (2 * gl_FragCoord.y - h) / min(w, h);
	//fragment
	fragment_color = vec4(color(gl_FragCoord.y / h), 1);
}