#pragma once

#include "i_generador_multicanal.hpp"
#include "i_generador_muestra.hpp"

#include <vector>
#include <array>

class GeneradorStereo : public IGeneradorMulticanal {
    private:
        IGeneradorMuestra& m_left;
        IGeneradorMuestra& m_right;

        std::array<IGeneradorMuestra*, 2> m_canales;

    public:
        GeneradorStereo(
            IGeneradorMuestra& left,
            IGeneradorMuestra& right
        );

        std::uint16_t canales() const override;

        std::vector<double> siguienteFrame() override;
};