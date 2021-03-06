#version 400 core
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition; 
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragPosition;
out vec4 fragColor;
out vec2 fragUV;

uniform mat4 P;

void main(){
	//Set the x,y position on the screen
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	//The z position is zero since we are in 2D
	gl_Position.z = 0.0;
	//Indicate that the coordinates are normalized
	gl_Position.w = 1.0;
	
	fragPosition = vertexPosition;
	fragColor = vertexColor;
	fragUV = vec2(vertexUV.x, 1.0-vertexUV.y);
}