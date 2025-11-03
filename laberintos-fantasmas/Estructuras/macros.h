#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

#define MIN(X,Y) ((X)<(Y)?(X):(Y))

///MACROS PARA RETORNOS
#define LLENA 1
#define NO_LLENA 2
#define VACIA 3
#define NO_VACIA 4
#define SIN_MEMORIA 5
#define INSERCION_SUCIA 6

#define SIN_DUPLICADO 7
#define CON_DUPLICADO 8

#define IGUALES 9
#define DISTINTOS 10
#define NO_EXISTE -2
#define EXISTE 1

#define ERROR -1
#define TODO_OK 0


#define COMPLETO 1
#define NO_COMPLETO 0

#define BALANCEADO 1
#define NO_BALANCEADO 0

#define AVL 1
#define NO_AVL 0



///MACROS PARA TAMANIOS
#define MAXLINE 1024
#define TAM_VEC 32
#define TAM_FIL_COL 64

///TYPEDEF DE STRUCTS

typedef struct
{
    int numero;
    unsigned apariciones;
}tNumeros;

typedef struct
{
    int cantidad;
    int suma;
}tPromedio;

typedef struct
{
    int fecha;
    int nro_cuenta;
    char movimiento;
    float importe;
}tClientes;

///PUNTEROS A FUNCIONES
typedef int(*cmp)(const void*,const void*);
typedef void(*reduccion) (const void*,void *);
typedef void(*accion) (void*);
typedef int(*accionDuplicado) (void*,const void*);
typedef int(*condicion) (void*);

#endif // MACROS_H_INCLUDED
