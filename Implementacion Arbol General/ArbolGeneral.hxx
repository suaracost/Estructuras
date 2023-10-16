#include "ArbolGeneral.h"
#include <queue> // Se incliye para el recorrido nivelOrden
#include <iostream>
#include <iterator>
#include <list>

template <class T>
ArbolGeneral<T>::ArbolGeneral() 
{
  this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) 
{
  NodoGeneral<T>* nodo = new NodoGeneral<T>();
  nodo->fijarDato(val);
  this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() 
{
  delete this->raiz;
  this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() 
{
  return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() 
{
  return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) 
{
  this->raiz = nraiz;
}

// Propuesta de Implementacion de la funcion: insertarNodo
//
template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) 
  {
    // Si está vacío, creamos un nuevo nodo y lo convertimos en la raíz
    NodoGeneral<T>* nodo = new NodoGeneral<T>();
    nodo->fijarDato(n);
    this->raiz = nodo;
    return true;  // Indicamos que se ha insertado el nodo exitosamente
  } 
  else 
  {
    // Si el árbol no está vacío, llamamos a la función auxiliar para insertar en el subárbol
    return insertarNodoEnSubarbol(this->raiz, padre, n);
  }
}

template <class T>
bool ArbolGeneral<T>::insertarNodoEnSubarbol(NodoGeneral<T>* nodo, T padre, T n) 
{
  // Verificamos si el valor del nodo actual es igual al padre que buscamos
  if (nodo->obtenerDato() == padre) 
  {
    // Creamos un nuevo nodo con el valor 'n' y lo agregamos como descendiente del nodo actual
    // La funcion "adicionarDesc" crea el nodo y le asigna el valor del parametro que recibe
    // - por esto solo vasta llamar a esta funcion y enviar n como parametro
    /* Esto CREO que ya no iria, solo lo dejo mientras las pruebas
    NodoGeneral<T>* nuevoNodo = new NodoGeneral<T>();
    nuevoNodo->fijarDato(n);
    */    
    nodo->adicionarDesc(n);
    return true;  // Indicamos que se ha insertado el nodo exitosamente
  } 
  else 
  {
    // Si el nodo actual no es el padre que buscamos, exploramos sus descendientes
    bool insertado = false;
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) 
    {
      // Llamamos recursivamente a la función en cada descendiente para intentar insertar el nodo
      insertado = insertado || insertarNodoEnSubarbol(*it, padre, n);
    }
    return insertado;
  }
}
//

// Propuesta de Implementacion de la funcion: eliminarNodo
//
template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n) 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) {
    return false;  // Si el árbol está vacío, no se puede eliminar nada
  } 
  else if (this->raiz->obtenerDato() == n) 
  {

    // Si el valor a eliminar es la raíz, eliminamos la raíz y la ponemos en NULL
    delete this->raiz;
    this->raiz = NULL;
    return true;  // Indicamos que se ha eliminado el nodo exitosamente
  } 
  else 
  {
    return eliminarNodoEnSubarbol(this->raiz, n);
  }
}

template <class T>
bool ArbolGeneral<T>::eliminarNodoEnSubarbol(NodoGeneral<T>* nodo, T n) 
{
  bool eliminado = false;
  typename std::list< NodoGeneral<T>* >::iterator it = nodo->desc.begin();
  while (it != nodo->desc.end()) 
  {
    // Si el nodo hijo tiene el valor que queremos eliminar
    if ((*it)->obtenerDato() == n) 
    {
      if ((*it)->altura() != -1)
      {
        // si eliminamos un nodo sus desendientes pasan al padre del nodo eliminado
        nodo->desc.splice(nodo->desc.end(), (*it)->desc); // se funciona la lista del nodo padre con la lista del nodo eliminado
      }
      delete *it;  // Eliminamos el nodo hijo
      it = nodo->desc.erase(it);  // Lo eliminamos de la lista de descendientes
      eliminado = true;  // Indicamos que se ha eliminado el nodo exitosamente
    } 
    else 
    {
      // Si no lo hemos eliminado, continuamos explorando el subárbol de ese nodo hijo
      eliminado = eliminado || eliminarNodoEnSubarbol(*it, n);
      ++it;
    }
  }
  return eliminado;
}
//

// Propuesta de Implementacion de la funcion: buscar
//
template <class T>
bool ArbolGeneral<T>::buscar(T n) 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) 
  {
    return false;  // Si el árbol está vacío, no se puede encontrar nada
  }
  else if (this->raiz->obtenerDato() == n) 
  {
    return true;  // Si encontramos el valor en la raíz, retornamos true
  } 
  else 
  {
    return buscarEnSubarbol(this->raiz, n);
  }
}

template <class T>
bool ArbolGeneral<T>::buscarEnSubarbol(NodoGeneral<T>* nodo, T n) 
{
  bool encontrado = false;
  typename std::list< NodoGeneral<T>* >::iterator it = nodo->desc.begin();
  while (it != nodo->desc.end()) 
  {
    // Si el nodo hijo tiene el valor que estamos buscando
    if ((*it)->obtenerDato() == n) 
    {
      encontrado = true;  // Indicamos que encontramos el valor
      break;  // Salimos del ciclo ya que lo hemos encontrado
    } 
    else 
    {
      // Si no lo hemos encontrado, continuamos explorando el subárbol de ese nodo hijo
      encontrado = encontrado || buscarEnSubarbol(*it, n);
      ++it;
    }
  }
  return encontrado;
}
//

// Se esta encontrando la altura del arbol, con recurrencia dentro del arbol
//
template <class T>
int ArbolGeneral<T>::altura() 
{
  if (this->esVacio())
  {
    return -1;
  }
  else
  {
    return this->altura(this->raiz);
  }
}

template <class T>
int ArbolGeneral<T>::altura(NodoGeneral<T>* nodo) 
{
  int alt = -1;

  if (nodo->esHoja()) 
  {
    alt = 0;
  }
  else 
  {
    int alth;
    typename std::list< NodoGeneral<T>* >::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); it++)
    {
      alth = this->altura(*it);
      if (alt < alth+1)
        alt = alth+1;
    }
  }
  
  return alt;
}
//

// Propuesta de Implementacion de la funcion: tamano
//
template <class T>
unsigned int ArbolGeneral<T>::tamano() 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) 
  {
    return 0;  // Si el árbol está vacío, el tamaño es 0
  } 
  else 
  {
    return tamanoEnSubarbol(this->raiz);
  }
}

template <class T>
unsigned int ArbolGeneral<T>::tamanoEnSubarbol(NodoGeneral<T>* nodo) 
{
  unsigned int totalTamano = 1;  // Comenzamos con 1 para contar el nodo actual
  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) 
  {
    // Llamamos recursivamente a la función en cada descendiente y acumulamos los tamaños
    totalTamano += tamanoEnSubarbol(*it);
  }
  return totalTamano;
}
//

// Se esta recorriendo el arbol en preOrden, con recurrencia dentro del arbol 
//
template <class T>
void ArbolGeneral<T>::preOrden() 
{
  if (!this->esVacio())
    this->preOrden(this->raiz);
  
}

template <class T>
void ArbolGeneral<T>::preOrden(NodoGeneral<T>* nodo) 
{
  std::cout << nodo->obtenerDato() << " ";

  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); it++) 
  {
    this->preOrden(*it);
  }
}
//

// Propuesta de Implementacion de la funcion: posOrden
//
template <class T>
void ArbolGeneral<T>::posOrden() 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) 
  {
    std::cout << "No se puede recorrer un árbol vacío" << std::endl;
  } 
  else 
  {
    posOrdenEnSubarbol(this->raiz);
  }
}

template <class T>
void ArbolGeneral<T>::posOrdenEnSubarbol(NodoGeneral<T>* nodo) 
{
  typename std::list< NodoGeneral<T>* >::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) 
  {
    // Llamamos recursivamente a la función en cada descendiente
    posOrdenEnSubarbol(*it);
  }
  // Después de recorrer los descendientes, imprimimos el dato del nodo actual
  std::cout << nodo->obtenerDato() << " ";
}
//

// Propuesta de Implementacion de la funcion: nivelOrden
//
template <class T>
void ArbolGeneral<T>::nivelOrden() 
{
  // Verificamos si el árbol está vacío
  if (this->esVacio()) 
  {
    std::cout << "El árbol está vacío" << std::endl;
    return;
  }

  // Utilizamos una cola para el recorrido por niveles
  std::queue<NodoGeneral<T>*> cola;
  cola.push(this->raiz);  // Insertamos la raíz en la cola
  
  // Realizamos el recorrido por niveles utilizando la cola
  while (!cola.empty()) 
  {
    NodoGeneral<T>* nodo = cola.front();
    cola.pop();  // Sacamos el primer elemento de la cola
    std::cout << nodo->obtenerDato() << " ";  // Imprimimos el dato del nodo
    
    // Insertamos en la cola todos los hijos del nodo actual
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) 
    {
      cola.push(*it);
    }
  }
}