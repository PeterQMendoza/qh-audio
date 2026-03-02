#pragma once

#include "i_generador_multicanal.hpp"
#include "i_generador_muestra.hpp"

#include <array>

class GeneradorQuad : public IGeneradorMulticanal {
    private:
        std::array<IGeneradorMuestra*, 4> m_canales;

    public:
        GeneradorQuad(
            IGeneradorMuestra& c1,
            IGeneradorMuestra& c2,
            IGeneradorMuestra& c3,
            IGeneradorMuestra& c4
        );

        std::uint16_t canales() const override;

        std::vector<double> siguienteFrame() override;
};