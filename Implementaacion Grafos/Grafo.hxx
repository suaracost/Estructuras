#include "Grafo.h"

#include <iostream>
#include <stack>
#include <limits>
#include <algorithm>

template<class T, class U>
bool Grafo<T, U>::buscarVertice(T vertice) 
{
    if (vertices.size() == 0) 
    {
        return false;
    }
    for (int i = 0; i < this->vertices.size(); i++) 
    {
        if (this->vertices[i].X == vertice.X && this->vertices[i].Y == vertice.Y) 
        {
            return true;
        }
    }
    return false;
}

template<class T, class U>
int Grafo<T, U>::indiceVertice(T vertice) 
{
    int indice = -1;
    for (int i = 0; i < this->vertices.size(); i++) 
    {
        if (this->vertices[i].X == vertice.X && this->vertices[i].Y == vertice.Y) 
        {
            indice = i;
        }
    }
    return indice;
}

template<class T, class U>
bool Grafo<T, U>::insertarVertice(T vertice) 
{

    if (buscarVertice(vertice)) 
    {
        return false;
    }
    this->vertices.push_back(vertice);

    int n = this->vertices.size();
    this->matriz_adyacencia.resize(n);
    for (int i = 0; i < this->matriz_adyacencia.size(); i++)
        this->matriz_adyacencia[i].resize(n);
    return true;
}

template<class T, class U>
float Grafo<T, U>::distanciaA(T vertice1, T vertice2) 
{
    float distancia = 0;

    float x1 = vertice1.X;
    float y1 = vertice1.Y;

    float x2 = vertice2.X;
    float y2 = vertice2.Y;
    
    distancia = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

    return distancia;
}

template<class T, class U>
bool Grafo<T, U>::conectarVertices(T vertice1, T vertice2, U peso) 
{
    if (!buscarVertice(vertice1)) 
    {
        return false;
    }
    if (!buscarVertice(vertice2)) 
    {
        return false;
    }

    int n1 = indiceVertice(vertice1);
    int n2 = indiceVertice(vertice2);

    this->matriz_adyacencia[n1][n2] = peso;
    return true;
}

template<class T, class U>
bool Grafo<T, U>::buscarArista(T vertice1, T vertice2) 
{
    
    if (!buscarVertice(vertice1)) 
    {
        return false;
    }
    if (!buscarVertice(vertice2)) 
    {
        return false;
    }

    int n1 = indiceVertice(vertice1);
    int n2 = indiceVertice(vertice2);
    return this->matriz_adyacencia[n1][n2] != 0;
}

template<class T, class U>
U Grafo<T, U>::valorConexion(T vertice1, T vertice2) 
{
    if (!buscarVertice(vertice1)) 
    {
        return 0;
    }
    if (!buscarVertice(vertice2)) 
    {
        return 0;
    }

   
    int n1 = indiceVertice(vertice1);
    int n2 = indiceVertice(vertice2);
    return this->matriz_adyacencia[n1][n2];
}

template<class T, class U>
void Grafo<T, U>::imprimirMatriz() 
{
    std::cout << "\nMatriz de adyacencia:\n\n";

    for (int i = 0; i < this->vertices.size()+1; i++) 
    {
        if (i==0)
            std::cout << "X";
        else
            std::cout << "\t\t" << vertices[i-1].X << "," << vertices[i-1].Y;
    }
    std::cout << "\n";
    for (int i = 0; i < this->vertices.size()+1; i++) 
    {
        std::cout << "---\t\t";
    }
    std::cout << "\n\n";

    for (int i = 0; i < this->matriz_adyacencia.size(); i++) 
    {
        std::cout << vertices[i].X << "," << vertices[i].Y;
        
        for (int j = 0; j < this->matriz_adyacencia[i].size(); j++) 
        {
            std::cout << "\t\t" << this->matriz_adyacencia[i][j];
        }
        std::cout << "\n\n";
    }
}

template<class T, class U>
std::vector< std::pair<T, T> > Grafo<T, U>::prim(T vertice) 
{
    std::vector<T> visitados;
    std::vector<T> grafo = this->vertices;
    std::vector<T> noVisitados = grafo;
    std::vector< std::pair<T, T> > aristas;
    visitados.push_back(vertice);
    noVisitados.erase(noVisitados.begin() + indiceVertice(vertice));
    T nuevo;
    T actual;
    while (visitados.size() != grafo.size()) 
    {
        U menor = 456361;
        for (int i = 0; i < visitados.size(); i++) 
        {
            for (int j = 0; j < noVisitados.size(); j++) 
            {
                if (buscarArista(visitados[i], noVisitados[j])) 
                {
                    if (valorConexion(visitados[i], noVisitados[j]) < menor) 
                    {
                        menor = valorConexion(visitados[i], noVisitados[j]);
                        actual = visitados[i];
                        nuevo = noVisitados[j];
                    }
                }
            }
        }

        visitados.push_back(nuevo);
        
        auto it = noVisitados.begin();

        for(int i=0; i<noVisitados.size(); i++)
        {
            if(noVisitados[i].X == nuevo.X && noVisitados[i].Y == nuevo.Y)
            {
                it = noVisitados.begin() + i;
            }
        }
        
        noVisitados.erase(it);
        aristas.push_back(std::make_pair(actual, nuevo));
    }
    return aristas;
}

template<class T, class U>
U Grafo<T, U>::disPrim(std::pair<T, T> tupla)
{
    T vertice1;
    vertice1.X = tupla.first.X;
    vertice1.Y = tupla.first.Y;

    T vertice2;
    vertice2.X = tupla.second.X;
    vertice2.Y = tupla.second.Y;
   
    int n1 = indiceVertice(vertice1);
    int n2 = indiceVertice(vertice2);

    return this->matriz_adyacencia[n1][n2];
}

template<class T, class U>
std::vector< std::pair<T, T> > Grafo<T, U>::dijkstra(T vertice) 
{
    T verticeActual = vertice;
    std::vector<U> distancias;
    std::vector<T> visitados;
    std::vector<T> grafo = this->vertices;
    std::vector<T> noVisitados = this->vertices;
    std::vector<T> prev(grafo.size());

    for (int i = 0; i < grafo.size(); i++) 
    {
        distancias.push_back(456361);
    }
    distancias[indiceVertice(verticeActual)] = 0;

    while (!noVisitados.empty()) 
    {
        U menor = 456361;
        for (int i = 0; i < noVisitados.size(); i++) 
        {
            if (distancias[indiceVertice(noVisitados[i])] < menor) 
            {
                menor = distancias[indiceVertice(noVisitados[i])];
                verticeActual = noVisitados[i];
            }
        }
        visitados.push_back(verticeActual);

        auto it = noVisitados.begin();

        for(int i=0; i<noVisitados.size(); i++)
        {
            if(noVisitados[i].X == verticeActual.X && noVisitados[i].Y == verticeActual.Y)
            {
                it = noVisitados.begin() + i;
            }
        }
        
        noVisitados.erase(it);

        for (int i = 0; i < grafo.size(); i++)
        {
            if (buscarArista(verticeActual, grafo[i])) 
            {
                U distanciaVertice = distancias[indiceVertice(verticeActual)];
                U distanciaVecino = distancias[indiceVertice(grafo[i])];
                U nuevaDistancia = distanciaVertice + valorConexion(verticeActual, grafo[i]);

                if (distanciaVecino > nuevaDistancia) 
                {
                    distancias[indiceVertice(grafo[i])] = nuevaDistancia;
                    prev[indiceVertice(grafo[i])] = verticeActual;
                }
            }
        }
    }

    std::vector< std::pair<T, T> > conexiones;

    for(int i=0; i<prev.size(); i++)
    {
        if (i == indiceVertice(vertice))
        {
            continue;
        }
        else
        {
            conexiones.push_back(std::make_pair(prev[i], grafo[i]));
        }
    }

    return conexiones;
}

template<class T, class U>
U Grafo<T, U>::disDijk(std::pair<T, T> tupla)
{
    T vertice1;
    vertice1.X = tupla.first.X;
    vertice1.Y = tupla.first.Y;

    T vertice2;
    vertice2.X = tupla.second.X;
    vertice2.Y = tupla.second.Y;
   
    int n1 = indiceVertice(vertice1);
    int n2 = indiceVertice(vertice2);

    return this->matriz_adyacencia[n1][n2];
}