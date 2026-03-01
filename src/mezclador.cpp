#include "mezclador.hpp"

void Mezclador::agregarEntrada(IGeneradorMuestra& modulo){
    m_entradas.push_back(&modulo);
}

double Mezclador::siguienteMuestra(){
    if (m_entradas.empty()){
        return 0.0;
    }

    double suma = 0.0;

    for (auto* modulo : m_entradas)
        suma += modulo->siguienteMuestra();

    return suma / m_entradas.size(); // normalizacion
}