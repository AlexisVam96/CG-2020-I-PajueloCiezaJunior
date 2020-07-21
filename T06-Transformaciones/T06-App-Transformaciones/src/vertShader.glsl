

#version 330
layout (location = 1) in vec3 vColor;
layout (location = 0) in vec3 vPosition;
uniform mat4 model; 
out vec4 vertexColor;
void main()
{	
	gl_Position = model * vec4(0.45 * vPosition.x, 0.45 * vPosition.y , 0.45 * vPosition.z ,1.0);
	vertexColor = vec4(vColor,1.0); }