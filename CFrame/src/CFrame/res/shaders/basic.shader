#shader vertex
#version 410 core
layout(location = 0)in vec4 position;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_MVP;
out vec4 fragPos;
void main()
{
   gl_Position = u_MVP * position  ;
   fragPos = position;
};

#shader fragment
#version 410 core
out vec4 color;
uniform vec4 u_Color;

uniform vec2 u_RectMin;       // Bottom-left corner of the rectangle (x, y)
uniform vec2 u_RectMax;       // Top-right corner of the rectangle (x, y)
uniform float u_Radius;

in vec4 fragPos;

float sdRoundedBox(in vec2 p, in vec2 b, in vec4 r)
{
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x  = (p.y > 0.0) ? r.x  : r.y;
    vec2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

void main()
{
	vec2 p = fragPos.xy - (u_RectMin + u_RectMax) * 0.5; // Transform to box center space
    vec2 b = (u_RectMax - u_RectMin) * 0.5; // Half of the box size
    vec4 r = vec4(u_Radius, u_Radius, u_Radius, u_Radius); // Radius for all corners

    // Compute signed distance from the fragment to the rounded box
    float dist = sdRoundedBox(p, b, r);

    // If the distance is negative or zero, we're inside the box, color the fragment
    if (dist < 0.0)
    {
        color = u_Color;
    }
    else
    {
        discard; // Discard fragments outside the rounded box
    }
};