#include "motor_render.hpp"

#include <stdexcept>

MotorRender::MotorRender(
    IGeneradorMulticanal& generador,
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
    if (m_tasaMuestra == 0){
        throw std::invalid_argument("Tasa de muestra invalida");
    }

    if (m_duracion == 0){
        throw std::invalid_argument("Duracion invalida");
    }
}

void MotorRender::renderizar(const std::string& archivo)
{
    const std::uint32_t totalFrames = m_tasaMuestra * m_duracion;

    // Configuración del WAV (fluent API)
    m_wav.setDuracion(m_duracion);
    m_wav.setTasaMuestra(m_tasaMuestra);
    m_wav.setGenerador(m_generador);

    EscrituraBinaria escritor(archivo);

    const std::uint32_t dataSize = totalFrames * m_wav.blockAlign();

    m_wav.escribirCabecera(escritor, dataSize);

    procesarAudio(escritor, totalFrames);
}

void MotorRender::procesarAudio(
    EscrituraBinaria& escritor,
    std::uint32_t totalFrames
)
{
    m_env.noteOn();

    const std::uint32_t noteOffFrame =
        static_cast<std::uint32_t>(m_tasaMuestra * 2.0);

    for (std::uint32_t i = 0; i < totalFrames; ++i)
    {
        if (i == noteOffFrame){
            m_env.noteOff();
        }

        auto frame = m_generador.siguienteFrame();

        m_wav.escribirFrame(escritor, frame);
    }
}