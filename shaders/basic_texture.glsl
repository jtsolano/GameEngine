#stage vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUv;

out vec2 vUv;   // output to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vUv = aUv;
}

#stage fragment
#version 330 core

in vec2 vUv;     // must match vertex shader's out (type + name)
out vec4 FragColor;

uniform sampler2D ourTexture;


void main()
{
	FragColor = texture(ourTexture, vUv);
}