#version 460 core

#define max_points 128

out vec4 fragment_color;

uniform int width;
uniform int height;
uniform int points_count;
uniform float points_size;
uniform vec4 points_color;
uniform vec2 points[max_points];

void main(void)
{
	//data
	bool test = false;
	const float w = float(width);
	const float h = float(height);
	const float x1 = (2 * gl_FragCoord.x - w) / min(w, h);
	const float x2 = (2 * gl_FragCoord.y - h) / min(w, h);
	//points
	for(uint i = 0; i < points_count; i++)
	{
		if(length(vec2(x1, x2) - points[i]) < points_size)
		{
			test = true;
			break;
		}
	}
	//fragment
	if(!test) discard;
	fragment_color = vec4(points_color);
}