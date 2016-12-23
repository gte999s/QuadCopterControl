@echo off
set COMPILER=gcc
				set COMPFLAGS=-c -fexceptions -fno-omit-frame-pointer -DMATLAB_MEX_FILE  -DMATLAB_MEX_FILE  
				set OPTIMFLAGS=-O -DNDEBUG 
				set DEBUGFLAGS=-g 
				set LINKER=gcc 
				set LINKFLAGS=-m64 -Wl,--no-undefined -shared -L"C:\Program Files\MATLAB\R2015b\extern\lib\win64\mingw64" -llibmx -llibmex -llibmat -lm -llibmwlapack -llibmwblas -Wl,"C:\Program Files\MATLAB\R2015b/extern/lib/win64/mingw64/mexFunction.def" 
				set LINKDEBUGFLAGS=-g
				set NAME_OUTPUT=-o "%OUTDIR%%MEX_NAME%%MEX_EXT%"
set PATH=C:\TDM-GCC-64\\bin;C:\Program Files\MATLAB\R2015b\extern\include\win64;C:\Program Files\MATLAB\R2015b\extern\include;C:\Program Files\MATLAB\R2015b\simulink\include;C:\Program Files\MATLAB\R2015b\lib\win64;%MATLAB_BIN%;%PATH%
set INCLUDE=%MW_MINGW64_LOC%\include;;%INCLUDE%
set LIB=%MW_MINGW64_LOC%\lib;;%LIB%
set LIBPATH=C:\Program Files\MATLAB\R2015b\extern\lib\win64;%LIBPATH%

gmake SHELL="cmd" -f QuadSim_sfun.gmk
