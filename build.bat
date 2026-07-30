@echo off
chcp 65001

echo 初始化...
cd /d D:\C++\RPG_Game
rmdir /s /q build
mkdir build
cd build

echo 初始化完成，开始构建...
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER=D:/MinGW/mingw64/bin/gcc.exe -DCMAKE_CXX_COMPILER=D:/MinGW/mingw64/bin/g++.exe

echo 构建完成，开始编译...
D:\MinGW\mingw64\bin\mingw32-make.exe

echo 编译完成！开始运行
.\bin\RPG_Game.exe