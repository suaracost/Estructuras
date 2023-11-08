#ifndef __GRAFO__H__
#define __GRAFO__H__

#include <vector>

template <class T, class U>
class Grafo 
{
  public:
    std::vector<T> vertices;
    std::vector< std::vector < U > > matriz_adyacencia;

  public:
    bool buscarVertice (T vertice);
    int indiceVertice(T vertice);
    bool insertarVertice(T vertice);
    float distanciaA(T vertice1, T vertice2);
    bool conectarVertices(T vertice1, T vertice2, U peso);
    bool buscarArista(T vertice1, T vertice2);
    U valorConexion(T vertice1, T vertice2);
    void imprimirMatriz();
    std::vector< std::pair<T, T> > prim(T vertice);
    U disPrim(std::pair<T, T> tupla);
    std::vector< std::pair<T, T> > dijkstra(T vertice);
    U disDijk(std::pair<T, T> tupla);
};

#include "Grafo.hxx"

#endif