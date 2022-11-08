#version 300 es
precision mediump float;

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
layout(location = 2) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vPosition_vs;
out vec3 vNormal_vs;
out vec2 vTexCoords;

void main(){
    // Passage en coordonnées homogènes
    vec4 hPosition = vec4(aVertexPosition, 1);
    vec4 hNormal = vec4(aVertexNormal, 0);

    // Application de la MVP sur la position et de la (MV-1)T sur la normal
    vPosition_vs = vec3(uMVMatrix * hPosition);
    vNormal_vs = vec3(uNormalMatrix * hNormal);
    vTexCoords = aVertexTexCoords;

    gl_Position = uMVPMatrix * hPosition;
}