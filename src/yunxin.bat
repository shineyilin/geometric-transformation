taskkill /F /IM pro.exe 
del pro.exe
g++ *.cpp -lgraphics -lgdi32 -limm32 -lmsimg32 -lole32 -loleaut32 -lwinmm -luuid -mwindows -o pro.exe

start pro.exe