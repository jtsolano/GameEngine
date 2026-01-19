#stage vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;   // output to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vColor = aColor;
}

#stage fragment
#version 330 core

in vec3 vColor;     // must match vertex shader's out (type + name)
out vec4 FragColor;

uniform sampler2D ourTexture;

void main()
{
	vec2 uv = gl_FragCoord.xy / vec2(800.0, 600.0);

	vec4 texColor = texture(ourTexture, uv);

	FragColor = vec4(vColor,1.0);
}