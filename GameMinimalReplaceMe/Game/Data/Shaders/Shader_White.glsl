// Shader_White.glsl

#ifdef WIN32
#define lowp
#define mediump
#else
precision mediump float;
#endif

#ifdef VertexShader

attribute vec4 a_Position;

uniform mat4 u_WorldViewProj;

void main()
{
    gl_Position = u_WorldViewProj * a_Position;
}

#endif

#ifdef FragmentShader

void main()
{
    gl_FragColor = vec4(1,1,1,1);
}

#endif
