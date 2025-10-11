#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct sNodo
{
    void* info;
    unsigned tamanio;
    struct sNodo* sig;
} tNodo;

typedef struct
{
    tNodo *pri;
    tNodo *ult;
}tCola;

///PRIMITIVAS
void colaCrear(tCola *cola);
int colaEncolar(tCola *cola, const void *info, unsigned bytes);
int colaVerPrimero(const tCola *cola, void *info, unsigned bytes);
int colaQuitar(tCola *cola, void *info, unsigned bytes);
int colaVacia(const tCola *cola);
void colaVaciar(tCola *cola);

#endif // COLA_H_INCLUDED
