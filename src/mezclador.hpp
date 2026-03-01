#pragma once

#include "i_generador_muestra.hpp"
#include <vector>

class Mezclador final : public IGeneradorMuestra {
    // Modulo de mezclador
    public:
        void agregarEntrada(IGeneradorMuestra& modulo);

        double siguienteMuestra() override;

    private:
        std::vector<IGeneradorMuestra*> m_entradas;
};