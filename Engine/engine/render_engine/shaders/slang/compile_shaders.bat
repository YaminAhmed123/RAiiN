@echo off
REM Compile the fragment shader
slangc fragment_shader.slang -target spirv -stage fragment -entry main -profile spirv_1_3 -o ../../../../../SPIR-V/frag.spv
IF ERRORLEVEL 1 (
    echo Failed to compile fragment shader!
    pause
    exit /b 1
)

REM Compile the vertex shader
slangc vertex_shader.slang -target spirv -stage vertex -entry main -profile spirv_1_3 -o ../../../../../SPIR-V/vert.spv
IF ERRORLEVEL 1 (
    echo Failed to compile vertex shader!
    pause
    exit /b 1
)

echo Shaders compiled successfully!
