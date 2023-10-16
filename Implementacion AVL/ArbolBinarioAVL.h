#ifndef ARBOLBINARIOAVL_H
#define ARBOLBINARIOAVL_H

#include "NodoBinarioAVL.h"
template <class T>

class ArbolBinarioAVL {
protected:
  NodoBinarioAVL<T> *raiz;

public:
  ArbolBinarioAVL();
  ~ArbolBinarioAVL();
  T datoRaiz();
  void setRaiz(NodoBinarioAVL<T> *raiz);
  NodoBinarioAVL<T> *getRaiz();
  bool esVacio();
  int altura(NodoBinarioAVL<T> *inicio);
  int tamano(NodoBinarioAVL<T> *inicio);
  bool buscar(T val);
  NodoBinarioAVL<T> *getSucesor(NodoBinarioAVL<T> *nodo);
  NodoBinarioAVL<T> *giroDerecha(NodoBinarioAVL<T> *&inicio);
  NodoBinarioAVL<T> *giroIzquierdaDerecha(NodoBinarioAVL<T> *&padre);
  NodoBinarioAVL<T> *giroIzquierda(NodoBinarioAVL<T> *&inicio);
  NodoBinarioAVL<T> *giroDerechaIzquierda(NodoBinarioAVL<T> *&padre);
  void balancear(T val);
  bool insertar(T val);
  bool eliminar(T val);
  void preOrden(NodoBinarioAVL<T> *inicio);
  void inOrden(NodoBinarioAVL<T> *inicio);
  void posOrden(NodoBinarioAVL<T> *inicio);
  void nivelOrden(NodoBinarioAVL<T> *inicio);
};
#include "ArbolBinarioAVL.hxx"

#endif // ARBOLBINARIOAVL_H