#ifndef __NODOQUADTREE_H__
#define __NODOQUADTREE_H__

class NodoQuadtree 
{
  private:
    int dato;
    NodoQuadtree* hijoIzqArriba;
    NodoQuadtree* hijoIzqAbajo;
    NodoQuadtree* hijoDerArriba;
    NodoQuadtree* hijoDerAbajo;
  
  public:
    NodoQuadtree();
    NodoQuadtree(int val);
    bool esHoja();
    bool completo();
    int getDato();
    void setDato(int val);
    NodoQuadtree* getHijoIzqArriba();
    void setHijoIzqArriba(NodoQuadtree* nodo);
    NodoQuadtree* getHijoIzqAbajo();
    void setHijoIzqAbajo(NodoQuadtree* nodo);
    NodoQuadtree* getHijoDerArriba();
    void setHijoDerArriba(NodoQuadtree* nodo);
    NodoQuadtree* getHijoDerAbajo();
    void setHijoDerAbajo(NodoQuadtree* nodo);
};

#include "NodoQuadtree.hxx"

#endif