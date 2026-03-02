#pragma once

#include "i_generador_multicanal.hpp"
#include "i_generador_muestra.hpp"

#include <vector>

class GeneradorStereo : public IGeneradorMulticanal {
private:
    IGeneradorMuestra& m_left;
    IGeneradorMuestra& m_right;

public:
    GeneradorStereo(
        IGeneradorMuestra& left,
        IGeneradorMuestra& right
    );

    std::vector<double> siguienteFrame() override;
};