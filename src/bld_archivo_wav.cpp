#include "bld_archivo_wav.hpp"

#include <stdexcept>
#include <algorithm>

ConstructorArchivoWav& ConstructorArchivoWav::setTasaMuestra(
    std::uint32_t tasa
){
    if (tasa == 0){
        throw std::invalid_argument("La tasa de muestra no puede ser 0");
    }
    m_tasaMuestra = tasa;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setBitProfundidad(
    std::uint16_t profundidad
){
    if (profundidad != 8 &&
        profundidad != 16 &&
        profundidad != 24 &&
        profundidad != 32)
    {
        throw std::invalid_argument(
            "Bit profundidad no soportada (8,16,24,32)"
        );
    }

    m_bitProfundidad = profundidad;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setCanales(
    std::uint16_t canales
){
    if (canales == 0){
        throw std::invalid_argument("Numero de canales invalido");
    }
    m_canales = canales;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setDuracion(
    std::uint32_t duracion
){
    if (duracion == 0){
        throw std::invalid_argument("Duracion no valida");
    }
    m_segundosDuracion = duracion;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setGenerador(
    IGeneradorMuestra& generador
){
    m_generador = &generador;
    return *this;
}

void ConstructorArchivoWav::construir(const std::string& filename){
    if(!m_generador){
        throw std::runtime_error("Generador de muestra no definido");
    }

    EscrituraBinaria escritor(filename);

    const std::uint32_t totalMuestras = m_tasaMuestra * m_segundosDuracion;
    const std::uint16_t alinearBloque = m_canales * (m_bitProfundidad / 8);

    const std::uint32_t sizeFragmentoDato = totalMuestras * alinearBloque;

    escribirCabecera(escritor, sizeFragmentoDato);
    escribirMuestra(escritor, totalMuestras);
}

void ConstructorArchivoWav::escribirCabecera(
    EscrituraBinaria& escritor,
    std::uint32_t sizeData
) const {
    const std::uint16_t blockAlign =
        m_canales * (m_bitProfundidad / 8);

    const std::uint32_t byteRate =
        m_tasaMuestra * blockAlign;

    const std::uint32_t riffSize =
        36 + sizeData;

    escritor.escribirCadena("RIFF");
    escritor.escribir(riffSize);
    escritor.escribirCadena("WAVE");

    escritor.escribirCadena("fmt ");
    escritor.escribir<std::uint32_t>(16);
    escritor.escribir<std::uint16_t>(1);
    escritor.escribir(m_canales);
    escritor.escribir(m_tasaMuestra);
    escritor.escribir(byteRate);
    escritor.escribir(blockAlign);
    escritor.escribir(m_bitProfundidad);

    escritor.escribirCadena("data");
    escritor.escribir(sizeData);
}

void ConstructorArchivoWav::escribirMuestra(
    EscrituraBinaria& escritor,
    std::uint32_t totalMuestra
) const {
    for (std::uint32_t i = 0; i < totalMuestra; ++i)
    {
        double muestra = m_generador->siguienteMuestra();
        muestra = std::clamp(muestra, -1.0, 1.0);

        switch (m_bitProfundidad)
        {
            case 16:
            {
                constexpr double maxAmp = 32767.0;
                const std::int16_t sample =
                    static_cast<std::int16_t>(muestra * maxAmp);

                for (std::uint16_t c = 0; c < m_canales; ++c){
                    escritor.escribir(sample);
                }
                break;
            }

            case 8:
            {
                // PCM 8-bit es unsigned
                const std::uint8_t sample =
                    static_cast<std::uint8_t>(
                        (muestra + 1.0) * 127.5
                    );

                for (std::uint16_t c = 0; c < m_canales; ++c){
                    escritor.escribir(sample);
                }
                break;
            }

            default:
                throw std::runtime_error(
                    "Bit profundidad no implementada"
                );
        }
    }
}
