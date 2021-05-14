build:
	gcc -Wfatal-errors \
	-std=c99 \
	./*.c \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-o renderer1.exe

run:
	start ./renderer.exe

clean:
	rm renderer.exe