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

    string indicarTipoEspecie(){ //Indica si la especie a crear sera un heroe o un orco. Se utiliza cuando vamos a agregar una especie
        
        string tipo;
        cout << "\n1. Agregar especie de heroe\n" << endl;
        cout << "2. Agregar especie de orco\n" << endl;
        cin >> tipo;
        cin.ignore();

        return tipo;
    }

    void agregarEspecie(){ 

       string tipo=indicarTipoEspecie(); //Cuando tipo sea 1 sera un heroe, cuando sea 2 sera un orco

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

        cantidad++; //<-- cantidad+1
        cout << "\nEspecie " << nuevo->nombre << " agregada exitosamente" << endl;
    }

    void mostrarEspecies(){
        
        if(cantidad==0){

            cout << "No hay especies" << endl;
            return;
        }

        Especie* actual = cabeza;
        int id=0; //Ayudara a buscar al nodo

        while(actual!=NULL){
            
            cout << "\n----- " << actual->nombre <<  " -----\n" << endl;

            if(actual->dano!=0){ //<-- Muestra el daño si es orco

                cout << "Daño: " << actual->dano << endl;

            }else{ //<-- Muestra la fortaleza si es heroe

                cout << "Fortaleza: " << actual->fortaleza << endl;

            }
            cout << "Salud: " << actual->salud << endl;
            cout << "Rapidez: " << actual->rapidez << endl;            

            id++; 

            cout << "\nid: " << id << endl;
            actual = actual->siguiente; //Pasa al siguiente nodo
        }

    }
    

    void modificarEspecie(){

        if(cantidad==0){

            cout << "No hay especies" << endl;
            return;
        }

        mostrarEspecies();

        int pos;
        cout << "\nIndique el id de la especie que desea modificar" << endl;
        cin >> pos;

        if(pos<0 || pos>cantidad){

            cout << "Posicion invalida" << endl;
            return;
        }

        Especie* actual = cabeza; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la buscada
        int i=1;
        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        cout << "\nIndique si desea una especie de heroe o de orco" << endl;

        string tipo=indicarTipoEspecie();

        if(tipo!="1" & tipo!="2"){ //Evita numeros que no sean 1 o 2

            cout << "Valor invalido";
            return;
        }

        cout << "\nIngrese los nuevos datos de la especie" << endl;

        cout << "Nombre: ";

        getline(cin, actual->nombre);  

        if(tipo=="1"){

            actual->dano=0;
            cout << "Fortaleza: ";
            cin >> actual->fortaleza; // Recibe frotaleza si es heroe

        }else{

            actual->fortaleza=0;
            cout << "Daño: ";
            cin >> actual->dano; // Recibe daño si es orco

        }

        cout << "Salud: ";
        cin >> actual->salud; 

        cout << "Rapidez: ";
        cin >> actual->rapidez; 
       
        cout << "\nEspecie " << actual->nombre << " modificado exitosamente" << endl;




    }

    void eliminarEspecie(){

        if(cantidad==0){

            cout << "No hay especies" << endl;
            return;
        }

        int pos;
        cout << "Indique el numero de la especie a eliminar (1 - " << cantidad << " )" << endl;
        cin >> pos;
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "Posicion invalida" << endl;
            return;
        }

        Especie* actual = cabeza;
        Especie* anterior;

        if(pos==1){
            
            cabeza=cabeza->siguiente;
            delete actual;
        }else{

            for(int i=1; i<pos; i++ ){

            anterior=actual;
            actual=actual->siguiente;

            }

            anterior->siguiente = actual->siguiente;
            delete actual;
            cantidad--;
            cout << "Especie eliminada exitosamente" << endl;
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
        cout << "1. Agregar\n" << endl;
        cout << "2. Modificar\n" << endl;
        cout << "3. Mostar\n" << endl;
        cout << "4. Eliminar\n" << endl;
        cout << "5. Salir del programa\n" << endl;
        
}

void menuAgregar(int &opcion2){

    cout <<"\n---------  Agregar  ---------\n" << endl;
    cout << "1. Agregar Especie\n" << endl;
    cout << "2. Agregar Personaje\n" << endl;
    cout << "3. Agregar Implemento\n" << endl;
    cout << "4. Agregar Poder Magico\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    
    cin >> opcion2;
    cin.ignore();
    

}


void menuModificar(int &opcion2){

    cout <<"\n---------  Modificar  ---------\n" << endl;
    cout << "1. Modificar Especie\n" << endl;
    cout << "2. Modificar Personaje\n" << endl;
    cout << "3. Modificar Implemento\n" << endl;
    cout << "4. Modificar Poder Magico\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    
    cin >> opcion2;
    cin.ignore();
    

}

void menuEliminar(int &opcion2){

    cout <<"\n---------  Eliminar  ---------\n" << endl;
    cout << "1. Eliminar Especie\n" << endl;
    cout << "2. Eliminar Personaje\n" << endl;
    cout << "3. Eliminar Implemento\n" << endl;
    cout << "4. Eliminar Poder Magico\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    
    cin >> opcion2;
    cin.ignore();
    

}


int main(){

    ListaEspecie lista;
    string tipo;
    int opcion;
    int opcion2;
    while(opcion!=5){
        
        mostarMenu();
        cin >> opcion;
        cin.ignore();

         switch (opcion) {
            case 1:
                
                menuAgregar(opcion2);
            
                switch (opcion2){

                    case 1:
                        lista.agregarEspecie();
                        break;

                    case 2: 

                        break;

                    case 3:
            
                        break;

                    case 4:

                        break;

                    case 5:

                        break;

                    default:

                        cout << "Opcion invalida. Intente nuevamente" << endl;
                }
                
                break;

            case 2:

                menuModificar(opcion2);

                switch (opcion2){

                    case 1:
                        lista.modificarEspecie();
                        break;

                    case 2: 

                        break;

                    case 3:
            
                        break;

                    case 4:

                        break;

                    case 5:

                        break;

                    default:

                        cout << "Opcion invalida. Intente nuevamente" << endl;
                }
                
                break;

            case 3:

                lista.mostrarEspecies();

                
                break;

            case 4:
                
                lista.mostrarEspecies();
        
                menuEliminar(opcion2);
            
                switch (opcion2){

                    case 1:
                        lista.eliminarEspecie();
                        break;

                    case 2: 

                        break;

                    case 3:
            
                        break;

                    case 4:

                        break;

                    case 5:

                        break;

                    default:

                        cout << "Opcion invalida. Intente nuevamente" << endl;
                }

                break;

            case 5:

                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida. Intente de nuevo.\n";
        }

    }
}
