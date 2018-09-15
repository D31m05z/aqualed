#!/bin/bash

cmake -DCMAKE_INSTALL_PREFIX=install -Hglm -Bbuild/glm
cmake --build build/glm --target install

cmake -DCMAKE_INSTALL_PREFIX=install -Hglfw -Bbuild/glfw
cmake --build build/glfw --target install

cmake -DCMAKE_INSTALL_PREFIX=install -Himgui -Bbuild/imgui
cmake --build build/imgui --target install
