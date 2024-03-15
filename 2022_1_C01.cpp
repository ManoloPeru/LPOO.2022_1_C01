#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX = 20;

// Función para validar las dimensiones del tablero
bool validarDimensiones(int n, int m) {
    //mayor a CERO Y menor al maximo: 20
    return (n > 0 && m > 0 && n <= MAX && m <= MAX);
}

// Función para imprimir un tablero
void imprimirTablero(char tablero[][MAX], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para generar los ejércitos de acuerdo a las reglas establecidas
void generarEjercitos(char ejercito1[][MAX], char ejercito2[][MAX], int n, int m, int espaciosVacios, char opcionJugador1, char opcionJugador2) {
    srand(time(0)); // Inicializar la semilla para la generación aleatoria

    char guerrerosJugador1[2];
    char jefeJugador1;

    char guerrerosJugador2[2];
    char jefeJugador2;

    // Determinar los tipos de guerreros y jefe para el jugador 1
    if (opcionJugador1 == 'L') {
        guerrerosJugador1[0] = 'A';
        guerrerosJugador1[1] = 'B';
        jefeJugador1 = 'L';
    }
    else if (opcionJugador1 == 'T') {
        guerrerosJugador1[0] = 'C';
        guerrerosJugador1[1] = 'D';
        jefeJugador1 = 'T';
    }

    // Determinar los tipos de guerreros y jefe para el jugador 2
    if (opcionJugador2 == 'J') {
        guerrerosJugador2[0] = 'E';
        guerrerosJugador2[1] = 'F';
        jefeJugador2 = 'J';
    }
    else if (opcionJugador2 == 'Z') {
        guerrerosJugador2[0] = 'G';
        guerrerosJugador2[1] = 'H';
        jefeJugador2 = 'Z';
    }

    // Poblar los tableros con guerreros 
    // y luego remplazamos al Jefe y los vacios
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ejercito1[i][j] = guerrerosJugador1[rand() % 2];
            ejercito2[i][j] = guerrerosJugador2[rand() % 2];
        }
    }
    cout << "==== Inicializando Ejercito 1 =======================" << endl;
    imprimirTablero(ejercito1, n, m);
    cout << endl;
    
    // Inicializar contadores para la cantidad de jefes colocados
    int jefesColocados1 = 0;
    int jefesColocados2 = 0;
    int espaciosVacios2 = espaciosVacios;
    
    // Agregar al ejército 1, el jefe
    int iValorAleatorio = rand() % (n * m);
    int iContAux = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Generar jefe del ejército
            if (iValorAleatorio == iContAux && jefesColocados1 == 0) {
                ejercito1[i][j] = jefeJugador1;
                jefesColocados1++;
            }
            iContAux++;
        }
    }
    cout << "==== Ejercitos 1 + Jefe =======================" << endl;
    imprimirTablero(ejercito1, n, m);
    cout << endl;
    // Registrar lo vacios en ejercito 1
    int espaciosVaciosColocados = 0;
    while (espaciosVaciosColocados < espaciosVacios) {
        int fila = rand() % n;
        int columna = rand() % m;
        if (ejercito1[fila][columna] != jefeJugador1) {
            ejercito1[fila][columna] = ' ';
            espaciosVaciosColocados++;
        }
    }
    cout << "==== Ejercitos 1 + Jefe + vacios =======================" << endl;
    imprimirTablero(ejercito1, n, m);
    cout << endl;

    cout << "==== Inicializando Ejercito 2 =======================" << endl;
    imprimirTablero(ejercito2, n, m);
    cout << endl;
    
    // Agregar al ejército 2, el jefe
    iValorAleatorio = rand() % (n * m);
    iContAux = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Generar jefe del ejército
            if (iValorAleatorio == iContAux && jefesColocados2 == 0) {
                ejercito2[i][j] = jefeJugador2;
                jefesColocados2++;
            }
            iContAux++;
        }
    }
    cout << "==== Ejercitos 2 + Jefe =======================" << endl;
    imprimirTablero(ejercito2, n, m);
    cout << endl;
    // Registrar lo vacios en ejercito 2
    espaciosVaciosColocados = 0;
    while (espaciosVaciosColocados < espaciosVacios2) {
        int fila = rand() % n;
        int columna = rand() % m;
        if (ejercito2[fila][columna] != jefeJugador2) {
            ejercito2[fila][columna] = ' ';
            espaciosVaciosColocados++;
        }
    }
    cout << "==== Ejercitos 1 + Jefe + vacios =======================" << endl;
    imprimirTablero(ejercito2, n, m);
    cout << endl;
}

// Función para realizar un disparo en el tablero del oponente
void disparar(char tablero[][MAX], int x, int y) {
    //Si no es igual a ninguno de los jefes
    if (tablero[x][y] != ' ' && tablero[x][y] != 'L' && tablero[x][y] != 'T' && tablero[x][y] != 'J' && tablero[x][y] != 'Z') {
        tablero[x][y] = 'X'; // El guerrero ha sido eliminado
    }
}

// Función para verificar si un ejército ha sido derrotado
bool ejercitoDerrotado(char tablero[][MAX], int x, int y, char jefe1, char jefe2) {
    if (tablero[x][y] == jefe1 || tablero[x][y] == jefe2) {
        return true; // El jefe del ejército ha caido, perdio
    }
    return false; // No se encontró al jefe del ejército, contiua
}

int main() {
    int n, m;
    // Solicitar y validar las dimensiones del tablero
    do {
        cout << "Ingrese las dimensiones del tablero que simulara los ejercitos (N y M): ";
        cin >> n >> m;
        if (!validarDimensiones(n, m)) {
            cout << "Error: Dimensiones no validas. Debe ingresar dos numeros mayores que 0 y menores o iguales que 20." << endl;
        }
    } while (!validarDimensiones(n, m));

    int espaciosVacios = (n * m) / 10;

    char ejercito1[MAX][MAX];
    char ejercito2[MAX][MAX];

    cout << "Los ejercitos han sido creados y cada uno tiene " << espaciosVacios << " espacios vacíos." << endl;

    int opcion; //Del menu seleccionado
    bool juegoTerminado = false; // Variable para controlar el fin del juego
    int turno = 1; // Variable para determinar el turno del jugador

    do {
        cout << "==================================================" << endl;
        cout << "\nBienvenido al juego de los 300 guerreros de LPOO" << endl;
        cout << "==================================================" << endl;
        cout << "Las opciones son:" << endl;
        cout << "[1] Generar ejercitos." << endl;
        cout << "[2] Jugar." << endl;
        cout << "[3] Salir." << endl;
        cout << "Ingrese opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Jugador 1 elija entre el Ejercito de Leonidas (L), Temistocles (T): ";
            char opcionJugador1;
            cin >> opcionJugador1;

            cout << "Jugador 2 elija entre el Ejercito de Jerjes (J) o Artemisa (Z): ";
            char opcionJugador2;
            cin >> opcionJugador2;

            // Generar los ejércitos de forma aleatoria
            generarEjercitos(ejercito1, ejercito2, n, m, espaciosVacios, opcionJugador1, opcionJugador2);
            break;
        case 2:
            if (ejercito1[0][0] == '\0' || ejercito2[0][0] == '\0') {
                cout << "Error: Debe generar los ejercitos antes de jugar." << endl;
                break;
            }
            cout << "==== Inicializamos el juego: ======================================" << endl;
            while (!juegoTerminado) {
                // Imprimir tablero del jugador actual
                if (turno == 1) {
                    cout << "Turno del Jugador 1, este es su ejercito:" << endl;
                    imprimirTablero(ejercito1, n, m);
                }
                else {
                    cout << "Turno del Jugador 2, este es su ejercito:" << endl;
                    imprimirTablero(ejercito2, n, m);
                }

                int x, y;
                cout << "Ingrese las posiciones del guerrero a seleccionar (fila columna): ";
                cin >> x >> y;

                if (turno == 1) {
                    //Guerrero a disparar
                    char guerreroDisparar = ejercito1[x - 1][y - 1];
                    cout << "Guerrero a disparar:" << guerreroDisparar << endl;
                    int iIntentos = 1;
                    if(guerreroDisparar == 'A' || guerreroDisparar == 'C')
                        iIntentos = 2;
                    while (iIntentos > 0)
                    {
                        cout << "Ingrese las posiciones del disparo a realizar (fila columna): ";
                        cin >> x >> y;
                        disparar(ejercito2, x - 1, y - 1);
                        if (ejercitoDerrotado(ejercito2, x - 1, y - 1, 'J', 'Z')) {
                            cout << "====> El jugador 1 ha GANADO la partida!" << endl;
                            juegoTerminado = true;
                            break;
                        }
                        else
                        {
                            cout << "====> FALLO !" << endl;
                        }
                        iIntentos--;
                        turno = 2;
                    }
                }
                else {
                    //Guerrero a disparar
                    char guerreroDisparar = ejercito2[x - 1][y - 1];
                    cout << "Guerrero a disparar:" << guerreroDisparar << endl;
                    int iIntentos = 1;
                    if (guerreroDisparar == 'E' || guerreroDisparar == 'G')
                        iIntentos = 2;
                    while (iIntentos > 0)
                    {
                        cout << "Ingrese las posiciones del disparo a realizar (fila columna): ";
                        cin >> x >> y;
                        disparar(ejercito1, x - 1, y - 1);
                        if (ejercitoDerrotado(ejercito1, x - 1, y - 1, 'L', 'T')) {
                            cout << "====> El jugador 2 ha GANADO la partida!" << endl;
                            juegoTerminado = true;
                            break;
                        }
                        else
                        {
                            cout << "====> FALLO !" << endl;
                        }
                        iIntentos--;
                        turno = 1;
                    }
                }
                if (juegoTerminado) {
                    cout << "====> FELICIDADES" << endl;
                }
                else
                {
                    cout << "==== Cambio de jugador ======================================" << endl;
                }
            }
            break;
        case 3:
            cout << "Gracias por jugar. ¡Hasta luego!" << endl;
            break;
        default:
            cout << "Opción no válida. Por favor, ingrese una opción válida." << endl;
        }
    } while (opcion != 3);

    return 0;
}
