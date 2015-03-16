#include <stdio.h>
#include <stdlib.h>
#include "nodos.h"

//linea de prueba
void imprimirEstado(int estado[]);
void PushFrontera(Cola *cola, Arbol nodo);
void Push(Cola *cola, Arbol nodo);
Arbol Pop(Cola *cola);
int colaVacia(Cola c);

int verificarEstado(int estado[], int otroEstado[]);
int *moverPuzzle(int estado[], movimiento accion);
int buscarCero(int estado[]);
int *intercambiar(int n1, int n2, int estado[]);
Arbol crearNodo(Arbol padre,movimiento accion, int costo, int estado[]);
int busquedaA_estrella(int estado[]);
int buscarExplorados(Cola Explorados,int estado[]);
int buscarFrontera(Cola frontera, int estado[]);
int fueraDeLugar(int estado[]);
int tieneSolucion(int estado[]);



int cFrontera = 0;
int cExplorados = 0;
int nodosCreados = 0;

int solucion[casillas] = {1,2,3,4,5,6,7,8,0};

int main(void){
    int estado[casillas]={1,5,3,8,0,6,4,7,2};
    printf("\n8 puzzle - Busqueda por Amplitud\n\n");
    busquedaA_estrella(estado);
    return 0;
}


void imprimirEstado(int estado[]){
    int i;
    for(i = 0; i < casillas;i++){
        if(i % 3 == 0)
            printf("\n\n");
        printf("%d\t",estado[i]);
    }
    printf("\n\n");
}

int verificarEstado(int estado[], int otroEstado[]){
    //función que verifica si dos estados son iguales
    int i;
    // un ciclo for para comparar cada elemento del arreglo, en caso de que uno falle retorna False
    for(i = 0; i < casillas; i++){
        if(estado[i] != otroEstado[i])
            return False;
    }
    return True;
}

//funciones Pop y Push para agregar los nodos explorados y los de frontera
//se usa la estructura de datos: Cola ordenada
void PushFrontera(Cola *cola, Arbol nodo) {
    pNodo nuevo, anterior;

    nuevo = (Cola)malloc(sizeof(tipoNodo));
    nuevo->nArbol = nodo;

    /* Si la cola esta vacia, el elemento agregado era el primero */
    if(colaVacia(*cola) || (*cola)->nArbol->h > nodo->h) {
        /* Añadimos la lista a continuación del nuevo nodo */
        nuevo->siguiente = *cola;
        /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
        *cola = nuevo;
    } else {
        /* Buscar el nodo con la heuristica menor */
        anterior = *cola;
        /* Avanzamos hasta el último elemento o hasta que el siguiente tenga
           un valor mayor que la heristica del nodo que queremos ingresar a la cola */
        while(anterior->siguiente && anterior->siguiente->nArbol->h <= nodo->h)
            anterior = anterior->siguiente;
        /* Insertamos el nuevo nodo después del nodo anterior */
        nuevo->siguiente = anterior->siguiente;
        anterior->siguiente = nuevo;
    }
}



void Push(Cola *cola, Arbol nodo){
    //se crea un nuevo nodo;
    Cola nuevo;
    //se reserva el espacio en memoria para el nodo
    nuevo = (Cola)malloc(sizeof(tipoNodo));
    //se asigna los datos del individuo al nodo
    nuevo->nArbol = nodo;
    //ahora siguiente apunta inicio de la cola
    nuevo->siguiente = *cola;
    // la cola apunta al nuevo nodo y este queda en la cima
    *cola = nuevo;
}


Arbol Pop(Cola *cola){
    // se crean dos nodos
    Cola nodo,aux = NULL;
    // el auxiliar recibe la cola al igual que nodo
    aux=*cola;
    nodo = *cola;
    //si la cola esta vacia se retorna NULL
    if(!nodo) return 0;
    //si existe algo en la cola, el penultimo nodo pasa a ser el ultimo y se retorna el nodo aux
    *cola = nodo->siguiente;
    return aux->nArbol;
}

int colaVacia(Cola c) {
    return (c == NULL);
}

//////////////////////////////////////////////////////////////////////////

int *moverPuzzle(int estado[], movimiento accion){
    int ubicacion = buscarCero(estado);
    int *nuevoEstado = NULL;
   if(ubicacion == 0){
        if(accion == arriba)
            return estado; // si no hay opcion de movimiento, entonces se regresa el estado igual
        if(accion == abajo){
            nuevoEstado = intercambiar(0, 3, estado);
            return nuevoEstado;
        }
        if(accion == izquierda)
            return estado; // si no hay opcion de movimiento, entonces se regresa el estado igual
        if(accion == derecha){
            nuevoEstado = intercambiar(0, 1, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 1){
        if(accion == arriba)
            return estado; // si no hay opcion de movimiento, entonces se regresa el estado igual
        if(accion == abajo){
            nuevoEstado = intercambiar(1, 4, estado);
            return nuevoEstado;
        }
        if(accion == izquierda){
            nuevoEstado = intercambiar(1, 0, estado);
            return nuevoEstado;
        }
        if(accion == derecha){
            nuevoEstado = intercambiar(1, 2, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 2){
        if(accion == arriba)
            return estado;
        if(accion == abajo){
            nuevoEstado = intercambiar(2, 5, estado);
            return nuevoEstado;
        }
        if(accion == izquierda){
            nuevoEstado = intercambiar(1, 2, estado);
            return nuevoEstado;
        }
        if(accion == derecha)
            return estado;
   }


   if(ubicacion == 3){
        if(accion == arriba){
            nuevoEstado = intercambiar(0, 3, estado);
            return nuevoEstado;
        }
        if(accion == abajo){
            nuevoEstado = intercambiar(3, 6, estado);
            return nuevoEstado;
        }
        if(accion == izquierda)
            return estado;
        if(accion == derecha){
            nuevoEstado = intercambiar(3, 4, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 4){
        if(accion == arriba){
            nuevoEstado = intercambiar(1, 4, estado);
            return nuevoEstado;
        }
        if(accion == abajo){
            nuevoEstado = intercambiar(4, 7, estado);
            return nuevoEstado;
        }
        if(accion == izquierda){
            nuevoEstado = intercambiar(4, 3, estado);
            return nuevoEstado;
        }
        if(accion == derecha){
            nuevoEstado = intercambiar(4, 5, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 5){
        if(accion == arriba){
            nuevoEstado = intercambiar(2, 5, estado);
            return nuevoEstado;
        }
        if(accion == abajo){
            nuevoEstado = intercambiar(5, 8, estado);
            return nuevoEstado;
        }
        if(accion == izquierda){
            nuevoEstado = intercambiar(4, 5, estado);
            return nuevoEstado;
        }
        if(accion == derecha)
            return estado;
   }


   if(ubicacion == 6){
        if(accion == arriba){
            nuevoEstado = intercambiar(3, 6, estado);
            return nuevoEstado;
        }
        if(accion == abajo)
            return estado;
        if(accion == izquierda)
            return estado;
        if(accion == derecha){
            nuevoEstado = intercambiar(6, 7, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 7){
        if(accion == arriba){
            nuevoEstado = intercambiar(4, 7, estado);
            return nuevoEstado;
        }
        if(accion == abajo)
            return estado;
        if(accion == izquierda){
            nuevoEstado = intercambiar(6, 7, estado);
            return nuevoEstado;
        }
        if(accion == derecha){
            nuevoEstado = intercambiar(7, 8, estado);
            return nuevoEstado;
        }
   }
   if(ubicacion == 8){
        if(accion == arriba){
            nuevoEstado = intercambiar(5, 8, estado);
            return nuevoEstado;
        }
        if(accion == abajo)
            return estado;
        if(accion == izquierda){
            nuevoEstado = intercambiar(7, 8, estado);
            return nuevoEstado;
        }
        if(accion == derecha)
            return estado;
   }
}


int buscarCero(int estado[]){
    int i;
    for(i = 0; i < casillas; i++){
        if(estado[i] == 0)
            return i;
    }
}

int *intercambiar(int n1, int n2, int estado[]){
    int aux = estado[n1];
    estado[n1] = estado[n2];
    estado[n2] = aux;
    return estado;
}

Arbol crearNodo(Arbol padre,movimiento accion, int costo, int estado[]){
    Arbol nodo = NULL;
    int *temp;
    int temp2[casillas];
    int i;
    nodo = (Arbol)malloc(sizeof(tipoNodoArbol));
    if(padre == NULL){
        for(i = 0; i < casillas; i++){
            temp2[i] = estado[i];
            nodo->estado[i] = temp2[i];
        }
        nodo->padre = NULL;
        nodo->accion = accion;
        nodo->costo = 0; // es el padre
        return nodo;
    }
    for(i = 0; i < casillas; i++)
        temp2[i] = estado[i];

    temp = moverPuzzle(temp2, accion);
    for(i = 0; i < casillas; i++)
        nodo->estado[i] = temp[i];
    nodo->padre = padre;
    nodo->accion = accion;
    nodo->costo = (int)padre->costo + 1; //1 es el costo del nuevo estado
    return nodo;
}

int busquedaA_estrella(int estado[]){
    int i,j,e[casillas];
    Arbol nodo = NULL;
    Arbol hijo = NULL;
    //Cola acciones = NULL;
    movimiento m;
    // estructura auxiliares para el control la busqueda
    Cola frontera = NULL;
    Cola Explorados = NULL;
    //Pila pilaExplorados = NULL;
    // se crea el primer nodo (Padre)
    nodo = crearNodo(NULL,izquierda,0,estado);

    if(verificarEstado(nodo->estado,solucion) == True){
        printf("El estado inicial era la solucion");
        imprimirEstado(nodo->estado);
        printf("\nEl costo fue de %d\n", nodo->costo);
        return True;
    }
    printf("Estado Inicial");
    imprimirEstado(nodo->estado);
    PushFrontera(&frontera, nodo);

    while(true){
        if(frontera == NULL)
            return False;

        //sacamos un nodo de la frontera
        nodo = Pop(&frontera);

        //agregamos el nodo al  conjunto de explorados
        Push(&Explorados, nodo);

        for(i = 0; i < 4; i++){
            if(i==0) m = arriba;
            if(i==1) m = abajo;
            if(i==2) m = izquierda;
            if(i==3) m = derecha;

            hijo = crearNodo(nodo,m,nodo->costo,nodo->estado);
            if(buscarExplorados(Explorados,hijo->estado) == False && buscarFrontera(frontera,hijo->estado) == False){
                if(verificarEstado(hijo->estado,solucion) == True){
                    printf("\n-----------------------------------------------------------\n");
                    printf("\n Se ha encontrado una solucion\n");
                    printf("\n-----------------------------------------------------------\n");
                    printf("\n frontera + explorados =  %d nodos\n", cFrontera + cExplorados);
                    printf("\n Se llego al nivel %d\n", hijo->costo);
                    printf("\n Acciones para llegar del estado inicial al estado meta\n");
                    printf("\n-----------------------------------------------------------\n");
                    /*while(hijo->padre != NULL){

                        PushExplorados(&acciones, hijo);
                        hijo = hijo->padre;
                    }*/
                    /*while(acciones){
                        nodo = PopExplorados(&acciones);
                        if(nodo->accion == izquierda){
                            printf("\nizquierda\n");
                            imprimirEstado(nodo->estado);
                        }
                        if(nodo->accion == derecha){
                            printf("\nderecha\n");
                            imprimirEstado(nodo->estado);
                        }
                        if(nodo->accion == arriba){
                            printf("\narriba\n");
                            imprimirEstado(nodo->estado);
                        }
                        if(nodo->accion == abajo){
                            printf("\nabajo\n");
                            imprimirEstado(nodo->estado);
                        }
                    }*/

                    return True;
                }
                else{
                    PushFrontera(&frontera,hijo);
                    //imprimirEstado(hijo->estado);
                }
            }
        }
    }
    return False;
}

int buscarExplorados(Cola Explorados, int estado[]){
    Cola nodo = Explorados;
    if(nodo == NULL)
        return False;
    while(nodo){
        if(verificarEstado(nodo->nArbol->estado,estado) == True){
            return True;
        }
        nodo = nodo->siguiente;
    }
    return False;
}


int buscarFrontera(Cola frontera, int estado[]){
    Cola nodo = frontera;
    if(nodo == NULL)
        return False;
    while(nodo){
        if(verificarEstado(nodo->nArbol->estado,estado) == True){
            return True;
        }
        nodo = nodo->siguiente;
    }
    return False;
}

void limpiarC(Cola *c){
    Cola temp = *c;
    if(temp->siguiente)
        limpiarC(&temp->siguiente);
    free(temp);
}

//funcion para verificar si el estado inicial dado tiene solucion, recibe como parametro un arreglo entero (estado)
int tieneSolucion(int estado[]){
    int i,j;
    int inversiones = 0;
    printf("Verificando el estado siguiente\n");
    imprimirEstado(estado);
    /*for que compara si el elemento de la izquierda es mayor al de la derecha,
     en dado de que sea así se aumenta el contador de inversiones*/
    for(i = 0; i < casillas; i++){
        for(j = i + 1; j < casillas; j++){
            if(estado[j] > estado[i])
                inversiones++;
        }
    }
    /*debido a que el numero de casillas del tablero es impar
    la solucion tiene un numero de inversiones par
    */
    if (inversiones%2 == 0){
        return True;
    }
    return False;
}

//funcion para calcular la heuristica acerca del numero de cuadros fuera de su posicion en el estado meta
int fueraDeLugar(int estado[]){
    int sumFueraLugar = 0;
    int i, j;
    /*si el elemento i del estado dado es diferente al elemento i de la solucion
    se aumenta la suma de elementos fuera de su lugar */
    for(i = 0; i < casillas; i++){
        if(estado[i] != solucion[i])
            sumFueraLugar++;
    }
    return sumFueraLugar;
}
