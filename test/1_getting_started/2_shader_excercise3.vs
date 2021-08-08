#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 ourColor;

void main(){
    gl_Position = vec4(aPos, 1.0);
    ourColor = vec3(aPos);  // 顶点颜色等于顶点位置
}
