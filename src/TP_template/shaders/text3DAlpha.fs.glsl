// #version 300 es
// precision mediump float;
#version 330 core

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec3 vTexCoords;

uniform sampler2D uTexture;
uniform vec3 uLightPos;

out vec4 fFragColor;

vec3 tint=vec3(109.f/255.f,48.f/255.f,194.f/255.f);

vec2 uv=vPosition_vs.xy/vec2(1920,1080);
float tintPow=.5f;

vec3 c1=vec3(.4039,.349,.8235);
vec3 c2=vec3(.8235,.349,.349);

void main(){
    float light=min(1.f/pow(distance(uLightPos,vPosition_vs),2.f),1.f);
    vec4 textColor=texture(uTexture,vTexCoords.xy);
    fFragColor=vec4(light*mix(textColor.xyz,mix(c1,c2,textColor.y),tintPow),textColor.w);
}