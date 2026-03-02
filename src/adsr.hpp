#pragma once

#include "i_generador_muestra.hpp"

#include <cstdint>

class ADSR final : public IGeneradorMuestra {
    // Modulo adsr real (envolvente)
    public:
        ADSR(double attack,
            double decay,
            double sustain,
            double release,
            std::uint32_t tasaMuestra
        );

        void noteOn();
        void noteOff();

        double siguienteMuestra() override;

    private:
        enum class Estado { Idle, Attack, Decay, Sustain, Release };

        Estado m_estado { Estado::Idle };

        double m_attack;
        double m_decay;
        double m_sustain;
        double m_release;
        std::uint32_t m_tasaMuestra;

        double m_nivel {0.0};
};