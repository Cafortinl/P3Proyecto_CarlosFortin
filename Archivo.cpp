#include "File.hpp"
#include "Archivo.hpp"
#include <string>

using namespace std;

Archivo::Archivo(){
}

Archivo::Archivo(string n, string d, int t) : File(n,d,t){
}