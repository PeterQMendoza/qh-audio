#include "modulo_base.hpp"

void ModuloBase::conectar(IGeneradorMuestra& input) {
    m_input = &input;
}