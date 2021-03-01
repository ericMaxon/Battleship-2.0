#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

//Longitud permitida de caracteres
#define CHAR_TAM 32 
//Tamanio del tablero 8 + 1 para la ubicacion de los indicadores de columna y fila
#define COLUMNAS 9 
#define FILAS 9 
//Cantidad de jugadores, tamaño de los distintos barcos.
#define CANT_JUG 2
#define BARCOGRAN 4
#define BARCOMED 3
#define BARCOCHIC 2
//Estructura que maneja las variables de las coordenadas
struct Coordenadas{
	char columna;
	int fila;
	int columna_ant;
	int fila_ant;
 } coor;
//Estructura que maneja las variables pertenecientes al juego de Battleship
struct Battleship{
	char nombre[CHAR_TAM];
	int racha;
	int tablero_def[FILAS][COLUMNAS];
	int tablero_atk[FILAS][COLUMNAS];
	int unidades;
}Jugadores[CANT_JUG];
/*
	Podria haber usado arreglos en paralelo en vez de usar el struct.
	char Jugador[CANT_JUG][CHAR_TAM](reemplazaria la variable nombre;
	int racha[CANT_JUG];
	int tablero_def[CANT_JUG][FILAS][COLUMNA];
	int tablero_def[CANT_JUG][FILAS][COLUMNA]; 
	int unidades[CANT_JUG}
*/
//Inicializadores
void Indicaciones();
void InicializarVariables();
//Funciones principales.
void CrearBarcos(int unidades, int cantidad, int jugador);
void Atacar(int atacante, int defensor);
//Para verificar que la insercion de la popa no este lejos de los esperado
bool VerificarPosicionHorizontal(int unidades, int col, int col_ant);
bool VerificarPosicionVertical(int unidades, int fil, int fil_ant);
//Operaciones de validaciones y metodos auxiliares
char ValidarOrientacion(int jugador);
void ValidarCoordenadas(int jugador, int etapa);//Etapa denota el estado o momento en que se usara si para la creacion de los barcos o el ataque
void Insertar(int fil, int col, int jugador, int unidades, int orien,int parte);
void AsignarAnterior(int fila, int columna);
void MostrarTableroNormal(int jugador);
void MostrarTableroAtaque(int jugador);
void MostrarOrientacion(char orientacion, int parte);
//Metodos para la lectura de datos
char LeerDatosChar();
char* LeerCadenas();
struct Coordenadas Posicion();

int main(void) {
	int p, b;
	Indicaciones();
	InicializarVariables();
	//Creacion de barcos
	for(p = 0; p < CANT_JUG; p++){
		printf("\nJugador %d, ingrese su nombre\n", p+1);
		strcpy(Jugadores[p].nombre, LeerCadenas());
		system("cls");
		printf("\n%s, organice su flota de %d unidades:\n", Jugadores[p].nombre, BARCOCHIC);
		CrearBarcos(BARCOCHIC, 2, p);
		printf("\n%s, organice su flota de %d unidades:\n", Jugadores[p].nombre, BARCOMED);
		CrearBarcos(BARCOMED, 2, p);
		printf("\n%s, organice su flota de %d unidades:\n", Jugadores[p].nombre, BARCOGRAN);
		CrearBarcos(BARCOGRAN, 1, p);
		printf("\nAsi quedo su tablero, %s\n", Jugadores[p].nombre);
		MostrarTableroNormal(p);
		printf("\nPasale al que sigue\n");
		system("pause");
		system("cls");
	}
	bool estadoPartida;
	int atacante = 0;int defensor=1;int aux;
	
	do{
		printf("\t\t\t\t\tEs el turno de %s, de atacar\n\n\n", Jugadores[atacante].nombre);
		Atacar(atacante, defensor);
		estadoPartida = Jugadores[defensor].unidades == 0;
		//Para cuando un jugador termine con las unidades del oponente, omitir las lineas del cambio de turno.
		if(!estadoPartida)
			continue;
		//Las siguientes 3 lineas, es para pasar de turno a los jugadores.
		atacante = defensor;
		aux = 1 - atacante;
		defensor = aux;
	}while(estadoPartida);
	system("cls");
	printf("\n\n\n\t\tFelicidades %s!\n\tHaz ganado con una racha de: %d.", Jugadores[atacante].nombre, Jugadores[atacante].racha);
	MostrarTableroAtaque(atacante);
	MostrarTableroNormal(atacante);
	printf("\n\t\tGracias por jugar\n");
  	return 0;
	}

void Indicaciones(){
	printf("\n\t\t\t\tBienvenido a Battleship!");
	//printf("\n\n\tPor favor maximize la ventanilla para disfrutar al maximo el juego");
	printf("\n\n\tLas Reglas del juego seran las siguientes: \n\tCada jugador tendra:\n\t	2 barcos de 2 unidades\n\t  2 barcos de 3 unidades\n\t  1 barco de 4 unidades");
	printf("\n\n\tAl colocar los barcos puedes hacerlo de forma horizontal o vertical evitando que se toquen entre ellos,");
	printf("\n\tcolocando primero la proa (parte frontal del barco), luego la popa (parte trasera del barco).");
	printf("\n\n\tEl jugador que acierte mantendra el turno");
	printf("\n\n\tDebe introducir las coordenadas de la siguiente manera:\n\t Coordenada [letra, numero]\n\n");
	printf("\tNOTA\n\t En el tablero defensa, esto %c marcara las posiciones donde estan sus barcos, mientras que el\n\t%c es el que marca las flotas que han sido tumbadas", 219, 178);
	printf("\n\t En el tablero de ataque, este %c marcara las posiciones en las que usted fallo el tiro, y el %c\n\t marcara las posiciones en las que derrumbo un barco\n\n",206,178);
	system("pause");
	system("cls");
	}
void InicializarVariables(){
    int i, j, jug;
		for(jug = 0; jug < CANT_JUG; jug++){
			
			for( i = 1; i < 9; i++){
					//Numeros de las filas del tablero
					Jugadores[jug].tablero_def[i][0] = i;
					Jugadores[jug].tablero_atk[i][0] = i;
					//caracteres del tablero
					for( j = 1; j < 9; j++){
						Jugadores[jug].tablero_def[i][j] = 177;
						Jugadores[jug].tablero_atk[i][j] = 177;       
					}
			}
			
			for( i = 0; i < 9; i++){
				//Letras de las columnas del tablero
					Jugadores[jug].tablero_def[0][i] = 64 + i;
					Jugadores[jug].tablero_atk[0][i] = 64 + i;
					
					//espacio vacio del tablero, que corresponde a la esquina superior izq.
					if(Jugadores[jug].tablero_def[0][i] == 64){
							Jugadores[jug].tablero_def[0][i] = 220;
							Jugadores[jug].tablero_atk[0][i] = 220;
					}
			}
			
		}
		coor.columna = 0;
		coor.fila = 0;
		coor.fila_ant = 0;
		coor.columna_ant = 0;
	}
void CrearBarcos(int unidades, int cantidad, int jugador){
	char orien;
	bool error;
	int propa;int aux;//0 es para proa, 1 para popa
	int cant;
	for(cant = 1;cant <= cantidad; cant++){
		printf("Posicionamiento del barco %d, de %d unidades\n", cant, unidades);
		propa = 0;
		while(propa < 2){
			MostrarTableroNormal(jugador);
			if(propa == 0){
				//Orientacion del barco
				orien = ValidarOrientacion(jugador);
				MostrarOrientacion(orien, propa);
				//Posicion de la proa
				ValidarCoordenadas(jugador, 1);
				Insertar(coor.fila, coor.columna, jugador, unidades, orien, propa);
				system("pause");
				system("cls");
			}
			if(propa == 1){ 
				do{
					
				MostrarOrientacion(orien,propa);
				//Posicion de la proa
				ValidarCoordenadas(jugador, 1);
					ValidarCoordenadas(jugador, 1);
					if(orien == 'h'&& coor.fila == coor.fila_ant){
						error = VerificarPosicionHorizontal(unidades, coor.columna, coor.columna_ant);
						continue;
					}
					if(orien == 'v' && coor.columna == coor.columna_ant){
						error = VerificarPosicionVertical(unidades, coor.fila, coor.fila_ant);
					continue;
					}
					if(coor.columna != coor.columna_ant || coor.fila != coor.fila_ant){
						error = true; 
						printf("Por favor arme su barco correctamente\n");
						system("pause");
						continue;
					}	
				}while(error);
				Insertar(coor.fila, coor.columna, jugador, unidades, orien, propa);	
				system("pause");
				system("cls");
			}
			propa += 1;		
		}	
	}
	}
void Atacar(int atacante, int defensor){
	bool acertado;
	bool error;
	do{
		printf("\t\t\t\tEstamos atacando\n\n");
		printf("\t\t%s, llevas una racha de %d: \n", Jugadores[atacante].nombre, Jugadores[atacante].racha);
		MostrarTableroAtaque(atacante);
		MostrarTableroNormal(atacante);
		ValidarCoordenadas(atacante, 2);
		
		acertado = (Jugadores[defensor].tablero_def[coor.fila][coor.columna] == 219);
		if(acertado){
			Jugadores[atacante].racha += 1;
			Jugadores[defensor].unidades--;
			Jugadores[atacante].tablero_atk[coor.fila][coor.columna] = 178;
			Jugadores[defensor].tablero_def[coor.fila][coor.columna] = 178;
			printf("\n\n\t\tHaz acertado, perfecto");
			printf("\nSu racha actual es: %d\n", Jugadores[atacante].racha);
			system("pause");
			system("cls");
		}else{
			Jugadores[atacante].tablero_atk[coor.fila][coor.columna] = 206;
			Jugadores[defensor].tablero_def[coor.fila][coor.columna] = 206;
			printf("\n\n\tHaz fallado");
			if(Jugadores[atacante].racha >= 1)
				printf("\n\tHaz perdido una racha de %d\n", Jugadores[atacante].racha);
			Jugadores[atacante].racha = 0;
			system("pause");
			system("cls");
		}
	}while(acertado);
	}
void MostrarTableroNormal(int jugador){
	int i, j;
	printf("\n");
	for(i = 0; i < 9; i++){
		printf("%c\t", Jugadores[jugador].tablero_def[0][i]);
	}
	for(i = 1; i < 9; i++){
		printf("\n%d\t", Jugadores[jugador].tablero_def[i][0]);
		for(j = 1; j < 9; j++){
			printf("%c\t", Jugadores[jugador].tablero_def[i][j]);
		}
	}
	}
void MostrarTableroAtaque(int jugador){
	int i, j;
	printf("\n");
	for(i = 0; i < 9; i++){
		printf("%c\t", Jugadores[jugador].tablero_atk[0][i]);
	}
	for(i = 1; i < 9; i++){
		printf("\n%d\t", Jugadores[jugador].tablero_atk[i][0]);
		for(j = 1; j < 9; j++){
			printf("%c\t", Jugadores[jugador].tablero_atk[i][j]);
		}
	}
	}
void MostrarOrientacion(char orien, int parte){
	char * orient;
	if(orien == 'h' || orien == 'H')
		orient = "Horizontal";
	else if(orien == 'v'|| orien == 'V')
		orient = "Vertical";
	
	printf("\nOrientacion: %s\n", orient);
	if (parte==0)
		printf("\nIngrese las coordenadas de la proa de su barco:\n");
	else if(parte == 1)
		printf("\nIngrese las coordenadas de la popa de su barco:\n");
}
bool VerificarPosicionHorizontal(int unidades, int col, int col_ant){
	if(col >= col_ant + unidades || col <= col_ant - unidades){
		printf("La popa esta muy lejos de la proa, intente nuevamente\n");
		system("pause");
		return true;
	}
	if(unidades >= BARCOMED){
		if(col == col_ant + (unidades - 2) || col == col_ant - (unidades - 2) ||col == col_ant - (unidades - 3) || col == col_ant + (unidades - 3)){
			printf("La popa esta muy cerca de la proa, intente nuevamente\n");
			system("pause");
			return true;
		}
	}
	return false;
	}
bool VerificarPosicionVertical(int unidades, int fil, int fil_ant){
	if(fil >= fil_ant + unidades || fil <= fil_ant - unidades){
		printf("La popa esta muy lejos de la proa, intente nuevamente\n");
		system("pause");
		return true;
	}
	if(unidades >= BARCOMED){
		if(fil == fil_ant + (unidades - 2) || fil == fil_ant - (unidades - 2) || fil == fil_ant - (unidades - 3) || fil == fil_ant + (unidades - 3)){
			printf("La popa esta muy cerca de la proa, intente nuevamente\n");
			system("pause");
			return true;
		}
	}
	return false;
	}
char ValidarOrientacion(int jugador){
	bool error;
	char orien;
		do{
			printf("\nDesea colocar su flota de forma horizontal (h), o vertical (v)?\n");
			orien = LeerDatosChar();
			error = (orien != 'h' && orien != 'H') && (orien != 'v' && orien != 'V');

			if(error){
				printf("\nOrientacion incorrecta\n");
				system("pause");
				system("cls");
				MostrarTableroNormal(jugador);
			}	
		}while(error);
		return orien;
	}
void ValidarCoordenadas(int jugador, int etapa){
	bool error;
	char* orientacion;
		do{
			coor = Posicion();

			//Verificar que no sea un espacio ya ocupado.
			if(etapa == 1)
				error = Jugadores[jugador].tablero_def[coor.fila][coor.columna] == 219;
			if (etapa == 2)
				error = Jugadores[jugador].tablero_atk[coor.fila][coor.columna] == 206;
			if(error){
				printf("\nEl espacio ya esta ocupado\n");
				system("pause");
				system("cls");
				MostrarTableroNormal(jugador);
				continue;
				}
		}while(error);
	}
void AsignarAnterior(int fila, int columna){
	coor.fila_ant = fila;
	coor.columna_ant = columna;
}
void Insertar(int fil, int col, int jugador, int unidades, int orien, int parte){
		int i;
		if(parte == 0){
				AsignarAnterior(fil, col);
				Jugadores[jugador].tablero_def[fil][col] = 219;
		}
		if(parte == 	1){
				AsignarAnterior(fil, col);
				//Para completar el espacio faltante del barco
				if(orien == 104)//Insercion vertical
					for(i = 0; i < unidades - 1; i++)
						Jugadores[jugador].tablero_def[fil][col - i] = 219;

				if(orien == 118)//Insercion horizontal
					for(i = 0; i < unidades - 1; i++)
						Jugadores[jugador].tablero_def[fil - i][col] = 219;
		}
		Jugadores[jugador].unidades += unidades;
	}
char LeerDatosChar(){
	char lectura;
		fflush(stdin);
		scanf("%c", &lectura);
	return lectura;
 }
char* LeerCadenas(){
	char lectura[CHAR_TAM];
	fflush(stdin);
	scanf("%s", &lectura);
	return lectura;
 }
struct Coordenadas Posicion(){
		bool error = false;
		do{		
			fflush(stdin);
			printf("\nIngrese la columna, seguido de coma y por ultimo la fila""<Columna>, <Fila>""\n");
			scanf("%c, %d", &coor.columna, &coor.fila);
			coor.columna -= 64;
			//Verificar que este dentro de los limites las coordenadas indicadas.
			error = (coor.columna < 1 && coor.columna > 8) || (coor.fila < 1 && coor.fila > 8);
			if(error){
				printf("\nEstas fueras del limite de posicionaniento\n");
				continue;
				}
		}while(error);
		return coor;
 }
