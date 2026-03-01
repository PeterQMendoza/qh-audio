#pragma once

#include "i_generador_muestra.hpp"
#include "oscilador_seno.hpp"

class GeneradorSeno final: public IGeneradorMuestra {
    private:
        OsciladorSeno<float> m_oscilador;

    public:
        explicit GeneradorSeno(
            double frecuencia,
            double amplitud,
            double tasaMuestra
        ) noexcept;
        double siguienteMuestra() noexcept override;
};