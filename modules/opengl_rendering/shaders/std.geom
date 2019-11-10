#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;
in vec3 vPos[];
out vec3 normal;
out vec3 fragPos;

void main(void)
{
    vec3 a = (vPos[1] - vPos[0]).xyz;
    vec3 b = (vPos[2] - vPos[0]).xyz;
    vec3 N = normalize(cross(b, a));

    for (int i=0; i < gl_in.length(); ++i) {
        gl_Position = gl_in[i].gl_Position;
        normal = N;
        EmitVertex();
    }

    EndPrimitive();
}
