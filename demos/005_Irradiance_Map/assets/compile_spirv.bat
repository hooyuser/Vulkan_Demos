@echo off
IF NOT EXIST "shaders" mkdir "shaders"
cd ..\..\..\
.\extern\vulkan\Bin32\glslc.exe %~dp0glsl_shaders\shader.vert -o %~dp0shaders\vert.spv
.\extern\vulkan\Bin32\glslc.exe %~dp0glsl_shaders\shader.frag -o %~dp0shaders\frag.spv
echo Compilation complete!
pause