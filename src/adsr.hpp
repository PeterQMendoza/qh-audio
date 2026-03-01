#pragma once

#include "i_generador_muestra.hpp"

class ADSR final : public IGeneradorMuestra {
    // Modulo adsr real (envolvente)
    public:
        ADSR(double attack,
            double decay,
            double sustain,
            double release,
            double sampleRate);

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
        double m_sampleRate;

        double m_nivel {0.0};
};