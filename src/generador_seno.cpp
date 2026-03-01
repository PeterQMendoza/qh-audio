#include "generador_seno.hpp"

GeneradorSeno::GeneradorSeno(
    double frecuencia,
    double amplitud,
    double tasaMuestra
) noexcept
: m_oscilador(
    static_cast<float>(frecuencia),
    static_cast<float>(amplitud),
    static_cast<float>(tasaMuestra)
) {

}

double GeneradorSeno::siguienteMuestra() noexcept {
    return static_cast<double>(m_oscilador.proceso());
}