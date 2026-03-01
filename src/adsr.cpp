#include "adsr.hpp"

ADSR::ADSR(
    double attack,
    double decay,
    double sustain,
    double release,
    double sampleRate
)
    : m_attack(attack),
      m_decay(decay),
      m_sustain(sustain),
      m_release(release),
      m_sampleRate(sampleRate)
{
}

void ADSR::noteOn(){
    m_estado = Estado::Attack;
}

void ADSR::noteOff(){
    m_estado = Estado::Release;
}

double ADSR::siguienteMuestra(){
    switch (m_estado)
    {
        case Estado::Idle:
            break;

        case Estado::Attack:
            m_nivel += 1.0 / (m_attack * m_sampleRate);
            if (m_nivel >= 1.0)
            {
                m_nivel = 1.0;
                m_estado = Estado::Decay;
            }
            break;

        case Estado::Decay:
            m_nivel -= (1.0 - m_sustain) / (m_decay * m_sampleRate);
            if (m_nivel <= m_sustain)
            {
                m_nivel = m_sustain;
                m_estado = Estado::Sustain;
            }
            break;

        case Estado::Sustain:
            break;

        case Estado::Release:
            m_nivel -= m_sustain / (m_release * m_sampleRate);
            if (m_nivel <= 0.0)
            {
                m_nivel = 0.0;
                m_estado = Estado::Idle;
            }
            break;
    }

    return m_nivel;
}