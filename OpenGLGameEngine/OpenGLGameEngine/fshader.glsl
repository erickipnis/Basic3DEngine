#version 330

in vec3 L;
in vec3 E;
in vec3 H;
in vec3 N;

in vec4 color;

in vec2 textureCoord;

out vec4 glFragColor;

uniform sampler2D imageTexture;


void main()
{
	vec4 hue = texture(imageTexture, textureCoord);

	vec3 ambient = hue.rgb * vec3(.1);
	vec3 diffuse = hue.rgb * vec3(.8) * max(dot(N, L), 0.0);
	vec3 specular = vec3(1) * vec3(.1) * pow(max(dot(N, H), 0.0), 75.0);
	
	glFragColor = vec4((ambient + diffuse + specular), hue.a); 
}
