#pragma once

#include "i_generador_muestra.hpp"

class ModuloBase : public IGeneradorMuestra {
    protected:
        IGeneradorMuestra* m_input{nullptr};

    public:
        void conectar(IGeneradorMuestra& input);
};