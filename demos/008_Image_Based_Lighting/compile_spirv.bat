@echo off
cd assets
IF NOT EXIST "shaders" mkdir "shaders"
cd ..\..\..\
.\extern\vulkan\Bin32\glslc.exe %~dp0assets\glsl_shaders\shader.vert -o %~dp0assets\shaders\vert.spv
.\extern\vulkan\Bin32\glslc.exe %~dp0assets\glsl_shaders\shader.frag -o %~dp0assets\shaders\frag.spv
echo SPIRV compilation complete!
pause