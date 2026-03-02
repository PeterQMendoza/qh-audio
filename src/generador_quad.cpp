#include "generador_quad.hpp"

GeneradorQuad::GeneradorQuad(
    IGeneradorMuestra& c1,
    IGeneradorMuestra& c2,
    IGeneradorMuestra& c3,
    IGeneradorMuestra& c4
)
{
    m_canales = { &c1, &c2, &c3, &c4 };
}

std::vector<double> GeneradorQuad::siguienteFrame()
{
    return {
        m_canales[0]->siguienteMuestra(),
        m_canales[1]->siguienteMuestra(),
        m_canales[2]->siguienteMuestra(),
        m_canales[3]->siguienteMuestra()
    };
}

std::uint16_t GeneradorQuad::canales() const {
    return static_cast<std::uint16_t>(m_canales.size());
}