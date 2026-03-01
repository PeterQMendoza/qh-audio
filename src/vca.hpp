#pragma once

#include "i_generador_muestra.hpp"

class VCA final : public IGeneradorMuestra {
    // Amplificador controlado
    private:
        IGeneradorMuestra* m_audio{nullptr};
        IGeneradorMuestra* m_modulador{nullptr};
    public:
        VCA();

        void setEntradaAudio(IGeneradorMuestra& in);
        void setModulador(IGeneradorMuestra& mod);

        double siguienteMuestra() override;

};