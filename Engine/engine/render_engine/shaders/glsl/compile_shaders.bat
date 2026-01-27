@echo off
REM Compile vertex shader
glslc -fshader-stage=vert vertex_shader.glsl -o ../../../../../SPIR-V/vert.spv

REM Compile fragment shader
glslc -fshader-stage=frag fragment_shader.glsl -o ../../../../../SPIR-V/frag.spv

echo Shaders compiled successfully.
