#ifndef _QUADTREE_H__
#define _QUADTREE_H__

#include "NodoQuadtree.h"

class Quadtree 
{
  protected:
    NodoQuadtree* raiz;

  public:
    Quadtree();
    Quadtree(int val);
    bool esVacio();
    NodoQuadtree* getRaiz();
    void setRaiz(NodoQuadtree* n);
    bool insertarNodo(int n);
    bool insertarNodoEnSubarbol(NodoQuadtree* nodo, int n);
    void preOrden();
    void preOrden(NodoQuadtree* nodo);
    int** crearImagen(int** matriz, NodoQuadtree* nodo, int desplazoX, int desplazoY, int tamanioCuadrante);
};

#include "Quadtree.hxx"

#endif