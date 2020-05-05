#include "File.hpp"
#include <string>

using namespace std;

File::File(){
}

File::File(string n, string d, int t){
    nombre = n;
    direccion = d;
    tipo = t;
}

void File::setNombre(string x){
    nombre = x;
}

string File::getNombre(){
    return nombre;
}

void File::setDireccion(string x){
    direccion = x;
}

string File::getDireccion(){
    return direccion;
}

void File::setTipo(int x){
    tipo = x;
}

int File::getTipo(){
    return tipo;
}

void File::setContenedor(Carpeta* x){
    contenedor = x;
}

Carpeta* File::getContenedor(){
    return contenedor;
}