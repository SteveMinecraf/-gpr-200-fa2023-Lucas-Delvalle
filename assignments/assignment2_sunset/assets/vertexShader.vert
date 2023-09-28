#version 450
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUV;
out vec2 fragUV;
void main() {
    fragUV = vUV; 
    gl_Position = vec4(vPos, 1.0);
}