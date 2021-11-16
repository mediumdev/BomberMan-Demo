uniform mediump vec4 color;
varying highp vec4 frag_pos;
varying highp vec4 texc;
uniform sampler2D tex;

void main(void)
{
	gl_FragColor = (texture2D(tex, texc.st).rgba) * color;
}
