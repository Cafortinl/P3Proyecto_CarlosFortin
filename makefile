add:
	g++ terminal.cpp \
	File.cpp \
	Carpeta.cpp \
	Archivo.cpp \
	-lncurses \
	-o terminal
clean:
	rm terminal
