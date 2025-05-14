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

struct Personaje{
    Especie especie;
    string nombre;
    Personaje* siguiente;
};

struct Implemento{
    string nombre;
    string tipo; //<-- Indica si el implemento sera de daño, de cura o de defensa
    int usos; //<-- Cantidad de usos del implemento
    int fortNecesaria; //<-- Fortaleza minima para usar el implemento
    int valor; //<-- Daño, cura o defensa que otorga
    Implemento*siguiente;
};

struct Sala{

    int numeroDeSala;
    int distancia;
    int cantidadOrcos;
    Sala*siguiente;
};

class ListaEspecie{

    protected: // <-- Hace a los metodos inaccesibles en el main pero accecibles en las clases "hijas" (ListaPersona)

    Especie* cabeza;
    int cantidad;

    //metodos
    public: // <-- Hace a los metodos accesibles en el main

    ListaEspecie() : cabeza(NULL), cantidad(0) {} //<-- Constructor

    ~ListaEspecie(){   //<-- Destructor

        Especie* actual = cabeza; //Dirige el puntero actual al primer puntero de la lista

        while(actual!=NULL){

            Especie* temp= actual; //Puntero auxiliar apunta al actual

            actual= actual->siguiente; //El puntero actual pasa a la siguiente posicion
            
            delete temp; //Borra los datos del puntero auxiliar

        }
    }

    string indicarTipoEspecie(){ //Indica si la especie a crear sera un heroe o un orco. Se utiliza cuando vamos a agregar una especie
        
        string tipo;
        cout << "\n------- Tipo de Especie -------\n" << endl;
        cout << "1. Agregar especie de heroe\n" << endl;
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

        cout << "\n------- Ingrese datos de la Especie -------\n" << endl;
        cout << "Nombre: ";
        getline(cin, nuevo->nombre); // Hace lo mismo que cin, pero agarra todas las palabras, no solo una

        if(tipo=="1"){ // Recibe frotaleza si es heroe

            nuevo->dano=0;
            cout << "Fortaleza: ";
            while(!(cin >> nuevo->fortaleza)){ //Evita que ponga letras
                cout << "Entrada invalida. Ingrese un numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(nuevo->fortaleza<0){ 
                nuevo->fortaleza=1;
            }

        }else{

            nuevo->fortaleza=0;
            cout << "Daño: ";
            while(!(cin >> nuevo->dano)){ // Recibe daño si es orco
                cout << "Entrada invalida. Ingrese un numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 

            if(nuevo->dano<0){ 
                nuevo->dano=1;
            }
        }

        

        cout << "Salud: ";
        while(!(cin >> nuevo->salud)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(nuevo->salud<0){ 
                nuevo->salud=1;
            }

        cout << "Rapidez: ";
        while(!(cin >> nuevo->rapidez)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(nuevo->rapidez<0){ 
                nuevo->rapidez=1;
            }
       
        nuevo->siguiente = cabeza; //El puntero siguiente al nuevo nodo pasa a apuntar al primero
        cabeza = nuevo; //El nuevo nodo pasa a ser el primero de la lista

        cantidad++; //<-- cantidad+1
        cout << "\nEspecie " << nuevo->nombre << " agregada exitosamente" << endl;
    }

    bool comprobarNumeroDeEspecie(){ //Comprueba que la lista no este vacia. Solo se usa en el main sobre la funcion mostrarEspecies
        if(cantidad==0){
            return false;
        }else{
            return true;
        }
    }

    void mostrarEspecies(){
    
        Especie* act = cabeza;
        int id=0; //Ayudara a buscar al nodo

        while(act!=NULL){
            
            cout << "\n----- " << act->nombre <<  " -----\n" << endl;

            if(act->dano!=0){
                cout << "Daño: " << act->dano << endl;
            }else{
                cout << "Fortaleza: " << act->fortaleza << endl;
            }
            cout << "Salud: " << act->salud << endl;
            cout << "Rapidez: " << act->rapidez << endl;            

            id++; //Mostrara la posicion del nodo

            cout << "\nid: " << id << endl;
            act = act->siguiente; //Pasa al siguiente nodo
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

        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "ERROR. id invalido" << endl;
            return;
        }

        Especie* actual = cabeza; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la posicion de la buscada
        int i=1;
        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        string tipo=indicarTipoEspecie();

        if(tipo!="1" & tipo!="2"){ //Evita numeros que no sean 1 o 2

            cout << "Valor invalido";
            return;
        }

        cout << "\n---- Ingrese nuevos datos de la Especie ----\n" << endl;

        cout << "Nombre: ";
        getline(cin, actual->nombre); // Hace lo mismo que cin, pero agarra todas las palabras, no solo una

        if(tipo=="1"){ // Recibe frotaleza si es heroe

            actual->dano=0;
            cout << "Fortaleza: ";
            while(!(cin >> actual->fortaleza)){ //Evita que ponga letras
                cout << "Entrada invalida. Ingrese un numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            if(actual->fortaleza<0){ 
                actual->fortaleza=1;
            }

        }else{

            actual->fortaleza=0;
            cout << "Daño: ";
            while(!(cin >> actual->dano)){ // Recibe daño si es orco
                cout << "Entrada invalida. Ingrese un numero: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 

            if(actual->dano<0){ 
                actual->dano=1;
            }

        }

        cin.ignore();

        cout << "Salud: ";
        while(!(cin >> actual->salud)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->salud<0){ 
                actual->salud=1;
            }

        cout << "Rapidez: ";
        while(!(cin >> actual->rapidez)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->rapidez<0){ 
                actual->rapidez=1;
            }
       
        cout << "\nEspecie " << actual->nombre << " modificado exitosamente" << endl;




    }

    void eliminarEspecie(){

         if(cantidad==0){

            cout << "No hay especies" << endl;
            return;
        }

        mostrarEspecies();

        int pos;
        cout << "Indique el id de la especie a eliminar" << endl;

        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "ERROR. id invalido" << endl;
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
            
            
        }
        cantidad--;
        cout << "Especie eliminada exitosamente" << endl;
    }

    int getCantidad(){
        return cantidad;
    }

    Especie* getDatosEspecie(){

        mostrarEspecies();

        int pos;
        cout << "\nIndique el id de la especie buscada" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){ //Si el usuario pone un id invalido, devuelve nulo (se usara para hacer return en agregar peronaje).
            return nullptr;
        }

        Especie* actual = cabeza; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la posicion de la buscada

        int i=1;
        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        return actual;
    }
};

class ListaPersonaje{ //<-- Permite usar variables y metodos de ListaEspecie en ListaPersonaje

    Personaje* cabezaPers;
    int cantidadPers;

    //metodos
    public:

    ListaPersonaje(): cabezaPers(NULL), cantidadPers(0){}
        
    ~ListaPersonaje(){
        Personaje* actual = cabezaPers; 

        while(actual!=NULL){

            Personaje* temp= actual; 

            actual= actual->siguiente; 
            
            delete temp; 
        }
    }

    void agregarPersonaje(int cantidadEsp, ListaEspecie listaesp){ 

        if(cantidadEsp==0){
            cout << "Crea primero una especie" << endl;
            return;
        }

        Especie* buscado = listaesp.getDatosEspecie(); //<-- Devuelve puntero a la especie indicada

        if (buscado == nullptr) { // Verifica si el puntero es nulo
            cout << "No se pudo agregar el personaje debido a un ID inválido." << endl;
            return;
        }

        if(buscado->dano!=0){ //<-- Asegura que el personaje no sea un orco
            cout << "Los personajes no pueden ser ninguna especie de orco" << endl;
            return;
        }

        Personaje* nuevo = new Personaje;
        
        cout << "\n------- Ingrese nombre del personaje -------\n" << endl;
        cout << "Nombre: ";
        getline(cin, nuevo->nombre); 
        cin.ignore();

        nuevo->especie.dano=0;//Daño es 0 porque es un heroe
        
        nuevo->especie.fortaleza = buscado->fortaleza;  //las estadisticas de la especie se guardan en la variable especie de personaje
        nuevo->especie.salud = buscado->salud; 
        nuevo->especie.rapidez = buscado->rapidez;
        nuevo->especie.nombre = buscado->nombre;

        nuevo->siguiente = cabezaPers; //El puntero siguiente al nuevo nodo pasa a apuntar al primero
        cabezaPers = nuevo; //El nuevo nodo pasa a ser el primero de la lista

        cantidadPers++;
        cout << "\nPersonaje " << nuevo->nombre << " agregada exitosamente" << endl;
    }

    void mostrarPersonajes(){
        
        if(cantidadPers==0){

            cout << "No hay personajes" << endl;
            return;
        }

        Personaje* actual = cabezaPers;
        int id=0; //Ayudara a buscar al nodo

        while(actual!=NULL){
            
            cout << "\n----- " << actual->nombre <<  " -----\n" << endl;

            cout << "Especie: " << actual->especie.nombre << endl;
            cout << "Daño: " << actual->especie.dano << endl;
            cout << "Fortaleza " << actual->especie.fortaleza << endl;
            cout << "Salud: " << actual->especie.salud << endl;
            cout << "Rapidez: " << actual->especie.rapidez << endl;      

            id++; 

            cout << "\nid: " << id << endl;
            actual = actual->siguiente; //Pasa al siguiente personaje
        }

    }
    

    void modificarPersonaje(ListaEspecie listaesp){

        if(cantidadPers==0){

            cout << "No hay personajes" << endl;
            return;
        }

        mostrarPersonajes();

        int pos;
        cout << "\nIndique el id del personaje que desea modificar" << endl;

        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidadPers){

            cout << "Posicion invalida" << endl;
            return;
        }

        Personaje* actual = cabezaPers; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la buscada
        int i=1;

        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        Especie* buscado = listaesp.getDatosEspecie(); 

        if (buscado == nullptr) { // Verifica si el puntero es nulo
            cout << "No se pudo agregar el personaje debido a un ID inválido." << endl;
            return;
        }

        if(buscado->dano!=0){
            cout << "Los personajes no pueden ser ninguna especie de orco" << endl;
            return;
        }

        cout << "\n------- Ingrese nuevo nombre del personaje -------\n" << endl;
        cout << "Nombre: ";
        getline(cin, actual->nombre); 
        
        actual->especie.dano=0;
        actual->especie.fortaleza = buscado->fortaleza;  
        actual->especie.salud = buscado->salud; 
        actual->especie.rapidez = buscado->rapidez;




    }

    void eliminarPersonaje(){

        if(cantidadPers==0){

            cout << "No hay personajes" << endl;
            return;
        }

        mostrarPersonajes();

        int pos;
        cout << "Indique el id del personaje a eliminar" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidadPers){

            cout << "Posicion invalida" << endl;
            return;
        }

        Personaje* actual = cabezaPers;
        Personaje* anterior;

        if(pos==1){
            
            cabezaPers=cabezaPers->siguiente;
            delete actual;
        }else{

            for(int i=1; i<pos; i++ ){

            anterior=actual;
            actual=actual->siguiente;
            anterior->siguiente = actual->siguiente;
            delete actual;

            }
        }

        
        cantidadPers--;
        cout << "Personaje eliminado exitosamente" << endl;
    }
};

class ListaImplementos{
    Implemento* cabeza;
    int cantidad;

    public:
    

    ListaImplementos() : cabeza(NULL), cantidad(0) {} //<-- Constructor

    ~ListaImplementos(){   //<-- Destructor

        Implemento* actual = cabeza; //Dirige el puntero actual al primer puntero de la lista

        while(actual!=NULL){

            Implemento* temp= actual; //Puntero auxiliar apunta al actual

            actual= actual->siguiente; //El puntero actual pasa a la siguiente posicion
            
            delete temp; //Borra los datos del puntero auxiliar

        }
    }

    string indicarTipoImplemento(){ //Indica si el implemento a crear sera de daño, cura o defensa
        
        string tipo;

        cout << "\n------- Tipo de Implemento  -------\n" << endl;
        cout << "1. Agregar implemento de daño\n" << endl;
        cout << "2. Agregar implemento de defensa\n" << endl;
        cout << "3. Agregar implemento de cura\n" << endl;

        cin >> tipo;
        cin.ignore();

        return tipo;
    }

    void agregarImplemento(){ 

       string tipo=indicarTipoImplemento(); //Cuando tipo sea 1 sera de daño, cuando sea 2 sera de defensa y cuando sea 3 de cura

       if(tipo!="1" & tipo!="2" & tipo!="3"){

            cout << "Valor invalido";
            return;
        }

        Implemento* nuevo= new Implemento;

        cout << "\n------ Ingrese los datos del implemento ------\n" << endl;
        cout << "Nombre: ";
        getline(cin, nuevo->nombre);  

        if(tipo=="1"){
            nuevo->tipo = "Daño";
        }

        if(tipo=="2"){
            nuevo->tipo = "Defensa";
        }

        if(tipo=="3"){
            nuevo->tipo = "Cura";
        }

        cout << "Usos: ";
        while(!(cin >> nuevo->usos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(nuevo->usos<0){ 
                nuevo->usos=1;
            }

        cout << "Fortaleza necesaria: ";
        while(!(cin >> nuevo->fortNecesaria)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(nuevo->fortNecesaria<0){ 
                nuevo->fortNecesaria=1;
            }
        
        cout << "Valor del daño/cura/defensa: ";

        while(!(cin >> nuevo->valor)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(nuevo->valor<0){ 
                nuevo->valor=1;
            }
        
        nuevo->siguiente = cabeza; //El primer nodo pasa a ser el siguiente al creado
        cabeza = nuevo; //El nodo nuevo es ahora el primero

        cantidad++; 
        cout << "\nImplemento " << nuevo->nombre << " agregado exitosamente" << endl;
    }

    void mostrarImplementos(){
        
        if(cantidad==0){

            cout << "No hay implementos" << endl;
            return;
        }

        Implemento* actual = cabeza;
        int id=0; //Ayudara a buscar al nodo

        while(actual!=NULL){
            
            cout << "\n----- " << actual->nombre <<  " -----\n" << endl;
            cout << "Tipo: " << actual->tipo << endl;
            cout << "Usos: " << actual->usos << endl;
            cout << "Fortaleza necesario: " << actual->fortNecesaria << endl;            
            cout << "Valor: " << actual->valor << endl;

            id++; 

            cout << "\nid: " << id << endl;
            actual = actual->siguiente; //Pasa al siguiente nodo
        }

    }
    

    void modificarImplemento(){

        if(cantidad==0){

            cout << "No hay implementos" << endl;
            return;
        }

        mostrarImplementos();

        int pos;
        cout << "\nIndique el id del implemento que desea modificar" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "Posicion invalida" << endl;
            return;
        }

        Implemento* actual = cabeza; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la buscada
        int i=1;
        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        string tipo=indicarTipoImplemento();

        if(tipo!="1" & tipo!="2" & tipo!="3"){ 

            cout << "Valor invalido";
            return;
        }

        cout << "\n---- Ingrese los nuevos datos del implemento ----\n" << endl;

        cout << "Nombre: ";

        getline(cin, actual->nombre);  

        if(tipo=="1"){

            actual->tipo= "Daño";

        }

        if(tipo=="2")
        {
            actual->tipo= "Defensa";

        }

        if(tipo=="3")
        {
            actual->tipo= "Cura";

        }

        cout << "Usos: ";
        while(!(cin >> actual->usos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->usos<0){ 
                actual->usos=1;
            }

        cout << "Fortaleza necesaria: ";
        while(!(cin >> actual->fortNecesaria)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->fortNecesaria<0){ 
                actual->fortNecesaria=1;
            }

        cout << "Valor: ";
        while(!(cin >> actual->valor)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->valor<0){ 
                actual->valor=1;
            }

        cout << "\nImplemento " << actual->nombre << " modificado exitosamente" << endl;

    }

    void eliminarImplemento(){

        if(cantidad==0){

            cout << "No hay implementos" << endl;
            return;
        }

        mostrarImplementos();

        int pos;
        cout << "Indique el id del implemento a eliminar" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "ERROR. id invalido" << endl;
            return;
        }

        Implemento* actual = cabeza;
        Implemento* anterior;

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
            cout << "Implemento eliminado exitosamente" << endl;
        }
    }


};

class ListaSalas{

    Sala* cabeza;
    int cantidad;

    public:
    

    ListaSalas() : cabeza(NULL), cantidad(0) {} //<-- Constructor

    ~ListaSalas(){   //<-- Destructor

        Sala* actual = cabeza; //Dirige el puntero actual al primer puntero de la lista

        while(actual!=NULL){

            Sala* temp= actual; //Puntero auxiliar apunta al actual

            actual= actual->siguiente; //El puntero actual pasa a la siguiente posicion
            
            delete temp; //Borra los datos del puntero auxiliar

        }
    }

    void agregarSala(){ 

        Sala* nuevo= new Sala;

        cout << "\n------ Ingrese los datos de la sala ------\n" << endl;
        

        cout << "Distancia: ";
        while(!(cin >> nuevo->distancia)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(nuevo->distancia<0){ 
                nuevo->distancia=1;
            }

        nuevo->cantidadOrcos=0;
        nuevo->numeroDeSala=cantidad+1;
       
        nuevo->siguiente = cabeza; //El primer nodo pasa a ser el siguiente al creado
        cabeza = nuevo; //El nodo nuevo es ahora el primero

        cantidad++; 
        cout << "\nSala numero " << nuevo->numeroDeSala << " agregado exitosamente" << endl;
    }

    void mostrarSalas(){
        
        if(cantidad==0){

            cout << "No hay salas" << endl;
            return;
        }

        Sala* actual = cabeza;
        int id=0; //Ayudara a buscar al nodo

        while(actual!=NULL){
            
            cout << "\n----- Sala numero " << actual->numeroDeSala <<  " -----\n" << endl;
            cout << "Distancia: " << actual->distancia << endl;
            cout << "Cantidad de orcos: " << actual->cantidadOrcos << endl;
    
            id++; 

            cout << "\nid: " << id << endl;
            actual = actual->siguiente; //Pasa al siguiente nodo
        }

    }
    

    void modificarSala(){

        if(cantidad==0){

            cout << "No hay salas disponibles" << endl;
            return;
        }

        mostrarSalas();

        int pos;
        cout << "\nIndique el id de la sala que desea modificar" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "Posicion invalida" << endl;
            return;
        }

        Sala* actual = cabeza; //Establece un puntero inicial que recorrera todas las especies hasta llegar a la buscada
        int i=1;
        while(i<pos){

            i++;
            actual=actual->siguiente;

        }

        cout << "\n---- Ingrese los nuevos datos de la sala ----\n" << endl;

        

        cout << "Distancia: ";
        while(!(cin >> actual->distancia)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        cin.ignore();

        if(actual->distancia<0){ 
                actual->distancia=1;
            }

        cout << "\nSala numero " << actual->numeroDeSala<< " modificado exitosamente" << endl;

    }

    void eliminarSala(){

        if(cantidad==0){

            cout << "No hay salas disponibles" << endl;
            return;
        }

        mostrarSalas();

        int pos;
        cout << "Indique el id de la sala a eliminar" << endl;
        while(!(cin >> pos)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        if(pos<0 || pos>cantidad){

            cout << "ERROR. id invalido" << endl;
            return;
        }

        Sala* actual = cabeza;
        Sala* anterior;

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
            cout << "Sala eliminado exitosamente" << endl;
        }
    }

};



void menuPrincipal(){

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
    cout << "4. Agregar Sala\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    cin >> opcion2;
}

void menuMostrar(int &opcion2){

    cout <<"\n---------  Mostrar  ---------\n" << endl;
    cout << "1. Mostrar Especie\n" << endl;
    cout << "2. Mostrar Personaje\n" << endl;
    cout << "3. Mostrar Implemento\n" << endl;
    cout << "4. Mostrar Sala\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    cin >> opcion2;
}

void menuModificar(int &opcion2){

    cout <<"\n---------  Modificar  ---------\n" << endl;
    cout << "1. Modificar Especie\n" << endl;
    cout << "2. Modificar Personaje\n" << endl;
    cout << "3. Modificar Implemento\n" << endl;
    cout << "4. Modificar Sala\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    cin >> opcion2;
}

void menuEliminar(int &opcion2){

    cout <<"\n---------  Eliminar  ---------\n" << endl;
    cout << "1. Eliminar Especie\n" << endl;
    cout << "2. Eliminar Personaje\n" << endl;
    cout << "3. Eliminar Implemento\n" << endl;
    cout << "4. Eliminar Sala\n" << endl;
    cout << "5. Regresar al menu\n" << endl;

    cin >> opcion2;
}


int main(){

    cout << "UCAB. Elaborado por: Carlos La Verde, Ricardo Hernandez y Jean Paul Saviñon" << endl;

    ListaEspecie listaEsp;
    ListaPersonaje listaPers;
    ListaImplementos listaImp;
    ListaSalas listaSal;

    string tipo; //Indicara tipo de especie
    int opcion;
    int opcion2;

    while(opcion!=5){
        
        menuPrincipal();
        while(!(cin >> opcion)){
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
       

         switch (opcion) {
            case 1:
                
                menuAgregar(opcion2);
            
                switch (opcion2){

                    case 1:
                        listaEsp.agregarEspecie();
                        break;

                    case 2: 
                        int cantidadEspe;
                        cantidadEspe=listaEsp.getCantidad();
                        listaPers.agregarPersonaje(cantidadEspe, listaEsp);
                        break;

                    case 3:
                        listaImp.agregarImplemento();
                        break;

                    case 4:
                        listaSal.agregarSala();
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
                        listaEsp.modificarEspecie();
                        break;

                    case 2: 
                        listaPers.modificarPersonaje(listaEsp);
                        break;

                    case 3:
                        listaImp.modificarImplemento();
                        break;

                    case 4:
                        listaSal.modificarSala();
                        break;

                    case 5:

                        break;

                    default:

                        cout << "Opcion invalida. Intente nuevamente" << endl;
                }
                
                break;

            case 3:

                menuMostrar(opcion2);

                switch (opcion2){

                    case 1: {
                        bool listaVacia=listaEsp.comprobarNumeroDeEspecie();

                        if(listaVacia==true){
                            listaEsp.mostrarEspecies();
                        }else{
                            cout << "No hay especies" << endl;
                        }

                        break;
                    }

                    case 2: 
                        listaPers.mostrarPersonajes();
                        break;

                    case 3:
                        listaImp.mostrarImplementos();
                        break;

                    case 4:
                        listaSal.mostrarSalas();
                        break;

                    case 5:

                        break;

                    default:

                        cout << "Opcion invalida. Intente nuevamente" << endl;
                }

                break;

            case 4:
                
                menuEliminar(opcion2);
            
                switch (opcion2){

                    case 1:
                        listaEsp.eliminarEspecie();
                        break;

                    case 2: 
                        listaPers.eliminarPersonaje();
                        break;

                    case 3:
                        listaImp.eliminarImplemento();
                        break;

                    case 4:
                        listaSal.eliminarSala();
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