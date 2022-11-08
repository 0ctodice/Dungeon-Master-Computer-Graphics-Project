#version 300 es
precision mediump float;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTextureCoord;

out vec3 vFragColor;
out vec2 vFragTextureCoord;

void main(){
    vFragColor = vec3(1.0,0.,0.);
    vFragTextureCoord = aVertexTextureCoord;
    vec2 position = aVertexPosition;
    gl_Position = vec4(position, 0, 1);;
}