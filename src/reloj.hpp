#pragma once

#include <cstdint>

class Reloj {
    public:
        Reloj(double bpm, uint32_t tasaMuestra);

        void avanzar() noexcept;

        void setBpm(double bpm);

        bool esBeat() const noexcept;

        std::uint64_t muestraActual() const noexcept;

    private:
        double m_bpm = 120.0;
        uint32_t m_tasaMuestra;
        uint64_t m_contadorMuestra = 0;
        uint64_t m_muestraPorBeat = 0;
};