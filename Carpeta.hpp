#include "File.hpp"
#include <string>
#include <vector>

using namespace std;

class Carpeta : public File{
    private:
        vector<File> archivos;
        vector<Carpeta> carpetas;
        vector<Carpeta> contenedor;
    public:
        Carpeta();
        Carpeta(string n, string d, int t);
        void addArchivo(File x);
        File getArchivo(int x);
        void setArchivos(vector<File> a);
        vector<File> getArchivos();
        void addCarpeta(Carpeta x);
        vector<Carpeta> getCarpetas();
        void setContenedor(Carpeta x);
        Carpeta getContenedor();
};