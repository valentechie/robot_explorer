// Simulación de un Robot Explorador en un Tablero con Obstáculos

// Autor: Valentina
// Fecha: 16/12

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>

struct Tablero {
    char** tablero; // Asignación dinámica de memoria en Arrays
    int filas;
    int columnas;
};

struct Robot {
    int Rx;
    int Ry;
};

struct Obstaculo {
    int fila;
    int columna;
};

// CREACION DE LOS PROTOTIPOS DE LAS FUNCIONES
void leerArchivo(const std::string&, int&, int&, int&, int&, Obstaculo*&, int&);
void crearTablero(Tablero&);
void verTablero(Tablero&);
bool validarMovimiento(Tablero&, int, int);
bool movimientoPosible(Tablero&, Robot&);
void moverRobot(Tablero&, Robot&);
int estadoActual(Tablero&, char);
void liberarMemoria(Tablero&, Obstaculo*);

int main() {
    Obstaculo* obstaculos = nullptr;  // Puntero a los obstáculos

    // SOLO PUEDEN HABER 10 OBSTACULOS
    int num_obstaculos = 0;  // Número de obstáculos leídos
    Tablero entorno;
    int n_filas = 0, m_columnas = 0, robot_filas = 0, robot_columnas = 0;
    
    std::string archivo = "config.txt";
    leerArchivo(archivo, n_filas, m_columnas, robot_filas, robot_columnas, obstaculos, num_obstaculos);
    
    entorno.filas = n_filas;
    entorno.columnas = m_columnas;

    crearTablero(entorno);
    
    // Colocar el robot en el tablero
    // EL ROBOT SE VISUALIZA CON CARACTER A
    entorno.tablero[robot_filas][robot_columnas] = 'A';
    Robot robot = {robot_filas, robot_columnas};
    

    // Colocar los obstáculos en el tablero
    for (int i = 0; i < 10; i++) {
        if (obstaculos[i].fila != robot.Rx || obstaculos[i].columna != robot.Ry) {
            entorno.tablero[obstaculos[i].fila][obstaculos[i].columna] = '#';
        } else {
            std::cerr << "Error: Un obstaculo no puede estar en la misma posición que el robot.\n";
            liberarMemoria(entorno, obstaculos);
            return 0;
        }
    }

    while (movimientoPosible(entorno, robot)) {
        verTablero(entorno);
        std::cout << "Celdas recorridas: " << estadoActual(entorno, '*') << std::endl;
        std::cout << "Celdas libres: " << estadoActual(entorno, '.') << std::endl;

        std::cout << "Presione Enter para continuar . . .";
        std::cin.get();
        system("clear");

        moverRobot(entorno, robot);
    }

    verTablero(entorno);
    std::cout << "Celdas recorridas: " << estadoActual(entorno, '*') << std::endl;
    std::cout << "Celdas libres: " << estadoActual(entorno, '.') << std::endl;

    std::ofstream escribir_salida("salida.txt");
    assert(escribir_salida.is_open());
    for (int i = 0; i < entorno.filas; i++) {
        for (int j = 0; j < entorno.columnas; j++) {
            escribir_salida << entorno.tablero[i][j] << " ";
        }
        escribir_salida << std::endl;
    }

    escribir_salida << "Celdas recorridas: " << estadoActual(entorno, '*') << std::endl;
    escribir_salida << "Celdas libres: " << estadoActual(entorno, '.') << std::endl;
    escribir_salida.close();
    
    liberarMemoria(entorno, obstaculos);
    return 0;
}

void leerArchivo(const std::string& archivo, int& n_filas, int& m_columnas, int& robot_filas, int& robot_columnas, Obstaculo*& obstaculos, int& num_obstaculos) {
    std::string lineas;
    std::ifstream leer_archivo(archivo);
    assert(leer_archivo.is_open());

    int contador = 0;
    while (std::getline(leer_archivo, lineas)) {
        contador++;
   
        if(contador == 1) {
            std::string encontrar = ",";
            std::size_t posicion = lineas.find(encontrar);

            std::string linea1_der = lineas.substr(0, posicion);
            std::string linea1_izq = lineas.substr(posicion + 1);

            if (stoi(linea1_der) < 0 || stoi(linea1_izq) < 0) {
                std::cerr << "Error: Las dimensiones del tablero deben ser mayores a cero." << std::endl;
                return;
            }

            n_filas = stoi(linea1_der);
            m_columnas = stoi(linea1_izq);
        }

        if(contador == 2) {
            std::string encontrar = ",";
            std::size_t posicion = lineas.find(encontrar);

            std::string linea2_der = lineas.substr(0, posicion);
            std::string linea2_izq = lineas.substr(posicion + 1);

            robot_filas = stoi(linea2_der);
            robot_columnas = stoi(linea2_izq);
            
            // Verificación de que las coordenadas estén dentro del tablero
            if (robot_filas < 0 || robot_filas >= n_filas || robot_columnas < 0 || robot_columnas >= m_columnas) {
                std::cerr << "Error: Las coordenadas del robot estan fuera de los limites del tablero" << std::endl;
                return;
            }
        }
   
        if(contador >= 3) {
            std::string encontrar = ",";
            std::size_t posicion = lineas.find(encontrar);

            std::string linea3_der = lineas.substr(0, posicion);
            std::string linea3_izq = lineas.substr(posicion + 1);

            int obstaculo_fila = stoi(linea3_der);
            int obstaculo_columna = stoi(linea3_izq);

            
            // Reservar memoria para los obstáculos
            Obstaculo* temp = new Obstaculo[num_obstaculos + 1];
            for (int i = 0; i < num_obstaculos; ++i) {
                temp[i] = obstaculos[i];
            }

            temp[num_obstaculos].fila = obstaculo_fila;
            temp[num_obstaculos].columna = obstaculo_columna;

            delete[] obstaculos;
            obstaculos = temp;
            num_obstaculos++;
        }
    }
    leer_archivo.close();
}

void crearTablero(Tablero& mapa) {
    mapa.tablero = new char*[mapa.filas];
    for(int i = 0; i < mapa.filas; i++) {
        mapa.tablero[i] = new char[mapa.columnas];
    }

    for(int i = 0; i < mapa.filas; i++) {
        for(int j = 0; j < mapa.columnas; j++) {
            mapa.tablero[i][j] = '.';
        }
    }
}

void verTablero(Tablero& mapa) {
    for(int i = 0; i < mapa.filas; i++) {
        for(int j = 0; j < mapa.columnas; j++) {
            std::cout << mapa.tablero[i][j] << " ";
        }
        std::cout << "\n";
    }
}

bool validarMovimiento(Tablero& mapa, int fila, int columna) {
    if (fila < 0 || fila >= mapa.filas || columna < 0 || columna >= mapa.columnas) {
        return false;
    }

    if (mapa.tablero[fila][columna] == '*' || mapa.tablero[fila][columna] == '#' || mapa.tablero[fila][columna] == 'A') {
        return false;
    }
    return true;
}

bool movimientoPosible(Tablero& mapa, Robot& robot) {
    return (validarMovimiento(mapa, robot.Rx - 1, robot.Ry) || validarMovimiento(mapa, robot.Rx + 1, robot.Ry) ||  
            validarMovimiento(mapa, robot.Rx, robot.Ry - 1) || validarMovimiento(mapa, robot.Rx, robot.Ry + 1) ||  
            validarMovimiento(mapa, robot.Rx - 1, robot.Ry - 1) || validarMovimiento(mapa, robot.Rx - 1, robot.Ry + 1) ||
            validarMovimiento(mapa, robot.Rx + 1, robot.Ry - 1) || validarMovimiento(mapa, robot.Rx + 1, robot.Ry + 1));
}

void moverRobot(Tablero& mapa, Robot& robot) {
    int nueva_fila = robot.Rx;
    int nueva_columna = robot.Ry;
   
    int movimientos[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
   
    for (int i = 0; i < 8; i++) {
        nueva_fila = robot.Rx + movimientos[i][0];
        nueva_columna = robot.Ry + movimientos[i][1];
       
        if (validarMovimiento(mapa, nueva_fila, nueva_columna)) {
            mapa.tablero[robot.Rx][robot.Ry] = '*';
           
            robot.Rx = nueva_fila;
            robot.Ry = nueva_columna;
            mapa.tablero[robot.Rx][robot.Ry] = 'A';
            return;
        }
    }
}

int estadoActual(Tablero& mapa, char signo) {
    int contador = 0;
    for(int i = 0; i < mapa.filas; i++) {
        for(int j = 0; j < mapa.columnas; j++) {
            if (mapa.tablero[i][j] == signo) {
                contador++;
            }
        }
    }
    return contador;
}

void liberarMemoria(Tablero& mapa, Obstaculo* obstaculos) {
    if (mapa.tablero != nullptr) {
        for (int i = 0; i < mapa.filas; i++) {
            if (mapa.tablero[i] != nullptr) {
                delete[] mapa.tablero[i];
            }
        }
        delete[] mapa.tablero;
        mapa.tablero = nullptr;
    }
    
    delete[] obstaculos;
}
