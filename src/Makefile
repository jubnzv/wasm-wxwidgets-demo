all: wx web

wx:
	/usr/bin/clang++ -c -o GraphicsEngine.o -c GraphicsEngine.cpp
	/usr/bin/clang++ -c `wx-config --cxxflags` -o FrontendWx.o -c FrontendWx.cpp
	/usr/bin/clang++ `wx-config --libs std,gl` -lGL -lGLEW -o wx FrontendWx.o GraphicsEngine.o

web:
	em++ GraphicsEngine.cpp -std=c++11 -O2 -s WASM=1 -o GraphicsEngine_wasm.o
	em++ FrontendWasm.cpp -std=c++11 -O2 -s WASM=1 -s USE_GLFW=3 -o FrontendWasm.o
	# em++ -std=c++11 -O2 FrontendWasm.o GraphicsEngine_wasm.o -o ../static/test.html -lglfw -s WASM=1 -s USE_GLFW=3
	em++ -std=c++11 -O2 FrontendWasm.o GraphicsEngine_wasm.o -o ../static/index.js -lglfw -s WASM=1 -s USE_GLFW=3

clean:
	rm -f *.o
	rm -f wx
	rm -f ../static/index.js
	rm -f ../static/test.html
	rm -f ../static/index.wasm
