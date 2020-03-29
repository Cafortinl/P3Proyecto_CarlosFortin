#include "File.hpp"
#include "Carpeta.hpp"
#include <string>
#include <vector>

using namespace std;

Carpeta::Carpeta(){
}

Carpeta::Carpeta(string n, string d, int t) : File(n,d,t){
}

void Carpeta::addArchivo(File x){
    archivos.push_back(x);
}

File Carpeta::getArchivo(int x){
    if(x < archivos.size())
        return archivos[x];
}

void Carpeta::setArchivos(vector<File> a){
    archivos = a;
}

vector<File> Carpeta::getArchivos(){
    return archivos;
}

void Carpeta::addCarpeta(Carpeta x){
    carpetas.push_back(x);
}

vector<Carpeta> Carpeta::getCarpetas(){
    return carpetas;
}

void Carpeta::setContenedor(Carpeta x){
    contenedor.push_back(x);
}

Carpeta Carpeta::getContenedor(){
    return contenedor[0];
}