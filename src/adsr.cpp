#include "adsr.hpp"

ADSR::ADSR(
    double attack,
    double decay,
    double sustain,
    double release,
    std::uint32_t tasaMuestra
)
    : m_attack(attack),
      m_decay(decay),
      m_sustain(sustain),
      m_release(release),
      m_tasaMuestra(tasaMuestra)
{
    // incrementos lineales por muestra
    m_attack  = (attack  > 0.0) ? 1.0 / (attack  * tasaMuestra) : 1.0;
    m_decay   = (decay   > 0.0) ? (1.0 - sustain) / (decay * tasaMuestra) : 1.0;
    m_release = (release > 0.0) ? sustain / (release * tasaMuestra) : 1.0;
}

void ADSR::noteOn(){
    m_estado = Estado::Attack;
}

void ADSR::noteOff(){
    if(m_estado != Estado::Idle){
        m_estado = Estado::Release;
    }
}

double ADSR::siguienteMuestra(){
    switch (m_estado)
    {
        case Estado::Idle:
            break;

        case Estado::Attack:
            m_nivel += 1.0 / (m_attack * m_tasaMuestra);
            if (m_nivel >= 1.0)
            {
                m_nivel = 1.0;
                m_estado = Estado::Decay;
            }
            break;

        case Estado::Decay:
            m_nivel -= (1.0 - m_sustain) / (m_decay * m_tasaMuestra);
            if (m_nivel <= m_sustain)
            {
                m_nivel = m_sustain;
                m_estado = Estado::Sustain;
            }
            break;

        case Estado::Sustain:
            break;

        case Estado::Release:
            m_nivel -= m_sustain / (m_release * m_tasaMuestra);
            if (m_nivel <= 0.0)
            {
                m_nivel = 0.0;
                m_estado = Estado::Idle;
            }
            break;
    }

    return m_nivel;

}