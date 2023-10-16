#include "ArbolGeneral.h"
#include <iostream>

int main() 
{
    ArbolGeneral<int> arbol(0);  // Creamos un árbol con raíz 0
    
    // Insertamos nodos en el árbol
    arbol.insertarNodo(0, 1);  // Insertamos el nodo 1 como hijo de 0
    arbol.insertarNodo(0, 2);  // Insertamos el nodo 2 como hijo de 0
    arbol.insertarNodo(0, 3);  // Insertamos el nodo 3 como hijo de 0
    
    arbol.insertarNodo(1, 4);  // Insertamos el nodo 4 como hijo de 1
    arbol.insertarNodo(1, 5);  // Insertamos el nodo 5 como hijo de 1
    
    arbol.insertarNodo(4, 10);  // Insertamos el nodo 10 como hijo de 4
    arbol.insertarNodo(4, 11);  // Insertamos el nodo 11 como hijo de 4
    
    arbol.insertarNodo(5, 12);  // Insertamos el nodo 12 como hijo de 5
    
    arbol.insertarNodo(2, 6);   // Insertamos el nodo 6 como hijo de 2
    arbol.insertarNodo(2, 7);   // Insertamos el nodo 7 como hijo de 2
    
    arbol.insertarNodo(7, 15);  // Insertamos el nodo 15 como hijo de 7
    
    arbol.insertarNodo(3, 8);   // Insertamos el nodo 8 como hijo de 3
    
    arbol.insertarNodo(8, 13);  // Insertamos el nodo 13 como hijo de 8
    arbol.insertarNodo(8, 14);  // Insertamos el nodo 14 como hijo de 8
    
    arbol.insertarNodo(3, 9);   // Insertamos el nodo 9 como hijo de 3

    // Imprimimos el árbol en preorden
    std::cout << "Recorrido preorden: ";
    arbol.preOrden();
    std::cout << std::endl;
    
    // Imprimimos el árbol en posorden
    std::cout << "Recorrido posorden: ";
    arbol.posOrden();
    std::cout << std::endl;
    
    // Imprimimos el árbol en nivelorden
    std::cout << "Recorrido nivelorden: ";
    arbol.nivelOrden();
    std::cout << std::endl;
    
    // Verificamos si el nodo 6 existe en el árbol
    if (arbol.buscar(6)) 
    {
        std::cout << "El nodo 6 existe en el arbol" << std::endl;
    } 
    else 
    {
        std::cout << "El nodo 6 no existe en el arbol" << std::endl;
    }
    
    // Imprimimos la altura del árbol
    std::cout << "Altura del arbol: " << arbol.altura() << std::endl;
    
    // Imprimimos el tamaño del árbol
    std::cout << "Tamano del arbol: " << arbol.tamano() << std::endl;
    
    // Eliminamos el nodo 4 y su subárbol
    arbol.eliminarNodo(4);
    
    // Imprimimos el árbol en preorden después de eliminar
    std::cout << "Recorrido preorden despues de eliminar nodo 4: ";
    arbol.preOrden();
    std::cout << std::endl;
    
    return 0;
}