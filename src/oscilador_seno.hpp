#pragma once

#include "i_generador_muestra.hpp"

#include <cmath>
#include <numbers>
#include <concepts>

template <std::floating_point T = float>
class OsciladorSeno final : public IGeneradorMuestra {
    private:
        T m_frecuencia{};
        T m_amplitud{};
        T m_tasaMuestra{};

        T m_fase{0};
        T m_incrementoFase{0};

        void actualizarIncremento() noexcept;
    public:
        static constexpr T dos_pi = T{2} * std::numbers::pi_v<T>;

        explicit OsciladorSeno(
            T frecuencia,
            T amplitud,
            T tasaMuestra = T{44100}
        ) noexcept;

        [[nodiscard]]
        T proceso() noexcept;

        void reset() noexcept;

        void setFrecuencia(T frecuencia) noexcept;

        void setAmplitud(T amplitud) noexcept;

        [[nodiscard]]
        T frecuencia() const noexcept;

        [[nodiscard]]
        T amplitud() const noexcept;

        double siguienteMuestra() override;
};

#include "oscilador_seno.tpp"