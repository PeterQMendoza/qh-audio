#pragma once

#include "i_generador_muestra.hpp"
#include <vector>

class Mezclador final : public IGeneradorMuestra {
    // Modulo de mezclador
    private:
        std::vector<IGeneradorMuestra*> m_entradas;
    public:
        void agregarEntrada(IGeneradorMuestra& modulo);

        double siguienteMuestra() override;

};