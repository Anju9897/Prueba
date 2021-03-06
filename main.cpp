#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <list>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <dirent.h>
#include <iomanip>
#include "sha256.h"

using namespace std;

void info(string cadena);
bool crearAdmin();
bool login();
bool evaluar(string cadena);
int cant_Usuarios();
string limpiarCadena(string cadena);
void usar(string cadena);
void crear(string cadena);
void insertar(string cadena);
void editar(string cadena);
void eliminar(string cadena);
void ver(string cadena);
void ejecutar(string cadena);
void renombrar(string cadena);
void listar(string cadena);
void informacion();
void infoCrear();
void infoTabla();
void crearBaseDeDatos(string entrada);
void cambiarNombreBD(string nombre1, string nombre2);
bool carpetaUsuarios();
bool carpetaBD();
bool comprobar(string entrada);
bool evaluarTabla(string contenido, string nombre);
bool hayStringsRepetidos(vector<string>);
bool existeTabla(string nombre);
bool evaluarValoresTabla(string nombre, string valores);
int ListaTokens(string cadena);
int cantArgumentos(string cadena);
vector<int> posicionesIniciales();
vector<string> listaDeTablas();
vector<string> nombresTablas();
vector<string> listaDatos(string datos);
vector<string> separarDatos(string cadena);
vector<string> obtenerListaId(string nombre);
vector<string> obtenerFilas(string nombre);
string convertirMayusculas(string cadena);
string obtenerPalabra(string cadena, int n);
string leer(string texto);
string separarParentesis(string cadena);
string unirCorchetes(string cadena);
string separarCorchetes(string cadena);
string muestra_contenido_de(const std::string &a_carpeta);
string Lectura(string basedatos);
string prepararTabla(string nombre, vector<string> lista);
string obtenerTabla(string nombre);
string quitarVariables(string nombre);
string ubicacion();
string encriptar(string cadena);
string desencriptar(string cadena);
void crearArchivoUsuarios();
void escribir(string texto,string texto2);
void entrada();
void insertarEnTabla(string nombre, string cadena, string id, string sobra);
void crearTabla(string nombre, string cadena, string sobra);
void titulo();
void limpiaPantalla(){system("cls || clear");}
void insertar_Al_Final(string cadena);
void reemplazar(string url, string texto);
void traducir(string texto);
void eliminarFila(string tabla, string id);
void editarTabla(string tabla, string id, string cadena1, string cadena2, string sobra);

//VARIABLES GLOBALES!!!
//SE CARGAN LOS PERMISOS DE USUARIO AL MOMENTO DE LOGEARSE
string _nombre, _puerto, _dataBase="";
bool _Crear,_ElimTabYBd,_ElimFila,_InsertFila,_Leer,_Actualizar,_Privilegios;

//*************************************************************************************************************
//**************************************        USUARIOS     *************************************************
//*************************************************************************************************************
class Usuarios{
    private:
        string nombre;
        string clave;
        bool Crear;//Permite crear nuevas tablas o bases de datos.
        bool ElimTabYBd;//Permite eliminar tablas o bases de datos.
        bool ElimFila;//Permite eliminar filas de las tablas.
        bool InsertFila;//Permite insertar filas en las tablas.
        bool Leer;//Permite leer las bases de datos.
        bool Actualizar;//Permite actualizar las filas de las tablas.
        bool Privilegios;//todos los privilegios (actualizar nombre de las bases de datos y asignar mas privilegios)
    public:
        Usuarios();
        Usuarios(string nom, string clav, bool cre, bool Elim1, bool Elim2, bool inse, bool lee, bool actua, bool priv){
            this->nombre=nom;
            this->clave=clav;
            this->Crear=cre;
            this->ElimTabYBd=Elim1;
            this->ElimFila=Elim2;
            this->InsertFila=inse;
            this->Leer=lee;
            this->Actualizar=actua;
            this->Privilegios=priv;
        }
        string getNombre(){return nombre;}
        void setNombre(string nom){this->nombre=nom;}

        string getClave(){return clave;}
        void setClave(string clav){this->clave=clave;}

        bool getCrear(){return Crear;}
        void setCrear(bool cre){this->Crear=cre;}

        bool getElimTabYBd(){return ElimTabYBd;}
        void setElimTabYBd(bool Elim1){this->ElimTabYBd=Elim1;}

        bool getElimFila(){return ElimFila;}
        void setElimFila(bool Elim2){this->ElimFila=Elim2;}

        bool getInsertFila(){return InsertFila;}
        void setInsertFila(bool inser){this->InsertFila=inser;}

        bool getLeer(){return Leer;}
        void setLeer(bool lee){this->Leer=lee;}

        bool getActualizar(){return Actualizar;}
        void setActualizar(bool actualiza){this->Actualizar=actualiza;}

        bool getPrivilegios(){return Privilegios;}
        void setPrivilegios(bool priv){this->Privilegios=priv;}
};
Usuarios ObtenerUsuario(int num){
    string carpeta = ubicacion();
    string cadena = carpeta+"/UwuDB.sql";
    /////////////////////////////////////////////
    string texto=leer(cadena);
    ////////////////////////////////////////////////
    char arreglo[texto.length()+1];
    strcpy(arreglo, texto.c_str());
    int cantidad=-3;
    cadena="";
    //Cuenta cuantos usuarios se encuentran almacenados y lo guarda en "cantidad" y almacena en "cadena" los usuarios
    for(int i=0;i<texto.length();i++){
        if(arreglo[i]=='#'){
                cantidad++;
        }
        if(cantidad>=0){
            cadena+=arreglo[i+1];
        }
    }
    Usuarios *U[cantidad];
    //ciclo for que extrae todos los usuarios del archivo y los guarda en memoria
    char arreglo2[cadena.length()+1];
    strcpy(arreglo2, cadena.c_str());
    int j=0;
    for(int i=0;i<cantidad;i++){
        string Todouser="",nombre="",clave="";
        bool Crear=false,ElimTabYBd=false,ElimFila=false,InsertFila=false,Leer=false,Actualizar=false, Privilegios=false;
        while(arreglo2[j]!='#'){
            Todouser+=arreglo2[j];
            j++;
        }
        //"Todouser" Contiene en texto plato el usuario
        j++;
        char arreglo3[Todouser.length()+1];
        strcpy(arreglo3, Todouser.c_str());
        int contador=1;//9 columnas
        for(int k=0;k<Todouser.length();k++){
                if(arreglo3[k]==';')contador++;
                if(contador==1)nombre+=arreglo3[k];
                else if((contador==2)&&(arreglo3[k]!=';'))clave+=arreglo3[k];
                else if((contador==3)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){Crear=true;}}
                else if((contador==4)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){ElimTabYBd=true;}}
                else if((contador==5)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){ElimFila=true;}}
                else if((contador==6)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){InsertFila=true;}}
                else if((contador==7)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){Leer=true;}}
                else if((contador==8)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){Actualizar=true;}}
                else if((contador==9)&&(arreglo3[k]!=';')){if(arreglo3[k]=='1'){Privilegios=true;}}
        }

        U[i] = new Usuarios(nombre,clave,Crear,ElimTabYBd,ElimFila,InsertFila,Leer,Actualizar,Privilegios);
    }
    return *U[num];
}
//*************************************************************************************************************
//**************************************        MAIN     *************************************************
//*************************************************************************************************************
int main()
{
    string carpeta = ubicacion();
    bool pasar=false, validarPuerto=true, corrupto=false;
    int nP=0;
    do{
        corrupto=false;
        if(comprobar("/home/config")){
            string lee=leer("/home/config.sql");
            char a[lee.length()];
            strcpy(a, lee.c_str());
            if(lee.length()>7){
                if((a[0]=='p')&&(a[1]=='u')&&(a[2]=='e')&&(a[3]=='r')&&(a[4]=='t')&&(a[5]=='o')&&(a[6]==':')){
                    for(int i=8;i<lee.length()-1;i++){
                    if(a[i]<48 || a[i]>57){
                        corrupto=true;
                    }
                    }

                }else{
                    corrupto=true;
                }
            }else{
                corrupto=true;
            }
        }else{
            if(nP==0){
                cout<<"Hemos detectado que no se a configurado el puerto escucha"<<endl;
            }
            validarPuerto=true;
            cout<<"Porfavor digite el puerto a utilizar"<<endl;
            cout <<"Puerto: ";
            string puerto;
            getline(cin, puerto);
            char b[puerto.length()];
            strcpy(b, puerto.c_str());
            for(int i=0;i<puerto.length();i++){
                if((b[i]>=48)&&(b[i]<=57)){

                }else{
                    validarPuerto=false;
                }
            }
            if(validarPuerto){
                ofstream file;
                file.open("/home/config.sql");
                file.close();
                escribir("/home/config.sql","puerto: "+puerto);
                cout<<"Se definio el puerto "<<'"'<<puerto<<'"'<<" como el puerto de escucha"<<endl;
            }else{
                cout<<"El puerto "<<'"'<<puerto<<'"'<<" no es un puerto valido, intente con un numero"<<endl;
            }
        }
        if(!corrupto){
                if(validarPuerto){
                    pasar=true;
                }
            }else{
            cout<<"Error! Archivo de configuracion corrupto"<<endl;
            validarPuerto=true;
            cout<<"Porfavor digite el puerto a utilizar"<<endl;
            cout <<"Puerto: ";
            string puerto;
            getline(cin, puerto);
            char b[puerto.length()];
            strcpy(b, puerto.c_str());
            for(int i=0;i<puerto.length();i++){
                if((b[i]>=48)&&(b[i]<=57)){

                }else{
                    validarPuerto=false;
                }
            }
            if(validarPuerto){
                cout<<"Se definio el puerto "<<'"'<<puerto<<'"'<<" como el puerto de escucha"<<endl;
                string url="/home/config.sql";
                char link[url.length()];
                strcpy(link, url.c_str());
                string entrada="puerto: "+puerto;
                char nombre_puerto[entrada.length()];
                strcpy(nombre_puerto, entrada.c_str());
                ofstream file;
                file.open(link);
                file << nombre_puerto;
                file.close();
            }else{
                cout<<"El puerto "<<'"'<<puerto<<'"'<<" no es un puerto valido, intente con un numero"<<endl;
            }
            }
        nP++;
    }while(!pasar);
    bool autorizar=false;
    //verificar si es primera sesion para crear carpeta de usuarios, base de datos y configuracion
    limpiaPantalla();
    bool Nusuario=false;
    if(carpetaBD()){
        //Si no hay carpeta BD, se crea
        crearArchivoUsuarios();
        if(crearAdmin()){
            Nusuario=true;
        }else{
            Nusuario=false;
        }
    }else{
        limpiaPantalla();
        //comprobar si hay archivo de usuario en la carpeta
        string direccion=carpeta+"/UwuDB";
        if(comprobar(direccion)){
            //leer archivo
            if(cant_Usuarios()>=1){
                if(login()){
                autorizar=true;
            }
            }else{
                if(crearAdmin()){
                    Nusuario=true;
                }else{
                    Nusuario=false;
            }
            }

        }else{
            //Crear archivo
            crearArchivoUsuarios();
            //leer archivo
            if(crearAdmin()){
                Nusuario=true;
            }else{
                Nusuario=false;
            }
        }
    }
    if(Nusuario){
        if(login()){
            autorizar=true;
        }
    }
    if(autorizar){
    	limpiaPantalla();
        titulo();
        cout<<"Bienvenido "<<_nombre<<"\ndigite "<<'"'<<"INFO;"<<'"'<<" para ver la lista de comandos disponibles"<<endl;
        entrada();
    }else{
        cout<<"Credenciales no validas!"<<endl;
    }
    return 0;
}
void titulo(){
    cout<<"*************************************************************************\n";
    cout<<"***                                                                   ***\n";
    cout<<"***   **      **  **        **  **      **   ********    *********    ***\n";
    cout<<"***   **      **  **        **  **      **   **    ***   **     **    ***\n";
    cout<<"***   **      **  **        **  **      **   **      **  **      **   ***\n";
    cout<<"***   **      **   **  **  **   **      **   **      **  **    **     ***\n";
    cout<<"***   **      **   **  **  **   **      **   **      **  **    **     ***\n";
    cout<<"***   **      **   **  **  **   **      **   **      **  **      **   ***\n";
    cout<<"***    **    **     ***  ***     **    **    **    ***   **     **    ***\n";
    cout<<"***      ****        *    *        ****      ********    *********    ***\n";
    cout<<"***                                                                   ***\n";
    cout<<"*************************************************************************\n";
}
void entrada(){
    int n=0;
    string cad="";
    do{
        cad="";
        vector<string> lista;
        string cadena,c;
        char ultimo;
       do{
            if(cadena=="" && lista.size()==0){
               cout << "UwuDB > ";
            }else{
                cout<<"\t";
            }
            getline(cin, cadena);
            c=limpiarCadena(cadena);
            lista.push_back(c);
            char a[c.length()+1];
            strcpy(a, c.c_str());
            ultimo=a[c.length()-1];
        }while(ultimo!=';');
    for (int i = 0; i < lista.size(); i++){
        cad+=lista[i]+" ";
        }
    cad = limpiarCadena(cad);
    }while(evaluar(cad));
}
bool login(){
    limpiaPantalla();
    string nombre;
    string clave;
    cout<<"Bienvenido a UwuDB"<<endl;
    cout << "Usuario: ";
    getline(cin, nombre);
    cout << "Clave: ";
    getline(cin, clave);
    for(int i=0;i<cant_Usuarios();i++){
        if((ObtenerUsuario(i).getNombre()==nombre)&&(ObtenerUsuario(i).getClave()==SHA256::cifrar(clave))){
            _nombre=ObtenerUsuario(i).getNombre();
            _Crear=ObtenerUsuario(i).getCrear();
            _ElimTabYBd=ObtenerUsuario(i).getElimTabYBd();
            _ElimFila=ObtenerUsuario(i).getElimFila();
            _InsertFila=ObtenerUsuario(i).getInsertFila();
            _Leer=ObtenerUsuario(i).getLeer();
            _Actualizar=ObtenerUsuario(i).getActualizar();
            _Privilegios=ObtenerUsuario(i).getPrivilegios();
            return true;
        }
    }
    return false;
}
bool evaluar(string cadena){
    bool eva = true,verificacion = true;
    char a[cadena.length()+1];//convierte la cadena string en arreglo de caracteres a[]
    strcpy(a, cadena.c_str());
    int contador=0;
    do{
        contador++;
    }while((contador<cadena.length()) && (a[contador]!=' ') && (a[contador]!=';'));//"contador" cuenta la cantidad de letras de la primer palabra del arreglo y la guarda
    //info, usar, crear, editar, eliminar, inspeccionar
    if(cadena!=""){
            string cad="";
            for(int i=0;i<contador;i++){
                cad+=a[i];
            }
            switch(ListaTokens(convertirMayusculas(cad))){
                case 1:
                    info(cadena);
                    break;
                case 2:
                    crear(cadena);
                    break;
                case 3:
                    editar(cadena);
                    break;
                case 4:
                    eliminar(cadena);
                    break;
                case 5:
                    ver(cadena);
                    break;
                case 6:
                    usar(cadena);
                    break;
                case 7:
                    limpiaPantalla();
                    break;
                case 8:
                    if(a[cadena.length()-1]==';'){
                        cout<<"\nUwuDB le desea buen dia ;)\n";
                        eva = false;
                    }else{
                        cout<<"Error! "<<'"'<<cadena<<'"'<<" no valida"<<endl;
                    }
                    break;
                case 9:
                    ejecutar(cadena);
                break;
                case 10:
                    renombrar(cadena);
                break;
                case 11:
                    listar(cadena);
                break;
                case 12:
                    insertar(cadena);
                break;
                default:
                    //si la cadena no se encuentra en la lista de tokens
                    verificacion = false;
                    break;
            }
    if(!verificacion){
        cout<<"Error sintactico "<<'"';
    for(int i=0;i<contador;i++){
        cout<<a[i];
    }
    cout<<'"'<<" no valido\n";
    }
    }
    return eva;
}
int ListaTokens(string cadena){
    //Pasar string cadena -> char a[]
    cadena=limpiarCadena(separarCorchetes(convertirMayusculas(cadena)));
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    /*  ********************************************************************************
        *                               LISTA DE TOKENS                                *
        ********************************************************************************
        *     NUMERO     *                TOKEN                                        *
        *        0       *    CADENA NO LISTADA PERO VALIDA                            *
        *        1       *    INFO                                                     *
        *        2       *    CREAR                                                    *
        *        3       *    EDITAR                                                   *
        *        4       *    ELIMINAR                                                 *
        *        5       *    VER                                                      *
        *        6       *    USAR                                                     *
        *        7       *    LIMPIAR                                                  *
        *        8       *    SALIR                                                    *
        *        9       *    EJECUTAR                                                 *
        *        10      *    RENOMBRAR                                                *
        *        11      *    LISTAR                                                   *
        *        12      *    INSERTAR                                                 *
        *        101     *    BASEDATOS                                                *
        *        102     *    USUARIO                                                  *
        *        103     *    TABLA                                                    *
        *        104     *    TABLAS                                                   *
        *        105     *    BD                                                       *
        *        106     *    EN                                                       *
        *        107     *    REGISTRO                                                 *
        *        201     *    CLAVE                                                    *
        *        202     *    VALORES                                                  *
        *        301     *    ENTERO                                                   *
        *        302     *    DECIMAL                                                  *
        *        303     *    CARACTER                                                 *
        *        304     *    LLAVE                                                    *
        *        305     *    PRIMARIA                                                 *
        *        501     *    ENTERO [ ### ]                                           *
        *        502     *    DECIMAL [ ### ]                                          *
        *        503     *    CARACTER [ ### ]                                         *
        ********************************************************************************
        *     ERRORES    *                                                             *
        *       -1       *    CARACTERES NO VALIDOS -> !"#$%&/()=???*[*???;:_ etc...       *
        *       -2       *    VARIABLE DETECTADA PERO, LO QUE HAY EN LOS CORCHETES     *
        *                *    NO ES NUMERO O TIENE ESPACIO ej. ENTERO[hola]            *
        *       -3       *    VARIABLE DETECTADA PERO NO HAY PARAMETROS -> variable[]  *
        ********************************************************************************
    */

    int id=0;
    if(cadena=="INFO")id=1;
    else if(cadena=="CREAR") id=2;
    else if(cadena=="EDITAR") id=3;
    else if(cadena=="ELIMINAR") id=4;
    else if(cadena=="VER") id=5;
    else if(cadena=="USAR") id=6;
    else if(cadena=="LIMPIAR") id=7;
    else if(cadena=="SALIR") id=8;
    else if(cadena=="EJECUTAR") id=9;
    else if(cadena=="RENOMBRAR") id=10;
    else if(cadena=="LISTAR") id=11;
    else if(cadena=="INSERTAR") id=12;

    else if(cadena=="BASEDATOS") id=101;
    else if(cadena=="USUARIO") id=102;
    else if(cadena=="TABLA") id=103;
    else if(cadena=="TABLAS") id=104;
    else if(cadena=="BD") id=105;
    else if(cadena=="EN") id=106;
    else if(cadena=="REGISTRO") id=107;

    else if(cadena=="CLAVE") id=201;
    else if(cadena=="VALORES") id=202;

    else if(cadena=="ENTERO") id=301;
    else if(cadena=="DECIMAL") id=302;
    else if(cadena=="CARACTER") id=303;

    else if(cadena=="LLAVE") id=304;
    else if(cadena=="PRIMARIA") id=305;

    //comprobar que el token no comience con numero
    if((a[0]>=48)&&(a[0]<=57)){
        return -1;
    }
    //Lista de tokens de variables ENTERO [ ### ] DECIMAL [ ### ] CARACTER [ ### ]
    //ENTERO [ ### ]
    int variable=0;
    if((cadena.length()>=10)&&(a[0]=='E')&&(a[1]=='N')&&(a[2]=='T')&&(a[3]=='E')&&(a[4]=='R')&&(a[5]=='O')&&(a[6]==' ')&&(a[7]=='[')&&(a[cadena.length()-1]==']')&&(a[cadena.length()-2]==' ')){
        variable=1;
    }
    //DECIMAL [ ### ]
    else if((cadena.length()>=11)&&(a[0]=='D')&&(a[1]=='E')&&(a[2]=='C')&&(a[3]=='I')&&(a[4]=='M')&&(a[5]=='A')&&(a[6]=='L')&&(a[7]==' ')&&(a[8]=='[')&&(a[cadena.length()-1]==']')&&(a[cadena.length()-2]==' ')){
        variable=2;
    }
    //CARACTER [ ### ]
    else if((cadena.length()>=12)&&(a[0]=='C')&&(a[1]=='A')&&(a[2]=='R')&&(a[3]=='A')&&(a[4]=='C')&&(a[5]=='T')&&(a[6]=='E')&&(a[7]=='R')&&(a[8]==' ')&&(a[9]=='[')&&(a[cadena.length()-1]==']')&&(a[cadena.length()-2]==' ')){
        variable=3;
    }
    //si detect??? alguna variable, se asegurar??? que hay numero entre corchete
    if(variable>0){
        if((variable==1)&&(cadena.length()==10)) return -3;
        else if((variable==2)&&(cadena.length()==11)) return -3;
        else if((variable==3)&&(cadena.length()==12)) return -3;
        else{
        string Corchetes="";

        for(int i=(8+variable);i<(cadena.length()-2);i++){
            Corchetes+=a[i];
        }
        char b[Corchetes.length()+1];
        strcpy(b, Corchetes.c_str());
        for(int i=0;i<Corchetes.length();i++){
            if((b[i]>=48)&&(b[i]<=57)){

            }else{
                return -2; //SI NO HAY NUMERO EN CORCHETES, RETORNA
            }
        }
        return (variable+500);
    }
    }
    //comprobar que el token no posea un caracter invalido
    bool invalido=false;
    for(int i=0;i<cadena.length();i++){
        if(((a[i]>=65)&&(a[i]<=90))||((a[i]>=48)&&(a[i]<=57))||(a[i]=='-')||(a[i]=='_')){invalido=false;}
        else{
        invalido=true;
        return -1;}}
    if(invalido) id = -1;
    return id;
}


//*************************************************************************************************************
//**************************************        COMANDOS      *************************************************
//*************************************************************************************************************

//---------------------------------------
//FUNCIONES TIENEN QUE VER CON LOS USUARIOS
int cant_Usuarios(){
    string url=ubicacion();
    string cadena = url+"/UwuDB.sql";
    string texto=leer(cadena);
    char arreglo[texto.length()+1];
    strcpy(arreglo, texto.c_str());

    int cantidad=-3;
    cadena="";
    //Cuenta cuantos usuarios se encuentran almacenados y lo guarda en "cantidad" y almacena en "cadena" los usuarios
    for(int i=0;i<texto.length();i++){
        if(arreglo[i]=='#'){
                cantidad++;
        }
        if(cantidad>=0){
            cadena+=arreglo[i+1];
        }
    }
    return cantidad;
}
bool crearAdmin(){
    string url=ubicacion()+"/UwuDB.sql";
    string r;
    string usuario;
    string contra;
    cout<<"Bienbenido a UwuDB\n"<<endl;
    cout<<"No se detectaron usuarios registrados"<<endl;
    cout<<"Desea crear uno?Y/N "<<endl;
    getline(cin, r);
    if((r=="y")||(r=="Y")){
        limpiaPantalla();
        cout<<"Creando usuario admin"<<endl;
        cout<<"Digite su nombre de usuario: ";
        getline(cin, usuario);
        cout<<"Digite su clave de usuario: ";
        getline(cin, contra);
        /////////////////////////////////////////////////////////////////////
        string cadena=usuario+";"+SHA256::cifrar(contra)+";1;1;1;1;1;1;1#";
        ////////////////////////////////////////////////////////////////////
        escribir(url,cadena);
        cout<<"Usuario creado"<<endl;
        return true;
    }else if((r=="n")||(r=="N")){
        evaluar("salir;");
    }else{
        cout<<'"'<<r<<'"'<<" No es valido, no se creo un nuevo usuario"<<endl;
    }
    return false;
}
//FIN    FUNCIONES TIENEN QUE VER CON LOS USUARIOS

//---------------------------------------
//FUNCIONES DE COMANDOS A USAR *
//Crear base de datos, usuario y tablas
void insertar(string cadena){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    int contador=0;
    string parte1="";
    string parte2="";
    for(int i=0;i<cadena.length();i++){
        if(a[i]==';'){
            contador++;
        }
        if(contador==0){
            parte1+=a[i];
        }
    }
    if(contador>1){
        for(int i=parte1.length()+1;i<cadena.length();i++){
            parte2+=a[i];
        }
        cadena=limpiarCadena(parte1+";");
        parte2=limpiarCadena(parte2);
    }
    cadena=limpiarCadena(separarParentesis(cadena));
    char b[cadena.length()];
    strcpy(b, cadena.c_str());
    if(cadena.length()==9){
        cout<<"Error! no se detecto nada para INSERTAR"<<endl;
    }else{
        string argumento2=obtenerPalabra(cadena,2);
        if(ListaTokens(argumento2)==106){
        if(cadena.length()==12){
            cout<<"Error! se esperaba el nombre de la tabla"<<endl;
        }else{
        string argumento3=obtenerPalabra(cadena,3);
        if(_dataBase==""){
            cout<<"Error! no se pudo buscar la tabla "<<'"'<<argumento3<<'"'<<" por que no hay una base de datos seleccionada"<<endl;
        }else{
            if(ListaTokens(argumento3)==0){
            if(cadena.length()==(13+argumento3.length())){
                cout<<"Error! se esperaban los valores a insertar"<<endl;
            }else{
                string argumento4=obtenerPalabra(cadena,4);
                if(ListaTokens(argumento4)==202){
                    if(cadena.length()==(14+argumento3.length()+argumento4.length())){
                        cout<<"Error! se esperaban los valores a insertar"<<endl;
                    }else{
                    string argumento5=obtenerPalabra(cadena,5);
                    if(argumento5=="("){
                    if(b[cadena.length()-2]==')'){
                        if(cadena.length()==(25+argumento3.length())){
                            cout<<"Error! No se detectaron valores a insertar! ingrese algunos entre parantesis"<<endl;
                        }else{
                        vector<string> lista = nombresTablas();
                        bool encontrada=false;
                        for(int i=0;i<lista.size();i++){
                            if(lista[i]==argumento3){
                                encontrada=true;
                            }
                        }
                        if(encontrada){
                        string argumentos="";
                        for(int i=(23+argumento3.length());i<(cadena.length()-3);i++){
                            argumentos+=b[i];
                        }
                        //SI LLEGAMOS AQUI, ES POR QUE SE LA SINTAXIS DE LA INSERCION ES BUENA, AHORA FALTA VER SI LOS DATOS CONCUERDAN
                        if(evaluarValoresTabla(argumento3,argumentos)){
                            //TODO ESTA BIEN, AHORA VAMOS A INSERTARLOS :D
                            vector<string> datos = listaDatos(argumentos);
                            vector<string> datosParaInsercion;
                            for(int i=0;i<datos.size();i++){
                                char arreglofinal[datos[i].length()];
                                strcpy(arreglofinal, datos[i].c_str());
                                string cadena2="";
                                if(arreglofinal[0]==39){
                                    for(int j=1;j<datos[i].length()-1;j++){
                                        cadena2+=arreglofinal[j];
                                    }
                                    cadena2=limpiarCadena(cadena2);
                                    datosParaInsercion.push_back(cadena2);
                                }else{
                                    datosParaInsercion.push_back(datos[i]);
                                }
                            }
                            //datos ParaInsercion CONTIENE LOS DATOS VALIDOS PARA INSERTAR
                            string cadenaInsercion=datosParaInsercion[0];
                            for(int i=1;i<datosParaInsercion.size();i++){
                                cadenaInsercion+=";"+datosParaInsercion[i];
                            }
                            cadenaInsercion+="#";
                            //LLEGAMOS HASTA AQUI Y TODO ES VALIDO, PROCEDEMOS A INSERTAR LOS VALORES
                            if(_InsertFila){
                                insertarEnTabla(argumento3,cadenaInsercion,datosParaInsercion[0],parte2);
                            }else{
                                cout<<"Lo sentimos pero este usuario no tiene los permisos de insercion"<<endl;
                            }
                        }else{
                            cout<<"No se pudieron insertar los valores!"<<endl;
                        }
                        }else{
                            cout<<"No se encontro la tabla "<<'"'<<argumento3<<'"'<<" intente con "<<'"'<<"LISTAR TABLAS;"<<'"'<<" para ver la lista de tablas creadas"<<endl;
                        }
                        }
                    }else{
                        cout<<"Error! se esperaba "<<'"'<<")"<<'"'<<" al final de la cadena"<<endl;
                    }
                    }else{
                        cout<<"Error! se esperaba "<<'"'<<"("<<'"'<<" al inicio de los valores"<<endl;
                    }
                }
                }else{
                    cout<<"Error! "<<'"'<<argumento4<<'"'<<" no es valido! en su lugar se esperaba "<<'"'<<"VALORES"<<'"'<<endl;
                }
            }
            }else if(ListaTokens(argumento3)==-1){
                cout<<"Error! "<<'"'<<argumento3<<'"'<<" contiene caracteres no validos"<<endl;
            }else{
                cout<<"Error! "<<'"'<<argumento3<<'"'<<" es una palabra reservada"<<endl;
            }
        }
        }
        }else if(ListaTokens(argumento2)==-1){
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" contiene caracteres no validos"<<endl;
        }else{
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" no valido para "<<'"'<<"INSERTAR"<<'"'<<endl;
            cout<<"Intente con "<<'"'<<"INFO INSERTAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"INSERTAR"<<'"'<<endl;
        }
    }

}
void usar(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    if(cadena.length()==5){
        cout<<"Error: "<<'"'<<"USAR"<<'"'<<" necesita mas argumentos"<<endl;
        cout<<"Intente con "<<'"'<<"INFO USAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"USAR"<<'"'<<endl;
    }else{
        string argumento2=obtenerPalabra(cadena,2);
        if(cadena.length() == (argumento2.length()+5)){
            cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
            cout<<"Intente con "<<'"'<<"INFO USAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"USAR"<<'"'<<endl;
        }else{
            if(a[argumento2.length()+5]==';'){
            if(ListaTokens(convertirMayusculas(argumento2))==0){
            string enlaceBD=ubicacion()+"/";
            if(comprobar(enlaceBD+argumento2)){
                _dataBase=argumento2;
                cout<<"Base de datos " <<'"'<<_dataBase<<'"'<<" seleccionada"<<endl;
            }else{
                cout<<"La base de datos "<<'"'<<argumento2<<'"'<<" no existe"<<endl;
            }
            if(cadena.length() > (argumento2.length()+6)){
                string exceso="";
                for(int i=argumento2.length()+6;i<cadena.length();i++){
                    exceso+=a[i];
                }
                evaluar(limpiarCadena(exceso));
            }}
            else{
                cout<<"Error! "<<'"'<<argumento2<<'"'<<" no es un nombre de base de datos"<<endl;
            }
            }else{
                cout<<"Error! demasiados argumentos"<<endl;
                cout<<"Intente con "<<'"'<<"INFO USAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"USAR"<<'"'<<endl;
            }
        }
    }
}
void crear(string cadena){
    cadena=limpiarCadena(separarParentesis(cadena));
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    int contador=0;
    if(cadena.length()==6){
        cout<<"Error: "<<'"'<<"CREAR"<<'"'<<" necesita mas argumentos"<<endl;
        cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
    }else{
    string argumento2=obtenerPalabra(cadena,2);
    switch(ListaTokens(convertirMayusculas(argumento2))){
        case 1:
            //token 1 -> INFO
            if(cadena.length()==11){
                infoCrear();
            }else{
                cout<<"Error! "<<'"'<<cadena<<'"'<<" no valido"<<endl;
            }
            break;
        case 101:
            {
            //token 101 -> BASEDATOS
            if(cadena.length()==15){
                cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
            }else if(a[15]==';'){
                cout<<"Error: Se requiere el nombre de la base de datos"<<endl;
            }
            else{
                string argumento3=obtenerPalabra(cadena,3);
                int cantTokens=1;
                int k=0;
                do{
                    if(a[k]==' '){
                        cantTokens++;
                    }
                    k++;
                }while((a[k]!=';') && (k!=cadena.length()));
                bool Punto_Y_Coma=true;
                bool despues=true;
                if(cadena.length()==k)Punto_Y_Coma=false;
                if(k==cadena.length()-1)despues=false;
                string cadena2="";
                if((Punto_Y_Coma) && (cantTokens==3)){
                    if(ListaTokens(convertirMayusculas(argumento3))==0){
                    if(_Crear){
                        crearBaseDeDatos(argumento3);
                    }else{
                        cout<<"El usuario "<<'"'<<_nombre<<'"'<<" no cuenta con los permisos necesarios"<<endl;
                    }
                    if(despues){
                    for(int i=0;i<cadena.length()-k-1;i++){
                        cadena2+=a[i+k+1];
                    }}}else{
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" no se puede usar como nombre de base de datos"<<endl;}
                }else{
                    cout<<"Error: No se pudo crear la base de datos "<<'"'<<argumento3<<'"'<<endl;
                    cout<<"se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
                }
                evaluar(limpiarCadena(cadena2));
            }
            }
            break;
        case 102:
            {
            //token 102 -> USUARIO
            if(cadena.length() == 13){
                cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
            }else{
            if(a[13]==';'){
                cout<<"Error! falta el nombre del usuario"<<endl;
                cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
            }else{
                string argumento3=obtenerPalabra(cadena,3);
                //Evaluar el resto de la cadena
                if(cadena.length() == (argumento3.length()+14)){
                    cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
                }
                else{
                if(ListaTokens(convertirMayusculas(argumento3))==0){
                    if(a[7+argumento2.length()+argumento3.length()]==';'){
                        cout<<"Error! falta la clave de usuario"<<endl;
                    }
                    else{
                    string argumento4=obtenerPalabra(cadena,4);
                    int longitud = 8+argumento2.length()+argumento3.length()+argumento4.length();
                    if(ListaTokens(convertirMayusculas(argumento4))==201){
                        if(cadena.length() == longitud){
                            cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                        }else{
                        if((cadena.length() == (longitud+1)) && (a[longitud]==';')){
                            cout<<"Error! se esperaba la clave"<<endl;
                            cout<<"Por favor ingrese su clave de usuario entre comillas simples '' "<<endl;
                        }else{
                        //programacion que recibira la clave -> 'clave'
                        int cont=longitud+1;
                        string cadena2="";
                        string sobrante="";
                        bool puntoYcoma=false;
                        while(cont<cadena.length() && a[cont]!=';'){
                            cadena2+=a[cont];
                            if(a[cont+1]==';'){
                                puntoYcoma=true;
                            }
                            cont++;
                        }
                        if(puntoYcoma){
                        char arreglo2[cadena2.length()+1];
                        strcpy(arreglo2, cadena2.c_str());
                        bool primero=false;
                        bool ultimo=false;
                        if(arreglo2[0]==39)primero=true;
                        if(arreglo2[cadena2.length()-1]==39)ultimo=true;
                        if(primero && ultimo){
                            string cadena3="";
                            for(int i=1;i<cadena2.length()-1;i++){cadena3+=arreglo2[i];}
                            cadena3 = limpiarCadena(cadena3);
                            //verificar si lo que hay entre '' es valido
                            bool comilla=false;//si hay comillas dentro de comillas '  hola' mu'ndo  '
                            bool masDuna=false;//si hay mas de un argumento dentro de las comillas
                            char arreglo3[cadena3.length()+1];
                            strcpy(arreglo3, cadena3.c_str());
                            for(int i=0;i<cadena3.length();i++){
                                if(arreglo3[i]==39)comilla=true;
                                if(arreglo3[i]==' ')masDuna=true;}
                            if(comilla)cout<<"Error! contrasena no valida. mala implementacion de comillas '"<<endl;
                            else if(masDuna)cout<<"la clave no puede tener espacios"<<endl;
                            else if(cadena3=="")cout<<"Error! no se detecto la clave!"<<endl;
                            else {
                                if(_Crear){
                                string temporal=_dataBase;
                                _dataBase="UwuDB";
                                vector<string> nombresU = obtenerListaId("USUARIOS");
                                bool Urepetido=false;
                                for(int i=0;i<nombresU.size();i++){
                                    if(argumento3==nombresU[i]){
                                        Urepetido = true;
                                    }
                                }
                                if(Urepetido){
                                    cout<<"No se pudo crear el usuario por que ya se encuentra registrado"<<endl;
                                }else{
                                    ////////////////////////////////////////////////////////////////////////////////////
                                    string cadena_usuario=argumento3+";"+SHA256::cifrar(cadena3)+";0;0;0;0;0;0;0#";
                                    ////////////////////////////////////////////////////////////////////////////////////
                                    string enlaceBD=ubicacion()+"/UwuDB.sql";
                                    escribir(enlaceBD,cadena_usuario);
                                    cout<<"Usuario "<<'"'<<argumento3<<'"'<<" creado"<<endl;
                                }

                                }else{
                                    cout<<"El usuario "<<'"'<<_nombre<<'"'<<" no cuenta con los permisos necesarios"<<endl;
                                }
                                int contar=0;
                                while(a[contar]!=';'){
                                    contar++;
                                }
                                string paraEvaluar="";
                                int _longitud=contar+1;
                                if(_longitud<cadena.length()){
                                    for(int i=_longitud;i<cadena.length();i++){
                                        paraEvaluar+=a[i];
                                    }
                                    evaluar(limpiarCadena(paraEvaluar));
                                }}
                        }else{
                            cout<<"Error! falta de clave de usuario 'clave' "<<endl;
                            cout<<"Intente con: CREAR USUARIO nombre_usuario CLAVE 'clave_usuario';"<<endl;
                        }
                        }else{
                            cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                        }}}
                    }else{
                        cout<<"Error! se esperaba "<<'"'<<"CLAVE"<<'"'<<" luego del nombre de usuario"<<endl;
                        cout<<"Intente con: CREAR USUARIO nombre_usuario CLAVE 'clave_usuario';"<<endl;
                    }}}
                else{
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" no se puede usar como nombre de usuario"<<endl;
                }}}}}
            break;
        case 103:
            //token 103 -> TABLA
            if(cadena.length()==12){
                cout<<"Error! se esperaba el nombre de la tabla"<<endl;
                cout<<"Intente con "<<'"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
            }else{
                string argumento3=obtenerPalabra(cadena,3);
                if(convertirMayusculas(argumento3)=="INFO"){
                    if(a[16]==';'){
                        infoTabla();
                        if(cadena.length()>17){
                            string exceso="";
                            for(int i=18;i<cadena.length();i++){
                                exceso+=a[i];
                            }
                            evaluar(limpiarCadena(exceso));
                        }
                    }else{
                        cout<<"Error! "<<'"'<<cadena<<'"'<<" con el comando INFO mala implementacion"<<endl;
                    }
                }else{
                    argumento3=obtenerPalabra(cadena,3);
                    if(ListaTokens(convertirMayusculas(argumento3))==0){
                        //llegamos a "CREAR TABLA nombre"
                        //Ahora validamos que no halla exceso en la linea de comandos "crear tabla nombre(); EXCESO DE ARGUMENTOS; "
                        string cadenaParte1="";
                        string cadenaParte2="";
                        int exceso=-1;
                        for(int i=0;i<cadena.length();i++){if(a[i]==';'){exceso++;}}
                        int contar=0;
                        //exceso guarda cuantos ";" hay en toda la instruccion "CREAR TABLA nombre(); USAR BD hola; aaaahhh;" = 2 instrucciones de mas
                        if(exceso>=1){//si hay una o mas instrucciones despues de ";" las separar???
                            do{
                                cadenaParte1+=a[contar];
                                contar++;
                            }while(a[contar]!=';');
                            cadenaParte1+=";";
                            for(int i=contar+1;i<cadena.length();i++){
                                cadenaParte2+=a[i];
                            }
                            cadenaParte2=limpiarCadena(cadenaParte2);
                        }else{
                            cadenaParte1=cadena;
                        }
                        char b[cadenaParte1.length()+1];
                        strcpy(b,cadenaParte1.c_str());
                        if(obtenerPalabra(cadenaParte1,4)=="("){
                            if(b[cadenaParte1.length()-2]==')'){
                                //Si llegamos a esta linea de codigo significa que evaluamos correctamente que se escribiera CREAR TABLA nombre(#####);
                                //ahora hay que evaluar que lo que esto entre los parentecis sea correcto (############);
                                string interior="";
                                for(int i=(argumento3.length()+15);i<cadenaParte1.length()-3;i++){
                                    interior+=b[i];
                                }
                                //la variable -> "interior" posee los parametros de la creacion de la tabla ( parametros )
                                if(evaluarTabla(interior,argumento3)){
                                    //SI EVALUAR TABLA DEVUELVE VERDADERO SIGNIFICA QUE TODA LA CADENA INGRESADA ES VALIDA
                                    if(_Crear){
                                        crearTabla(argumento3,interior,cadenaParte2);
                                    }else{
                                        cout<<"Este usuario no cuenta con los permisos necesarios para crear tablas"<<endl;
                                    }
                                }else{
                                    cout<<"No se pudo crear la tabla "<<argumento3<<endl;
                                }
                            }else{
                                cout<<"Error! se esperaba "<<'"'<<")"<<'"'<<" al final de creacion de tabla"<<endl;
                            }
                        }else{
                            cout<<"Error! luego de "<<'"'<<argumento3<<'"'<<" se esperaba "<<'"'<<"("<<'"'<<endl;
                        }
                    }else if(argumento3=="("){
                        cout<<"Error! se necesita el nombre de la tabla!"<<endl;
                    }else if(ListaTokens(convertirMayusculas(argumento3))==-1){
                        cout<<"Error! "<<'"'<<argumento3<<'"'<<" no valido"<<endl;
                    }else{
                        cout<<"Error! "<<'"'<<argumento3<<'"'<<" es una palabra reservada"<<endl;
                    }
                }
            }
            break;
        default:
            cout<<"Error: "<<'"'<<argumento2<<'"'<<" argumento no valido para "<<'"'<<"CREAR"<<'"'<<"\nIntente con "<<
            '"'<<"INFO CREAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"CREAR"<<'"'<<endl;
            break;
    }
    }
}
void editar(string cadena){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    int contador=0;
    string parte1="";
    string parte2="";
    for(int i=0;i<cadena.length();i++){
        if(a[i]==';'){
            contador++;
        }
        if(contador==0){
            parte1+=a[i];
        }
    }
    if(contador>1){
        for(int i=parte1.length()+1;i<cadena.length();i++){
            parte2+=a[i];
        }
        cadena=limpiarCadena(parte1+";");
        parte2=limpiarCadena(parte2);
    }
    cadena=limpiarCadena(separarParentesis(cadena));
    char b[cadena.length()];
    strcpy(b, cadena.c_str());

    if(cadena.length()==7){
        cout<<"Error el comando "<<'"'<<"EDITAR"<<'"'<<" necesita mas argumentos"<<endl;
        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
    }else{
        string argumento2=obtenerPalabra(cadena,2);
        if(ListaTokens(argumento2)==0){
            if(cadena.length()==8+argumento2.length()){
                cout<<"Error! se esperaba "<<'"'<<"LLAVE"<<'"'<<" luego de "<<argumento2<<endl;
                cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
            }else{
                string argumento3=obtenerPalabra(cadena,3);
                if(ListaTokens(argumento3)==304){
                    if(cadena.length()==14+argumento2.length()){
                        cout<<"Error! se esperaba el valor de la llave primaria de los datos a editar"<<endl;
                        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                    }else{
                        string argumento4 = obtenerPalabra(cadena,4);
                        char arg4[argumento4.length()];
                        strcpy(arg4, argumento4.c_str());
                        bool pasar = true;
                        for(int i=0;i<argumento4.length();i++){
                            if((arg4[i]>=48)&&(arg4[i]<=57)){
                            }else if((arg4[i]>=65)&&(arg4[i]<=90)){
                            }else if((arg4[i]>=97)&&(arg4[i]<=122)){
                            }else if((arg4[i]=='.')||(arg4[i]=='_')||(arg4[i]=='-')||(arg4[i]==',')){
                            }else{
                                pasar=false;
                            }
                        }
                        if(pasar){
                            if(cadena.length()==15+argumento2.length()+argumento4.length()){
                                cout<<"Error! se esperaban los parametros a editar"<<endl;
                                cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                            }else{
                                if(_dataBase!=""){
                                string argumento5=obtenerPalabra(cadena,5);
                                if(argumento5=="("){
                                if(cadena[cadena.length()-2]==')'){
                                    string interior="";
                                    for(int i=16+argumento2.length()+argumento4.length();i<cadena.length()-2;i++){
                                        interior+=cadena[i];
                                    }
                                    if(interior==" ) ( "){
                                        cout<<"Error! no se detectaron los parametros de edicion"<<endl;
                                        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                    }else{
                                    int izquierda=0,derecha=0;
                                    for(int i=0;i<interior.length();i++){
                                        if(interior[i]=='('){
                                            izquierda++;
                                        }
                                        if(interior[i]==')'){
                                            derecha++;
                                        }
                                    }
                                    if((izquierda==1)&&(derecha==1)){
                                        if(interior[1]==')'){
                                            cout<<"No se detectaron los nombres de las columnas (primer parentesis)"<<endl;
                                            cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                        }else if(interior[interior.length()-2]=='('){
                                            cout<<"No se detectaron los nombres de los datos (segundo parentesis)"<<endl;
                                            cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                        }else{
                                            //SI LLEGAMOS AQUI EL USUARIO DIGITO EDITAR nombre LLAVE id (#####)(#####);
                                            //Falta comprobar si el contenido de los parentesis en valido
                                            vector<string> listaT = nombresTablas();
                                            bool encontrado=false;
                                            for(int i=0;i<listaT.size();i++){
                                                if(argumento2==listaT[i]){
                                                    encontrado=true;
                                                }
                                            }
                                            if(encontrado){
                                            encontrado=false;
                                            vector<string> listaID = obtenerListaId(argumento2);
                                            for(int i=0;i<listaID.size();i++){
                                                if(argumento4==listaID[i]){
                                                    encontrado=true;
                                                }
                                            }
                                            if(encontrado){
                                                string resultado1="";
                                                string resultado2="";
                                                int _contador=0;
                                                while(interior[_contador]!=')'){
                                                    resultado1+=interior[_contador];
                                                    _contador++;
                                                }
                                                for(int i=_contador+3;i<interior.length();i++){
                                                    resultado2+=interior[i];
                                                }
                                                editarTabla(argumento2,argumento4,resultado1,resultado2,parte2);
                                            }else{
                                                cout<<"Error! no se encontro ningun registro con llave primaria "<<'"'<<argumento4<<'"'<<endl;
                                            }
                                            }else{
                                                cout<<"Error! la tabla "<<'"'<<argumento2<<'"'<<" no existe"<<endl;
                                            }
                                        }
                                    }else if(izquierda>derecha){
                                        cout<<"Error! falta "<<'"'<<")"<<'"'<<endl;
                                        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                    }else if(izquierda<derecha){
                                        cout<<"Error! falta "<<'"'<<"("<<'"'<<endl;
                                        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                    }else{
                                        cout<<"Error! se detectaron demasiados parentesis en la peticion"<<endl;
                                        cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                    }

                                    }
                                }else{
                                    cout<<"Error! se esperaba "<<'"'<<")"<<'"'<<" al final de la linea"<<endl;
                                    cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                }
                                }else{
                                    cout<<"Error! "<<'"'<<argumento5<<'"'<<" no valido! en su lugar se esperaba "<<'"'<<"("<<'"'<<endl;
                                    cout<<"Intente con "<<'"'<<"INFO EDITAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"EDITAR"<<'"'<<endl;
                                }
                                }else{
                                    cout<<"No se a seleccionado ninguna base de datos"<<endl;
                                }
                            }
                        }else{
                            cout<<"Error! se detectaron caracteres invalidos en "<<argumento4<<endl;
                        }
                    }
                }else if(ListaTokens(argumento3)==-1){
                    cout<<"Error! se detectaron caracteres invalidos en "<<'"'<<argumento3<<'"'<<endl;
                }else if(ListaTokens(argumento3)==0){
                    cout<<"Error! no se reconoce "<<'"'<<argumento3<<'"'<<endl;
                }else{
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" no es valido"<<endl;
                }
            }
        }else if(ListaTokens(argumento2)==-1){
            cout<<"Error! se detectaron caracteres invalidos en "<<'"'<<argumento2<<'"'<<endl;
        }else{
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" es una palabra reservada"<<endl;
        }
    }
}
void eliminar(string cadena){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    int contador=0;
    string parte1="";
    string parte2="";
    for(int i=0;i<cadena.length();i++){
        if(a[i]==';')contador++;
        if(contador==0)parte1+=a[i];
    }
    if(contador>1){
        for(int i=parte1.length()+1;i<cadena.length();i++)parte2+=a[i];
        cadena=limpiarCadena(parte1+";");
        parte2=limpiarCadena(parte2);
    }
    if(cadena.length()==9){
        cout<<"Error! no se detectaron datos a eliminar"<<endl;
        cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
    }else{
        string argumento2 = obtenerPalabra(cadena,2);
        if(ListaTokens(argumento2)==103){
            //ELIMINAR TABLA
            if(cadena.length()==15){
                cout<<"Error! ingrese el nombre de la tabla que desea eliminar"<<endl;
                cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
            }else{
                string argumento3 = obtenerPalabra(cadena,3);
                if(ListaTokens(argumento3)==0){
                    if(parte1.length()==15+argumento3.length()){
                        if(_dataBase!=""){
                            vector<string> lista = nombresTablas();
                            bool validar=false;
                            for(int i=0;i<lista.size();i++){
                                if(argumento3==lista[i]){
                                    validar=true;
                                }
                            }
                            if(validar){
                                if(_dataBase=="UwuDB"){
                                    cout<<"ALERTA! las tablas almacenadas en "<<'"'<<"UwuDB"<<'"'<<" no pueden ser eliminadas!"<<endl;
                                }else{
                                string respuesta;
                                cout<<"Esta seguro de eliminar la tabla "<<'"'<<argumento3<<'"'<<"? esta accion no se podra deshacer"<<endl;
                                cout<<"1. Si"<<endl;
                                cout<<"2. No"<<endl;
                                getline(cin, respuesta);
                                if((convertirMayusculas(respuesta) == "SI")||(respuesta=="1")||(convertirMayusculas(respuesta) == "SI;")||(respuesta=="1;")){
                                    vector<string> listaT = listaDeTablas();
                                    string insersionFinal="";
                                    for(int i=0;i<listaT.size();i++){
                                        if(lista[i]!=argumento3){
                                            insersionFinal+=("$"+listaT[i]+"#");
                                        }
                                    }
                                    if(insersionFinal==""){
                                        insersionFinal=" ";
                                    }
                                    string link=ubicacion()+"/"+_dataBase+".sql";
                                    if(_ElimTabYBd){
                                        reemplazar(link,insersionFinal);
                                        cout<<"Tabla "<<'"'<<argumento3<<'"'<<" eliminada exitosamente"<<endl;
                                    }else{
                                        cout<<"Este usuario no cuenta con los permisos para eliminar tablas"<<endl;
                                    }
                                    if(parte2!=""){
                                        evaluar(parte2);
                                    }
                                }else{
                                    cout<<"No se elimino la tabla "<<'"'<<argumento3<<'"'<<endl;
                                }}
                            }else{
                                cout<<"No se encontro la tabla "<<'"'<<argumento3<<'"'<<" en la base de datos "<<'"'<<_dataBase<<'"'<<endl;
                            }
                        }else{
                            cout<<"Error! no hay ninguna base de datos seleccionada"<<endl;
                            cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                        }
                    }else{
                        cout<<"Error! "<<'"'<<parte1<<'"'<<" contiene demasiados argumentos"<<endl;
                        cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                    }
                }else if(ListaTokens(argumento3)==-1){
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" contiene caracteres no validos"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                }else{
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" no valido para ELIMINAR"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                }
            }
        }else if(ListaTokens(argumento2)==106){
            //ELIMINAR REGISTRO
            if(cadena.length()==12){
                cout<<"Error! falta el nombre de la tabla"<<endl;
                cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
            }else{
                string argumento3 = obtenerPalabra(cadena,3);
                if(ListaTokens(argumento3)==0){
                    if(_dataBase!=""){
                        vector<string> tablas = nombresTablas();
                        bool aprobar=false;
                        for(int i=0;i<tablas.size();i++){
                            if(argumento3==tablas[i]){
                                aprobar=true;
                            }
                        }
                        if(aprobar){
                            if(cadena.length()==13+argumento3.length()){
                                cout<<"Error! se esperaba "<<'"'<<"LLAVE"<<'"'<<endl;
                                cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                            }else{
                                string argumento4 = obtenerPalabra(cadena,4);
                                if(ListaTokens(argumento4)==304){
                                    if(cadena.length()==19+argumento3.length()){
                                        cout<<"Error! ingrese a continuacion el valor de la llave primaria de la fila que desea eliminar"<<endl;
                                        cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                                    }else{
                                        string argumento5 = obtenerPalabra(cadena,5);
                                        if(cadena.length()==(20+argumento3.length()+argumento5.length())){
                                            //SI ESTAMOS AQUI SE COMPROBO QUE LA SOLICITUD DE ELIMINACION ES VALIDA
                                            char arg5[argumento5.length()];
                                            strcpy(arg5, argumento5.c_str());
                                            bool pasar = true;
                                            for(int i=0;i<argumento5.length();i++){
                                                if((arg5[i]>=48)&&(arg5[i]<=57)){
                                                }else if((arg5[i]>=65)&&(arg5[i]<=90)){
                                                }else if((arg5[i]>=97)&&(arg5[i]<=122)){
                                                }else if((arg5[i]=='.')||(arg5[i]=='_')||(arg5[i]=='-')||(arg5[i]==',')){
                                                }else{
                                                    pasar=false;
                                                }
                                            }
                                            if(pasar){
                                                pasar = false;
                                                vector<string> lista_Llaves_Primarias = obtenerListaId(argumento3);
                                                for(int i=0;i<lista_Llaves_Primarias.size();i++){
                                                    if(argumento5==lista_Llaves_Primarias[i]){
                                                        pasar=true;
                                                    }
                                                }
                                                if(pasar){
                                                    if(_ElimFila){
                                                        eliminarFila(argumento3,argumento5);
                                                        if(parte2!=""){
                                                        evaluar(parte2);
                                                        }
                                                    }else{
                                                        cout<<"Este usuario no cuenta con los permisos para eliminar registros"<<endl;
                                                    }
                                                }else{
                                                    cout<<"No se encontro ningun resistro con la llave primaria "<<'"'<<argumento5<<'"'<<endl;
                                                }
                                            }else{
                                                cout<<"Error! se detectaron caracteres no validos en "<<'"'<<argumento5<<'"'<<endl;
                                                cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                                            }
                                        }else{
                                            cout<<"Error! se detectaron demasiados argumentos en la solicitud"<<endl;
                                            cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                                        }
                                    }
                                }else if(ListaTokens(argumento4)==-1){
                                    cout<<"Error! "<<'"'<<argumento4<<'"'<<" contiene caracteres invalidos"<<endl;
                                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                                }else{
                                    cout<<"Error! "<<'"'<<argumento4<<'"'<<" no valido para ELIMINAR"<<endl;
                                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                                }
                            }
                        }else{
                            cout<<"La tabla "<<'"'<<argumento3<<'"'<<" no existe"<<endl;
                        }
                    }else{
                        cout<<"Alerta! no se detecto ninguna base de datos seleccionada, seleccione una para continuar"<<endl;
                        cout<<"Intente con "<<'"'<<"INFO USAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"USAR"<<'"'<<endl;
                    }
                }else if(ListaTokens(argumento3)==-1){
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" contiene caracteres invalidos"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                }else{
                    cout<<"Error! "<<'"'<<argumento3<<'"'<<" no es valido para eliminar"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
                }
            }
        }else if((ListaTokens(argumento2)==101)||(ListaTokens(argumento2)==105)){
            //ELIMINAR BASE DE DATOS
            string contenido = muestra_contenido_de(ubicacion());
            char b[contenido.length()+1];
            strcpy(b, contenido.c_str());
            string archivos="";
            for(int i=5;i<contenido.length();i++){
                archivos+=b[i];
            }
            archivos=limpiarCadena(archivos);
            int j=1;
            char c[archivos.length()+1];
            strcpy(c, archivos.c_str());
            for(int i=0;i<archivos.length();i++){
                if(c[i]==' '){
                    j++;
                }}
            string basesDatos[j];
            for(int i=0;i<j;i++){
                basesDatos[i]=obtenerPalabra(archivos,i+1);}
            int si=0;
            for(int i=0;i<j;i++){
            char d[basesDatos[i].length()+1];
            strcpy(d, basesDatos[i].c_str());
            if(basesDatos[i].length()>4){
                if((d[basesDatos[i].length()-4]=='.')&&(d[basesDatos[i].length()-3]=='s')&&(d[basesDatos[i].length()-2]=='q')&&(d[basesDatos[i].length()-1]=='l')){
                    si++;
                }}}
            string baseLimpia[si];
            int total=0;
            for(int i=0;i<j;i++){
            char d[basesDatos[i].length()+1];
            strcpy(d, basesDatos[i].c_str());
            if(basesDatos[i].length()>4){
                if((d[basesDatos[i].length()-4]=='.')&&(d[basesDatos[i].length()-3]=='s')&&(d[basesDatos[i].length()-2]=='q')&&(d[basesDatos[i].length()-1]=='l')){
                for(int cuenta=0;cuenta<(basesDatos[i].length()-4);cuenta++){
                    baseLimpia[total]+=d[cuenta];
                }
                total++;
                }}}
            string argumento3=obtenerPalabra(cadena,3);
            bool continuar=false;
            for(int i=0;i<si;i++){
                if(argumento3==baseLimpia[i]){
                    continuar=true;
                }
            }
            if(continuar){
                if(argumento3!="UwuDB"){
                string respuesta;
                cout<<"Esta seguro de eliminar la base de datos "<<'"'<<argumento3<<'"'<<"? esta accion no se podra deshacer"<<endl;
                cout<<"1. Si"<<endl;
                cout<<"2. No"<<endl;
                getline(cin, respuesta);
                if((convertirMayusculas(respuesta) == "SI")||(respuesta=="1")||(convertirMayusculas(respuesta) == "SI;")||(respuesta=="1;")){
                    string eliminacion="rm "+ubicacion()+"/"+argumento3+".sql";
                    char elim[eliminacion.length()+1];
                    strcpy(elim,eliminacion.c_str());
                    if(_ElimTabYBd){
                        system(elim);
                        cout<<'"'<<argumento3<<'"'<<" eliminada exitosamente"<<endl;
                    }else{
                        cout<<"Este usuario no cuenta con los permisos para eliminar bases de datos"<<endl;
                    }
                }else{
                    cout<<"No se elimino la base de datos "<<argumento3<<endl;
                }}else{
                    cout<<"ALERTA! no se puede eliminar la base de datos pricipal!"<<endl;
                }
            }else{
                cout<<"No se encontro la base de datos "<<'"'<<argumento3<<'"'<<endl;
            }
        }else if(ListaTokens(argumento2)==-1){
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" contiene caracteres no validos"<<endl;
            cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
        }else{
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" no valido para ELIMINAR"<<endl;
            cout<<"Intente con "<<'"'<<"INFO ELIMINAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"ELIMINAR"<<'"'<<endl;
        }
    }
}
void ver(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    if(cadena.length()==3){
        cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<endl;
        cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
    }else if(cadena.length() == 4){
            cout<<"Error! hacen falta argumentos\n"<<endl;
            cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
    }else{
        string argumento2 = obtenerPalabra(cadena,2);
        if(argumento2=="*"){
            if((cadena.length()==6)&&(a[5]==';')){
                cout<<"Error! luego de "<<'"'<<"*"<<'"'<<" se necesita el nombre de la tabla"<<endl;
                cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
            }else if(cadena.length()==5){
            cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<endl;
            }else{
            string argumento3=obtenerPalabra(cadena,3);
            if(ListaTokens(convertirMayusculas(argumento3))==0){
                if(cadena.length()==(6+argumento3.length())){
                    cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<endl;
                    cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
                }else if(a[(6+argumento3.length())]==';'){
                    if(_dataBase==""){
                       cout<<"No se a seleccionado ninguna base de datos"<<endl;
                       cout<<"Intente con "<<'"'<<"USAR baseEjemplo;"<<'"'<<endl;
                       cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
                    }else{
                        if(_Leer){
                            if((convertirMayusculas(_dataBase)=="UWUDB")&&(convertirMayusculas(argumento3)=="USUARIOS")){
                            cout<<"\n**********************"<<endl;
                            cout<<"\tUSUARIOS"<<endl;
                            cout<<"**********************"<<endl;
                            for(int i=0;i<cant_Usuarios();i++){
                                cout<<"\t"<<ObtenerUsuario(i).getNombre()<<endl;
                            }
                            cout<<"**********************"<<endl;
                        }else{
                            string urlDB=ubicacion();
                            if(leer(urlDB+"/"+_dataBase+".sql")==" "){
                                cout<<"Error! la tabla "<<'"'<<argumento3<<'"'<<" no existe"<<endl;
                            }else{
                                vector<string> nombresT = nombresTablas();
                                bool paso=false;
                                for(int i=0;i<nombresT.size();i++){
                                    if(argumento3==nombresT[i]){
                                        paso=true;
                                    }
                                }
                                if(paso){
                                    traducir(quitarVariables(argumento3));
                                }else{
                                    cout<<"Error! la tabla "<<'"'<<argumento3<<'"'<<" no existe"<<endl;
                                }
                            }
                        }
                        if(cadena.length()>(7+argumento3.length())){
                            string sobrante="";
                            for(int i=(7+argumento3.length());i<cadena.length();i++){
                                sobrante+=a[i];
                            }
                            evaluar(limpiarCadena(sobrante));
                        }
                        }else{
                            cout<<"Este usuario no cuenta con los permisos para ver las tablas"<<endl;
                        }
                    }

                }else{
                    cout<<"Error! se detectaron demasiados argumentos en la sentencia"<<endl;
                    cout<<"Intente con "<<'"'<<"INFO VER;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"VER"<<'"'<<endl;
                }
            }else if(ListaTokens(convertirMayusculas(argumento3))==-1){
                cout<<'"'<<argumento3<<'"'<<" no es valido"<<endl;
            }else{
                cout<<"Error! no se puede buscar "<<'"'<<argumento3<<'"'<<" debido a que es una palabra reservada"<<endl;
            }

        }
        }else cout<<"Error! "<<'"'<<argumento2<<'"'<<" no valido"<<endl;

    }
}
void ejecutar(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    int contador=0;
    do{
        contador++;
    }while((contador<cadena.length()) && (a[contador]!=' '));
    if(cadena.length()==8){
        cout<<"Error: "<<'"'<<"EJECUTAR"<<'"'<<" necesita mas argumentos\n";
    }else{
        char b[cadena.length()-9];
        int j=0;
        for(int i=9;i<cadena.length();i++){
            b[j]=a[i];
            j++;
        }
        string aa="";
        for(int i=0;i<cadena.length()-9;i++){
        	aa+=b[i];
        }
        char c[aa.length()];
            strcpy(c, aa.c_str());
        if(_Crear&&_ElimTabYBd&&_ElimFila&&_InsertFila&&_Leer&&_Actualizar&&_Privilegios){
            system(c);
        }else{
            cout<<"ALERTA!!! El comando ejecutar solo esta disponible para los usuarios administradores!"<<endl;
        }
    }
}
void renombrar(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    int contador=0;
    if(cadena.length()==9){
        cout<<"Error: "<<'"'<<"RENOMBRAR"<<'"'<<" necesita mas argumentos"<<endl;
        cout<<"Intente con "<<'"'<<"INFO RENOMBRAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"RENOMBRAR"<<'"'<<endl;
    }else{
    if(ListaTokens(convertirMayusculas(obtenerPalabra(cadena,2)))==0){
        string argumento2=obtenerPalabra(cadena,2);
        if(cadena.length()==(10+argumento2.length())){
            cout<<"Error! se necesita "<<'"'<<";"<<'"'<<endl;
            cout<<"Intente con "<<'"'<<"INFO RENOMBRAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"RENOMBRAR"<<'"'<<endl;
        }else{
        if((cadena.length()==(11+argumento2.length())) && (a[10+argumento2.length()])==';'){
            cout<<"Error! ingrese el nuevo nombre de la base de datos"<<endl;
        }else{
        string argumento3 = obtenerPalabra(cadena,3);
        if(convertirMayusculas(argumento3)=="A"){
        if((cadena.length()==(12+argumento2.length()))|| ((cadena.length()==(13+argumento2.length()))&&(a[12+argumento2.length()]==';'))){
            cout<<"No se pudo cambiar el nombre, se esperaba el nuevo nombre de la base de datos"<<endl;
            cout<<"Intente con "<<'"'<<"INFO RENOMBRAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"RENOMBRAR"<<'"'<<endl;
        }else{
        string argumento4=obtenerPalabra(cadena,4);
        if(ListaTokens(convertirMayusculas(argumento4))==0){
            if(cadena.length()==(13+argumento2.length()+argumento4.length())){
            cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
            cout<<"Intente con "<<'"'<<"INFO RENOMBRAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"RENOMBRAR"<<'"'<<endl;
        }else if(a[13+argumento2.length()+argumento4.length()]==';'){
            if(_Privilegios){
                cambiarNombreBD(argumento2,argumento4);
                cout << "La base de datos " << argumento2 << " ha sido renombrada a "<< argumento4 <<" exitosamente"<<endl;
            }else{
                cout<<"El usuario "<<'"'<<_nombre<<'"'<<" no cuenta con los permisos necesarios"<<endl;
            }
            string paraEvaluar="";
            int longitud=14+argumento2.length()+argumento4.length();
            if(longitud<cadena.length()){
                for(int i=longitud;i<cadena.length();i++){
                    paraEvaluar+=a[i];
                }
                evaluar(limpiarCadena(paraEvaluar));
            }
        }else{
            cout<<"Error! se detectaron demasiados argumentos"<<endl;
            cout<<"Intente con "<<'"'<<"INFO RENOMBRAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"RENOMBRAR"<<'"'<<endl;
        }
        }else cout<<"Error! no de puede usar"<<'"'<<argumento4<<'"'<<" por que es una palabra reservada"<<endl;

        }}else cout<<"Error! "<<'"'<<obtenerPalabra(cadena,3)<<'"'<<" no valido"<<endl;
        }}
    }else{
        cout<<"Error! no de puede usar "<<'"'<<obtenerPalabra(cadena,2)<<'"'<<" por que es una palabra reservada"<<endl;
    }}
}
void listar(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    if(cadena.length()==6){
        cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
        cout<<"Intente con "<<'"'<<"INFO LISTAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"LISTAR"<<'"'<<endl;
    }else if(cadena.length() == 7){
        cout<<"LISTAR nesesita mas argumentos"<<endl;
        cout<<"Intente con "<<'"'<<"INFO LISTAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"LISTAR"<<'"'<<endl;
    }else{
        string argumento2=obtenerPalabra(cadena,2);
        if((ListaTokens(argumento2)==101)||(ListaTokens(argumento2)==105)){
            if(cadena.length()==(7+argumento2.length())){
                cout<<"Error! se esperaba "<<'"'<<";"<<'"'<<" al final de la linea"<<endl;
                cout<<"Intente con "<<'"'<<"INFO LISTAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"LISTAR"<<'"'<<endl;
            }else if((cadena.length()==(8+argumento2.length()))&&(a[7+argumento2.length()]==';')){
            	//recive los nombres de los archivos que se encuentran en la carpeta de base de datos
            	//pero con 3 puntos antes y todos los nombres concatenados, asi que hay que limpiarlos
            	string contenido = muestra_contenido_de(ubicacion());
            	char b[contenido.length()+1];
                strcpy(b, contenido.c_str());
                string archivos="";
                for(int i=5;i<contenido.length();i++){
                    archivos+=b[i];
                }
                archivos=limpiarCadena(archivos);
                int j=1;
                char c[archivos.length()+1];
                strcpy(c, archivos.c_str());
                for(int i=0;i<archivos.length();i++){
                    if(c[i]==' '){
                        j++;
                    }}
                string basesDatos[j];
                for(int i=0;i<j;i++){
                    basesDatos[i]=obtenerPalabra(archivos,i+1);}
                int si=0;
                for(int i=0;i<j;i++){
                char d[basesDatos[i].length()+1];
                strcpy(d, basesDatos[i].c_str());
                if(basesDatos[i].length()>4){
                    if((d[basesDatos[i].length()-4]=='.')&&(d[basesDatos[i].length()-3]=='s')&&(d[basesDatos[i].length()-2]=='q')&&(d[basesDatos[i].length()-1]=='l')){
                        si++;
                    }}}
                string baseLimpia[si];
                int total=0;
                for(int i=0;i<j;i++){
                char d[basesDatos[i].length()+1];
                strcpy(d, basesDatos[i].c_str());
                if(basesDatos[i].length()>4){
                    if((d[basesDatos[i].length()-4]=='.')&&(d[basesDatos[i].length()-3]=='s')&&(d[basesDatos[i].length()-2]=='q')&&(d[basesDatos[i].length()-1]=='l')){
                    for(int cuenta=0;cuenta<(basesDatos[i].length()-4);cuenta++){
                        baseLimpia[total]+=d[cuenta];
                    }
                    total++;
                    }}}
                if(_Leer){
                    cout<<"\n******************************"<<endl;
                    cout<<"\tBASES DE DATOS"<<endl;
                    cout<<"******************************"<<endl;
                    for(int i=0;i<total;i++){
                        cout<<"\t"<<baseLimpia[i]<<endl;
                    }
                    cout<<"******************************\n"<<endl;
                }else{
                    cout<<"El usuario no cuenta con los permisos necesarios"<<endl;
                }

            }else{
                string eval = "";
                for(int i=10;i<cadena.length();i++){
                    eval+=a[i];
                }
                evaluar(limpiarCadena(eval));
            }
        }else if((ListaTokens(argumento2)==103)||(ListaTokens(argumento2)==104)){
            if(_dataBase==""){
                cout<<"No hay base de datos seleccionada intente con "<<'"'<<"USAR NombreBaseDatos"<<'"'<<endl;
                cout<<"Intente con "<<'"'<<"INFO USAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"USAR"<<'"'<<endl;
            }else{
                if(_Leer){
                    vector<string> lista = nombresTablas();
                    cout<<"\n******************************"<<endl;
                    cout<<"\tTABLAS"<<endl;
                    cout<<"******************************"<<endl;
                    for(int i=0;i<lista.size();i++){
                        cout<<"\t"<<lista[i]<<endl;
                    }
                    cout<<"******************************\n"<<endl;
                }else{
                    cout<<"El usuario no cuenta con los permisos necesarios"<<endl;
                }

            }
        }else if(ListaTokens(argumento2)==-1){
            cout<<"Error! caracteres invalidos en "<<'"'<<argumento2<<'"'<<endl;
        }else if(ListaTokens(argumento2)==0){
            cout<<"Error! No se puede listar "<<'"'<<argumento2<<'"'<<endl;
        }
        else{
            cout<<"Error! "<<'"'<<argumento2<<'"'<<" no es valido para LISTAR"<<endl;
            cout<<"Intente con "<<'"'<<"INFO LISTAR;"<<'"'<<" para ver la lista de argumentos validos para "<<'"'<<"LISTAR"<<'"'<<endl;
        }
    }
}
void info(string cadena){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    int contador=0;
    string parte1="";
    string parte2="";
    for(int i=0;i<cadena.length();i++){
        if(a[i]==';')contador++;
        if(contador==0)parte1+=a[i];
    }
    if(contador>1){
    for(int i=parte1.length()+1;i<cadena.length();i++)parte2+=a[i];
        cadena=limpiarCadena(parte1+";");
        parte2=limpiarCadena(parte2);
    }
    if(cadena.length()==5){ //info; = 5
         informacion();
    }else{
        string argumento2 = obtenerPalabra(cadena,2);
        if(cadena.length()== 6+argumento2.length()){
            switch(ListaTokens(argumento2)){
                case 2: //info crear;
                    infoCrear();
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 3: //info editar;
                    cout << "Editar Registros de una tabla en la base de datos:\n"<<endl;
                    cout <<"EDITAR nombre_tabla LLAVE id_registro (campo1, campo2,... campoN) (valorNuevo1,valorNuevo2,...,valorNuevoN);\n" << endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 4: //info eliminar;
                    cout << "Eliminar Registros, tablas y bases de datos segun sea nesesario:\n"<<endl;
                    //AQUI HARIA FALTA EL FORMATO DE elminiar de cada uno
                    cout <<"ELIMINAR Registros de una TABLA:" << endl;
                    cout <<"ELIMINAR EN nombre_tabla LLAVE id_registro;\n"<<endl;
                    cout <<"ELIMINAR una TABLA de una BASE DE DATOS:" << endl;
                    cout <<"ELIMINAR TABLA nombre_tabla;\n"<<endl;
                    cout <<"ELIMINAR una BASE DE DATOS:" << endl;
                    cout <<"ELIMINAR BD nombre_base_datos;"<<endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 5: //info ver;
                    cout <<'"'<<"VER"<<'"'<<" nos permitira ver la informacion que se encuentra en una tabla de la base de datos:\n";
                    cout <<"VER * nombre_tabla;"<<endl;
                    cout <<"Nota: para VER la informacion de tabla debe de haberse puesto en uso una base de datos ej. USAR mi_bd;" << endl;;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 6: //info usar;
                    cout << "Permitira poner en uso la base de datos que deseemos para trabajar con el en los procesos que se deseen\n" <<endl;
                    cout << "USAR nombre_basedatos;";
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 10: //info renombrar;
                    cout << "permitira renombrar una base datos\n";
                    cout << "RENOMBRAR nombre_basedatos1 A nombre_basedatos2;"<<endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case 11: //info listar;
                    cout << "Para listar las BASES DE DATOS:\n";
                    cout << "LISTAR BD;\n\n";
                    cout << "Para listar tablas de una base de datos:\n";
                    cout << "LISTAR TABLAS;\n";
                    cout <<"Nota: para listar tabla debe de haberse puesto en uso una base de datos,\npara informacion de dar uso digite 'info usar;'" << endl;;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                break;
                case 12: //info insertar;
                    cout << "Insertar un registro dentro de una tabla de la base de datos:\n";
                    cout << "INSERTAR EN nombre_tabla VALORES(valor1,valor2,...valorN);"<<endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
                case -1: //info asldhalsdh; (caracteres no validos)
                    cout<< "Error! "<<argumento2<<" contiene caracteres no validos"<<endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;

                default:
                    cout << "Error! Argumento '" <<argumento2<< "' no valido"<<endl;
                    if(parte2!=""){
                        evaluar(parte2);
                    }
                break;
            }
        }else if(cadena.length()> 6+argumento2.length()){ //hay mas de 2 argumentos en la cadena
            if(parte2!=""){
                evaluar(parte2);
            }
        }
    }
}
//FIN    FUNCIONES DE COMANDOS A USAR*

//---------------------------------------
//FUNCIONES DE INFO *
void informacion(){
    cout<<"\nGestor de base de datos UwuDB\n";
    cout<<"Alpha v1.0\n\n";
    cout<<"Lista de comandos:\n";
    cout<<"1-  "<<'"'<<"INFO"<<'"'<<" -Muestra informacion del gestor de base de datos y lista de comandos\n";
    cout<<"2-  "<<'"'<<"CREAR"<<'"'<<" -Para crear una nueva base de datos, usuario o tablas\n";
    cout<<"3-  "<<'"'<<"INSERTAR"<<'"'<<" -Para Insertar un nuevo registro a una tabla de la base de datos\n";
    cout<<"4-  "<<'"'<<"EDITAR"<<'"'<<" -Para editar informacion almacenada en las tablas\n";
    cout<<"5-  "<<'"'<<"ELIMINAR"<<'"'<<" -Para eliminar una base de datos o tabla\n";
    cout<<"6-  "<<'"'<<"VER"<<'"'<<" -Para ver informacion de las tablas\n";
    cout<<"7-  "<<'"'<<"USAR"<<'"'<<" -Antes para acceder a las bases de datos ej. "<<'"'<<"USAR miBD;"<<'"'<<"\n";
    cout<<"8-  "<<'"'<<"RENOMBRAR"<<'"'<<" -Para renombrar las bases de datos \n";
    cout<<"9-  "<<'"'<<"LISTAR"<<'"'<<" -Para ver la lista de bases de datos ej. "<<'"'<<"LISTAR BD;"<<'"'<<"\n";
    cout<<"10- "<<'"'<<"LIMPIAR"<<'"'<<" -Limpia la pantalla\n";
    cout<<"11- "<<'"'<<"SALIR"<<'"'<<" -Para cerrar UwuDB\n\n";
    cout << "Nota: todas las sentencias debean de finalizar con " << '"'<<";"<<'"'<<" para ser reconocidos por el gestor" << endl;
}
void infoCrear(){
    cout<<"\nLista de argumentos validos para comando "<<'"'<<"CREAR"<<'"'<<"\n"<<endl;
    cout<<"1- "<<'"'<<"BASEDATOS"<<'"'<<" para crear una Base de datos"<<endl;
    cout<<"2- "<<'"'<<"USUARIO"<<'"'<<" para crear un usuario"<<endl;
    cout<<"3- "<<'"'<<"TABLA"<<'"'<<" para la creacion de tablas\n"<<endl;
    cout<<"Ejemplos: \n"<<endl;
    cout<<'"'<<"crear BASE DE DATOS:"<<'"'<<endl;
    cout<<"CREAR BASEDATOS MiBase;\n"<<endl;
    cout<<'"'<<"crear USUARIO:"<<'"'<<endl;
    cout<<"CREAR USUARIO MiUsuario CLAVE 'clave123';\n"<<endl;
    cout<<'"'<<"crear una TABLA"<<'"'<<endl;
    infoTabla();
}
void infoTabla(){
    cout<<"CREAR TABLA miTabla("<<endl;
    cout<<"   id entero[15] Llave Primaria,\n";
    cout<<"   Nombre caracter[100],"<<endl;
    cout<<"   edad decimal[10]"<<endl;
    cout<<");"<<endl;
}
//FIN    FUNCIONES DE INFO*

//---------------------------------------
//FUNCIONES QUE TIENEN QUE VER CON BASEDATOS
void crearBaseDeDatos(string entrada){
    string entrada2=ubicacion()+"/";
    if(comprobar(entrada2+entrada)){
        cout<<"La base de datos "<<'"'<<entrada<<'"'<<" ya existe"<<endl;
    }else{
        cout<<"Base de datos "<<'"'<<entrada<<'"'<<" creada"<<endl;
        entrada+=".sql";
        entrada2+=entrada;
        char c[entrada2.length()];
        strcpy(c, entrada2.c_str());
        ofstream file;
        file.open(c);
        file.close();
    }
}
void cambiarNombreBD(string nombre1, string nombre2){
    if(comprobar(ubicacion()+"/"+nombre1)){
        //LINUX
        string comando="mv "+ubicacion()+"/"+nombre1+".sql "+ubicacion()+"/"+nombre2+".sql ";
        char a[comando.length()];
        strcpy(a, comando.c_str());
        system(a);
    }else{
        cout<<"La base de datos "<<'"'<<nombre1<<'"'<<" no existe"<<endl;
    }
}
//FIN         FUNCIONES QUE TIENEN QUE VER CON BASEDATOS

//---------------------------------------
//FUNCIONES QUE TIENEN QUE VER CON TABLAS
string prepararTabla(string nombre, vector<string> lista){
    string resultado="$"+nombre+"#";
    vector<string> lista2;
    for(int i = 0; i < lista.size(); i++){
        if(cantArgumentos(lista[i])==4){
            lista2.push_back(lista[i]);
        }
    }
    for(int i = 0; i < lista.size(); i++){
        if(cantArgumentos(lista[i])==2){
            lista2.push_back(lista[i]);
        }
    }
    resultado+=convertirMayusculas(obtenerPalabra(lista2[0],2)+" "+obtenerPalabra(lista2[0],3)+" "+obtenerPalabra(lista2[0],4));
    for(int i=1;i<lista2.size();i++){
        resultado+=";"+convertirMayusculas(obtenerPalabra(lista2[i],2));
    }
    resultado+="#"+obtenerPalabra(lista2[0],1);
    for(int i=1;i<lista2.size();i++){
        resultado+=";"+obtenerPalabra(lista2[i],1);
    }
    resultado+="#";
    return resultado;
}
string obtenerTabla(string nombre){
    vector<string> lista = listaDeTablas();
    vector<string> nombres = nombresTablas();
    for(int i=0;i<nombres.size();i++){
        if(nombre==nombres[i])return lista[i];
    }
}
void crearTabla(string nombre, string cadena, string sobra){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    vector<string> lista;
    string bloque="";
    int cantBloques=1;
    for(int i=0;i<cadena.length();i++){
        if(a[i]==','){
            cantBloques++;
        }
    }
    int N_bloque=0;
    for(int i=0;i<cadena.length();i++){
        if((a[i]==',') || (i==cadena.length())){
            lista.push_back(unirCorchetes(limpiarCadena(bloque)));
            bloque="";
        }else{
            bloque+=a[i];
        }
    }
    lista.push_back(unirCorchetes(limpiarCadena(bloque)));
    //SI ESTAMOS AQUI SE COMPROBO QUE LA TABLA SE PUEDE CREAR, SOLO FALTA VER SI EXISTE YA LA TABLA
        if(_dataBase=="UwuDB"){
        cout<<"ALERTA!!! no se pueden crear tablas en la base de datos principal! seleccione otra base de datos!"<<endl;
    }else{
    if(existeTabla(nombre)){
        cout<<"No se pudo crear la tabla "<<nombre<<" por que ya se encuentra creada"<<endl;
    }else{
        //INSERTAMOS LA NUEVA TABLA AL FINAL DE LA CADENA
        if(_dataBase!=""){
            insertar_Al_Final(prepararTabla(nombre,lista));
        cout<<"Tabla "<<'"'<<nombre<<'"'<<" creada"<<endl;
        }
        if(sobra.length()>0){
            evaluar(sobra);
        }
    }
    }
}
bool evaluarTabla(string contenido, string nombre){
    char a[contenido.length()+1];
    strcpy(a, contenido.c_str());
    if(a[0]==','){
        cout<<"Error! no se detecta la primer columna: "<<'"'<<","<<'"'<<" al inicio de los parametros"<<endl;
        return false;
    }else if(a[contenido.length()-1]==','){
        cout<<"Error! no se detecta la ultima columna: "<<'"'<<","<<'"'<<" al final de los parametros"<<endl;
        return false;
    }else if(contenido==""){
        cout<<"Error! no se detectaron parametros en la creacion de la tabla "<<'"'<<nombre<<'"'<<endl;
        return false;
    }else{
    //SI ENTRAMOS AQUI SIGNIFICA QUE SI HAY PARAMETROS EN LA TABLA Y NO HAY "," AL INICIO O AL FINAL
    vector<string> lista;
    vector<string> lista2;
    string bloque="";
    int cantBloques=1;
    for(int i=0;i<contenido.length();i++){
        if(a[i]==','){
            cantBloques++;
        }
    }
    if(cantBloques==1){
        cout<<"No se puede crear la tabla "<<'"'<<nombre<<'"'<<" con solo 1 columna"<<endl;
        return false;
    }else{
        int N_bloque=0;
        for(int i=0;i<contenido.length();i++){
            if((a[i]==',') || (i==contenido.length())){
                lista.push_back(unirCorchetes(limpiarCadena(bloque)));
                bloque="";
            }else{
                bloque+=a[i];
            }
        }
        lista.push_back(unirCorchetes(limpiarCadena(bloque)));
        //"lista" CONTIENE UNA LISTA DE LOS PARAMETROS POR SEPARADO DE LA TABLA QUE DESEAMOS CREAR
        int llavePrimaria=0;
        for(int i=0;i<cantBloques;i++){
            //EVALUAREMOS BLOQUE POR BLOQUE
            if((cantArgumentos(lista[i])==2) || (cantArgumentos(lista[i])==4)){
                if(ListaTokens(obtenerPalabra(lista[i],1))==0){
                    if((ListaTokens(obtenerPalabra(lista[i],2))>=501)&&(ListaTokens(obtenerPalabra(lista[i],2))<=503)){
                            lista2.push_back(obtenerPalabra(lista[i],1));
                    }else if(ListaTokens(obtenerPalabra(lista[i],2))==0){
                        cout<<"Error! "<<'"'<<obtenerPalabra(lista[i],2)<<'"'<<" no es nombre de variable"<<endl;
                        return false;
                    }else if(ListaTokens(obtenerPalabra(lista[i],2))==-1){
                        cout<<"Error! "<<'"'<<obtenerPalabra(lista[i],2)<<'"'<<" no es nombre de variable"<<endl;
                        return false;
                    }else if(ListaTokens(obtenerPalabra(lista[i],2))==-2){
                        cout<<"Error! en parametros de variable "<<'"'<<obtenerPalabra(lista[i],2)<<'"'<<" solo con numeros enteros!"<<endl;
                        return false;
                    }else if(ListaTokens(obtenerPalabra(lista[i],2))==-3){
                        cout<<"Error! no se detectaron parametros en la variable "<<'"'<<obtenerPalabra(lista[i],2)<<'"'<<endl;
                        return false;
                    }else{
                        cout<<"Error! "<<'"'<<obtenerPalabra(lista[i],2)<<'"'<<" es una variable reservada"<<endl;
                        return false;
                    }
                }else if(ListaTokens(obtenerPalabra(lista[i],1))==-1){
                    cout<<"Error! se detectaron caracteres invalidos en "<<'"'<<obtenerPalabra(lista[i],1)<<'"'<<endl;
                    return false;
                }else{
                    cout<<"Error! "<<'"'<<obtenerPalabra(lista[i],1)<<'"'<<" es una variable reservada"<<endl;
                    return false;
                }
            }else{
                cout<<"Error! "<<lista[i]<<" no valida"<<endl;
                return false;
            }
            if(cantArgumentos(lista[i])==4){
                if(ListaTokens(obtenerPalabra(lista[i],3))==304){//304 es LLAVE
                    if(ListaTokens(obtenerPalabra(lista[i],4))==305){//304 es PRIMARIA
                        llavePrimaria++;
                    }else{
                        if(ListaTokens(obtenerPalabra(lista[i],4))==-1){
                        cout<<"Error! se detectaron caracteres no validos en "<<'"'<<obtenerPalabra(lista[i],4)<<'"'<<endl;
                        }else{
                            cout<<"Error! no se acepto "<<'"'<<obtenerPalabra(lista[i],4)<<'"'<<" se esperaba PRIMARIA"<<endl;
                        }
                        return false;
                    }
                }else{
                    if(ListaTokens(obtenerPalabra(lista[i],3))==-1){
                        cout<<"Error! se detectaron caracteres no validos en "<<'"'<<obtenerPalabra(lista[i],3)<<'"'<<endl;
                    }else{
                        cout<<"Error! no se acepto "<<'"'<<obtenerPalabra(lista[i],3)<<'"'<<" se esperaba LLAVE PRIMARIA"<<endl;
                    }
                    return false;
                }
            }
        }
        if(llavePrimaria==0){
            cout<<"Para crear la tabla debe nombrar una columna como llave primaria"<<endl;
            return false;
        }else if(llavePrimaria>1){
            cout<<"Error! no se puede crear una tabla con mas de 1 llave primaria"<<endl;
            return false;
        }

        //ALGORITMO QUE DETECTA SI ESTAN REPETIDAS LAS COLUMNAS
        if(!hayStringsRepetidos(lista2)){
            cout<<"Error! no se puede crear tabla con columnas repetidas"<<endl;
            return false;
        }
     }}
    return true;
}
bool existeTabla(string nombre){
    bool respuesta=false;
    if(_dataBase==""){
        cout<<"Error! No hay ninguna base de datos selecionada"<<endl;
    }else{
        if(_dataBase=="UwuDB"){
            cout<<"ALERTA! no se pueden crear tablas nuevas en la base de datos UwuDB seleccione otra base de datos"<<endl;
        }else{
            string direccion=ubicacion()+"/"+_dataBase+".sql";
            if(Lectura(direccion).length()==1){
                respuesta= false;
            }else{
                vector<string> lista = nombresTablas();
                for(int i = 0; i < lista.size(); i++)if(lista[i]==nombre)respuesta=true;
            }
        }
    }
    return respuesta;
}
bool evaluarValoresTabla(string nombre, string valores){
    bool retorno=true;
    char a[valores.length()+1];
    strcpy(a, valores.c_str());
    if(a[0]==','){
        cout<<"Error! no se detecta la primer columna: "<<'"'<<","<<'"'<<" al inicio de los parametros"<<endl;
        return false;
    }else if(a[valores.length()-1]==','){
        cout<<"Error! no se detecta la ultima columna: "<<'"'<<","<<'"'<<" al final de los parametros"<<endl;
        return false;
    }
    vector<string> datos = listaDatos(valores);
    vector<string> datosLimpios;
    vector<int> listaTipos;
    vector<int> TamanioTipos;
    for(int i=0;i<datos.size();i++){
        char arreglo[datos[i].length()+1];
        strcpy(arreglo, datos[i].c_str());
        if(datos[i]=="'"){
            cout<<"Error! no se puede insertar "<<'"'<<" ' "<<'"'<<endl;
            return false;
        }else if((datos[i]=="''")||(datos[i]=="' '")){
            cout<<"Error! cadena vacia "<<endl;
            return false;
        }else if((arreglo[0]==39)&&(arreglo[datos[i].length()-1]==39)){
            string cadenaDeCaracteres="";
            for(int j=1;j<datos[i].length()-1;j++){
                cadenaDeCaracteres+=arreglo[j];
            }
            cadenaDeCaracteres=limpiarCadena(cadenaDeCaracteres);
            if(cantArgumentos(cadenaDeCaracteres)==1){
                char arreglo2[cadenaDeCaracteres.length()+1];
                strcpy(arreglo2, cadenaDeCaracteres.c_str());
                for(int f=0;f<cadenaDeCaracteres.length();f++){
                    if((arreglo2[f]==35)||(arreglo2[f]==59)){
                    cout<<"Error! " <<'"'<<cadenaDeCaracteres<<'"'<<" contiene caracteres invalidos"<<endl;
                    return false;
                    }
                }
            }else{
            for(int k=0;k<cantArgumentos(cadenaDeCaracteres);k++){
                char arreglo2[obtenerPalabra(cadenaDeCaracteres,k+1).length()+1];
                strcpy(arreglo2, obtenerPalabra(cadenaDeCaracteres,k+1).c_str());
                for(int f=0;f<obtenerPalabra(cadenaDeCaracteres,k+1).length();f++){
                    if((arreglo2[f]==35)||(arreglo2[f]==59)){
                        cout<<"Error! " <<'"'<<obtenerPalabra(cadenaDeCaracteres,k+1)<<'"'<<" contiene caracteres invalidos"<<endl;
                        return false;
            }}}}
            datosLimpios.push_back(cadenaDeCaracteres);
            listaTipos.push_back(503);//Numero de token almacenado para CARACTER[ ### ]
            TamanioTipos.push_back(cadenaDeCaracteres.length());
        }else if((arreglo[0]==39)&&(arreglo[datos[i].length()-1]!=39)){
            cout<<"Error! se esperaba "<<'"'<<" ' "<<'"'<<" al final de la linea"<<endl;
            return false;
        }else if((arreglo[0]!=39)&&(arreglo[datos[i].length()-1]==39)){
            cout<<"Error! se esperaba "<<'"'<<" ' "<<'"'<<" al comienzo de la linea"<<endl;
            return false;
        }else{
            //SI NO HAY ' AL INICIO Y AL FINAL, EVALUAREMOS SI ES UN NUMERO (ENTERO O DECIMAL)
        if(cantArgumentos(datos[i])>1){
            cout<<"Error! demasiados argumentos! argumentos en "<<'"'<<datos[i]<<'"'<<" solo se acepta una palabra!"<<endl;
            return false;
        }else{
            int puntos=0;
            for(int j=0;j<datos[i].length();j++){
                if(((arreglo[j]>=48)&&(arreglo[j]<=57))||(arreglo[j]=='.')){
                    if(arreglo[j]=='.'){
                        puntos++;
                    }
                }else{
                    cout<<"Error! "<<'"'<<datos[i]<<'"'<<" no valido"<<endl;
                    return false;
                }
            }
            if(puntos==1){
                if(datos[i]=="."){
                    cout<<"Error! "<<'"'<<datos[i]<<'"'<<" no valido"<<endl;
                }else{
                    if((arreglo[0]=='.')||(arreglo[datos[i].length()-1]=='.')){
                        cout<<"Error! "<<'"'<<datos[i]<<'"'<<" no valido"<<endl;
                    }else{
                         datosLimpios.push_back(datos[i]);
                         listaTipos.push_back(502);//Numero de token almacenado para DECIMAL[ ### ]
                         TamanioTipos.push_back(datos[i].length());
                    }
                }
            }else if(puntos==0){
                 datosLimpios.push_back(datos[i]);
                 listaTipos.push_back(501);//Numero de token almacenado para ENTERO[ ### ]
                 TamanioTipos.push_back(datos[i].length());
            }else{
                cout<<"Error! "<<'"'<<datos[i]<<'"'<<" no valido"<<endl;
                return false;
        }}}}
    string tabla = obtenerTabla(nombre);
    string linea1="";
    char b[tabla.length()+1];
    strcpy(b,tabla.c_str());
    int contador=nombre.length()+1;
    while(b[contador]!='#'){
        linea1+=b[contador];
        contador++;
    }
    vector<string> datos2 = separarDatos(linea1);
    vector<string> datos3;
    for(int i=0;i<datos2.size();i++){
        datos3.push_back(obtenerPalabra(datos2[i],1));
    }
    //datos3 CONTIENE LA LISTA DE TIPOS DE DATOS DE CADA COLUMNA

    if(listaTipos.size()>datos3.size()){
        cout<<"Error! se detectaron demasiadas columnas en la insercion"<<endl;
        cout<<"Los datos son: "<<datos3[0];
        for(int j=1;j<datos3.size();j++){
            cout<<","<<datos3[j];
        }
        cout<<"\n";
        return false;
    }else if(listaTipos.size()<datos3.size()){
        cout<<"Error! faltan "<<(datos3.size()-listaTipos.size())<<" columnas en la insercion"<<endl;
        cout<<"Los datos son: "<<datos3[0];
        for(int j=1;j<datos3.size();j++){
            cout<<","<<datos3[j];
        }
        cout<<"\n";
        return false;
    }else{
        for(int i=0;i<listaTipos.size();i++){
            if((ListaTokens(datos3[i])==503)&&(listaTipos[i]==503)){
                retorno=true;
            }else if((ListaTokens(datos3[i])==502)&&(listaTipos[i]==502)){
                retorno=true;
            }else if((ListaTokens(datos3[i])==501)&&(listaTipos[i]==501)){
                retorno=true;
            }else if((ListaTokens(datos3[i])==502)&&(listaTipos[i]==501)){
                retorno=true;
            }else{
                cout<<"Los datos no concuerdan!"<<endl;
                cout<<"Los datos deben ser: "<<datos3[0];
                for(int j=1;j<datos3.size();j++){
                    cout<<","<<datos3[j];
                }
                cout<<"\n";
                return false;
            }}}
        //LLEGAMOS AQUI Y LOS DATOS INGRESADOS CONCUERDAN CON LOS DE LA TABLA
        //SOLO FALTA VER QUE LAS LONGITUDES DE LAS VARIABLES TAMBIEN CONCUERDEN
        vector<int> posInicial;
        for(int i=0;i<datos3.size();i++){
            char c[datos3[i].length()+1];
            strcpy(c,datos3[i].c_str());
            for(int j=0;j<datos3[i].length();j++){
                if(c[j]=='['){
                    posInicial.push_back(j+1);
                }
            }
        }
        vector<string> longitudesString;
        vector<int> longitudesInt;

        for(int i=0;i<datos3.size();i++){
            char c[datos3[i].length()+1];
            strcpy(c,datos3[i].c_str());
            string longitudString="";
            for(int j=posInicial[i];j<datos3[i].length()-1;j++){
                longitudString+=c[j];
            }
            longitudesString.push_back(longitudString);
        }
        for(int i=0;i<longitudesString.size();i++){
            longitudesInt.push_back(atoi(longitudesString[i].c_str()));
        }
        for(int i=0;i<longitudesInt.size();i++){
            if(TamanioTipos[i]>longitudesInt[i]){
                cout<<"Error! no hay espacio suficiente para almacenar "<<'"'<<datosLimpios[i]<<'"'<<endl;
                cout<<"La longitud reservada es de "<<longitudesInt[i]<<endl;
                return false;
            }
        }
    return retorno;
}
vector<string> obtenerFilas(string nombre){
    vector<string> retorno;
    string tabla = obtenerTabla(nombre);
    char a[tabla.length()];
    strcpy(a,tabla.c_str());
    int contador=0, saltos=0, inicio=0;
    do{
        if(a[contador]=='#'){
            saltos++;
        }
        if(saltos==3){
            inicio=contador+1;
        }
        contador++;
    }while(inicio==0 && contador<tabla.length());

    if(contador==tabla.length()){
        return retorno;
    }

    string filas="";
    for(int i=inicio;i<tabla.length();i++){
        filas+=a[i];
    }
    filas+='#';

    char b[filas.length()];
    strcpy(b,filas.c_str());
    contador=0;
    for(int i=0;i<filas.length();i++){
        if(b[i]=='#'){
            contador++;
        }
    }
    string fila="";
    for(int i=0;i<filas.length();i++){
        if(b[i]!='#'){
            fila+=b[i];
        }else{
            retorno.push_back(fila);
            fila="";
        }
    }

    return retorno;
}
vector<string> obtenerListaId(string nombre){
    vector<string> filas = obtenerFilas(nombre);
    vector<string> id;
    for(int i=0;i<filas.size();i++){
        char a[filas[i].length()];
        strcpy(a,filas[i].c_str());

        int contador=0;
        string cadena="";

        while(a[contador]!=';'){
            cadena+=a[contador];
            contador++;
        }
        id.push_back(cadena);
    }
    return id;
}
void editarTabla(string tabla, string id, string cadena1, string cadena2, string sobra){
    cadena1=limpiarCadena(cadena1);
    cadena2=limpiarCadena(cadena2);
    vector<string> lista1;
    vector<string> lista2;
    if(cadena1[0]==','){
        cout<<"Error! no se detecta la primer columna: "<<'"'<<","<<'"'<<" al inicio de los parametros"<<endl;
    }else if(cadena1[cadena1.length()-1]==','){
        cout<<"Error! no se detecta la ultima columna: "<<'"'<<","<<'"'<<" al final de los parametros"<<endl;
    }else{
        //SI ENTRAMOS AQUI SIGNIFICA QUE NO HAY "," AL INICIO O AL FINAL
        string bloque="";
        int cantBloques=1;
        for(int i=0;i<cadena1.length();i++){
            if(cadena1[i]==','){
                cantBloques++;
            }
        }
        for(int i=0;i<cadena1.length();i++){
            if(cadena1[i]==','){
                lista1.push_back(limpiarCadena(bloque));
                bloque="";
            }else if(i==cadena1.length()-1){
                bloque+=cadena1[cadena1.length()-1];
                lista1.push_back(limpiarCadena(bloque));
                bloque="";
            }else{
                bloque+=cadena1[i];
            }
        }
        if(cadena2[0]==','){
        cout<<"Error! no se detecta el primer valor: "<<'"'<<","<<'"'<<" al inicio de los parametros"<<endl;
    }else if(cadena2[cadena2.length()-1]==','){
        cout<<"Error! no se detecta el ultimo valor: "<<'"'<<","<<'"'<<" al final de los parametros"<<endl;
    }else{
        //SI ENTRAMOS AQUI SIGNIFICA QUE NO HAY "," AL INICIO O AL FINAL
        string bloque="";
        int cantBloques=1;
        for(int i=0;i<cadena2.length();i++){
            if(cadena2[i]==','){
                cantBloques++;
            }
        }
        for(int i=0;i<cadena2.length();i++){
            if(cadena2[i]==','){
                lista2.push_back(limpiarCadena(bloque));
                bloque="";
            }else if(i==cadena2.length()-1){
                bloque+=cadena2[cadena2.length()-1];
                lista2.push_back(limpiarCadena(bloque));
                bloque="";
            }else{
                bloque+=cadena2[i];
            }
        }
        vector<string> filas = obtenerFilas(tabla);
        vector<string> idFilas = obtenerListaId(tabla);
        string filaSeleccionada;
        for(int i=0;i<filas.size();i++){
            if(id==idFilas[i]){
                filaSeleccionada=filas[i];
            }
        }
        //filaSeleccionada es la fila a editar
        string tablaCompleta=obtenerTabla(tabla);
        int contador1=0;
        while(tablaCompleta[contador1-1]!='#'){
            contador1++;
        }
        int contador2=contador1+1;
        while(tablaCompleta[contador2-1]!='#'){
            contador2++;
        }
        string tipoVariables="";
        for(int i=contador1;i<contador2-1;i++){
            tipoVariables+=tablaCompleta[i];
        }
        vector <string> Variables;
        string bloqueVariable="";

        for(int i=0;i<tipoVariables.length();i++){
            if(tipoVariables[i]==';'){
                Variables.push_back(obtenerPalabra(bloqueVariable,1));
                bloqueVariable="";
            }else if(i==tipoVariables.length()-1){
                Variables.push_back(bloqueVariable+tipoVariables[i]);
                bloqueVariable="";
            }else{
                bloqueVariable+=tipoVariables[i];
            }
        }

        int contador3=0,cantNumeral=0;
        while(cantNumeral<2){
            if(tablaCompleta[contador3]=='#'){
                cantNumeral++;
            }
            contador3++;
        }
        string idTablas="";
        while(tablaCompleta[contador3]!='#'){
            idTablas+=tablaCompleta[contador3];
            contador3++;
        }

        vector <string> IDTABLA;
        string bloqueIDTABLA="";

        for(int i=0;i<idTablas.length();i++){
            if(idTablas[i]==';'){
                IDTABLA.push_back(bloqueIDTABLA);
                bloqueIDTABLA="";
            }else if(i==idTablas.length()-1){
                IDTABLA.push_back(bloqueIDTABLA+idTablas[i]);
                bloqueIDTABLA="";
            }else{
                bloqueIDTABLA+=idTablas[i];
            }
        }
        bool valido=true;
        vector<bool> encontrado;
        for(int i=0;i<lista1.size();i++){
            bool si = false;
            for(int j=0;j<IDTABLA.size();j++){
                if(lista1[i]==IDTABLA[j]){
                    si=true;
                }
            }
            encontrado.push_back(si);
        }
        for(int i=0;i<lista1.size();i++){
            if(!encontrado[i]){
                cout<<"Error! "<<'"'<<lista1[i]<<'"'<<" no es un nombre de una columna"<<endl;
                valido=false;
            }
        }
        if(valido){
            if(hayStringsRepetidos(lista1)){
                //SI LLEGAMOS AQUI SIGUIFICA QUE LOS DATOS DEL PRIMER PARENTESIS SON CORRECTOS :D
                //FALTA EVALUAR LOS DATOS DEL SEGUNDO PARENTESIS
                if(lista2.size()==lista1.size()){
                    vector<int> N_TOKEN;
                    for(int i=0;i<lista2.size();i++){
                        string NombreDeDato=lista2[i];
                        if(NombreDeDato[0]==39){
                            if(NombreDeDato[NombreDeDato.length()-1]==39){
                                bool pasar=true;
                                for(int j=1;j<NombreDeDato.length()-1;j++){
                                   if(NombreDeDato[j]>=48 && NombreDeDato[j]<=57){
                                   }else if((NombreDeDato[j]=='.')||(NombreDeDato[j]==',')||(NombreDeDato[j]=='-')||(NombreDeDato[j]=='_')||(NombreDeDato[j]==32)){
                                   }else if(NombreDeDato[j]>=65 && NombreDeDato[j]<=90){
                                   }else if(NombreDeDato[j]>=97 && NombreDeDato[j]<=122){
                                   }else{
                                       pasar=false;
                                   }
                                }
                                if(pasar){
                                    if(NombreDeDato=="'"){
                                        cout<<"Error! "<<'"'<<" ' "<<'"'<<" no es valido"<<endl;
                                        N_TOKEN.push_back(-1);
                                    }else{
                                        N_TOKEN.push_back(503);
                                    }
                                }else{
                                    N_TOKEN.push_back(-1);
                                    cout<<"Error! se detectaron caracteres invalidos en "<<'"'<<NombreDeDato<<'"'<<endl;
                                }
                            }else{
                                N_TOKEN.push_back(-1);
                                cout<<"Error! se esperaba "<<'"'<<" ' "<<'"'<<" al final de "<<'"'<<NombreDeDato<<'"'<<endl;
                            }
                        }else if((NombreDeDato[NombreDeDato.length()-1]==39)&&(NombreDeDato[0]!=39)){
                            N_TOKEN.push_back(-1);
                            cout<<"Error! se esperaba "<<'"'<<" ' "<<'"'<<" al comienzo de "<<'"'<<NombreDeDato<<'"'<<endl;
                        }else{
                            bool VALIDAR=true;
                            for(int j=0;j<NombreDeDato.length();j++){
                                if(NombreDeDato[j]>=48 && NombreDeDato[j]<=57){
                                }else if(NombreDeDato[j]=='.'){
                                }else{
                                    VALIDAR=false;
                                }
                            }
                            if(VALIDAR){
                                int contadorPuntos=0;
                                for(int j=0;j<NombreDeDato.length();j++){
                                    if(NombreDeDato[j]=='.'){
                                        contadorPuntos++;
                                    }
                                }
                                if(contadorPuntos==0){
                                    N_TOKEN.push_back(501);
                                }else if(contadorPuntos==1){
                                    if(NombreDeDato[0]=='.'){
                                        N_TOKEN.push_back(-1);
                                        cout<<"Error! "<<'"'<<NombreDeDato<<'"'<<" no valido"<<endl;
                                    }else if(NombreDeDato[NombreDeDato.length()-1]=='.'){
                                        N_TOKEN.push_back(-1);
                                        cout<<"Error! "<<'"'<<NombreDeDato<<'"'<<" no valido"<<endl;
                                    }else{
                                        N_TOKEN.push_back(502);
                                    }
                                }else{
                                    N_TOKEN.push_back(-1);
                                    cout<<"Error! "<<'"'<<NombreDeDato<<'"'<<" no valido"<<endl;
                                }
                            }else{
                                N_TOKEN.push_back(-1);
                                cout<<"Error! "<<'"'<<NombreDeDato<<'"'<<" no valido"<<endl;
                            }
                        }
                    }
                        bool continuar=true;
                        for(int i=0;i<N_TOKEN.size();i++){
                            if(N_TOKEN[i]==-1){
                                continuar=false;
                            }
                        }
                        if(continuar){
                            //SI LLEGAMOS AQUI, LOS TOKENS DE EL SEGUNDO PARENTESIS SON VALIDOS SINTACTICAMENTE
                            vector<int> IDLISTA1;
                            for(int i=0;i<lista1.size();i++){
                                string eval=lista1[i];
                                for(int j=0;j<IDTABLA.size();j++){
                                    if(eval==IDTABLA[j]){
                                        IDLISTA1.push_back(ListaTokens(Variables[j]));
                                    }
                                }
                            }
                            vector <string> lista2_2;
                            for(int i=0;i<lista2.size();i++){
                                string _dato=lista2[i];
                                if(_dato[0]==39){
                                    string A="";
                                    for(int j=1;j<_dato.length()-1;j++){
                                        A+=_dato[j];
                                    }
                                    lista2_2.push_back(limpiarCadena(A));
                                }else{
                                    lista2_2.push_back(_dato);
                                }
                            }
                            bool pasar=true;
                            for(int i=0;i<N_TOKEN.size();i++){
                                if((IDLISTA1[i]==501)&&(N_TOKEN[i]==501)){
                                }else if((IDLISTA1[i]==502)&&(N_TOKEN[i]==502)){
                                }else if((IDLISTA1[i]==503)&&(N_TOKEN[i]==503)){
                                }else if((IDLISTA1[i]==502)&&(N_TOKEN[i]==501)){
                                }else{
                                pasar=false;
                                cout<<"Error! los tipos de datos no concuerdan! "<<'"'<<lista1[i]<<'"'<<" es ";
                                if(IDLISTA1[i]==501){
                                    cout<<"entero";
                                }else if(IDLISTA1[i]==502){
                                    cout<<"decimal";
                                }else{
                                    cout<<"cadena";
                                }
                                cout<<" y "<<'"'<<lista2_2[i]<<'"'<<" es";
                                if(N_TOKEN[i]==501){
                                    cout<<" entero";
                                }else if(N_TOKEN[i]==502){
                                    cout<<" decimal";
                                }else{
                                    cout<<" cadena";
                                }
                                cout<<"\n";
                            }
                            }
                        if(pasar){
                            vector<int> longitudesColumnas;
                            for(int i=0;i<lista1.size();i++){
                                string eval=lista1[i];
                                for(int j=0;j<IDTABLA.size();j++){
                                if(eval==IDTABLA[j]){
                                    string variable=Variables[j];
                                    int contador4=0;
                                    while(variable[contador4-1]!='['){
                                        contador4++;
                                    }
                                    int contador5=contador4+1;
                                    while(variable[contador5-1]!=']'){
                                        contador5++;
                                    }
                                    string variable2="";
                                    for(int i=contador4;i<contador5-1;i++){
                                        variable2+=variable[i];
                                    }
                                    longitudesColumnas.push_back(atoi(variable2.c_str()));
                                }
                                }
                            }
                            bool ultima=true;
                            for(int i=0;i<longitudesColumnas.size();i++){
                                if(lista2_2[i].length()<=longitudesColumnas[i]){

                                }else{
                                    ultima=false;
                                    cout<<"Error! con "<<'"'<<lista2_2[i]<<'"'<<" es demasiado grande"<<endl;
                                    cout<<"la longitud maxima para "<<'"'<<lista1[i]<<'"'<<" es de "<<'"'<<longitudesColumnas[i]<<'"'<<endl;
                                }
                            }
                            if(ultima){
                                //SI AS LLEGADO AQUI FELICIDADES! TODO EL EL COMANDO PARA EDITAR ES VALIDO :D
                                vector<string> listaDeFilas = obtenerFilas(tabla);
                                vector<string> listaDeDatos;
                                string palabra="";
                                for(int i=0;i<filaSeleccionada.length();i++){
                                    if(filaSeleccionada[i]==';'){
                                        listaDeDatos.push_back(palabra);
                                        palabra="";
                                    }else if(i==filaSeleccionada.length()-1){
                                        listaDeDatos.push_back(palabra+filaSeleccionada[i]);
                                        palabra="";
                                    }else{
                                        palabra+=filaSeleccionada[i];
                                    }
                                }
                            string nuevaFila1="";
                            for(int i=0;i<IDTABLA.size();i++){
                                string Lado1=IDTABLA[i];
                                bool datoColumna=false;
                                for(int j=0;j<lista1.size();j++){
                                    if(lista1[j]==Lado1){
                                        nuevaFila1+=lista2_2[j]+";";
                                        datoColumna=true;
                                    }
                                }
                                if(!datoColumna){
                                    nuevaFila1+=listaDeDatos[i]+";";
                                }
                            }
                            string nuevaFila2="";
                            for(int i=0;i<nuevaFila1.length()-1;i++){
                                nuevaFila2+=nuevaFila1[i];
                            }
                            int contador4=0;
                            string ID="";
                            while(nuevaFila2[contador4]!=';'){
                                ID+=nuevaFila2[contador4];
                                contador4++;
                            }
                            int contador5=0;
                            string ID2="";
                            while(filaSeleccionada[contador5]!=';'){
                                ID2+=filaSeleccionada[contador5];
                                contador5++;
                            }
                            if(ID==""){
                                cout<<"ALERTA! no se puede dejar el dato de la llave primaria vacio!"<<endl;
                            }else{
                                bool idPasar=true;
                                if(ID2==ID){
                                }else{
                                    for(int i=0;i<idFilas.size();i++){
                                        if(ID==idFilas[i]){
                                            idPasar=false;
                                        }
                                    }
                                }
                                if(idPasar){
                                    int contador6=0;
                                    int contador7=0;
                                    string preparaTabla="";
                                    while(contador7!=3){
                                        if(tablaCompleta[contador6]=='#'){
                                            contador7++;
                                        }
                                        preparaTabla+=tablaCompleta[contador6];
                                        contador6++;
                                    }
                                    for(int i=0;i<filas.size();i++){
                                        if(filas[i]==filaSeleccionada){
                                            preparaTabla+=nuevaFila2+"#";
                                        }else{
                                            preparaTabla+=filas[i]+"#";
                                        }
                                    }
                                    //preparaTabla contiene la nueva tabla
                                    vector<string> TODAS_LAS_TABLAS = listaDeTablas();
                                    vector<string> nombresT = nombresTablas();
                                    string baseDeDatos="";
                                    for(int i=0;i<TODAS_LAS_TABLAS.size();i++){
                                        if(nombresT[i]==tabla){
                                            baseDeDatos+="$"+preparaTabla;
                                        }else{
                                            baseDeDatos+="$"+TODAS_LAS_TABLAS[i]+"#";
                                        }
                                    }
                                    string link=ubicacion()+"/"+_dataBase+".sql";
                                    if(_Actualizar){
                                        reemplazar(link,baseDeDatos);
                                        cout<<"Datos actualizados correctamente"<<endl;
                                        if(sobra!=""){
                                            evaluar(sobra);
                                        }
                                    }else{
                                        cout << "el usuario no cuenta con permisos para actualizar registros" << endl;
                                    }
                                }else{
                                    cout<<"Error! no se puede reemplazar "<<'"'<<ID2<<'"'<<" por "<<'"'<<ID<<'"'<<endl;
                                    cout<<"El dato ya se encuentra listado"<<endl;
                                }
                            }
                            }
                        }
                        }
                        //editar dificil llave 3 (id,decimales,nombre,numero,apellido)(133,12.8,'kevin',1,' monroy  ');
                }else if(lista2.size()>lista1.size()){
                    cout<<"Error! se detectaron demasiados datos a editar. \nverifique que la candidad de datos en el lado izquierdo concuerde con el derecho"<<endl;
                }else{
                    cout<<"Error! faltan datos a editar. \nverifique que la candidad de datos en el lado izquierdo concuerde con el derecho"<<endl;
                }
            }else{
                cout<<"Error! se detectaron datos repetidos en la peticion del parentesis de la izquierda!"<<endl;
            }
        }else{
            cout<<"No se pudo editar "<<'"'<<tabla<<'"'<<endl;
        }


}}}
//FIN         FUNCIONES QUE TIENEN QUE VER CON TABLAS

//---------------------------------------
//FUNCIONES QUE TIENEN QUE VER CON FILAS
void insertarEnTabla(string nombre, string cadena, string id, string sobra){
    bool autorizar = true;
    if(obtenerFilas(nombre).size()==0){
        //NO HAY FILAS
        autorizar=true;
    }else{
        //HAY FILAS
        vector<string> ListaID = obtenerListaId(nombre);
        for(int i=0;i<ListaID.size();i++){
            if(ListaID[i]==id){
                autorizar = false;
            }
        }
    }
    if(!autorizar){
        cout<<"No se puede insertar por que ya existe un dato "<<id<<endl;
    }else{
        //SI LLEGAMOS HASTA AQUI SI SE PUEDE INSERTAR LA FILA
        vector<string> nombresT = nombresTablas();
        vector<string> listaT = listaDeTablas();
        string insersionFinal;
        for(int i=0;i<listaT.size();i++){
            if(nombresT[i]==nombre){
                insersionFinal+=("$"+listaT[i]+"#"+cadena);
            }else{
                insersionFinal+=("$"+listaT[i]+"#");
            }
        }
        string link=ubicacion()+"/"+_dataBase+".sql";
        reemplazar(link,insersionFinal);
        cout<<"Datos insertados correctamente"<<endl;
        if(sobra!=""){
            evaluar(sobra);
        }
    }
}
void eliminarFila(string tabla, string id){
    vector<string> lista_Llaves_Primarias = obtenerListaId(tabla);
    vector<string> listaFilas = obtenerFilas(tabla);
    string Tabla = obtenerTabla(tabla);
    string datos="$";
    int contador=0;
    int j=0;
    do{
        datos+=Tabla[j];
        if(Tabla[j]=='#'){
            contador++;
        }
        j++;
    }while(contador!=3);
    for(int i=0;i<listaFilas.size();i++){
        if(lista_Llaves_Primarias[i]!=id){
            datos+=listaFilas[i]+"#";
        }
    }
    string insersionFinal;
    vector<string> listaT = listaDeTablas();
    vector<string> nombresT = nombresTablas();

    for(int i=0;i<listaT.size();i++){
        if(nombresT[i]==tabla){
            insersionFinal+=(datos);
        }else{
            insersionFinal+=("$"+listaT[i]+"#");
        }
    }
    string link=ubicacion()+"/"+_dataBase+".sql";
    reemplazar(link,insersionFinal);
    cout<<"Fila eliminada correctamente"<<endl;
}
//FIN       FUNCIONES QUE TIENEN QUE VER CON FILAS

//---------------------------------------
//FUNCIONES DE PROCESOS
string separarParentesis(string cadena){
    string retorno="";
    char arreglo[cadena.length()+1];
    strcpy(arreglo, cadena.c_str());
    for(int i=0;i<cadena.length();i++){
        retorno+=arreglo[i];
        if((arreglo[i+1]=='(')||(arreglo[i+1]==')')){
            retorno+=" ";
        }
    }
    char arreglo2[retorno.length()+1];
    strcpy(arreglo2, retorno.c_str());
    string retorno2="";
    for(int i=0;i<retorno.length();i++){
        retorno2+=arreglo2[i];
            if((arreglo2[i]=='(')||(arreglo2[i]==')')){
            retorno2+=" ";
        }
    }
    return retorno2;
}
string separarCorchetes(string cadena){
    string retorno="";
    char arreglo[cadena.length()+1];
    strcpy(arreglo, cadena.c_str());
    for(int i=0;i<cadena.length();i++){
        retorno+=arreglo[i];
        if((arreglo[i+1]=='[')||(arreglo[i+1]==']')){
            retorno+=" ";
        }
    }
    char arreglo2[retorno.length()+1];
    strcpy(arreglo2, retorno.c_str());
    string retorno2="";
    for(int i=0;i<retorno.length();i++){
        retorno2+=arreglo2[i];
            if((arreglo2[i]=='[')||(arreglo2[i]==']')){
            retorno2+=" ";
        }

    }
    return retorno2;
}
string unirCorchetes(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    string inicio="";
    if((a[0]=='[')&&(a[1]==' ')){
        inicio+=a[0];
        for(int i=2;i<cadena.length();i++){
            inicio+=a[i];
        }
    }else{
        inicio=cadena;
    }
    string fin="";
    char b[inicio.length()+1];
    strcpy(b, inicio.c_str());
    if(((b[inicio.length()-1]=='[')||(b[inicio.length()-1]==']'))&&(b[inicio.length()-2]==' ')){
        for(int i=0;i<(inicio.length()-2);i++){
            fin+=b[i];
        }
        fin+=b[cadena.length()-1];
    }else{
        for(int i=0;i<inicio.length();i++){
            fin+=b[i];
        }
    }
    char c[fin.length()+1];
    strcpy(c, fin.c_str());
    string corcheteIzquierda="";
    for(int i=0;i<fin.length();i++){
        if((c[i]==' ')&&(c[i+1]=='[')){

        }else{
            corcheteIzquierda+=c[i];
        }
    }
    string corcheteIzquierda2="";
    char d[corcheteIzquierda.length()+1];
    strcpy(d, corcheteIzquierda.c_str());

    for(int i=0;i<corcheteIzquierda.length();i++){
        if((d[i]==' ')&&(d[i-1]=='[')){

        }else{
            corcheteIzquierda2+=d[i];
        }
    }
    string corcheteDerecha="";
    char e[corcheteIzquierda2.length()+1];
    strcpy(e, corcheteIzquierda2.c_str());
    for(int i=0;i<corcheteIzquierda2.length();i++){
        if((e[i]==' ')&&(e[i+1]==']')){

        }else{
            corcheteDerecha+=e[i];
        }
    }
    return corcheteDerecha;
}
string convertirMayusculas(string cadena){
    string respuesta="";
    char a[cadena.length()+1];//convierte la cadena string en arreglo de caracteres a[]
    strcpy(a, cadena.c_str());
    char b[cadena.length()];
    for(int i=0;i<cadena.length();i++){
        if((a[i]>96)&&(a[i])<123){
            b[i]=a[i]-32;
        }
        else{
            b[i]=a[i];
        }
        respuesta+=b[i];
    }
    return respuesta;
}
string obtenerPalabra(string cadena, int n){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    int contador=0,cont2=0;
    string argumento="";
    string resultado="";
    do{
        contador++;
    }while((contador<cadena.length()) && (a[contador]!=' ') && (a[contador]!=';'));
    for(int i=0;i<contador;i++){
        argumento+=a[i];
    }
    if(n==1){
        return argumento;
    }else{
        for(int i=0;i<n-1;i++){
            argumento="";
        do{
        contador++;
        }while((contador<cadena.length()) && (a[contador]!=' ') && (a[contador]!=';'));
        for(int i=0;i<contador;i++){
            argumento+=a[i];
        }
        }
        for(int i=0;i<argumento.length();i++){
            if(a[i-1]==' '){
                cont2++;
            }
            if(cont2==n-1){
                resultado+=a[i];
            }
        }
    }
    return resultado;
}
void traducir(string cadena){
    string nombre="";
    vector <string> cadenas;
    int contador=0;
    int filas=0;
    while(cadena[contador]!='#'){
        contador++;
    }
    string quitaNombre="";
    for(int i=contador;i<cadena.length();i++){
        quitaNombre+=cadena[i];
        if(cadena[i]=='#'){
            filas++;
        }
    }
    for(int i=0;i<contador;i++){
        nombre+=cadena[i];
    }
    quitaNombre+="#";
    string entra="";
    for(int i=1;i<quitaNombre.length();i++){
        if(quitaNombre[i]=='#'){
            cadenas.push_back(entra);
            entra="";
        }else{
            entra+=quitaNombre[i];
        }
    }
    contador=0;
    for(int i=0;i<cadenas[0].length();i++){
        if(cadenas[0][i]==';'){
            contador++;
        }
    }
    contador++;
    //cadenas contiene las filas y contador el numero de columnas por fila

    int mayores[contador];
    int bufer[contador];
    int n=0;

    for(int i=0;i<cadenas.size();i++){
        string fila=cadenas[i]+";";
        string entra="";
        n=0;
        for(int j=0;j<fila.length();j++){
            if(fila[j]==';'){
                if(i==0){
                    mayores[n]=entra.length();
                }else{
                    if(entra.length()>mayores[n]){
                        mayores[n]=entra.length();
                    }
                }
                n++;
                entra="";
            }else{
                entra+=fila[j];
            }
        }
    }
    //mayores contiene las longitudes maximas de las columnas
    int longitud=0;
    for(int i=0;i<contador;i++){
        longitud+=mayores[i];
    }
    int longitudTotal=longitud+(contador*4)+(contador-1);
    cout<<"|";
    for(int i=0;i<longitudTotal;i++){
        cout<<"-";
    }
    cout<<"|"<<endl;
    if(longitudTotal-nombre.length()<=0){
        cout<<nombre<<endl;
    }
    else{
        int lados=(longitudTotal-nombre.length())/2;
        cout<<"|";
        for(int i=0;i<lados;i++){
            cout<<" ";
        }
        if((lados*2)==longitudTotal-nombre.length()){
            cout<<nombre;
        }else{
            cout<<nombre+" ";
        }
        for(int i=0;i<lados;i++){
            cout<<" ";
        }
        cout<<"|"<<endl;
    }
    cout<<"|";
    for(int i=0;i<longitudTotal;i++){
        cout<<"-";
    }
    cout<<"|"<<endl;
    for(int i=0;i<cadenas.size();i++){
        string fila=cadenas[i]+";";
        string entra="";
        n=0;
        for(int j=0;j<fila.length();j++){
            if(fila[j]==';'){
                cout<< setw(mayores[n]+5) << left << "|  "+entra;
                n++;
                entra="";
            }else{
                entra+=fila[j];
            }
        }
        cout<<"|\n";
        if(i==0){

            cout<<"|";
            for(int k=0;k<longitudTotal;k++){
                cout<<"-";
            }
            cout<<"|"<<endl;


        }
    }
    cout<<"|";
    for(int i=0;i<longitudTotal;i++){
        cout<<"-";
    }
    cout<<"|"<<endl;
}
string quitarVariables(string nombre){

    string tabla = obtenerTabla(nombre);
    char a[tabla.length()];
    strcpy(a,tabla.c_str());

    int contador=0, pos=0;
    for(int i=0;i<tabla.length();i++){
        if(a[i]=='#'){
            contador++;
        }
        if(contador==2 && a[i]=='#'){
            pos=i+1;
        }
    }
    string limpia=nombre+"#";
    for(int i=pos;i<tabla.length();i++){
        limpia+=a[i];
    }
    return limpia;
}
bool hayStringsRepetidos(vector<string> lista){
    vector<string> unicos;
    for(int i=0; i<lista.size(); i++){
        if(find(unicos.begin(), unicos.end(), lista[i]) != unicos.end()) //si encuentra el valor
            return false; //esta repetido, y retorna falso
        else
            unicos.push_back(lista[i]);
    }
    return true; //si no hubo repetidos
}
int cantArgumentos(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    int contador=1;
    for(int i=0;i<cadena.length();i++){
        if(a[i]==' '){
           contador++;
        }
    }
    return contador;
}
vector<string> listaDatos(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    vector<string> lista;
    string bloque="";
    int cantBloques=1;
    for(int i=0;i<cadena.length();i++){
        if(a[i]==','){
            cantBloques++;
        }
    }
    int N_bloque=0;
    for(int i=0;i<cadena.length();i++){
        if((a[i]==',') || (i==cadena.length())){
            lista.push_back(unirCorchetes(limpiarCadena(bloque)));
            bloque="";
        }else{
            bloque+=a[i];
        }
    }
    lista.push_back(unirCorchetes(limpiarCadena(bloque)));

    return lista;
}
vector<string> separarDatos(string cadena){
    char a[cadena.length()+1];
    strcpy(a, cadena.c_str());
    vector<string> lista;
    string bloque="";
    int cantBloques=1;
    for(int i=0;i<cadena.length();i++){
        if(a[i]==';'){
            cantBloques++;
        }
    }
    int N_bloque=0;
    for(int i=0;i<cadena.length();i++){
        if((a[i]==';') || (i==cadena.length())){
            lista.push_back(unirCorchetes(limpiarCadena(bloque)));
            bloque="";
        }else{
            bloque+=a[i];
        }
    }
    lista.push_back(unirCorchetes(limpiarCadena(bloque)));

    return lista;
}
//limpiarCadena recibe la cadena string, elimina los espacios innecesarios y devuelve la cadena limpia
string limpiarCadena(string cadena){
    char arreglo[cadena.length()+1];//convierte la cadena string en arreglo de caracteres a[]
    strcpy(arreglo, cadena.c_str());
    int contador=0;
    //ciclo for que cuenta los espacios repetidos
    for(int i=0;i<cadena.length();i++){
        if((arreglo[i]==' ') && (arreglo[i+1]==' ')|| ((arreglo[i]==' ') && (arreglo[i+1]==';'))){
            contador++;
        }
    }
    int longitud=cadena.length()-contador;
    char arreglo2[longitud];
    int num=0;
    //ciclo for que quita los espacios repetidos y los guarda en arreglo2[]
    for(int i=0;i<cadena.length();i++){
        if(((arreglo[i]==' ') && (arreglo[i+1]==' ')) || ((arreglo[i]==' ') && (arreglo[i+1]==';'))){

        }else{
            arreglo2[num]=arreglo[i];
            num++;
        }
    }
    //detecta que no haya espacio en el inicio ni al final
    bool primero=false;
    bool ultimo=false;
    if(arreglo2[0]==' ')primero=true;
    if(arreglo2[longitud-1]==' ')ultimo=true;
    string cadena_limpia="";
    if(primero && ultimo){
        if(longitud==1){
            return "";
        }
        else{
            for(int i=1;i<=longitud-2;i++){
                cadena_limpia=cadena_limpia+arreglo2[i];
            }
        }
    }else if(primero){
        for(int i=1;i<=longitud-1;i++){
                cadena_limpia=cadena_limpia+arreglo2[i];
            }
    }else if(ultimo){
        for(int i=0;i<=longitud-2;i++){
                cadena_limpia=cadena_limpia+arreglo2[i];
            }
    }else{
        for(int i=0;i<longitud;i++){
                cadena_limpia=cadena_limpia+arreglo2[i];
            }
    }
    return cadena_limpia;
}
//FIN       FUNCIONES DE PROCESOS

//*************************************************************************************************************
//**************************************        ARCHIVOS      *************************************************
//*************************************************************************************************************
string leer(string cadena){
    char a[cadena.length()];
    strcpy(a, cadena.c_str());
    string cadena2="";
    fstream letras(a, ios::in|ios::out);
    letras.seekg(0, ios::beg);
    while(!letras.eof())
    cadena2+=((char)letras.get());
    letras.close();
    return cadena2;
}
void escribir(string url, string entrada){
    char a[url.length()+1];
    strcpy(a, url.c_str());

    char arreglo[entrada.length()+1];
    strcpy(arreglo, entrada.c_str());

    fstream letras(a, ios::in|ios::out);
    for(int i=0;i<entrada.length();i++){
        letras.seekp(0, ios::end);
        letras << arreglo[i];
    }
    letras.close();
}
bool comprobar(string entrada){
    entrada+=".sql";
    char c[entrada.length()];
    strcpy(c, entrada.c_str());
    ifstream fe(c, ios::in);
    if(fe.fail())return false;
    else return true;
}
string recoger(string cadena){
    string texto="";
    char arreglo[cadena.length()+1];
    strcpy(arreglo, cadena.c_str());
    for(int i=0;i<cadena.length();i++){
        if(arreglo[i-1]=='#'){
            texto+="\n";
        }
        texto+=cadena[i];
    }
    return texto;
}
void reemplazar(string url, string texto){
    char a[url.length()];
    strcpy(a,url.c_str());
    char b[texto.length()];
    strcpy(b,texto.c_str());
    ofstream file;
    file.open(a);
    file << b;
    file.close();
}
vector<string> listaDeTablas(){
    string palabra=ubicacion()+"/"+_dataBase+".sql";
    vector<int> tablas = posicionesIniciales();
    vector<string> lista;
    vector<string> lista2;
    for(int i=0;i<tablas.size();i++){
        char a[palabra.length()];
        strcpy(a, palabra.c_str());
        string cadena="";
        char letra;
        fstream letras(a, ios::in|ios::out);
        letras.seekg(tablas[i]+1, ios::beg);
        bool seguir=true;
        while(!letras.eof()&&seguir){
            cadena+=((char)letras.get());
            char b[cadena.length()];
            strcpy(b, cadena.c_str());
            if(b[cadena.length()-1]=='$'){
                seguir=false;
            }
        }
        letras.close();
        lista.push_back(cadena);
    }
    for(int i=0;i<lista.size();i++){
        char c[lista[i].length()];
        strcpy(c,lista[i].c_str());
        string resultado="";
        for(int j=0;j<lista[i].length()-2;j++){
            resultado+=c[j];
        }
        lista2.push_back(resultado);
    }
    return lista2;
}
vector<string> nombresTablas(){
    string palabra=ubicacion()+"/"+_dataBase+".sql";
    vector<int> tablas = posicionesIniciales();
    vector<string> lista;
    for(int i=0;i<tablas.size();i++){
        char a[palabra.length()];
        strcpy(a, palabra.c_str());
        string cadena="";
        char letra;
        fstream letras(a, ios::in|ios::out);
        letras.seekg(tablas[i], ios::beg);
        bool seguir=true;
        while(!letras.eof()&&seguir){
            cadena+=((char)letras.get());
            char b[cadena.length()];
            strcpy(b, cadena.c_str());
            if(b[cadena.length()-1]=='#'){
                seguir=false;
            }
        }
        letras.close();
        char c[cadena.length()];
        strcpy(c, cadena.c_str());
        string retorno="";
        for(int i=1;i<cadena.length()-1;i++){
            retorno+=c[i];
        }
        lista.push_back(retorno);
    }
    return lista;
}
vector<int> posicionesIniciales(){
    string direccion=ubicacion()+"/"+_dataBase+".sql";
    string tabla = Lectura(direccion);
    char tab[tabla.length()+1];
    strcpy(tab, tabla.c_str());
    vector<int> retorno;
    for(int i=0;i<tabla.length();i++)
    if(tab[i]=='$')retorno.push_back(i);
    return retorno;
}
void insertar_Al_Final(string cadena){
    string direccion=ubicacion()+"/"+_dataBase+".sql";
    char arreglo[cadena.length()+1];
    strcpy(arreglo, cadena.c_str());
    char arreglo2[direccion.length()+1];
    strcpy(arreglo2, direccion.c_str());
    fstream letras(arreglo2, ios::in|ios::out);
    for(int i=0;i<cadena.length();i++){
        letras.seekp(0, ios::end);
        letras << arreglo[i];
    }
    letras.close();
}
string muestra_contenido_de(const std::string &a_carpeta){
    string bd="";
    if (DIR *dpdf = opendir(a_carpeta.c_str()))
    {
        dirent *epdf;
        while (epdf = readdir(dpdf))
        {
            bd+=epdf->d_name;
            bd+=' ';
        }
    }
    return bd;
}
string Lectura(string basedatos){
    char arreglo[basedatos.length()+1];
    strcpy(arreglo, basedatos.c_str());
    string cadena="";
    char letra;
    fstream letras(arreglo, ios::in|ios::out);
    letras.seekg(0, ios::beg);
    while(!letras.eof())
    cadena+=((char)letras.get());
    letras.close();
    return cadena;
}
void crearArchivoUsuarios(){
    string direccion = ubicacion()+"/UwuDB.sql";
    char usuarios[direccion.length()+1];
    strcpy(usuarios, direccion.c_str());
    ofstream file;
    file.open(usuarios);
    file.close();
    ///////////////////////////////////////////////////
    string tab="$USUARIOS#CARACTER[100] LLAVE PRIMARIA;CARACTER[100];ENTERO[1];ENTERO[1];ENTERO[1];ENTERO[1];ENTERO[1];ENTERO[1];ENTERO[1]#NOMBRE;CLAVE;CREAR;ELIM_TABLA;ELIM_FILA;INSERT;VER;ACTUALIZAR;PRIVILEGIOS#";
    ////////////////////////////////////////////////////
    escribir(ubicacion()+"/UwuDB.sql",tab);
}
bool carpetaBD(){
    string direccion = "mkdir "+ubicacion();
    char a[direccion.length()+1];
    strcpy(a, direccion.c_str());
    bool respuesta = false;
    if(system(a)){
        respuesta = false;
    }else{
        respuesta = true;
    }
    return respuesta;
}
string ubicacion(){
    //windows es BD || en linux es /HOME/BD
    return "/home/BD";
}
string encriptar(string cadena){
    string res = "";
    int llave = 4;
    for(int i=0; i<cadena.length(); i++) res += cadena[i] + llave;
    return res;
}
string desencriptar(string cadena){
    string res = "";
    int llave = 4;
    for(int i=0; i<cadena.length(); i++) res += cadena[i] - llave;
    return res;
}
//FIN
