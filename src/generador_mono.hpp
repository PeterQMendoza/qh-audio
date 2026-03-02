#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"

class AdaptadorMonoAEstereo final : public IGeneradorMulticanal
{
    private:
        IGeneradorMuestra& m_fuente;

    public:
        explicit AdaptadorMonoAEstereo(IGeneradorMuestra& fuente);

        std::vector<double> siguienteFrame() override;
};