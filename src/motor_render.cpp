#include "motor_render.hpp"

#include <stdexcept>

MotorRender::MotorRender(
    IGeneradorMulticanal& generador,
    ADSR& envolvente,
    ConstructorArchivoWav& wav,
    std::uint32_t tasaMuestra,
    std::uint32_t duracionSegundos,
    double bpm
)
: m_generador(generador),
m_env(envolvente),
m_wav(wav),
m_tasaMuestra(tasaMuestra),
m_duracion(duracionSegundos),
m_reloj(bpm, tasaMuestra),// 80 bpm
m_programador(m_reloj),
m_totalFrames(static_cast<std::uint64_t>(tasaMuestra) * duracionSegundos)
{
    if (m_tasaMuestra == 0){
        throw std::invalid_argument("Tasa de muestra invalida");
    }

    if (m_duracion == 0){
        throw std::invalid_argument("Duracion invalida");
    }


    programarEventosIniciales(bpm);
}

void MotorRender::programarEventosIniciales(double bpm)
{
    const std::uint64_t muestraPorBeat = static_cast<std::uint64_t>((60.0 / bpm) * m_tasaMuestra);

    const std::uint64_t totalBeats = m_totalFrames / muestraPorBeat;

    for (std::uint64_t i = 0; i < totalBeats; ++i)
    {
        std::uint64_t tiempo = i * muestraPorBeat;

        m_programador.programar(
            tiempo,
            [this]() {
                m_env.noteOn();
            }
        );
    }
}

void MotorRender::renderizar(const std::string& archivo)
{
    // Configuración del WAV (fluent API)
    m_wav.setDuracion(m_duracion);
    m_wav.setTasaMuestra(m_tasaMuestra);
    m_wav.setGenerador(m_generador);

    EscrituraBinaria escritor(archivo);

    const std::uint32_t dataSize = m_totalFrames * m_wav.blockAlign();

    m_wav.escribirCabecera(escritor, dataSize);

    procesarAudio(escritor, m_totalFrames);
}

void MotorRender::procesarAudio(
    EscrituraBinaria& escritor,
    std::uint32_t totalFrames
)
{
    
    const std::uint32_t noteOffFrame = static_cast<std::uint32_t>(m_tasaMuestra * 2.0);
    
    for (std::uint32_t i = 0; i < totalFrames; ++i){
        const std::uint64_t muestraActual = m_reloj.muestraActual();

        // Eecutar eventos programados
        m_programador.procesar(muestraActual);

        // Disparo exacto en el beat
        if (m_reloj.esBeat()){
            m_env.noteOn();
        }

        
        if (i == noteOffFrame){
            m_env.noteOff();
        }
        
        auto frame = m_generador.siguienteFrame();
        
        // aplicar envolve a cada canal
        double amp = m_env.siguienteMuestra();// avanzar envelope

        for (auto& muestra : frame){
            muestra *= amp;
        }

        m_wav.escribirFrame(escritor, frame);

        m_reloj.avanzar();
    }
}