#include "ArbolBinarioAVL.h"
#include <queue>

using namespace std;

template <class T> ArbolBinarioAVL<T>::ArbolBinarioAVL() { this->raiz = NULL; }

template <class T> ArbolBinarioAVL<T>::~ArbolBinarioAVL() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

template <class T> T ArbolBinarioAVL<T>::datoRaiz() {
  return (this->raiz)->getDato();
}

template <class T> void ArbolBinarioAVL<T>::setRaiz(NodoBinarioAVL<T> *raiz) {
  this->raiz = raiz;
  return;
}

template <class T> NodoBinarioAVL<T> *ArbolBinarioAVL<T>::getRaiz() {
  return this->raiz;
}

template <class T> bool ArbolBinarioAVL<T>::esVacio() {
  if (this->raiz == NULL) {
    return true;
  }
  return false;
}

template <class T> int ArbolBinarioAVL<T>::altura(NodoBinarioAVL<T> *inicio) {
  int alturaIzq = 0;
  int alturaDer = 0;
  //Si no hay nodos
  if (inicio == NULL) {
    return -1;
  }
  //Si solo existe la raíz
  if (inicio->getHijoIzq() == NULL && inicio->getHijoDer() == NULL) {
    return 0;
  }
  //Se mide la altura por izquierda
  if (inicio->getHijoIzq() != NULL) {
    alturaIzq += altura(inicio->getHijoIzq()) + 1;
  }
  //Se mide la altura por derecha
  if (inicio->getHijoDer() != NULL) {
    alturaDer += altura(inicio->getHijoDer()) + 1;
  }
  //Se compara cual de las 2 alturas es mayor
  if (alturaIzq > alturaDer) {
    return alturaIzq;
  } else {
    return alturaDer;
  }
}

template <class T> int ArbolBinarioAVL<T>::tamano(NodoBinarioAVL<T> *inicio) {
  int n_nodosIzq = 0;
  int n_nodosDer = 0;
  //Si el arbol esta vacio
  if (inicio == NULL) {
    return 0;
  }
  //Si solo tiene raiz
  if (inicio->getHijoIzq() == NULL && inicio->getHijoDer() == NULL) {
    return 1;
  }
  //Se llama recursivamente la funcion para que recorra todos los nodos
  if (inicio->getHijoIzq() != NULL) {
    n_nodosIzq += tamano(inicio->getHijoIzq());
  }
  if (inicio->getHijoDer() != NULL) {
    n_nodosDer += tamano(inicio->getHijoDer());
  }
  return n_nodosIzq + n_nodosDer + 1;
}

template <class T> bool ArbolBinarioAVL<T>::buscar(T val) {
  NodoBinarioAVL<T> *nodo = this->raiz;
  //Se recorre todo el arbol buscando el dato
  while (nodo != NULL) {
    if (val < nodo->getDato()) {
      nodo = nodo->getHijoIzq();
    } else if (val > nodo->getDato()) {
      nodo = nodo->getHijoDer();
    } else {
      return true;
    }
  }
  return false;
}

template <class T>
NodoBinarioAVL<T> *ArbolBinarioAVL<T>::getSucesor(NodoBinarioAVL<T> *nodo) {
  NodoBinarioAVL<T> *sucesorPadre = nodo;
  NodoBinarioAVL<T> *sucesor = nodo;
  //Se busca el nodo con el siguiente valor más grande (sucesor)
  //Es decir del subárbol derecho y el menor nodo
  
  NodoBinarioAVL<T> *actual = nodo->getHijoDer();
  while (actual != NULL) {
    sucesorPadre = sucesor;
    sucesor = actual;
    actual = actual->getHijoIzq();
  }

  //Se verifica que el sucesor no sea el hijo directo del nodo
  if (sucesor != nodo->getHijoDer()) {
    sucesorPadre->setHijoIzq(sucesor->getHijoDer());
    sucesor->setHijoDer(nodo->getHijoDer());
  }
  return sucesor;
}

template <class T>
NodoBinarioAVL<T> 
*ArbolBinarioAVL<T>::giroDerecha(NodoBinarioAVL<T> *&padre) {
  NodoBinarioAVL<T> *n_padre = padre->getHijoIzq();
  padre->setHijoIzq(n_padre->getHijoDer());
  n_padre->setHijoDer(padre);
  return n_padre;
}

template <class T>
NodoBinarioAVL<T> *
ArbolBinarioAVL<T>::giroIzquierda(NodoBinarioAVL<T> *&padre) {
  NodoBinarioAVL<T> *n_padre = padre->getHijoDer();
  padre->setHijoDer(n_padre->getHijoIzq());
  n_padre->setHijoIzq(padre);
  return n_padre;
}

template <class T>
NodoBinarioAVL<T> *
ArbolBinarioAVL<T>::giroIzquierdaDerecha(NodoBinarioAVL<T> *&padre) {
  NodoBinarioAVL<T> **nodo = &(padre->hijoIzq);
  padre->setHijoIzq(giroIzquierda(*nodo));
  return giroDerecha(padre);
}

template <class T>
NodoBinarioAVL<T> *
ArbolBinarioAVL<T>::giroDerechaIzquierda(NodoBinarioAVL<T> *&padre) {
  NodoBinarioAVL<T> **nodo = &(padre->hijoDer);
  padre->setHijoDer(giroDerecha(*nodo));
  return giroIzquierda(padre);
}

template <class T> void ArbolBinarioAVL<T>::balancear(T val) {

  NodoBinarioAVL<T> **nodo = &(this->raiz);
  int alturaHijoIzq, alturaHijoDer, alturaHijoIzqIzq, alturaHijoIzqDer,
      alturaHijoDerDer, alturaHijoDerIzq;

  //Se recorre al arbol para balancear el arbol en cada nivel
  while (*nodo != NULL) {
    // Se calculan las alturas del hijo izquierdo y derecho, para ver la diferencia
    alturaHijoIzq = altura((*nodo)->getHijoIzq());
    alturaHijoDer = altura((*nodo)->getHijoDer());
    //Si la diferencia es mahyor a 1, se realiza un balanceo
    if (alturaHijoIzq - alturaHijoDer > 1) {
      alturaHijoIzqIzq = altura((*nodo)->getHijoIzq()->getHijoIzq());
      alturaHijoIzqDer = altura((*nodo)->getHijoIzq()->getHijoDer());
      //Se evalua que tipo de rotacion se debe realizar
      if (alturaHijoIzqIzq > alturaHijoIzqDer) {
        //rotación simple a la derecha
        *nodo = giroDerecha(*nodo); 
      } else {
        //rotación doble izquierda-derecha
        *nodo = giroIzquierdaDerecha(*nodo); 
      }
    } 
    if (alturaHijoDer - alturaHijoIzq > 1) {
      alturaHijoDerDer = altura((*nodo)->getHijoDer()->getHijoDer());
      alturaHijoDerIzq = altura((*nodo)->getHijoDer()->getHijoIzq());
      //Se evalua que tipo de rotacion se debe realizar
      if (alturaHijoDerDer > alturaHijoDerIzq) {
        //rotación simple a la izquierda
        *nodo = giroIzquierda(*nodo); 
      } else {
        //rotación doble derecha-izquierda
        *nodo = giroDerechaIzquierda(*nodo); 
      }
    }
    if (val < (*nodo)->getDato()) {
      nodo = &((*nodo)->hijoIzq);
    } else {
      nodo = &((*nodo)->hijoDer);
    }
  }
}

template <class T> bool ArbolBinarioAVL<T>::insertar(T val) {
  NodoBinarioAVL<T> **nodo = &(this->raiz);
  NodoBinarioAVL<T> *nuevo = new NodoBinarioAVL<T>(val);

  //Se verifica que el dato no este dentro del arbol
  if (buscar(val) == true)
    return false;

  //Se recorre el arbol hasta encontrar la posicion donde insertar el nuevo nodo
  while (*nodo != NULL) {
    if (val < (*nodo)->getDato()) {
      nodo = &((*nodo)->hijoIzq);
    } else {
      nodo = &((*nodo)->hijoDer);
    }
  }
  //Se inserta el nodo
  *nodo = nuevo;

  //Se hace el balanceo AVL
  balancear(val);

  return true;
}

template <class T> bool ArbolBinarioAVL<T>::eliminar(T val) {
  NodoBinarioAVL<T> *nodo = this->raiz;
  NodoBinarioAVL<T> *padre = NULL;
  bool es_hijo_izq = true;

  //El arbol esta vacio
  if (this->raiz == NULL) {
    return false;
  }

  // Buscar el nodo a eliminar
  while (nodo != NULL && nodo->getDato() != val) {
    padre = nodo;

    if (val < nodo->getDato()) {
      nodo = nodo->getHijoIzq();
      es_hijo_izq = true;
    } else {
      nodo = nodo->getHijoDer();
      es_hijo_izq = false;
    }
  }

  // El nodo a eliminar no fue encontrado
  if (nodo == NULL) {
    return false;
  }

  // Caso 1: El nodo a eliminar no tiene hijos
  if (nodo->getHijoIzq() == NULL && nodo->getHijoDer() == NULL) {
    if (nodo == this->raiz) {
      this->raiz = NULL;
    } else if (es_hijo_izq) {
      padre->setHijoIzq(NULL);
    } else {
      padre->setHijoDer(NULL);
    }
    delete nodo;
  }
  // Caso 2: El nodo a eliminar tiene un hijo
  else if (nodo->getHijoDer() == NULL) {
    if (nodo == this->raiz) {
      this->raiz = nodo->getHijoIzq();
    } else if (es_hijo_izq) {
      padre->setHijoIzq(nodo->getHijoIzq());
    } else {
      padre->setHijoDer(nodo->getHijoIzq());
    }
    delete nodo;
  } else if (nodo->getHijoIzq() == NULL) {
    if (nodo == this->raiz) {
      this->raiz = nodo->getHijoDer();
    } else if (es_hijo_izq) {
      padre->setHijoIzq(nodo->getHijoDer());
    } else {
      padre->setHijoDer(nodo->getHijoDer());
    }
    delete nodo;
  }
  // Caso 3: El nodo a eliminar tiene dos hijos
  else {
    NodoBinarioAVL<T> *sucesor = getSucesor(nodo);

    if (nodo == this->raiz) {
      this->raiz = sucesor;
    } else if (es_hijo_izq) {
      padre->setHijoIzq(sucesor);
    } else {
      padre->setHijoDer(sucesor);
    }

    sucesor->setHijoIzq(nodo->getHijoIzq());
    delete nodo;
  }

  // Balancear el árbol después de eliminar el nodo
  balancear(val);
  return true;
}

template <class T>
void ArbolBinarioAVL<T>::preOrden(NodoBinarioAVL<T> *inicio) {
  cout << inicio->getDato() << " ";
  if (inicio->getHijoIzq() != NULL) {
    preOrden(inicio->getHijoIzq());
  }
  if (inicio->getHijoDer() != NULL) {
    preOrden(inicio->getHijoDer());
  }
}

template <class T> void ArbolBinarioAVL<T>::inOrden(NodoBinarioAVL<T> *inicio) {
  if (inicio->getHijoIzq() != NULL) {
    inOrden(inicio->getHijoIzq());
  }
  cout << inicio->getDato() << " ";
  if (inicio->getHijoDer() != NULL) {
    inOrden(inicio->getHijoDer());
  }
}

template <class T>
void ArbolBinarioAVL<T>::posOrden(NodoBinarioAVL<T> *inicio) {
  if (inicio->getHijoIzq() != NULL) {
    posOrden(inicio->getHijoIzq());
  }
  if (inicio->getHijoDer() != NULL) {
    posOrden(inicio->getHijoDer());
  }
  cout << inicio->getDato() << " ";
}

template <class T>
void ArbolBinarioAVL<T>::nivelOrden(NodoBinarioAVL<T> *inicio) {
  queue<NodoBinarioAVL<T>> colaNivel;
  NodoBinarioAVL<T> nodo;
  colaNivel.push(*inicio);
  while (!colaNivel.empty()) {
    nodo = colaNivel.front();
    colaNivel.pop();
    cout << nodo.getDato() << " ";
    if (nodo.getHijoIzq() != NULL) {
      colaNivel.push(*nodo.getHijoIzq());
    }
    if (nodo.getHijoDer() != NULL) {
      colaNivel.push(*nodo.getHijoDer());
    }
  }
}