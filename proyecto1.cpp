#include <iostream>
#include <limits>
using namespace std;

struct Especie{

    string nombre;
    int fortaleza;
    int dano;
    int salud;
    int rapidez;
    Especie *siguiente;

};

class ListaEspecie{

    private: // <-- Hace a los metodos inaccesibles en el main

    Especie* cabeza;
    int cantidad;

    //metodos
    public: // <-- Hace a los metodos accesibles en el main

    ListaEspecie() : cabeza(NULL), cantidad(0) {} //<-- Constructor

    ~ListaEspecie(){   //<-- Destructor

        Especie* actual = cabeza; //Dirige el puntero actual al primer puntero de la lista

        while(actual!=NULL){

            Especie* temp= actual; //Puntero auxiliar pasa a ser el actual

            actual= actual->siguiente; //El puntero actual pasa a la siguiente posicion
            
            delete temp; //Borra los datos del puntero auxiliar

        }
    }

    void agregarEspecie(string tipo){ //Cuando tipo sea 1 sera un heroe, cuando sea 2 sera un orco

        if(tipo!="1" & tipo!="2"){ //Evita numeros que no sean 1 o 2

            cout << "Valor invalido";
            return;
        }

        Especie* nuevo= new Especie;

        cout << "\nIngrese los datos de la Especie\n";
        cout << "Nombre: ";
        getline(cin, nuevo->nombre); // Hace lo mismo que cin, pero agarra todas las palabras, no solo una

        if(tipo=="1"){

            nuevo->dano=0;
            cout << "Fortaleza: ";
            cin >> nuevo->fortaleza; // Recibe frotaleza si es heroe

        }else{

            nuevo->fortaleza=0;
            cout << "Daño: ";
            cin >> nuevo->dano; // Recibe daño si es orco

        }

        cout << "Salud: ";
        cin >> nuevo->salud; 

        cout << "Rapidez: ";
        cin >> nuevo->rapidez; 
       
        nuevo->siguiente = cabeza; //El puntero siguiente al nuevo nodo pasa a apuntar al primero
        cabeza = nuevo; //El nuevo nodo pasa a ser el primero de la lista
        cantidad=cantidad+1;

        cout << "\nEspecie " << nuevo->nombre << " agregada exitosamente" << endl;
    }

    void mostrarEspecies(){
        
        if(cantidad==0){

            cout << "No hay especies" << endl;
            return;
        }

        Especie* actual = cabeza;

        while(actual!=NULL){

            cout << "\n----- " << actual->nombre <<  " -----\n" << endl;

            if(actual->dano!=0){ //<-- Muestra el daño si es orco

                cout << "Daño: " << actual->dano << endl;

            }else{ //<-- Muestra la fortaleza si es heroe

                cout << "Fortaleza: " << actual->fortaleza << endl;

            }
            cout << "Salud: " << actual->salud << endl;
            cout << "Rapidez: " << actual->rapidez << endl;

            actual = actual->siguiente; //Pasa al siguiente nodo
        }

    }
};

struct Personaje{
    Especie especie;
    string nombre;
    Personaje* siguiente;
};

class listaPersonaje{

    Personaje* cabeza;
    int cantidad;

    //metodos
    public:

    listaPersonaje(): cabeza(NULL), cantidad(0){}

    ~listaPersonaje(){
        Personaje* actual = cabeza; 

        while(actual!=NULL){

            Personaje* temp= actual; 

            actual= actual->siguiente; 
            
            delete temp; 
        }
    }

    void agregarPersonaje(){

        Personaje* nuevo= new Personaje;
        cout << "Nombre: ";
        getline(cin, nuevo->nombre);
    }
};


void mostarMenu(){

    cout <<"\n---------  Menu  ---------\n" << endl;
        cout << "1. Agregar Especie\n" << endl;
        cout << "2. Agregar ....\n" << endl;
        cout << "3. Agregar ....\n" << endl;
        cout << "4. Mostrar Especies \n" << endl;
        cout << "5. Salir del programa\n" << endl;
        
}
int main(){

    ListaEspecie lista;
    string tipo;
    int opcion;

    while(opcion!=5){
        
        mostarMenu();
        cin >> opcion;
        cin.ignore();

         switch (opcion) {
            case 1:

                cout << "\n1. Agregar heroe\n" << endl;
                cout << "2. Agregar orco\n" << endl;
                cin >> tipo;
                cin.ignore();
                lista.agregarEspecie(tipo);
                break;

            case 2:
                break;
            case 3:
                break;
            case 4:
                lista.mostrarEspecies();
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }

    }
}