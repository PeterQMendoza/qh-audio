#pragma once

#include "i_generador_multicanal.hpp"
#include "i_generador_muestra.hpp"

#include <vector>
#include <memory>
#include <cmath>

class GeneradorBinaural : public IGeneradorMulticanal {
    public:
        GeneradorBinaural(
            std::shared_ptr<IGeneradorMuestra> fuente,
            double tasaMuestra
        );

        void setAzimuth(double grados); // -90 izquierda, +90 derecha
        std::vector<double> siguienteFrame() override;
        std::uint16_t canales() const override { return 2; }

    private:
        std::shared_ptr<IGeneradorMuestra> m_fuente;
        double m_tasaMuestra;

        double m_azimuthRad = 0.0;

        // Delay buffers para ITD
        std::vector<double> m_delayBufferL;
        std::vector<double> m_delayBufferR;
        std::size_t m_index = 0;
        std::size_t m_maxDelaySamples;

        double aplicarFiltro(double input, double& estado);
        double m_estadoFiltroL = 0.0;
        double m_estadoFiltroR = 0.0;
};