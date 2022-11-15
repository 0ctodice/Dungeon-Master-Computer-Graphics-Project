// #version 300 es
// precision mediump float;
#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec3 vTexCoords;

uniform sampler2D uTexture;
uniform vec3 uLightPos;

out vec4 fFragColor;

void main(){
    float light = 1.f / distance(uLightPos,vPosition_vs);
    vec4 textColor = texture(uTexture, vTexCoords.xy);
    fFragColor = vec4(light*textColor.xyz, textColor.w);
}