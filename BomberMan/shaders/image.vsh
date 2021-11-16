attribute highp vec4 vertex;
attribute highp vec4 texCoord;
uniform mediump mat4 matrix;
varying highp vec4 frag_pos;
varying highp vec4 texc;

void main(void)
{
	texc = texCoord;
	frag_pos = matrix * vertex;
	gl_Position = frag_pos;
}
