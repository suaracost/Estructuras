#include "ArbolBinarioOrd.h"

#include <iostream>
#include <queue>

template <class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd() 
{
    this->raiz = NULL;
}

template <class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd() 
{
    if(this->raiz != NULL)
    {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd(T val) 
{
  NodoBinario<T>* nodo = new NodoBinario<T>();
  nodo->fijarDato(val);
  this->raiz = nodo;
}

template <class T>
bool ArbolBinarioOrd<T>::esVacio() 
{
    return this->raiz == NULL;
}

template <class T>
T ArbolBinarioOrd<T>::datoRaiz() 
{
    return (this->raiz)->obtenerDato();
}

template <class T>
int ArbolBinarioOrd<T>::altura() 
{
    if (this->esVacio())
        return -1;
    else
        return this->altura(this->raiz);
}

template <class T>
int ArbolBinarioOrd<T>::altura(NodoBinario<T>* nodo) 
{
    int valt;

    if(nodo->esHoja())
        valt = 0;
    else
    {
        int altIzq = -1, altDer = -1;

        if (nodo->obtenerHijoIzq() != NULL)
            altIzq = this->altura(nodo->obtenerHijoIzq());
        if (nodo->obtenerHijoDer() != NULL)
            altDer = this->altura(nodo->obtenerHijoDer());
        
        if (altIzq > altDer)
            valt = altIzq + 1;
        else
            valt = altDer + 1;
    }

    return valt;
}

template <class T>
int ArbolBinarioOrd<T>::tamano() 
{
    if(this->esVacio())
        return 0;
    else
        return tamano(this->raiz);
}

template <class T>
unsigned int ArbolBinarioOrd<T>::tamano(NodoBinario<T>* nodo) 
{
    unsigned int totalTamano = 1;  // Comenzamos con 1 para contar el nodo actual
  
    if (nodo->obtenerHijoIzq() != NULL)
        totalTamano += tamano(nodo->obtenerHijoIzq());

    if (nodo->obtenerHijoDer() != NULL)
        totalTamano += tamano(nodo->obtenerHijoDer());

    return totalTamano;
}

template <class T>
bool ArbolBinarioOrd<T>::insertar(T val) 
{
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool insertado = false, duplicado = false;

    while (nodo != NULL)
    {
        padre = nodo;
        
        if (val < nodo->obtenerDato())
            nodo = nodo->obtenerHijoIzq();
        else if (val > nodo->obtenerDato())
            nodo = nodo->obtenerHijoDer();
        else
        {
            duplicado = true;
            break;
        }            
    }

    if (!duplicado)
    {
        NodoBinario<T>* nuevo = new NodoBinario<T>(val);

        if (nuevo != NULL)
        {
            if (val < padre->obtenerDato())
                padre->fijarHijoIzq(nuevo);
            else
                padre->fijarHijoDer(nuevo);
        }
        insertado = true;
    }

    return insertado;
}

template <class T>
bool ArbolBinarioOrd<T>::eliminar(T val) 
{
    NodoBinario<T>* nodo = this->raiz;
    NodoBinario<T>* padre = this->raiz;
    bool encontrado = false, eliminado = false;

    while (nodo != NULL )
    {
        if (val < nodo->obtenerDato())
        {
            padre = nodo;
            nodo = nodo->obtenerHijoIzq();
        }
        else if (val > nodo->obtenerDato())
        {
            padre = nodo;
            nodo = nodo->obtenerHijoDer();
        }
        else
        {
            encontrado = true;
            break;
        }            
    }
    
    if (encontrado == true)
    {
        if (nodo->esHoja())
        {
            if(padre->obtenerHijoIzq() != NULL && nodo->obtenerDato() == padre->obtenerHijoIzq()->obtenerDato())
                padre->fijarHijoIzq(NULL); 
            else if(nodo->obtenerDato() == padre->obtenerHijoDer()->obtenerDato())
                padre->fijarHijoDer(NULL);

            delete nodo;
            nodo = NULL;
            eliminado = true;
        }
        else if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() == NULL)
        {
            if (padre->obtenerHijoIzq()->obtenerDato() == nodo->obtenerDato())
                padre->fijarHijoIzq(nodo->obtenerHijoIzq());
            else if (padre->obtenerHijoDer()->obtenerDato() == nodo->obtenerDato())
                padre->fijarHijoDer(nodo->obtenerHijoIzq());
            
            nodo->fijarHijoIzq(NULL);
            delete nodo;
            nodo = NULL;
            eliminado = true;
        }
        else if (nodo->obtenerHijoDer() != NULL && nodo->obtenerHijoIzq() == NULL)
        {
            if (padre->obtenerHijoIzq()->obtenerDato() == nodo->obtenerDato())
                padre->fijarHijoIzq(nodo->obtenerHijoDer());
            else if (padre->obtenerHijoDer()->obtenerDato() == nodo->obtenerDato())
                padre->fijarHijoDer(nodo->obtenerHijoDer());
            
            nodo->fijarHijoDer(NULL);
            delete nodo;
            nodo = NULL;
            eliminado = true;
        }
        else if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL)
        {
            NodoBinario<T> *maximo = nodo->obtenerHijoIzq();
            NodoBinario<T> *padreMaximo = nodo;
            bool aux = false;

            while (aux == false)
            {
                if (maximo->obtenerHijoDer() != NULL)
                {
                    padreMaximo = maximo;
                    maximo = maximo->obtenerHijoDer();
                }
                else
                    aux = true;
            }

            nodo->fijarDato(maximo->obtenerDato());

            if(maximo->obtenerHijoIzq() == NULL)
            {
                padreMaximo->fijarHijoIzq(NULL);
                delete maximo;
                maximo = NULL;
                eliminado = true;
            }
            else if (maximo->obtenerHijoIzq() != NULL)
            {
                padreMaximo->fijarHijoIzq(maximo->obtenerHijoIzq());
                maximo->fijarHijoIzq(NULL);
                delete maximo;
                maximo = NULL;
                eliminado = true;
            }
        }
    }
    return eliminado;
}

template <class T>
bool ArbolBinarioOrd<T>::buscar(T val) 
{
    NodoBinario<T>* nodo = this->raiz;
    bool encontrado = false;

    while (nodo != NULL && !encontrado)
    {
        if (val < nodo->obtenerDato())
            nodo = nodo->obtenerHijoIzq();
        else if (val > nodo->obtenerDato())
            nodo = nodo->obtenerHijoDer();
        else
        {
            std::cout<<nodo->obtenerDato()<<" fue encontrado\n";
            encontrado = true;
        }
    }

    return encontrado;
}

template <class T>
void ArbolBinarioOrd<T>::preOrden() 
{
    if (!this->esVacio())
        this->preOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T>* nodo) 
{
    if (nodo != NULL)
    {
        std::cout << nodo->obtenerDato() << " ";
        this->preOrden(nodo->obtenerHijoIzq());
        this->preOrden(nodo->obtenerHijoDer());
    }
}   

template <class T>
void ArbolBinarioOrd<T>::inOrden() 
{
    if (!this->esVacio())
        this->inOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T>* nodo) 
{
    if (nodo != NULL)
    {
        this->inOrden(nodo->obtenerHijoIzq());
        std::cout << nodo->obtenerDato() << " ";
        this->inOrden(nodo->obtenerHijoDer());
    }
}

template <class T>
void ArbolBinarioOrd<T>::postOrden() 
{
    if (!this->esVacio())
        this->postOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd<T>::postOrden(NodoBinario<T>* nodo) 
{
    if (nodo != NULL)
    {
        this->postOrden(nodo->obtenerHijoIzq());
        this->postOrden(nodo->obtenerHijoDer());
        std::cout << nodo->obtenerDato() << " ";
    }
}

template <class T>
void ArbolBinarioOrd<T>::nivelOrden() 
{
    if(!this->esVacio())
    {
        std::queue <NodoBinario<T>*> cola;
        cola.push(this->raiz);

        while (!cola.empty())
        {
            NodoBinario<T>* nodo = cola.front();
            cola.pop();

            std::cout << nodo->obtenerDato() << " ";

            if (nodo->obtenerHijoIzq() != NULL)
                cola.push(nodo->obtenerHijoIzq());
            if (nodo->obtenerHijoDer() != NULL)
                cola.push(nodo->obtenerHijoDer());
        }
        
    }
}