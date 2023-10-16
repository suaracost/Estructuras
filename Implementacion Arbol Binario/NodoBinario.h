#ifndef __NODOBINARIO_H__
#define __NODOBINARIO_H__

template <class T>
class NodoBinario {
    protected:
        T dato;
        NodoBinario<T> *izq;
        NodoBinario<T> *der;
    public:
        NodoBinario();
        NodoBinario(T& val);
        ~NodoBinario();
        T obtenerDato();
        void fijarDato(T val);
        NodoBinario<T>* obtenerHijoIzq();
        NodoBinario<T>* obtenerHijoDer();
        void fijarHijoIzq(NodoBinario<T>* izq);
        void fijarHijoDer(NodoBinario<T>* der);
        bool esHoja();
        int altura();
        void recorridoInorden();
};

#include "NodoBinario.hxx"

#endif