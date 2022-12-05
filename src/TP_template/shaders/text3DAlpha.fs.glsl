// #version 300 es
// precision mediump float;
#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec3 vTexCoords;

uniform sampler2D uTexture;
uniform vec3 uLightPos;

out vec4 fFragColor;

vec3 c1=vec3(.4039,.349,.8235);
vec3 c2=vec3(.8235,.349,.349);
vec3 c3=vec3(.8235,.8235,.349);

float tintPow=.3f;

void main(){
    float light=min(1.f/pow(distance(uLightPos,vPosition_vs),2.f),1.f);
    vec4 textColor=texture(uTexture,vTexCoords.xy);
    fFragColor=vec4(light*mix(textColor.xyz,mix(c3,c2,textColor.y),tintPow),textColor.w);
}