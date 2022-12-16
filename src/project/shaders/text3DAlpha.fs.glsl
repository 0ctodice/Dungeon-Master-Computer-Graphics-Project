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

float tintPow=.8f;

float rand(vec2 col){
    return fract(sin(dot(col,col.yx))*1.);
}

float random(vec2 st){
    return fract(sin(dot(st.xy,vec2(12.9898,78.233)))*43758.5453123);
}

void main(){
    // float light=min(1.f/pow(distance(uLightPos,vPosition_vs),2.f),1.f);
    float light=min(1.f/pow(distance(uLightPos,vPosition_vs),2.f),1.f);
    vec4 textColor=texture(uTexture,vTexCoords.xy);
    fFragColor=vec4(light*mix(c2,textColor.xyz,tintPow),textColor.w);
    // fFragColor=vec4(light*textColor.xyz,textColor.w);
    // fFragColor=vec4(light*mix(textColor.xyz,mix(c3,c2,textColor.y),tintPow),textColor.w);
}