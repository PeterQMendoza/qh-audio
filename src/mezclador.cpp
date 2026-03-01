#include "mezclador.hpp"

void Mezclador::agregarEntrada(IGeneradorMuestra& modulo){
    m_entradas.push_back(&modulo);
}

double Mezclador::siguienteMuestra(){
    double suma = 0.0;

    for (auto* modulo : m_entradas)
        suma += modulo->siguienteMuestra();

    return suma;
}