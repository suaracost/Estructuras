#include "Quadtree.h"

Quadtree::Quadtree()
{
    this->raiz = NULL;
}

Quadtree::Quadtree(int n)
{
    NodoQuadtree* nodo = new NodoQuadtree();
    nodo->setDato(n);
    this->raiz = nodo;
}

bool Quadtree::esVacio()
{
    if (this->raiz == NULL)
        return true;
    else
        return false;
}

NodoQuadtree* Quadtree::getRaiz()
{
    return this->raiz;
}

void Quadtree::setRaiz(NodoQuadtree* n)
{
    this->raiz = n;
}

bool Quadtree::insertarNodo(int n) {
    
    if(this->esVacio()) {
        this->raiz->setDato(n);
        return true;
    } else {
        return this->insertarNodoEnSubarbol(this->raiz, n);
    }
}

bool Quadtree::insertarNodoEnSubarbol(NodoQuadtree* nodo, int n)
{
    bool insertado = false;

    if(nodo->getHijoIzqArriba() == NULL) 
    {
        NodoQuadtree* nuevo = new NodoQuadtree(n);
        nodo->setHijoIzqArriba(nuevo);
        insertado = true;
    } 

    else if(nodo->getHijoIzqArriba()->getDato() == 2 && !nodo->getHijoIzqArriba()->completo())
    {
        insertado = insertarNodoEnSubarbol(nodo->getHijoIzqArriba(), n);
    }

    if(!insertado){
        if(nodo->getHijoDerArriba() == NULL){
            NodoQuadtree* nuevo = new NodoQuadtree(n);
            nodo->setHijoDerArriba(nuevo);
            insertado = true;
        } 
        else if(nodo->getHijoDerArriba()->getDato() == 2 && !nodo->getHijoDerArriba()->completo()){
            insertado = insertarNodoEnSubarbol(nodo->getHijoDerArriba(), n);
        }
    }

    if(!insertado){
        if(nodo->getHijoDerAbajo() == NULL){
            NodoQuadtree* nuevo = new NodoQuadtree(n);
            nodo->setHijoDerAbajo(nuevo);
            insertado = true;
        } 
        else if(nodo->getHijoDerAbajo()->getDato() == 2 && !nodo->getHijoDerAbajo()->completo()){
            insertado = insertarNodoEnSubarbol(nodo->getHijoDerAbajo(), n);
        }
    }

    if(insertado == false)
    {
        if(nodo->getHijoIzqAbajo() == NULL)
        {
            NodoQuadtree* nuevo = new NodoQuadtree(n);
            nodo->setHijoIzqAbajo(nuevo);
            insertado = true;
        } 
        else if(nodo->getHijoIzqAbajo()->getDato() == 2 && !nodo->getHijoIzqAbajo()->completo())
        {
            insertado = insertarNodoEnSubarbol(nodo->getHijoIzqAbajo(), n);
        }
    }

    return insertado;
}

void Quadtree::preOrden() 
{
    if (!this->esVacio()) 
    {
        this->preOrden(this->raiz);
    }
};

void Quadtree::preOrden(NodoQuadtree* nodo) 
{
    std::cout << " " << nodo->getDato();
    
    if (nodo->getHijoIzqArriba() != NULL) {
        this->preOrden(nodo->getHijoIzqArriba());
    }

    if (nodo->getHijoIzqAbajo() != NULL) {
        this->preOrden(nodo->getHijoIzqAbajo());
    }

    if (nodo->getHijoDerArriba() != NULL) {
        this->preOrden(nodo->getHijoDerArriba());
    }

    if (nodo->getHijoDerAbajo() != NULL) {
        this->preOrden(nodo->getHijoDerAbajo());
    }
}

int** Quadtree::crearImagen(int** matriz, NodoQuadtree* nodo, int inicioX, int inicioY, int tamanioCuadrante)
{
    if (nodo->getDato() == 2)
    {
        tamanioCuadrante = tamanioCuadrante/2;
        matriz = crearImagen(matriz, nodo->getHijoIzqArriba(), inicioX, inicioY, tamanioCuadrante);
        matriz = crearImagen(matriz, nodo->getHijoIzqAbajo(), inicioX+tamanioCuadrante, inicioY, tamanioCuadrante);
        matriz = crearImagen(matriz, nodo->getHijoDerArriba(), inicioX, inicioY+tamanioCuadrante, tamanioCuadrante);
        matriz = crearImagen(matriz, nodo->getHijoDerAbajo(), inicioX+tamanioCuadrante, inicioY+tamanioCuadrante, tamanioCuadrante);
    }
    else if (nodo->getDato() == 1)
    {
        for(int i = inicioX; i < inicioX+tamanioCuadrante; i++)
        {
            for(int j = inicioY; j < inicioY+tamanioCuadrante; j++)
            {
                matriz[i][j] = 1;
            }
        }
    }
    else if (nodo->getDato() == 0)
    {
        for(int i = inicioX; i < inicioX+tamanioCuadrante; i++)
        {
            for(int j = inicioY; j < inicioY+tamanioCuadrante; j++)
            {
                matriz[i][j] = 0;
            }
        }
    }

    return matriz;
}