#pragma once

template <std::floating_point T>
OsciladorSeno<T>::OsciladorSeno(
    T frecuencia,
    T amplitud,
    T tasaMuestra
) noexcept
: m_frecuencia(frecuencia),
m_amplitud(amplitud),
m_tasaMuestra(tasaMuestra)
{
    actualizarIncremento();
}

template <std::floating_point T>
void OsciladorSeno<T>::actualizarIncremento() noexcept {
    m_incrementoFase = dos_pi * m_frecuencia / m_tasaMuestra;
}

template <std::floating_point T>
T OsciladorSeno<T>::proceso() noexcept {
    const T muestra = m_amplitud * std::sin(m_fase);

    m_fase += m_incrementoFase;

    if (m_fase >= dos_pi){
        m_fase -= dos_pi;
    }

    return muestra;
}

template <std::floating_point T>
void OsciladorSeno<T>::reset() noexcept {
    m_fase = T{0};
}

template <std::floating_point T>
void OsciladorSeno<T>::setFrecuencia(T frecuencia) noexcept {
    m_frecuencia = frecuencia;
    actualizarIncremento();
}

template <std::floating_point T>
void OsciladorSeno<T>::setAmplitud(T amplitud) noexcept {
    m_amplitud = amplitud;
}

template <std::floating_point T>
T OsciladorSeno<T>::frecuencia() const noexcept {
    return m_frecuencia;
}

template <std::floating_point T>
T OsciladorSeno<T>::amplitud() const noexcept {
    return m_amplitud;
}

template <std::floating_point T>
double OsciladorSeno<T>::siguienteMuestra() {
    return static_cast<double>(proceso());
}