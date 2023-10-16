#include "NodoQuadtree.h"

#include<iostream>

NodoQuadtree::NodoQuadtree()
{
    this->hijoIzqArriba = NULL;
    this->hijoIzqAbajo = NULL;
    this->hijoDerArriba = NULL;
    this->hijoDerAbajo = NULL;
}

NodoQuadtree::NodoQuadtree(int val)
{
    dato = val;
    this->hijoIzqArriba = NULL;
    this->hijoIzqAbajo = NULL;
    this->hijoDerArriba = NULL;
    this->hijoDerAbajo = NULL;
}

bool NodoQuadtree::esHoja()
{
    if (this->hijoIzqArriba == NULL && this->hijoIzqAbajo == NULL && this->hijoDerArriba == NULL && this->hijoDerAbajo == NULL)
        return true;
    else
        return false;
}

bool NodoQuadtree::completo()
{
    bool completo = true;

  if(this->hijoIzqArriba == NULL){
    completo = false;
  }
  else if(this->hijoIzqArriba->getDato() == 2){
    completo = completo && this->hijoIzqArriba->completo();
  }

  if(this->hijoIzqAbajo == NULL){
    completo = false;
  }
  else if(this->hijoIzqAbajo->getDato() == 2){
    completo = completo && this->hijoIzqAbajo->completo();
  }

  if(this->hijoDerArriba == NULL){
    completo = false;
  }
  else if(this->hijoDerArriba->getDato() == 2){
    completo = completo && this->hijoDerArriba->completo();
  }

  if(this->hijoDerArriba == NULL){
    completo = false;
  }
  else if(this->hijoDerArriba->getDato() == 2){
    completo = completo && this->hijoDerArriba->completo();
  }

  return completo;
}

int NodoQuadtree::getDato()
{
    return dato;
}

void NodoQuadtree::setDato(int val)
{
    this->dato = val;
}

NodoQuadtree* NodoQuadtree::getHijoIzqArriba()
{
    return this->hijoIzqArriba;
}

void NodoQuadtree::setHijoIzqArriba(NodoQuadtree* nodo)
{
    this->hijoIzqArriba = nodo;
}

NodoQuadtree* NodoQuadtree::getHijoIzqAbajo()
{
    return this->hijoIzqAbajo;
}

void NodoQuadtree::setHijoIzqAbajo(NodoQuadtree* nodo)
{
    this->hijoIzqAbajo = nodo;
}

NodoQuadtree* NodoQuadtree::getHijoDerArriba()
{
    return this->hijoDerArriba;
}

void NodoQuadtree::setHijoDerArriba(NodoQuadtree* nodo)
{
    this->hijoDerArriba = nodo;
}

NodoQuadtree* NodoQuadtree::getHijoDerAbajo()
{
    return this->hijoDerAbajo;
}

void NodoQuadtree::setHijoDerAbajo(NodoQuadtree* nodo)
{
    this->hijoDerAbajo = nodo;
}
