#ifndef NODOBINARIOAVL_H
#define NODOBINARIOAVL_H

template <class T>

class NodoBinarioAVL {
public:
  // Atributos
  T dato;
  NodoBinarioAVL<T> *hijoIzq;
  NodoBinarioAVL<T> *hijoDer;

  // Metodos
  NodoBinarioAVL();
  NodoBinarioAVL(T val);
  ~NodoBinarioAVL();
  T getDato();
  void setDato(T val);
  NodoBinarioAVL<T> *getHijoIzq();
  NodoBinarioAVL<T> *getHijoDer();
  void setHijoIzq(NodoBinarioAVL<T>* hijoIzq);
  void setHijoDer(NodoBinarioAVL<T>* hijoDer);
};

#include "NodoBinarioAVL.hxx"

#endif // NODOBINARIOAVL_H