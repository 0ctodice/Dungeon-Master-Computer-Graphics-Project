#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec3 vTexCoords;

uniform sampler2D uTexture;

out vec4 fFragColor;

void main(){
    fFragColor = texture(uTexture, vTexCoords.xy);
}