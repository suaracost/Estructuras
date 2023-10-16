#include "NodoBinario.h"

#include <iostream>

template <class T>
NodoBinario<T>::NodoBinario()
{
    this->izq = NULL;
    this->der = NULL;
}

template <class T>
NodoBinario<T>::NodoBinario(T &val)
{
    this->dato = val;
    this->izq = NULL;
    this->der = NULL;
}

template <class T>
NodoBinario<T>::~NodoBinario()
{
    if (this->izq != NULL)
    {
        delete this->izq;
    }
    if (this->der != NULL)
    {
        delete this->der;
    }
}

template <class T>
T NodoBinario<T>::obtenerDato()
{
    return this->dato;
}

template <class T>
void NodoBinario<T>::fijarDato(T val)
{
    this->dato = val;
}

template <class T>
NodoBinario<T> *NodoBinario<T>::obtenerHijoIzq()
{
    return this->izq;
}

template <class T>
NodoBinario<T> *NodoBinario<T>::obtenerHijoDer()
{
    return this->der;
}

template <class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T> *izq)
{
    this->izq = izq;
}

template <class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T> *der)
{
    this->der = der;
}

template <class T>
bool NodoBinario<T>::esHoja()
{
    return (this->izq == NULL) && (this->der == NULL);
}

template <class T>
int NodoBinario<T>::altura()
{
    int valt;

    if (this->esHoja())
    {
        valt = 0;
    }
    else
    {
        int altIzq = -1, altDer = -1;

        if (this->izq != NULL)
            altIzq = (this->izq)->altura();
        if (this->der != NULL)
            altDer = (this->der)->altura();

        if (altIzq > altDer)
            valt = altIzq + 1;
        else
            valt = altDer + 1;
    }

    return valt;
}

template <class T>
void NodoBinario<T>::recorridoInorden()
{
    if(this->izq != NULL)
        (this->izq)->recorridoInorden();

    std::cout << this->dato <<" "<< std::endl;
    
    if(this->der != NULL)
        (this->der)->recorridoInorden();
}