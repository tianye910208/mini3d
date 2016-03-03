
// Copyright (c) <2011> Daniel Peterson
// This file is part of Mini3D <www.mini3d.org>
// It is distributed under the MIT Software License <www.mini3d.org/license.php>


// ---------- BASIC OPENGL VERTEX SHADER --------------------------------------

char* vertexShaderGLSL = (char*) 

    "#ifdef GL_ES \n"
    "#ifdef GL_FRAGMENT_PRECISION_HIGH \n"
    "precision highp float; \n"
    "#else \n"
    "precision mediump float; \n"
    "#endif \n"
    "#endif \n"


    "uniform mat4 modelViewProj;"

    "attribute vec4 IN_position;"
    "attribute vec4 IN_color;"
    "attribute vec2 IN_texCoords;"

    "varying vec4 PS_color;"
    "varying vec2 PS_texCoords;"

    "void main()"
    "{"
    "    gl_Position = IN_position * modelViewProj;"
    "    PS_color = IN_color;"
    "    PS_texCoords = IN_texCoords;"
    "}"
; 


// ---------- BASIC OPENGL PIXEL SHADER ---------------------------------------

char* pixelShaderGLSL = (char*)

    "#ifdef GL_ES \n"
    "#ifdef GL_FRAGMENT_PRECISION_HIGH \n"
    "precision highp float; \n"
    "#else \n"
    "precision mediump float; \n"
    "#endif \n"
    "#endif \n"


    "uniform sampler2D texture0;"

    "varying vec4 PS_color;"
    "varying vec2 PS_texCoords;"

    "void main()"
    "{"
    "    gl_FragColor = PS_color * texture2D(texture0, PS_texCoords);"
    "}"
;


// ---------- BASIC DIRECTX VERTEX SHADER --------------------------------------

char* vertexShaderHLSL = (char*)

    "float4x4 modelViewProj : register(c0);"
    "texture texture0;"

    "struct data"
    "{"
    "    float4 position   : POSITION;"
    "    float4 color      : TEXCOORD;"
    "    float2 tex0       : TEXCOORD1;"
    "};"

    "void main( in data IN, out data PS )"
    "{"
    "    PS.position = mul(IN.position, modelViewProj);"
    "     PS.color = IN.color;"
    "    PS.tex0 = IN.tex0;"
    "}"
; 


// ---------- BASIC DIRECTX PIXEL SHADER ---------------------------------------

char* pixelShaderHLSL = (char*)

    "sampler2D texture0 : register(s0);"

    "struct v2p"
    "{"
    "    float4 position    : POSITION;"
    "    float4 color       : TEXCOORD;"
    "    float2 tex0        : TEXCOORD1;"
    "};"

    "void main( in v2p PS, out float4 pixel_color : COLOR0 )"
    "{"
    "    pixel_color =  PS.color * tex2D(texture0, PS.tex0);"
    "}"
;

