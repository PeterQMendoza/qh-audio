#include "generador_mono.hpp"

AdaptadorMonoAEstereo::AdaptadorMonoAEstereo(
    IGeneradorMuestra& fuente
)
: m_fuente(fuente) {

}

std::vector<double>AdaptadorMonoAEstereo::siguienteFrame()
{
    double s = m_fuente.siguienteMuestra();
    return { s, s }; // duplicación L/R
}
