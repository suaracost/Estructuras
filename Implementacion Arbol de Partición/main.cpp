#include "Quadtree.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
   if(argc != 3)
   {
    std::cout<<"Ingrese el nombre del archivo a leer y el nombre del archivo a escribir"<<std::endl;
   }
   else
   {
        std::string archivoLeer = argv[1];
        std::string archivoEscribir = argv[2];

        std::ifstream archivo(archivoLeer);//Se decide cual archivo txt va a leer!!!

        if (!archivo.is_open()) 
        {
            std::cout<<"No se pudo leer el archivo\n";
        }
        else
        {
            std::string linea;

            int a, l;
            if (std::getline(archivo, linea)) 
            {
                std::istringstream iss(linea);
            
                if (iss >> a >> l) 
                {
                    std::cout<<"El ancho es: "<<a<<"px y el largo es "<<l<<"px\n";
                } 
                else 
                {
                    std::cout<<"No se pudieron leer las dimensiones\n";
                    return 0;
                }
            }
            else 
            {
                std::cout<<"No hay nada en el archivo\n";
                return 0;
            }

            while (!archivo.eof())
            {
                std::getline(archivo, linea);
                std::cout<<"Esto es lo que se leyo del archivo: "<<linea<<std::endl;
                
                char caracter = linea[0];
                int numero = caracter - '0';
                Quadtree arbol(numero);

                for(int i = 1; i < linea.length(); i++) 
                {
                    caracter = linea[i];
                    numero = caracter - '0';
                    arbol.insertarNodo(numero);
                }

                std::cout << std::endl << "Recorrido preorden: ";
                arbol.preOrden();

                std::cout<<"\n";

                std::ofstream archivo(archivoEscribir);
                archivo<<"P1\n";
                archivo<<"# Imagen de prueba\n";
                archivo<<a<<" "<<l<<"\n";

                int** matrizImagen = new int*[a];
                for (int i=0; i<a; i++) 
                {
                    matrizImagen[i] = new int[l];
                }

                int** matrizFinal =  arbol.crearImagen(matrizImagen, arbol.getRaiz(), 0, 0, a);
                
                std::cout<<"\nLa matriz final es: \n";
                
                for (int i=0; i<a; i++) 
                {
                    for (int j=0; j<l; j++) 
                    {
                        std::cout<<matrizFinal[i][j]<<" ";
                        archivo<<matrizFinal[i][j]<<" ";
                    }
                    std::cout<<"\n";
                    archivo<<"\n";
                }
            }
        }
   }
}