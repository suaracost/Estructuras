#include "ArbolBinarioOrd.h"
#include <iostream>

int main() 
{
    ArbolBinarioOrd<int> arbol = ArbolBinarioOrd<int>(7);  

    std::cout<<"\ninsertar\n";
    arbol.insertar(3);
    arbol.insertar(0);
    arbol.insertar(5);
    arbol.insertar(-3);
    arbol.insertar(1);
    arbol.insertar(4);
    arbol.insertar(6);
    arbol.insertar(20);
    arbol.insertar(15);
    arbol.insertar(12);
    arbol.insertar(25);
    arbol.insertar(30);

    std::cout<<"\ndato raiz "<< arbol.datoRaiz();

    std::cout<<"\naltura "<< arbol.altura();

    std::cout<<"\ntamano "<< arbol.tamano();

    std::cout<<"\nbuscar\n";
    arbol.buscar(20);

    std::cout<<"\npreorden\n";
    arbol.preOrden();

    std::cout<<"\ninorden\n";
    arbol.inOrden();

    std::cout<<"\npostorden\n";
    arbol.postOrden();

    std::cout<<"\nnivelorden\n";
    arbol.nivelOrden();

    std::cout<<"\n\neliminar";
    arbol.eliminar(20);

    std::cout<<"\npreorden sin valor\n";
    arbol.preOrden();

    return 0;
}