#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tab_def1[9][9], tab_atk1[9][9], tab_def2[9][9], tab_atk2[9][9], col, fil, col_pas, fil_pas, uni1 = 14, uni2 = 14, jug;
char Jug[2][32],part[4],orie;

void InicializarVariables();
void Barco_De_Dos_unidades();
void Barco_De_Tres_Unidades();
void Barco_De_Cuatro_Unidades();
void Ataque();

int main(void){
    system("color FA");

    InicializarVariables();

    printf("\n\tBienvenido a Battleship!");
    printf("\n\n\tPor favor maximize la ventanilla para disfrutar al maximo el juego");
    printf("\n\n\tLas Reglas del juego seran las siguientes: \n\tCada jugador tendra:\n\t  2 barcos de 2 unidades\n\t  2 barcos de 3 unidades\n\t  1 barco de 4 unidades");
    printf("\n\n\tAl colocar los barcos puedes hacerlo de forma horizontal o vertical evitando que se toquen entre ellos,");
    printf("\n\tcolocando primero la proa (parte frontal del barco), luego la popa (parte trasera del barco).");
    printf("\n\n\tEl jugador que acierte mantendra el turno");
    printf("\n\n\tDebe introducir las coordenadas de la siguiente manera:\n\t Coordenada [letra,numero]\n\n");
    printf("\tNOTA\n\t En el tablero defensa, el numero 1 marcara las posiciones donde estan sus barcos, mientras que el\n\t numero -1 es el que marca las flotas que han sido tumbadas");
    printf("\n\t En el tablero de ataque, el numero 1 marcara las posiciones en las que usted fallo el tiro, y el -1\n\t marcara las posiciones en las que derrumbo un barco\n\n");
    system("pause");
    system("cls");


	//formacion de los barcos
    for(jug = 0; jug < 2; jug++){
        printf("Jugador %d, ingrese su nombre\n", jug);
        fflush(stdin);
        scanf("%s", &Jug[jug]);
        system("cls");
        Barco_De_Dos_unidades();
        Barco_De_Tres_Unidades();
        Barco_De_Cuatro_Unidades();
        printf("\nPasale al que sigue\n");
        system("pause");
        system("cls");
    }
    system("cls");
    printf("\n\n\t\tEsta listo para empezar?\n");
    system("pause");
    system("cls");
    do{
        for(jug = 0; jug < 1; jug++){
            system("cls");
            Ataque();
        }
    }while (uni1 != 0 && uni2 != 0);
    printf("cls");
    if(uni1 == 0)
        printf("\n\n\n\t\tFelicidades %s!", Jug[1]);
    else if(uni2 == 0)
        printf("\n\n\n\t\tFelicidades %s!", Jug[0]);
    printf("\n\t\tGracias por jugar\n");
}
void InicializarVariables(){
    int i, j;
    for( i = 1; i < 9; i++){
        for( j = 1; j < 9; j++){
                tab_def1[i][j] = 0;
                tab_atk1[i][j] = 0;
                tab_def2[i][j] = 0;
                tab_atk2[i][j] = 0;
        }
    }
    for( i = 0; i < 9; i++){
        tab_def1[0][i] = 64 + i;
        tab_atk1[0][i] = 64 + i;
        tab_def2[0][i] = 64 + i;
        tab_atk2[0][i] = 64 + i;

        if(tab_def1[0][i] == 64){
            tab_def1[0][i] = NULL;
            tab_atk1[0][i] = NULL;
            tab_def2[0][i] = NULL;
            tab_atk2[0][i] = NULL;
        }
    }
    for( i = 1; i < 9; i++){
        tab_def1[i][0] = i;
        tab_atk1[i][0] = i;
        tab_def2[i][0] = i;
        tab_atk2[i][0] = i;
    }
}

void Barco_De_Dos_unidades(){
    int cantBarco, proPa, i, j;
    for(cantBarco = 1; cantBarco < 3; cantBarco++){
        for(proPa = 0; proPa < 2; proPa++){
            //se imprime el tablero
            for( i = 0; i < 9; i++){
                if(jug == 0)
                    printf("%c\t",tab_def1[0][i]);
                else if(jug == 1)
                    printf("%c\t",tab_def2[0][i]);
            }

            for( i = 1; i < 9; i++){
                if (jug == 0)
                    printf("\n%d\t", tab_def1[i][0]);
                else if(jug == 1)
                    printf("\n%d\t", tab_def2[i][0]);

                for(j = 1; j < 9; j++){
                    if (jug == 0)
                        printf("%d\t", tab_def1[i][j]);
                    else if(jug == 1)
                        printf("%d\t", tab_def2[i][j]);
                }
            }

            //Aqui se pregunta la orientacion
            if(proPa == 0){
                printf("\n%s, organice su flota %d de 2 unidades:\n", Jug[jug],cantBarco);
                printf("Desea colocar su flota de forma horizontal (h), o vertical (v)?\n");
                fflush(stdin);
                scanf("%c", &orie);
            }
            if(orie != 'h' && orie != 'v'){
                printf("\nOrientacion incorrecta\n");
                proPa--;
                system("pause");
                system("cls");
            }
            else{
                system("cls");
                //se vuelve a imprimir el tablero
                for(i = 0; i < 9; i++){
                    if(jug == 0)
                        printf("%c\t",tab_def1[0][i]);
                    else if(jug == 1)
                        printf("%c\t",tab_def2[0][i]);
                }
                for(i = 1; i < 9; i++){
                    if (jug == 0)
                        printf("\n%d\t", tab_def1[i][0]);
                    else if(jug == 1)
                        printf("\n%d\t", tab_def2[i][0]);
                    for(j = 1; j < 9; j++){
                        if (jug == 0)
                            printf("%d\t", tab_def1[i][j]);
                        else if(jug == 1)
                            printf("%d\t", tab_def2[i][j]);
                    }
                }
                //aqui se asigna el valor segun la iteracion
                if(proPa == 0){
                    strcpy(part,"proa");
                }
                else{
                    strcpy(part,"popa");
                }
                printf("\nIngrese las coordenadas de la %s de su flota:\n", part);
                fflush(stdin);
                scanf("%c, %d", &col,&fil);

                //Para reemplazar el valor que esta guardado en la variable 'col' de ASCII a una posicion en el tablero
                    col -= 64;
                if(proPa == 0){
                    if(cantBarco == 1){
                        if (jug == 0){
                            if(tab_def1[fil][col] == 1){
                                proPa--;
                                printf("\nNo intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def1[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def1[fil][col] = 1;
                            }
                        }
                        else if (jug == 1){
                            if(tab_def2[fil][col] == 1){
                                proPa--;
                                printf("\nNo intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def2[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def2[fil][col] = 1;
                            }
                        }
                    }
                    if(cantBarco==2){
                        if(fil == fil_pas && col == col_pas){
                            printf("Intente una nueva posicion\n");
                            proPa--;
                            system("pause");
                        }
                            if(jug == 0){
                            fil_pas = fil;
                            col_pas = col;
                            tab_def1[fil][col] = 1;
                            }
                            else if(jug == 1){
                            fil_pas = fil;
                            col_pas = col;
                            tab_def2[fil][col] = 1;
                            }
                        }
                    }
                    //para todo proPa-- es resetear el for
                else if(proPa == 1){
                        if(orie == 'h' && fil == fil_pas){
                            if(col > col_pas + 1 || col < col_pas - 1){
                                proPa--;
                                printf("\nLa popa esta muy lejos de la proa, intente nuevamente\n");
                                system("pause");
                            }
                            else if(col == col_pas){
                                proPa--;
                                printf("\nPorfavor ingrese una coordenada nueva\n");
                                system("pause");
                            }
                            else if(col == col_pas + 1 || col == col_pas - 1){
                                if(jug == 0){
                                    if(tab_def1[fil][col] == 1){
                                        proPa--;
                                        printf("\nNo intente ocupar espacios que ya estan llenos\n");
                                        system("pause");
                                    }
                                    else if(tab_def1[fil][col] == 0){
                                        fil_pas = fil;
                                        col_pas = col;
                                        tab_def1[fil][col] = 1;
                                    }
                                }
                                else if(jug == 1){
                                    if(tab_def2[fil][col] == 1){
                                        proPa--;
                                        printf("\nNo intente ocupar espacios que ya estan llenos\n");
                                        system("pause");
                                    }
                                    else if(tab_def2[fil][col] == 0){
                                        fil_pas = fil;
                                        col_pas = col;
                                        tab_def2[fil][col] = 1;
                                    }
                                }
                        }
                    }
                        else if(orie == 'h' && fil != fil_pas){
                        proPa--;
                        printf("\nPor favor arme su barco correctamente\n");
                        system("pause");
                    }
                        else if(orie == 'v' && col == col_pas){
                        if(fil > fil_pas + 1 || fil < fil_pas - 1){
                            proPa--;
                            printf("\nLa popa esta muy lejos e la proa, intente nuevamente\n");
                            system("pause");
                        }
                        else if(fil == fil_pas){
                            proPa--;
                            printf("\nIngrese una coordenada nueva\n");
                            system("pasue");
                        }
                        else if (fil==fil_pas + 1|| fil==fil_pas - 1){
                            if(jug == 0){
                                if(tab_def1[fil][col] == 1){
                                    proPa--;
                                    printf("\nNo intente ocupar espacios que ya estan llenos\n");
                                    system("pause");
                                }
                                else if(tab_def1[fil][col] == 0){
                                    fil_pas = fil;
                                    col_pas = col;
                                    tab_def1[fil][col] = 1;
                                }
                            }
                            else if(jug == 1){
                                if(tab_def2[fil][col] == 1){
                                    proPa--;
                                    printf("\nNo intente ocuoar espacios que ya esten llenos\n");
                                    system("pause");
                                }
                                else if(tab_def2[fil][col] == 0){
                                    fil_pas = fil;
                                    col_pas = col;
                                    tab_def2[fil][col] = 1;
                                }
                            }
                        }
                    }
                        else if(orie == 'v' && col != col_pas){
                        proPa--;
                        printf("Por favor arme su barco correctamente\n");
                        system("pause");
                    }
                }
            }
        system("cls");
        }
    }
}
void Barco_De_Tres_Unidades(){
    //Barco de 3 unidades
    int cantBarco, proPa, i, j;
    for( cantBarco = 1; cantBarco <= 2; cantBarco++){
        for( proPa = 0; proPa < 2; proPa++){
            //imprimir tablaro
            for(i = 0; i < 9; i++){
                if(jug == 0)
                    printf("%c\t",tab_def1[0][i]);
                else if(jug == 1)
                    printf("%c\t",tab_def2[0][i]);
            }
            for(i = 1; i < 9; i++){
                if (jug == 0)
                    printf("\n%d\t", tab_def1[i][0]);
                else if(jug == 1)
                    printf("\n%d\t", tab_def2[i][0]);
                for(j = 1; j < 9; j++){
                    if (jug == 0)
                        printf("%d\t", tab_def1[i][j]);
                    else if(jug == 1)
                        printf("%d\t", tab_def2[i][j]);
                }
            }
            //Aqui se pregunta la orientacion
            if(proPa == 0){
                printf("\n%s, organice su flota %d de 3 unidades:\n", Jug[jug],cantBarco);
                printf("Desea colocar su flota de forma horizontal (h), o vertical (v)?\n");
                fflush(stdin);
                scanf("%c", &orie);
            }
            if(orie != 'h' && orie != 'v'){
                printf("\nOrientacion incorrecta");
                proPa--;
                system("pause");
            }
            else{
                system("cls");
                //nueva impresion del tablero
                for(i = 0; i < 9; i++){
                    if(jug == 0)
                        printf("%c\t",tab_def1[0][i]);
                    else if(jug == 1)
                        printf("%c\t",tab_def2[0][i]);
                }
                for(i = 1; i < 9; i++){

                    if (jug == 0)
                        printf("\n%d\t", tab_def1[i][0]);
                    else if(jug == 1)
                        printf("\n%d\t", tab_def2[i][0]);
                for(j = 1; j < 9; j++){
                    if (jug == 0)
                        printf("%d\t", tab_def1[i][j]);
                    else if(jug == 1)
                        printf("%d\t", tab_def2[i][j]);
                }
            }
            //aqui se asigna el valor segun la iteracion
            if(proPa == 0){
                strcpy(part,"proa");
            }
            else
                strcpy(part,"popa");

            printf("\nIngrese las coordenadas de la %s de su flota:\n", part);
            fflush(stdin);
            scanf("%c, %d", &col,&fil);
            //Para reemplazar el valor que esta guardado en la variable 'col' de ASCII a una posicion en el tablero
                col -= 64;
            if(proPa == 0){
                if(jug == 0){
                    if(tab_def1[fil][col] == 1){
                        proPa--;
                        printf("No intente ocupar espacios que ya estan llenos\n");
                        system("pause");
                    }
                    else if(tab_def1[fil][col] == 0){
                        tab_def1[fil][col] = 1;
                        fil_pas = fil;
                        col_pas = col;
                    }
                }
                else if(jug == 1){
                    if(tab_def2[fil][col] == 1){
                        proPa--;
                        printf("No intente ocupar espacios que ya estan llenos\n");
                        system("pause");
                    }
                    else if(tab_def2[fil][col] == 0){
                        tab_def2[fil][col] = 1;
                        fil_pas = fil;
                        col_pas = col;
                    }
                }
            }
            else if(proPa == 1){
                    if(orie == 'h' && fil == fil_pas){
                        if(col > col_pas + 2 || col < col_pas - 2){
                            printf("La popa esta muy lejos de la proa, intente nuevamente\n");
                            proPa--;
                            system("pause");
                        }
                        else if(col == col_pas + 1 || col == col_pas - 1){
                            printf("La popa esta muy cerca de la proa, intente nuevamente\n");
                            proPa--;
                            system("pause");
                        }
                        else if(col == col_pas){
                            printf("Porfavor ingrese una coordenada nueva\n");
                            proPa--;
                            system("pause");
                        }
                        else if(col == col_pas + 2 || col == col_pas - 2){
                            if(jug==0){
                                if(tab_def1[fil][col] == 1 || tab_def1[fil][(col + col_pas) / 2] == 1){
                                    proPa--;
                                    printf("No intente ocupar espacios que ya estan llenos\n");
                                    system("pause");
                                }
                                else if(tab_def1[fil][col] == 0){
                                    tab_def1[fil][(col + col_pas) / 2] = 1;
                                    tab_def1[fil][col] = 1;
                                    fil_pas = fil;
                                    col_pas = col;
                                }
                            }
                            else if(jug==1){
                                if(tab_def2[fil][col] == 1 || tab_def2[fil][(col + col_pas) / 2] == 1){
                                    proPa--;
                                    printf("No intente ocupar espacios que ya estan llenos\n");
                                    system("pause");
                                }
                                else if(tab_def2[fil][col] == 0){
                                    tab_def2[fil][(col + col_pas) / 2] = 1;
                                    tab_def2[fil][col] = 1;
                                    fil_pas = fil;
                                    col_pas = col;
                                }
                            }
                        }
                    }
                    else if(orie == 'h' && fil != fil_pas){
                        printf("Por favor arme su barco correctamente\n");
                        proPa--;
                        system("pause");
                    }
                    else if(orie == 'v' && col == col_pas){
                        if(fil > fil_pas + 2 || fil < fil_pas - 2){
                            printf("La popa esta muy lejos de la proa, intente nuevamente\n");
                            proPa--;
                            system("pause");
                        }
                        else if(fil == fil_pas + 1 || fil == fil_pas - 1){
                            printf("La popa esta muy cerca de la proa, intente nuevamente\n");
                            proPa--;
                            system("pause");
                        }
                        else if(fil == fil_pas){
                            printf("Ingrese una coordenada nueva\n");
                            proPa--;
                        }
                        else if (fil==fil_pas + 2 || fil==fil_pas - 2){
                            if(jug==0){
                                if(tab_def1[fil][col] == 1 || tab_def1[(fil + fil_pas) / 2][col] == 1){
                                    proPa--;
                                    printf("No intente ocupar espacios que ya estan llenos\n");
                                    system("pause");
                                }
                                else{
                                    tab_def1[(fil + fil_pas) / 2][col] = 1;
                                    tab_def1[fil][col] = 1;
                                    fil_pas = fil;
                                    col_pas = col;
                                }
                            }
                            else if(jug==1){
                                if(tab_def2[fil][col] == 1 || tab_def2[(fil + fil_pas) / 2][col] == 1){
                                    proPa--;
                                    printf("No intente ocupar espacios que ya estan llenos\n");
                                    system("pause");
                                }
                                else if(tab_def2[fil][col] == 0){
                                    tab_def2[(fil + fil_pas) / 2][col] = 1;
                                    tab_def2[fil][col] = 1;
                                    fil_pas = fil;
                                    col_pas = col;
                                }
                            }
                        }
                    }
                    else if(orie == 'v' && col != col_pas){
                        printf("Por favor arme su barco correctamente\n");
                        proPa--;
                        system("pause");
                    }
                }
            }
            system("cls");
        }
    }

}
void Barco_De_Cuatro_Unidades(){
    //Barco de 4 unidades
    int proPa,i,j;
    for(proPa = 0; proPa < 2; proPa++){
        //imprimir tablaro
        for(i = 0; i < 9; i++){
            if(jug == 0)
                printf("%c\t",tab_def1[0][i]);
            else if(jug == 1)
                printf("%c\t",tab_def2[0][i]);
        }
        for(i = 1; i < 9; i++){
            if (jug == 0)
                printf("\n%d\t", tab_def1[i][0]);
            else if(jug == 1)
                printf("\n%d\t", tab_def2[i][0]);
            for(j = 1; j < 9; j++){
                if (jug == 0)
                    printf("%d\t", tab_def1[i][j]);
                else if(jug == 1)
                    printf("%d\t", tab_def2[i][j]);
            }
        }

        if(proPa == 0){
            printf("\n%s, organice su flota de 4 unidades:\n", Jug[jug]);
            printf("Desea colocar su flota de forma horizontal (h), o vertical (v)?\n");
            fflush(stdin);
            scanf("%c", &orie);
        }
        if(orie != 'h' && orie != 'v'){
            printf("\nOrientacion incorrecta\n");
            proPa--;
            system("pause");
            system("cls");
        }else{
            system("cls");
            for(i = 0; i < 9; i++){
                if(jug == 0)
                    printf("%c\t",tab_def1[0][i]);
                else if(jug == 1)
                    printf("%c\t",tab_def2[0][i]);
            }
            for(i = 1; i < 9; i++){
                if (jug == 0)
                    printf("\n%d\t", tab_def1[i][0]);
                else if(jug == 1)
                    printf("\n%d\t", tab_def2[i][0]);
                for(j = 1; j < 9; j++){
                    if (jug == 0)
                        printf("%d\t", tab_def1[i][j]);
                    else if(jug == 1)
                        printf("%d\t", tab_def2[i][j]);
                }
            }
            if(proPa == 0)
                strcpy(part,"proa");
            else
                strcpy(part,"popa");
								
						printf("\nIngrese las coordenadas de la %s de su flota:\n", part);
						fflush(stdin);
						scanf("%c, %d", &col, &fil);
						col-= 64;
            
						if(proPa == 0){
                if(jug == 0){
                    fil_pas = fil;
                    col_pas = col;
                    tab_def1[fil][col] = 1;
                }
                else if(jug == 1){
                    fil_pas = fil;
                    col_pas = col;
                    tab_def2[fil][col] = 1;
                }
            }
            else if(proPa == 1){
                if(orie == 'h' && fil == fil_pas){
                    if(col >= col_pas + 4 || col <= col_pas - 4){
                        printf("La popa esta muy lejos de la proa, intente nuevamente\n");
                        proPa--;
                        system("pause");
                    }
                    else if(col == col_pas + 2 || col == col_pas + 1 || col == col_pas - 1 || col == col_pas - 2){
                        printf("La popa esta muy cerca de la proa, intente nuevamente\n");
                        proPa--;
                        system("pause");
                    }
                    else if(col == col_pas){
                        printf("Porfavor ingrese una coordenada nueva\n");
                        proPa--;
                        system("pause");
                    }
                    else if(col == col_pas + 3){
                        if(jug == 0){
                            if(tab_def1[fil][col] == 1 || tab_def1[fil][col - 1] == 1 || tab_def1[fil][col - 2] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def1[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def1[fil][col - 1] = 1;
                                tab_def1[fil][col - 2] = 1;
                                tab_def1[fil][col] = 1;
                            }
                        }
                        else if(jug == 1){
                            if(tab_def2[fil][col] == 1 || tab_def2[fil][col - 1] == 1 || tab_def2[fil][col - 2] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def2[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def2[fil][col - 1] = 1;
                                tab_def2[fil][col - 2] = 1;
                                tab_def2[fil][col] = 1;
                            }
                        }
                    }
                    else if(col == col_pas - 3){
                        if(jug == 0){
                            if(tab_def1[fil][col] == 1 || tab_def1[fil][col + 1] == 1 || tab_def1[fil][col + 2] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def1[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def1[fil][col + 1] = 1;
                                tab_def1[fil][col + 2] = 1;
                                tab_def1[fil][col] = 1;
                            }
                        }
                        else if(jug == 1){
                            if(tab_def2[fil][col] == 1 || tab_def2[fil][col + 1] == 1 || tab_def2[fil][col + 2] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def2[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def2[fil][col + 1] = 1;
                                tab_def2[fil][col + 2] = 1;
                                tab_def2[fil][col] = 1;
                            }
                        }
                    }
                }
                else if(orie == 'h' && fil != fil_pas){
                    printf("Por favor arme su barco correctamente\n");
                    proPa--;
                    system("pause");
                }
                else if(orie == 'v' && col == col_pas){
                    if(fil >= fil_pas + 4 || fil <= fil_pas - 4){
                        printf("La popa esta muy lejos de la proa, intente nuevamente\n");
                        proPa--;
                        system("pause");
                    }
                    else if(fil == fil_pas){
                        printf("Ingrese una coordenada nueva\n");
                        proPa--;
                    }
                    else if(fil == fil_pas + 2 || fil == fil_pas + 1 || fil == fil_pas - 1 || fil == fil_pas - 2){
                        printf("La popa esta muy cerca de la proa, intente nuevamente\n");
                        proPa--;
                        system("pause");
                    }
                    else if (fil == fil_pas + 3){
                        if(jug == 0){
                            if(tab_def1[fil][col] == 1 || tab_def1[fil - 1][col] == 1 || tab_def1[fil - 2][col] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def1[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def1[fil - 1][col] = 1;
                                tab_def1[fil - 2][col] = 1;
                                tab_def1[fil][col] = 1;
                            }
                        }
                        else if (jug == 1){
                            if(tab_def2[fil][col] == 1 || tab_def2[fil - 1][col] == 1 || tab_def2[fil - 2][col] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def2[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def2[fil - 1][col] = 1;
                                tab_def2[fil - 2][col] = 1;
                                tab_def2[fil][col] = 1;
                            }
                        }
                    }
                    else if(fil == fil_pas - 3){
                       if(jug == 0){
                            if(tab_def1[fil][col] == 1 || tab_def1[fil + 1][col] == 1 || tab_def1[fil + 2][col] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def1[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def1[fil + 1][col] = 1;
                                tab_def1[fil + 2][col] = 1;
                                tab_def1[fil][col] = 1;
                            }
                        }
                        else if (jug == 1){
                            if(tab_def2[fil][col] == 1 || tab_def2[fil + 1][col] == 1 || tab_def2[fil + 2][col] == 1){
                                proPa--;
                                printf("No intente ocupar espacios que ya estan llenos\n");
                                system("pause");
                            }
                            else if(tab_def2[fil][col] == 0){
                                fil_pas = fil;
                                col_pas = col;
                                tab_def2[fil + 1][col] = 1;
                                tab_def2[fil + 2][col] = 1;
                                tab_def2[fil][col] = 1;
                            }
                        }
                    }
                }
                else if(orie == 'v' && col != col_pas){
                    printf("Por favor arme su barco correctamente\n");
                    proPa--;
                    system("pause");
                }
            }
        }
    system("cls");
    }
}

void Ataque(){
    int racha = 0, i, j;
    do{
        printf("\n\n\t\tEs su turno %s\n", Jug[jug]);
        system("pause");
        system("cls");
        //imprimir tablero
        for(i = 0; i < 9; i++){
            if(jug == 0)
                printf("%c\t",tab_def1[0][i]);
            else if(jug == 1)
                printf("%c\t",tab_def2[0][i]);
        }
        for(i = 1; i < 9; i++){
            if (jug == 0)
                printf("\n%d\t", tab_def1[i][0]);
            else if(jug == 1)
                printf("\n%d\t", tab_def2[i][0]);
            for(j = 1; j < 9; j++){
                if (jug == 0)
                    printf("%d\t", tab_def1[i][j]);
                else if(jug == 1)
                    printf("%d\t", tab_def2[i][j]);
            }
        }
        printf("\n\n");
        //imprimir tablaro
        for(i = 0; i < 9; i++){
            if(jug == 1)
                printf("%c\t",tab_atk1[0][i]);
            else if(jug == 0)
                printf("%c\t",tab_atk2[0][i]);
        }
        for(i = 1; i < 9; i++){
            if (jug == 0)
                printf("\n%d\t", tab_atk1[i][0]);
            else if(jug == 1)
                printf("\n%d\t", tab_atk2[i][0]);
            for(j = 1; j < 9; j++){
                if (jug == 0)
                    printf("%d\t", tab_atk1[i][j]);
                else if(jug == 1)
                    printf("%d\t", tab_atk2[i][j]);
            }
        }
        printf("\nSeleccione una coordenada que quiera destruir\n");
        fflush(stdin);
        scanf("%c, %d", &col, &fil);
        col -= 64;
        if(jug == 0){
            if(tab_def2[fil][col] == 1){
                uni2--;
                racha++;
                tab_atk1[fil][col] = -1;
                tab_def2[fil][col] = -1;
                printf("\n\n\tDERRUMBADO!");
                printf("\n\n\tSu racha es de %d\n", racha);
                system("pause");
            }
            else if(tab_def2[fil][col] == 0){
                tab_atk1[fil][col] = 1;
                printf("\n\n\tFALLO!\n");
                if(racha > 1)
                    printf("\n\tUsted perdio su racha de %d\n", racha);
                racha = 0;
                system("pause");
            }
        }
        else if(jug == 1){
            if(tab_def1[fil][col] == 1){
                uni1--;
                racha++;
                tab_atk2[fil][col] = -1;
                tab_def1[fil][col] = -1;
                printf("\n\n\tDERRUMBADO!");
                printf("\n\n\tSu racha es de %d", racha);
                system("pause");
            }
            else if(tab_def1[fil][col] == 0){
                tab_atk2[fil][col] = 1;
                printf("\n\n\tFALLO!\n");
                if(racha > 1)
                    printf("\n\tusted perdio su racha de %d\n", racha);
                racha = 0;
                system("pause");
            }
        }
    }while(racha > 0 && (uni1 > 0 && uni2 > 0));
}
