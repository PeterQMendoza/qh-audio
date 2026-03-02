#include "generador_stereo.hpp"

GeneradorStereo::GeneradorStereo(
    IGeneradorMuestra& left,
    IGeneradorMuestra& right
)
: m_left(left), m_right(right){
    m_canales = { &left, &right};
}

std::vector<double> GeneradorStereo::siguienteFrame(){
    return {
        m_left.siguienteMuestra(),
        m_right.siguienteMuestra()
    };
}

std::uint16_t GeneradorStereo::canales() const {
    return static_cast<std::uint16_t>(m_canales.size());
}