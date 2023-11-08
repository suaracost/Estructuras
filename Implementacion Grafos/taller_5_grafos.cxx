#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

// TODO # 0: Incluir el archivo cabecera del grafo
#include "Grafo.h"

// -------------------------------------------------------------------------
struct Punto
{
  float X, Y;
  float distanciaA( const Punto& b ) const
    {
      float x = X - b.X;
      float y = Y - b.Y;
      return( std::sqrt( ( x * x ) + ( y * y ) ) );
    }
};

// -------------------------------------------------------------------------

// TODO # 1: Definir el tipo para un grafo con Puntos como vertices y costos reales
typedef Grafo< Punto, float > TGrafo;
typedef std::vector< float > TDist;

// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr
      << "Uso: " << argv[ 0 ] << " archivo_entrada"
      << std::endl;
    return( 1 );

  }

  // TODO # 2: Declarar el grafo
  TGrafo g;

  // Cargar el archivo en un bufer
  std::ifstream in_mesh_stream( argv[ 1 ], std::ifstream::binary );
  if( !in_mesh_stream )
  {
    std::cerr << "Error leyendo \"" << argv[ 1 ] << "\"" << std::endl;
    return( 1 );

  }
  in_mesh_stream.seekg( 0, in_mesh_stream.end );
  unsigned long in_mesh_file_length = in_mesh_stream.tellg( );
  in_mesh_stream.seekg( 0, in_mesh_stream.beg );
  char* in_mesh_file_buffer = new char[ in_mesh_file_length ];
  in_mesh_stream.read( in_mesh_file_buffer, in_mesh_file_length );
  in_mesh_stream.close( );
  std::istringstream in_mesh( in_mesh_file_buffer );

  // Leer los vertices desde el bufer
  long nPoints;
  in_mesh >> nPoints;
  for( long pId = 0; pId < nPoints; pId++ )
  {
    Punto pnt;
    in_mesh >> pnt.X >> pnt.Y;

    // TODO # 3: Insertar el Punto en el grafo
    g.insertarVertice( pnt );

  }

  // Leer las aristas desde el bufer
  long nEdges;
  in_mesh >> nEdges;
  for( long eId = 0; eId < nEdges; eId++ )
  {
    long start, end;
    in_mesh >> start >> end;

    // TODO # 4: Calcular el costo de la arista, insertarla en el grafo como no dirigida
    float cost = g.distanciaA(g.vertices[start], g.vertices[end]);
    g.conectarVertices(g.vertices[start], g.vertices[end], cost);
    g.conectarVertices(g.vertices[end], g.vertices[start], cost);

  }
  delete [] in_mesh_file_buffer;
  //gñ.ñimprimirMatriz();

  std::cout << "Porteria: " 
            << g.vertices[0].X << "," << g.vertices[0].Y << std::endl;

  // TODO # 5: Calcular distancias lineales (distancia Euclidiana)
  unsigned long s_id = 0;
  float dist_s_e = 0.0;
  TDist distLineales;

  std::cout<<std::endl<<"Distancias Euclidiana hasta la porteria"<<std::endl;
  
  for ( unsigned int j = 1; j < nPoints; ++j )
  {
    dist_s_e = g.distanciaA(g.vertices[s_id], g.vertices[j]);
    distLineales.push_back( dist_s_e );
    std::cout<<"("<<g.vertices[j].X<<", "<<g.vertices[j].Y<<") \t"<<dist_s_e<<std::endl;
  }

  // TODO # 6: Encontrar las rutas de costo minimo usando los algoritmos requeridos

  std::vector< std::pair<Punto, Punto> > primCasa = g.prim(g.vertices[0]);

  std::vector< std::pair<Punto, Punto> > dijkCasa = g.dijkstra(g.vertices[0]);

  
  // TODO # 7: Imprimir el informe de Prim
  // TODO # 8: Imprimir el informe de Dijkstra (mismo fomato que informe de Prim)
  float cosTotal, cosTotalD;
  for ( unsigned int j = 1; j < nPoints; ++j )
  {
    std::stack< std::pair<Punto, Punto> > ruta;
    std::vector< std::pair<Punto, Punto> > rutaDis;
    std::stack< std::pair<Punto, Punto> > ruta2;
    std::vector< std::pair<Punto, Punto> > ruta2Dis;


    std::cout << "\nCasa " << j << ": (" 
              << g.vertices[j].X << "," << g.vertices[j].Y << ") " << std::endl;
    std::cout << "Distancia lineal a porteria: " << distLineales[j-1] << std::endl;

    std::cout << "Camino segun algoritmo de Prim: ";
    bool terminado = false;
    Punto destino = g.vertices[j];

    while (terminado == false)
    {
      int aux = 0;

      for(int v=0; v<primCasa.size(); v++)
      {
        if(primCasa[v].second.X == destino.X && primCasa[v].second.Y == destino.Y)
        {
          ruta.push(primCasa[v]);
          rutaDis.insert(rutaDis.begin(), primCasa[v]);
          destino = primCasa[v].first;
          aux = v;
        }
      }
      
      if(primCasa[aux].first.X == g.vertices[0].X && primCasa[aux].first.Y == g.vertices[0].Y)
      {
        terminado = true;
      }
    };

    while(!ruta.empty())
    {
      std::cout << "(" << ruta.top().first.X << ", " << ruta.top().first.Y << ") --> ";
      ruta.pop();
    } 
    std::cout << "(" << g.vertices[j].X << ", " << g.vertices[j].Y << ")";

    std::cout << std::endl;
    std::cout << "Distancia total recorrida con algoritmo de Prim: ";
    cosTotal = 0.0;

    for(int i = 0; i < rutaDis.size( ); ++i )
      cosTotal += g.disPrim( rutaDis[i] );
    
    std::cout << cosTotal << std::endl;

    std::cout << "Comparacion de Prim con Dijkstra: ";
    Punto destino2 = g.vertices[j];
    bool terminado2 = false;

    while (terminado2 == false)
    {
      int aux = 0;

      for(int v=0; v<dijkCasa.size(); v++)
      {
        if(dijkCasa[v].second.X == destino2.X && dijkCasa[v].second.Y == destino2.Y)
        {
          ruta2.push(dijkCasa[v]);
          ruta2Dis.insert(ruta2Dis.begin(), dijkCasa[v]);
          destino2 = dijkCasa[v].first;
          aux = v;
        }
      }
      
      if(dijkCasa[aux].first.X == g.vertices[0].X && dijkCasa[aux].first.Y == g.vertices[0].Y)
      {
        terminado2 = true;
      }
    };

    while(!ruta2.empty())
    {
      std::cout << "(" << ruta2.top().first.X << ", " << ruta2.top().first.Y << ") --> ";
      ruta2.pop();
    }
    std::cout << "(" << g.vertices[j].X << ", " << g.vertices[j].Y << ")";
    

    std::cout << std::endl;
    std::cout << "Distancia total recorrida con algoritmo de Dijkstra: ";
    cosTotalD = 0.0;

     for( unsigned int i = 0; i < ruta2Dis.size( ); ++i )
      cosTotalD += g.disDijk( ruta2Dis[i] );
    
    std::cout << cosTotalD << std::endl;

  }

  return( 0 );
}

// eof - taller_5_grafos.cxx