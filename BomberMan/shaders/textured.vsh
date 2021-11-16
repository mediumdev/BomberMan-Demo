attribute highp vec4 vertex;
attribute highp vec4 texCoord;
uniform mediump mat4 matrix;
uniform mediump mat4 proj;
varying highp vec4 frag_pos;
varying highp vec4 texc;

void main(void)
{
	texc = texCoord;
	frag_pos = matrix * vertex;
	gl_Position = proj * frag_pos;
}