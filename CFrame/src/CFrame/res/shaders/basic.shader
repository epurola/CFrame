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
uniform vec4 u_Color2;
uniform float u_Time;
uniform float u_Speed;
uniform float u_BorderThickness;
 // Bottom-left corner of the rectangle (x, y)
uniform vec2 u_RectMin;      
// Top-right corner of the rectangle (x, y)
uniform vec2 u_RectMax;       
uniform float u_Radius;

in vec4 fragPos;

float sdRoundedBox(in vec2 p, in vec2 b, in vec4 r)
{
    //choose which set of corner radii to apply, 
    //based on the x position of the point p relative to the origin of the box
    r.xy = (p.x > 0.0) ? r.xy : r.zw;
    r.x  = (p.y > 0.0) ? r.x  : r.y;
    //This shifts the coordinates from being relative to the center of the box 
    //to being relative to the box's edges
    vec2 q = abs(p) - b + r.x;
    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - r.x;
}

void main()
{
    // Transform the coordinate space  relative to the rect ( Center of the rect = 0,0)
    //by substracting the centre of the rect from the fragments position
	vec2 p = fragPos.xy - (u_RectMin + u_RectMax) * 0.5; 
    // Half the width and the height to define rect bound in the new coord system ( Center of the rect = 0,0)
    vec2 b = (u_RectMax - u_RectMin) * 0.5;
    // Radius for all corners
    vec4 r = vec4(u_Radius, u_Radius, u_Radius, u_Radius); 

    // Compute signed distance from the fragment to the rounded box
    float dist = sdRoundedBox(p, b, r) + u_BorderThickness;

     // Normalize the coordinate for gradient effect 
    float gradient = (p.x + b.x + sin(u_Time * u_Speed) * b.x * 0.5) / (2.0 * b.x); // Horizontal gradient

    // Define gradient colors
    vec4 color1 = u_Color;
    vec4 color2 = u_Color2; 
    vec4 borderColor = vec4(0.0, 0.0, 0.0, 1.0);


    // Interpolate between the colors
    vec4 gradientColor = mix(color1, color2, gradient);

    // If the distance is negative or zero, we're inside the box, color the fragment
     if (dist < -u_BorderThickness) {
        // Inside the shape
        color = gradientColor;
    } else if (dist < u_BorderThickness) {
        // Border area
        color = borderColor;
    } else {
        // Outside
        discard;
    }
};