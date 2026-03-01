#include "vca.hpp"

VCA::VCA(
    IGeneradorMuestra& entrada,
    IGeneradorMuestra& control
)
    : m_entrada(entrada),
      m_control(control)
{
}

double VCA::siguienteMuestra(){
    return m_entrada.siguienteMuestra() * m_control.siguienteMuestra();
}