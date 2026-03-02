#include "generador_stereo.hpp"

GeneradorStereo::GeneradorStereo(
    IGeneradorMuestra& left,
    IGeneradorMuestra& right
)
: m_left(left), m_right(right){

}

std::vector<double> GeneradorStereo::siguienteFrame(){
    return {
        m_left.siguienteMuestra(),
        m_right.siguienteMuestra()
    };
}