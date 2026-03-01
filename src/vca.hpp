#pragma once

#include "i_generador_muestra.hpp"

class VCA final : public IGeneradorMuestra {
    // Amplificador controlado
    public:
        VCA(
            IGeneradorMuestra& entrada,
            IGeneradorMuestra& control
        );

        double siguienteMuestra() override;

    private:
        IGeneradorMuestra& m_entrada;
        IGeneradorMuestra& m_control;
};