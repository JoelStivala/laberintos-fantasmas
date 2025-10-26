#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include "../macros.h"

typedef struct aNodo{
    void *info;
    unsigned tam;
    struct aNodo *izq;
    struct aNodo *der;
}tNodoArbol;

typedef tNodoArbol *tArbol;

void crearArbolBin(tArbol *raiz);
int insertarEnArbolBinRecursivo(tArbol *raiz, const void *info, unsigned bytes, cmp comparacion, accionDuplicado funcion);
int insertarEnArbolBin(tArbol *raiz, const void *info, unsigned bytes, cmp comparacion, accionDuplicado funcion);
int recorrerArbolBinPreorden(tArbol *raiz, accion funcion);
int recorrerArbolBinPostorden(tArbol *raiz, accion funcion);
int recorrerArbolBinInorden(tArbol *raiz, accion funcion);
void* busquedaBin(tArbol *raiz, void *clave, unsigned bytes,cmp comparacion);
int arbolVacio(const tArbol *raiz);
int arbolLleno(const tArbol *raiz, unsigned bytes);
void vaciarArbol(tArbol *raiz);

///ejercicios para la proxima clase

int contarHojas(tArbol *raiz);
int contarNoHojas(tArbol *raiz);
int contarNodos(tArbol *raiz);
tNodoArbol* buscarClaveMayor(tArbol *raiz);
tNodoArbol* buscarClaveMenor(tArbol *raiz);
int recorrerSubarbolDer(tArbol *raiz, condicion funcion);
int _accionSubarbolDer(tArbol *raiz,condicion funcion);
int contarNodosPorClave(tArbol *raiz, const void *clave, int fnc(void*,const void*));
float promedioConClavePar(tArbol *raiz, tPromedio *p ,void promedio(void*,tPromedio*));
///pendiente de revision
int buscarPorNoClave(tArbol *raiz, void *noClave, unsigned bytes, int algo(void *,const void*));


int alturaArbol(tArbol *raiz);
int nivelArbol(tArbol *raiz);
///actividad del dia
int recorrerHastaNivel(tArbol *raiz, int nivel, void accion(void*));
int recorrerNivel(tArbol *raiz, int nivel, void accion(void*));
int recorrerDesdeNivel(tArbol *raiz, int nivel, void accion(void*));

//arbol completo, balanceado, avl y eliminar un nodo (se puede eliminar raiz)

int esArbolBinCompleto(tArbol *raiz);
int esArbolBinBalanceado(tArbol *raiz);
int esAVL(tArbol *raiz);
///eliminar aparciciones (pendientes)
int eliminarNodo(tArbol *raiz, void *clave, unsigned bytes,int cmp(const void*,const void*));
int eliminarRaiz(tArbol* elim, void *clave);


#endif // ARBOL_H_INCLUDED
