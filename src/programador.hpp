#pragma once

#include "reloj.hpp"

#include <queue>
#include <vector>
#include <functional>
#include <cstdint>

class Programador {
    public:
        Programador(Reloj& reloj);

        void programar(
            std::uint64_t tiempoMuestra,
            std::function<void()> accion
        );

        void procesar(std::uint64_t muestraActual);

        bool vacio() const noexcept;

    private:
        struct Evento {
            std::uint64_t tiempoMuestra;
            std::function<void()> accion;

            bool operator>(const Evento& otro) const {
                return tiempoMuestra > otro.tiempoMuestra;
            }
        };

        std::priority_queue<
            Evento,
            std::vector<Evento>,
            std::greater<Evento>
        > m_eventos;
        Reloj& m_reloj;
};