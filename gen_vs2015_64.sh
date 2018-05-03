mkdir -p build
cd build
cmake .. \
	-G "Visual Studio 14 2015 Win64" \
	-Dglfw3_DIR:PATH="C:/Program Files/GLFW/lib/cmake/glfw3"