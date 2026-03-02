#include "vca.hpp"

VCA::VCA(std::uint16_t canales)
: m_canales(canales)
{
    if (canales == 0 || canales > 4){
        throw std::invalid_argument("Canales permitidos: 1 a 4");
    }
}

void VCA::setEntradaAudio(IGeneradorMuestra& in){
    m_audio = &in;
}
void VCA::setModulador(IGeneradorMuestra& modulador){
    m_modulador = &modulador;
}

void VCA::setCanales(std::uint16_t canales)
{
    if (canales == 0 || canales > 4)
        throw std::invalid_argument("Canales permitidos: 1 a 4");

    m_canales = canales;
}

std::vector<double> VCA::siguienteFrame()
{
    if (!m_audio || !m_modulador)
        return std::vector<double>(m_canales, 0.0);

    const double audio = m_audio->siguienteMuestra();
    const double mod   = m_modulador->siguienteMuestra();
    const double salida = audio * mod;

    return std::vector<double>(m_canales, salida);
}

// std::uint16_t VCA::canales() const {
//     return m_canales;
// }