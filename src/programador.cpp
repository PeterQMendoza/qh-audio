#include "programador.hpp"

Programador::Programador(Reloj& reloj)
: m_reloj(reloj) {

}

void Programador::programar(
    std::uint64_t tiempoMuestra,
    std::function<void()> accion
)
{
    m_eventos.push({ tiempoMuestra, std::move(accion) });
}

void Programador::procesar(std::uint64_t muestraActual)
{
    while (
        !m_eventos.empty() &&
        m_eventos.top().tiempoMuestra <= muestraActual
    )
    {
        auto evento = m_eventos.top();
        m_eventos.pop();
        evento.accion();
    }
}

bool Programador::vacio() const noexcept
{
    return m_eventos.empty();
}