#pragma once

#include <cmath>
#include <numbers>
#include <concepts>

template <std::floating_point T = float>
class OsciladorSeno final{
    private:
        T m_frecuencia;
        T m_amplitud;
        T m_tasaMuestra;

        T m_fase {0};
        T m_incrementoFase {0};

        void actualizarIncremento() noexcept;
    public:
        static constexpr T dos_pi = T{2} * std::numbers::pi_v<T>;

        constexpr explicit OsciladorSeno(
            T frecuencia,
            T amplitud,
            T tasaMuestra = T{44100}
        ) noexcept;

        [[nodiscard]]
        T proceso() noexcept;

        constexpr void reset() noexcept;

        constexpr void setFrecuencia(T frecuencia) noexcept;

        constexpr void setAmplitud(T amplitud) noexcept;

        [[nodiscard]]
        constexpr T frecuencia() const noexcept;

        [[nodiscard]]
        constexpr T amplitud() const noexcept;
};

#include "oscilador_seno.tpp"