#ifndef NODOS_H_INCLUDED
#define NODOS_H_INCLUDED
#define casillas    9
#define MAX     4
#define False   0
#define True    1

enum movimiento{arriba = 3,abajo,izquierda,derecha,inicio};

//Nodo para la estructura tipo  arbol
typedef struct _nodo {
   int estado[casillas];
   int costo;
   movimiento accion;
   struct _nodo    *padre;
} tipoNodoArbol;
typedef tipoNodoArbol *Arbol;


//Nodo para la estructura tipo Colam cola y lista
typedef struct nodo{
    Arbol nArbol;
    struct nodo *siguiente;
}tipoNodo;

typedef tipoNodo *Cola;

typedef tipoNodo *Pila;
typedef tipoNodo *pNodo;


#endif // NODOS_H_INCLUDED
