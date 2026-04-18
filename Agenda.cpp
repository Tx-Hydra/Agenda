#include <iostream>
#include <fstream>
#include <windows.h>
#include <limits>
#include <vector>


struct tarea{
    std::string tareas;
    bool completada;
};
/*
int main() {
  // Create and open a text file
  std::fstream MyFile("filename.txt");

  // Write to the file
  std::MyFile << "Files can be tricky, but it is fun enough!";
  
  // Read from the file
  std::string myText;
  getline(MyFile, myText);
  std::cout << myText;

  // Close the file
  std::MyFile.close();
} 
*/
void crearlista(){
    std::ofstream MiLista("Tareas.txt", std::ios::app); //creo el archivo
}

tarea creartarea(){
    tarea tar;
    std::cout<<"Ingrese la tarea: ";
    std::getline(std::cin >> std::ws ,tar.tareas);
    tar.completada = false;
    return tar;
}

void agregartarea(tarea tar){
    std::ofstream agregar("Tareas.txt", std::ios::app);

    if (!agregar.is_open()) {
        std::cout << "Error al abrir archivo\n";
        return;
    }
    agregar << tar.tareas << "|" << tar.completada << "\n";
}


void actualziartarea(){
    std::ifstream archivo("Tareas.txt");
    std::vector<tarea> lista;
    std::string linea;


    while (getline(archivo, linea)) {
        tarea tar;
        int pos = linea.find('|');

        tar.tareas = linea.substr(0, pos);        
        tar.completada = (linea[pos + 1] == '1');

        lista.push_back(tar);
    }
    archivo.close();


    int i;
    std::cout << "Que tarea actualizar? \n R: ";
    std::cin >> i;
    if(lista[i].completada)
        lista[i].completada = false;
    else
        lista[i].completada = true;


    std::ofstream archivo2("Tareas.txt");
    for (auto& t : lista) {
        archivo2 << t.tareas << "|" << (t.completada ? 1 : 0) << "\n";
    }
}


void borrartarea(int tareaborrada){
    std::ifstream borrar("Tareas.txt");
    std::ofstream temp("temp.txt");

    if (!borrar.is_open()) {
        std::cout << "Error al abrir el archivo\n";
        return;
    }

    std::string linea;
    int contador = 0;
    bool eliminada = false;

    while (std::getline(borrar, linea)) {
        if (contador == tareaborrada) {
            eliminada = true;
        } else {
            temp << linea << "\n";
        }
        contador++;
    }

    borrar.close();
    temp.close();

    if (remove("Tareas.txt") != 0) {
    std::cout << "Error al eliminar archivo original\n";
    return;
    }
    if (rename("temp.txt", "Tareas.txt") != 0) {
        std::cout << "Error al renombrar archivo\n";
        return;
    }

    if (eliminada)
        std::cout << "Tarea eliminada correctamente\n";
    else
        std::cout << "Numero de linea invalido\n";
} 



void vertareas() {
    std::ifstream archivo("Tareas.txt");

    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo\n";
        return;
    }

    std::string linea;
    int i = 0;

    while (std::getline(archivo, linea)) {
        tarea t;

        int pos = linea.find('|');

        t.tareas = linea.substr(0, pos);
        t.completada = (linea[pos + 1] == '1');

        std::cout << i << " - " << t.tareas 
                  << " [" << (t.completada ? "si" : "no") << "]\n";

        i++;
    }
}


int main(){
    tarea tar;
    int opc = 1;
    int opc2 = 0;
    std::ifstream Lista;
    crearlista();
    while(opc != 2){
        std::cout<<"** Agenda **"<< std::endl ;
        std::cout<< std::endl <<"1- Abrir Agenda   2- Cerrar" << std::endl;
        std::cout<<"R: ";
        std::cin>>opc;
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout<<"Opcion no Valida";
            continue;
        }
        switch (opc){
        case 1:
            while (opc2 != 5){    
                std::cout<<"1- Crear Tarea    2- Ver Tareas    3- Actualizar Tarea\n         4- Borrar Tarea    5- Borrar Tarea\n";
                std::cout<<"R: ";
                std::cin>>opc2;
                if (std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                    std::cout<<"Opcion no Valida";
                    continue;
                }
                switch (opc2){
                    case 1:
                        tar = creartarea();
                        agregartarea(tar);
                        continue;;
                    case 2:
                        vertareas();
                        break;
                    case 3:
                        actualziartarea();
                        continue;
                    case 4:
                        int tareaborrada;
                        std::cout<<"Indique tarea a borrar: ";
                        std::cin>>tareaborrada;
                        borrartarea(tareaborrada);
                        continue;
                    case 5:
                        opc = 2;
                        break;
                    default:
                        continue;
            
                }
            }
        case 2:
            break;
        default:
            std::cout<<"* Ingreso no Valido *\n\n";
            continue;
        }
    }
}