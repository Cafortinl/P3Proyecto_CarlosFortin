#pragma once
#include <string>

using namespace std;

class Carpeta;

class File{
    private:
        int tipo;
        string nombre, direccion;
        Carpeta* contenedor;
    public:
        File();
        File(string n, string d, int t);
        void setNombre(string x);
        string getNombre();
        void setDireccion(string x);
        string getDireccion();
        void setTipo(int x);
        int getTipo();
        void setContenedor(Carpeta* x);
        Carpeta* getContenedor();
};