#include "reloj.hpp"

Reloj::Reloj(double bpm, uint32_t tasaMuestra)
    : m_bpm(bpm), m_tasaMuestra(tasaMuestra)
{
    m_muestraPorBeat = (60.0 / bpm) * tasaMuestra;
}

void Reloj::avanzar() noexcept {
    m_contadorMuestra++;
}

bool Reloj::esBeat() const noexcept{
    return m_contadorMuestra % m_muestraPorBeat == 0;
}

void Reloj::setBpm(double bpm){
    m_bpm = bpm;
    m_muestraPorBeat =static_cast<std::uint64_t>((60.0 / bpm) * m_tasaMuestra);
}

 std::uint64_t Reloj::muestraActual() const noexcept {
    return m_contadorMuestra;
}