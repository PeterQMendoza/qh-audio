#include "generador_binaural.hpp"

constexpr double kHeadRadius = 0.0875;
constexpr double kSpeedSound = 343.0;

GeneradorBinaural::GeneradorBinaural(
    std::shared_ptr<IGeneradorMuestra> fuente,
    double tasaMuestra
)
: m_fuente(fuente),
  m_tasaMuestra(tasaMuestra)
{
    double maxDelay = kHeadRadius / kSpeedSound;
    m_maxDelaySamples = static_cast<std::size_t>(maxDelay * tasaMuestra) + 1;

    m_delayBufferL.resize(m_maxDelaySamples, 0.0);
    m_delayBufferR.resize(m_maxDelaySamples, 0.0);
}

void GeneradorBinaural::setAzimuth(double grados)
{
    m_azimuthRad = grados * M_PI / 180.0;
}

double GeneradorBinaural::aplicarFiltro(double input, double& estado)
{
    // Filtro low-pass simple (sombra de cabeza)
    constexpr double alpha = 0.2;
    estado = alpha * input + (1 - alpha) * estado;
    return estado;
}

std::vector<double> GeneradorBinaural::siguienteFrame()
{
    double mono = m_fuente->siguienteMuestra();

    // ITD
    double delayTime =
        (kHeadRadius / kSpeedSound) * std::sin(m_azimuthRad);

    std::size_t delaySamples =
        static_cast<std::size_t>(std::abs(delayTime) * m_tasaMuestra);

    std::size_t readIndex =
        (m_index + m_maxDelaySamples - delaySamples) % m_maxDelaySamples;

    double left = mono;
    double right = mono;

    if (delayTime > 0)
        left = m_delayBufferL[readIndex];
    else
        right = m_delayBufferR[readIndex];

    // Guardar muestra actual en buffer
    m_delayBufferL[m_index] = mono;
    m_delayBufferR[m_index] = mono;

    // IID
    double gainL = 0.5 * (1 - std::sin(m_azimuthRad));
    double gainR = 0.5 * (1 + std::sin(m_azimuthRad));

    left *= gainL;
    right *= gainR;

    // Filtro espectral
    if (m_azimuthRad > 0)
        left = aplicarFiltro(left, m_estadoFiltroL);
    else
        right = aplicarFiltro(right, m_estadoFiltroR);

    m_index = (m_index + 1) % m_maxDelaySamples;

    return { left, right };
}