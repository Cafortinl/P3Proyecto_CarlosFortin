#include <iostream>
#include <ncurses.h>
#include <vector>
#include <fstream>
#include "File.hpp"
#include "Carpeta.hpp"
#include "Archivo.hpp"

using namespace std;

bool running = true;
Carpeta root("Home", "", 1);
Carpeta actual = root;
char a = ':', b = '~', at = '@';
string usuario = "home"; 
string maquina = "vm_gauss";
string c = "$ ";
int x,y,c_act = 1, pos_y = -1;
char com[150];
string comando;

void transformString(char a[150]);

void commands(){
    bool entro = false;
    bool mover = true;
    string comm, arg;
    if(comando != "exit" && comando != "ls" && comando != "clear" && comando != "cd/"){
        for(int i = 0;i < comando.size();i++){
            if(comando[i] == ' '){
                comm = comando.substr(0,i);
                arg = comando.substr(i+1, comando.size() - i+1);
                entro = true;
                break;
            }
        }
    }else{
        comm = comando;
    }
    if(comm == "clear"){
        clear();
        stdscr = newwin(y, x, 0, 0);
        wbkgd(stdscr, COLOR_PAIR(c_act));
        scrollok(stdscr,TRUE);
        refresh();
        pos_y = -1;
        mover = false;
    }else if(comm == "ls"){
        int cont = 0;
        for(int i = 0;i < actual.getArchivos().size();i++){
            if(cont <= 6){
                if(actual.getArchivos()[i].getTipo() == 1){
                    switch(c_act){
                        case 1:{
                            attron(COLOR_PAIR(7));
                            addstr(actual.getArchivos()[i].getNombre().c_str());
                            addstr("   ");
                            attroff(COLOR_PAIR(7));
                            break;
                        }

                        case 2:{
                            attron(COLOR_PAIR(8));
                            addstr(actual.getArchivos()[i].getNombre().c_str());
                            addstr("   ");
                            attroff(COLOR_PAIR(8));
                            break;
                        }

                        case 3:{
                            attron(COLOR_PAIR(9));
                            addstr(actual.getArchivos()[i].getNombre().c_str());
                            addstr("   ");
                            attroff(COLOR_PAIR(9));
                            break;
                        }
                    }
                    cont++;
                }else{
                    addstr(actual.getArchivos()[i].getNombre().c_str());
                    addstr("   ");
                    cont++;
                }
            }else{
                pos_y++;
                move(pos_y,0);
                if(actual.getArchivos()[i].getTipo() == 1){
                    switch(c_act){
                            case 1:{
                                attron(COLOR_PAIR(7));
                                addstr(actual.getArchivos()[i].getNombre().c_str());
                                attroff(COLOR_PAIR(7));
                                break;
                            }

                            case 2:{
                                attron(COLOR_PAIR(8));
                                addstr(actual.getArchivos()[i].getNombre().c_str());
                                attroff(COLOR_PAIR(8));
                                break;
                            }

                            case 3:{
                                attron(COLOR_PAIR(9));
                                addstr(actual.getArchivos()[i].getNombre().c_str());
                                attroff(COLOR_PAIR(9));
                                break;
                            }
                        }
                        cont = 0;
                }else{
                    addstr(actual.getArchivos()[i].getNombre().c_str());
                    addstr("   ");
                    cont = 0;
                }
            }
        }
    }else if(comm == "cd"){
        bool encontrada = false;
        string nombre = arg;
        if(actual.getCarpetas().size() != 0){
            for(int i = 0;i < actual.getCarpetas().size();i++){
                if(actual.getCarpetas()[i].getNombre() == nombre)
                    actual = actual.getCarpetas()[i];
                    encontrada = true;
                    break;
            }
            if(encontrada){
                mover = false;
            }else{
                addstr("No hay ninguna carpeta con ese nombre");
            }
        }else{
            addstr("Esta carpeta esta vacia");
        }
    }else if(comm == "cd/"){
        if(actual.getNombre() != "Home"){
            actual = actual.getContenedor();
            addstr(actual.getNombre().c_str());
            mover = false;
        }else{
            addstr("Ya esta en la carpeta raiz");
        }
    }else if(comm == "del"){
        string nombre = arg;
        bool existe = false;
        for(int i = 0;i < actual.getArchivos().size();i++){
            if(actual.getArchivos()[i].getNombre() == nombre){
                actual.getArchivos().erase(actual.getArchivos().begin() + i);
                existe = true;
                break;
            }
        }
        if(existe){
            mover = false;
        }else{
            addstr("El archivo no existe");
        }
    }else if(comm == "mkdir"){
        string nombre = arg;
        string dir = actual.getDireccion() + "/" + nombre;
        Carpeta temp(nombre, dir, 1);
        temp.setContenedor(actual);
        actual.addArchivo(temp);
        actual.addCarpeta(temp);
        mover = false;
    }else if(comm == "file"){
        string nombre = arg;
        string dir = actual.getDireccion() + "/" + nombre;
        //fstream fw(nombre, ios::out);
        //fw.open(nombre, ios::out);
        Archivo t(nombre, dir, 2);
        actual.addArchivo(t);
        mover = false;
    }else if(comm == "write"){

    }else if(comm == "read"){

    }else if(comm == "changeColor"){
        if(arg == "black"){
            c_act = 1;
            mover = false;
            wbkgd(stdscr, COLOR_PAIR(c_act));
            refresh();
        }else if(arg == "red"){
            c_act = 2;
            mover = false;
            wbkgd(stdscr, COLOR_PAIR(c_act));
            refresh();
        }else if(arg == "white"){
            c_act = 3;
            mover = false;
            wbkgd(stdscr, COLOR_PAIR(c_act));
            refresh();
        }else{
            addstr("El color ingresado no es valido");
        }

    }else if(comm == "changeUser"){
        usuario = arg;
        mover = false;
    }else if(comm == "changeMachine"){
        maquina = arg;
        mover = false;
    }else if(comm == "exit"){
        running = false;
    }else{
        string cc = "'";
        string error = "No existe el comando " + cc + comm + cc;
        addstr(error.c_str());
    }
    if(mover){
        if(pos_y < y)
            pos_y++;
        else{
            pos_y = y-1;
            wscrl(stdscr,1);
            refresh();
        }
        move(pos_y, 0);
    }
}

void printInfo(){
    if(pos_y < y-1)
        pos_y++;
    else{
        pos_y = y-1;
        wscrl(stdscr,1);
        refresh();
    }
    move(pos_y, 0);
    switch(c_act){
        case 1:{
            attron(COLOR_PAIR(4));
            addstr(usuario.c_str());
            addch(at);
            addstr(maquina.c_str());
            attroff(COLOR_PAIR(4));
            attron(COLOR_PAIR(1));
            addch(a);
            attroff(COLOR_PAIR(1));
            attron(COLOR_PAIR(7));
            addch(b);
            attroff(COLOR_PAIR(7));
            attron(COLOR_PAIR(7));
            addstr(actual.getDireccion().c_str());
            attroff(COLOR_PAIR(7));
            attron(COLOR_PAIR(1));
            addstr(c.c_str());
            attroff(COLOR_PAIR(1));
            break;
        }

        case 2:{
            attron(COLOR_PAIR(5));
            addstr(usuario.c_str());
            addch(at);
            addstr(maquina.c_str());
            attroff(COLOR_PAIR(5));
            attron(COLOR_PAIR(2));
            addch(a);
            attroff(COLOR_PAIR(2));
            attron(COLOR_PAIR(8));
            addch(b);
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(8));
            addstr(actual.getDireccion().c_str());
            attroff(COLOR_PAIR(8));
            attron(COLOR_PAIR(2));
            addstr(c.c_str());
            attroff(COLOR_PAIR(2));
            break;
        }

        case 3:{
            attron(COLOR_PAIR(6));
            addstr(usuario.c_str());
            addch(at);
            addstr(maquina.c_str());
            attroff(COLOR_PAIR(6));
            attron(COLOR_PAIR(3));
            addch(a);
            attroff(COLOR_PAIR(3));
            attron(COLOR_PAIR(9));
            addch(b);
            attroff(COLOR_PAIR(9));
            attron(COLOR_PAIR(9));
            addstr(actual.getDireccion().c_str());
            attroff(COLOR_PAIR(9));
            attron(COLOR_PAIR(3));
            addstr(c.c_str());
            attroff(COLOR_PAIR(3));
            break;
        }
    }
    
}

void fillArray(){
    for(int i = 0;i < 150;i++){
        com[i] = '=';
    }
}

void transformString(char a[150]){
    comando = "";
    int pos = 0;
    for(int i = 0; i < 150; i++){
        if(a[i] != '='){
            pos = i;
        }
    }
    for(int j = 0;j < pos;j++){
        comando += a[j];
    }
}

int main(){
    initscr();
    getmaxyx(stdscr,y,x);
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_BLACK);
    init_pair(2,COLOR_WHITE, COLOR_RED);
    init_pair(3,COLOR_BLACK, COLOR_WHITE);
    init_pair(4,COLOR_GREEN, COLOR_BLACK);
    init_pair(5,COLOR_GREEN, COLOR_RED);
    init_pair(6,COLOR_GREEN, COLOR_WHITE);
    init_pair(7,COLOR_BLUE, COLOR_BLACK);
    init_pair(8,COLOR_BLUE, COLOR_RED);
    init_pair(9,COLOR_BLUE, COLOR_WHITE);
    while(running){
        attrset(COLOR_PAIR(c_act));
        getmaxyx(stdscr,y,x);
        scrollok(stdscr,TRUE);
        refresh();
        printInfo();
        fillArray();
        getnstr(com,150);
        transformString(com);
        commands();
        refresh();
    }
    endwin();
    return 0;
}