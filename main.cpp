#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "./db.h"

using namespace std;

// Realiza una consulta a la bd, seleccionando el rut y el promedio de las notas
void avgGenerate(){
    // Se inicializa el archivo de salida
    std::ofstream fileOut("puntajesPromediados.csv");
    // Se inicializa la conexion a la BD
    PGconn* conexion = dbconnect((char *)DBSERVER,(int)DBPUERTO,(char *)DBNAME,(char *)DBUSER,(char *)DBPASSWORD);
    // Se inicializa variable que almacenará la consulta a la base de datos
    std::string query = "SELECT rut, round((nem+ranking+matematica+lenguaje+ciencias+historia)/6) FROM puntajes;";
    // Se inicializa variable que almacenará el resultado de la consulta
    PGresult* result = dbquery(conexion, (char *)query.c_str());
    // Se determina el numero de filas de la consulta
    long rows = dbnumrows(result);
    // Bucle for que recorre fila por fila 'result' para ir escribiendo en el archivo de salida el rut y su promedio
    for(int i=0; i<rows; i++){
        std::string rut = dbresult(result,i,0);
        std::string avg = dbresult(result,i,1);
        std::string line = rut + ";" + avg;
        fileOut << line << std::endl;  
    } 
    // Se cierra el archivo
    fileOut.close();
}

// Integrantes del grupo
void integrantes(){
    std::cout << "***Alumnos***" << std::endl;
    std::cout << "Brayan Parra" << std::endl;
    std::cout << "Lucas Carmona" << std::endl;
    std::cout << "Yerko Foncea" << std::endl; 
}

int main(int argc, char** argv) {
    avgGenerate();
    return 0;
}