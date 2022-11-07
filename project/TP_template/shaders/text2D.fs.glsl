#version 300 es
precision mediump float;

in vec3 vFragColor;
in vec2 vFragTextureCoord;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main(){
    fFragColor = (texture(uTexture, vFragTextureCoord)).xyz;
}