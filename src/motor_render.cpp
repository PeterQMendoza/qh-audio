#include "motor_render.hpp"

#include <stdexcept>

MotorRender::MotorRender(
    IGeneradorMuestra& generador,
    ADSR& envolvente,
    ConstructorArchivoWav& wav,
    std::uint32_t tasaMuestra,
    std::uint32_t duracionSegundos
)
: m_generador(generador),
m_env(envolvente),
m_wav(wav),
m_tasaMuestra(tasaMuestra),
m_duracion(duracionSegundos) {
    
}


void MotorRender::renderizar(const std::string& archivo)
{
    if (m_duracion == 0){
        throw std::runtime_error("Duracion invalida");
    }

    // Configurar wav
    m_wav.setDuracion(m_duracion);
    m_wav.setTasaMuestra(m_tasaMuestra);
    m_wav.setGenerador(m_generador);

    // Evento musical
    m_env.noteOn();
    m_wav.construir(archivo);
}