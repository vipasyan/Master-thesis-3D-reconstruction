
#version 330 core
out vec4 frag_color;
in vec3 col;
void main()
{
	frag_color = vec4(col, 1.0f);
}
