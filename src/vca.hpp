#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"

#include <vector>
#include <stdexcept>
#include <cstdint>

class VCA final : public IGeneradorMulticanal {
    // Amplificador controlado
    private:
        IGeneradorMuestra* m_audio{nullptr};
        IGeneradorMuestra* m_modulador{nullptr};
        std::uint16_t m_canales{1};
    public:
        explicit VCA(std::uint16_t canales = 1);

        void setEntradaAudio(IGeneradorMuestra& in);
        void setModulador(IGeneradorMuestra& mod);

        void setCanales(std::uint16_t canales);

        std::uint16_t canales() const override;

        [[nodiscard]]
        std::vector<double> siguienteFrame() override;

};