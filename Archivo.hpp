#include "File.hpp"
#include <string>

using namespace std;

class Archivo : public File{
    public:
        Archivo();
        Archivo(string n, string d, int t);
};