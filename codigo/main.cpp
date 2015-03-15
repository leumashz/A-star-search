#include <stdio.h>
#include <stdlib.h>
#include "nodos.h"

void imprimirEstado(int estado[]);
void PushFrontera(Cola *primero, Cola *ultimo, Arbol nodo);
Arbol PopFrontera(Cola *primero, Cola *ultimo);
void PushExplorados(Pila *pilaExplorados, Arbol expandido);
Arbol PopExplorados(Pila *pilaExplorados);

void copiar(int estadoOrigen[], int *estadoDestino);
int verificarEstado(int estado[], int otroEstado[]);
int *moverPuzzle(int estado[], movimiento accion);
int buscarCero(int estado[]);
int *intercambiar(int n1, int n2, int estado[]);
Arbol crearNodo(Arbol padre,movimiento accion, int costo, int estado[]);
int busquedaGrafo(int estado[]);
int buscarExplorados(Pila pilaExplorados,int estado[]);
int buscarFrontera(Cola fronteraInicio, int estado[]);

int cFrontera = 0;
int cExplorados = 0;

int main(void){
    int estado[casillas]={1,5,3,8,0,6,4,7,2};
    printf("\n8 puzzle - Busqueda por Amplitud\n\n");
    busquedaGrafo(estado);
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

void PushFrontera(Cola *primeroFrontera, Cola *ultimoFrontera, Arbol nodoArbol){
    //se crea un nuevo nodo
    Cola nuevo;
    cFrontera++;
    //se reserva espacio de memoria para ese nodo y se le asigna informacion
    nuevo = (Cola)malloc(sizeof(tipoNodo));
    nuevo->nArbol = nodoArbol;
    // el nuevo nodo se anexa al final
    nuevo->siguiente = NULL;
    //si el ultimo es nulo entonces apuntara a nuevo
    if(*ultimoFrontera) (*ultimoFrontera)->siguiente = nuevo;
    *ultimoFrontera = nuevo;
    //si no hay ningun nodo en la cola, el nuevo nodo sera el primero y el ultimo a la vez
    if(!*primeroFrontera) *primeroFrontera = nuevo;
}

Arbol PopFrontera(Cola *primeroFrontera, Cola *ultimoFrontera){
    // se crea un nodo aux y otro para manejar la cola
    Cola nodo,aux=NULL;
    cFrontera--;
    // nodo recibe la cola
    nodo = *primeroFrontera;
    //si la cola esta vacia se retorna null
    if(!nodo) return NULL;
    // si tiene algo se desliga de la cola y se retorna
    *primeroFrontera = nodo->siguiente;
    aux=nodo;
    if(!*primeroFrontera) *ultimoFrontera = NULL;
    return aux->nArbol;
}

void PushExplorados(Pila *pilaExplorados, Arbol expandido){
    //se crea un nuevo nodo;
    Pila nuevo;
    cExplorados++;
    //se reserva el espacio en memoria para el nodo
    nuevo = (Pila)malloc(sizeof(tipoNodo));
    //se asigna los datos del individuo al nodo
    nuevo->nArbol = expandido;
    //ahora siguiente apunta inicio de la pila
    nuevo->siguiente = *pilaExplorados;
    // la pila apunta al nuevo nodo y este queda en la cima
    *pilaExplorados = nuevo;
}

Arbol PopExplorados(Pila *pilaExplorados){
    // se crean dos nodos
    Pila nodo,aux = NULL;
    cFrontera--;
    // el auxiliar recibe la pila al igual que nodo
    aux=*pilaExplorados;
    nodo = *pilaExplorados;
    //si la pila esta vacia se retorna NULL
    if(!nodo) return 0;
    //si existe algo en la pila, el penultimo nodo pasa a ser el ultimo y se retorna el nodo aux
    *pilaExplorados = nodo->siguiente;
    return aux->nArbol;
}

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

int busquedaGrafo(int estado[]){
    int solucion[casillas] = {1,2,3,4,5,6,7,8,0};
    int i,j,e[casillas];
    Arbol nodo = NULL;
    Arbol hijo = NULL;
    Pila acciones = NULL;
    movimiento m;
    // estructura auxiliares para el control la busqueda
    Cola fronteraInicio = NULL;
    Cola fronteraFinal = NULL;
    Pila pilaExplorados = NULL;
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
    PushFrontera(&fronteraInicio, &fronteraFinal, nodo);

    while(true){
        if(fronteraInicio == NULL)
            return False;

        //sacamos un nodo de la frontera
        nodo = PopFrontera(&fronteraInicio, &fronteraFinal);

        //agregamos el nodo al  conjunto de explorados
        PushExplorados(&pilaExplorados, nodo);

        for(i = 0; i < 4; i++){
            if(i==0) m = arriba;
            if(i==1) m = abajo;
            if(i==2) m = izquierda;
            if(i==3) m = derecha;

            hijo = crearNodo(nodo,m,nodo->costo,nodo->estado);
            if(buscarExplorados(pilaExplorados,hijo->estado) == False && buscarFrontera(fronteraInicio,hijo->estado) == False){
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
                    PushFrontera(&fronteraInicio,&fronteraFinal,hijo);
                    //imprimirEstado(hijo->estado);
                }
            }
        }
    }
    return False;
}

int buscarExplorados(Pila pilaExplorados, int estado[]){
    Pila nodo = pilaExplorados;
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


int buscarFrontera(Cola fronteraInicio, int estado[]){
    Cola nodo = fronteraInicio;
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

void limpiarPila(Pila *p){
    Pila temp = *p;
    if(temp->siguiente)
        limpiarPila(&temp->siguiente);
    free(temp);
}
