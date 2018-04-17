#version 330 core
uniform vec4 ourColor;

out vec4 FragColor;

void main()
{
    //FragColor = vec4(ourColor, 1.0);
	FragColor = ourColor;
}
