#include "vca.hpp"

VCA::VCA()
{
}

double VCA::siguienteMuestra(){
    if (!m_audio || !m_modulador){
        return 0.0;
    }
    return m_audio->siguienteMuestra() * m_modulador->siguienteMuestra();
}

void VCA::setEntradaAudio(IGeneradorMuestra& in){
    m_audio = &in;
}
void VCA::setModulador(IGeneradorMuestra& modulador){
    m_modulador = &modulador;
}