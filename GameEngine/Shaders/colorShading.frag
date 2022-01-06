#version 400 core
//The fragment shader operates on each pixel in a given polygon

in vec2 fragPosition;
in vec4 fragColor;
in vec2 fragUV;

//This is the 3 component float vector that gets outputted to the screen for each pixel.
out vec4 color;

//uniform float time;
uniform sampler2D mySampler;

void main(){
	//Just hardcode the color to red
	//color = fragColor.rgb;
	//color = fragColor + vec4(1.0 * (cos(time)+1.0)*0.5, 1.0 * (cos(time+2.0)+1.0)*0.5, 
													//1.0 * (sin(time+1.0)+1.0)*0.5, 1.0);
	vec4 textureColor = texture(mySampler, fragUV);												
	//color = vec4(fragColor.r * (cos(fragPosition.x * 4.0 + time) + 1.0) * 0.5,
				//fragColor.g * (cos(fragPosition.y * 8.0 + time) + 1.0) * 0.5,
				//fragColor.b * (cos(fragPosition.x * 4.0 + time) + 1.0) * 0.5, fragColor.a) + textureColor;
	color = fragColor * textureColor;
	
}