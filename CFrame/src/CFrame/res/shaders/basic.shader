#shader vertex
#version 410 core
layout(location = 0)in vec4 position;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_MVP;
uniform vec2 u_Center;
uniform float u_ZIndex;
out vec4 fragPos;
out vec2 v_TexCoord;

void main()
{
   gl_Position = u_MVP *  vec4(position.x, position.y, u_ZIndex, 1.0);
   fragPos = position;
   v_TexCoord = texCoord;

};

#shader fragment
#version 410 core
out vec4 color;
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform vec4 u_Color2;
uniform vec4 u_BorderColor1;
uniform vec4 u_BorderColor2;
uniform float u_Time;
uniform float u_Speed;
uniform float u_BorderThickness;
 // Bottom-left corner of the rectangle (x, y)
uniform vec2 u_RectMin;      
// Top-right corner of the rectangle (x, y)
uniform vec2 u_RectMax;       
//Radius
uniform float u_BottomRight;
uniform float u_BottomLeft;
uniform float u_TopRight;
uniform float u_TopLeft;
uniform float u_BorderRight;
uniform float u_BorderLeft;
uniform float u_BorderTop;
uniform float u_BorderBottom;
uniform sampler2D u_Texture;
uniform float u_Angle;
uniform bool u_HasTexture;

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

 float selectBorderThickness(vec2 p, vec2 b) {
    float dx = abs(p.x) - b.x;
    float dy = abs(p.y) - b.y;

    // Determine which edge we're nearest
    if (dx > dy) {
        // Closer to LEFT or RIGHT
        return (p.x > 0.0) ?  u_BorderLeft : u_BorderRight;
    } else {
        // Closer to TOP or BOTTOM
        return (p.y > 0.0) ? u_BorderBottom: u_BorderTop;
    }
}

void main()
{

    // Transform the coordinate space  relative to the rect ( Center of the rect = 0,0)
    //by substracting the centre of the rect from the fragments position
	vec2 center = (u_RectMin + u_RectMax) * 0.5;

    // Compute the local coordinates relative to the center of the rectangle
    vec2 p = fragPos.xy - center;

    // Apply the rotation matrix
    float angleInRadians = -u_Angle * 3.14159265359 / 180.0;

   // Apply the rotation matrix
   float cosAngle = cos(angleInRadians);
   float sinAngle = sin(angleInRadians);
   vec2 rotatedP = vec2(
      cosAngle * p.x - sinAngle * p.y,
      sinAngle * p.x + cosAngle * p.y
    );
    // Use the rotated coordinates
    p = rotatedP;
    // Half the width and the height to define rect bound in the new coord system ( Center of the rect = 0,0)
    vec2 b = (u_RectMax - u_RectMin) * 0.5;
    // Radius for all corners
    vec4 r = vec4(u_BottomRight , u_TopRight, u_BottomLeft, u_TopLeft); //Bottom right, top right, bottom left, top left

    // Compute signed distance from the fragment to the rounded box

    float thickness = selectBorderThickness(p, b);
    float dist = sdRoundedBox(p, b, r) + thickness ;

     // Normalize the coordinate for gradient effect 
    float gradient = (p.x + b.x + sin(u_Time * u_Speed) * b.x * 0.5) / (2.0 * b.x); // Horizontal gradient

    // Define gradient colors
    vec4 color1 = u_Color;
    vec4 color2 = u_Color2; 
    vec4 borderColor1 = u_BorderColor1;
    vec4 borderColor2 = u_BorderColor2;

    // Interpolate between the colors
    vec4 gradientColor = mix(color1, color2, gradient);
    vec4 gradientBorderColor = mix(borderColor1, borderColor2, gradient);
    vec4 texColor = texture(u_Texture, v_TexCoord);
    
    // If the distance is negative or zero, we're inside the box, color the fragment
     if (dist < 0.0) {
        // Inside the shape
        if(u_HasTexture){
            color = texColor;
        }else{
            color = gradientColor;
        }
        
    } else if (dist <  thickness) {
        // Border area
        color = gradientBorderColor;
    } else {
        // Outside
        discard;
    }
};