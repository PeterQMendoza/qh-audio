#include "bld_archivo_wav.hpp"

#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>

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
    if (canales == 0 || canales > 4){
        throw std::invalid_argument("Canales permitidos: 1 a 4");
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
    IGeneradorMulticanal& generador
){
    m_generador = &generador;
    // m_canales = generador.canales();// sicronizacion automatica
    return *this;
}

void ConstructorArchivoWav::construir(const std::string& filename){
    if(!m_generador){
        throw std::runtime_error("Generador de muestra no definido");
    }

    EscrituraBinaria escritor(filename);

    const std::uint32_t totalFrames = m_tasaMuestra * m_segundosDuracion;
    
    const std::uint32_t sizeFragmentoDato = totalFrames * blockAlign();

    escribirCabecera(escritor, sizeFragmentoDato);
    escribirDatos(escritor, totalFrames);
}

void ConstructorArchivoWav::escribirCabecera(
    EscrituraBinaria& escritor,
    std::uint32_t sizeData
) const {
    const std::uint32_t riffSize = 36 + sizeData;

    escritor.escribirCadena("RIFF");
    escritor.escribir(riffSize);
    escritor.escribirCadena("WAVE");

    escritor.escribirCadena("fmt ");
    escritor.escribir<std::uint32_t>(16);
    escritor.escribir<std::uint16_t>(1);
    escritor.escribir(m_canales);
    escritor.escribir(m_tasaMuestra);
    escritor.escribir(byteRate());
    escritor.escribir(blockAlign());
    escritor.escribir(m_bitProfundidad);

    escritor.escribirCadena("data");
    escritor.escribir(sizeData);
}

void ConstructorArchivoWav::escribirDatos(
    EscrituraBinaria& escritor,
    std::uint32_t totalFrames
) const {
    for (std::uint32_t i = 0; i < totalFrames; ++i){
        escribirFrame(escritor, m_generador->siguienteFrame());
    }
}

void ConstructorArchivoWav::escribirMuestra(
    EscrituraBinaria& escritor,
    double muestra
) const {
    const double clamped = std::clamp(muestra, -1.0, 1.0);

    switch (m_bitProfundidad)
    {
        case 8:
        {
            // PCM 8-bit es unsigned
            const std::uint8_t sample = static_cast<std::uint8_t>(
                (clamped + 1.0) * 127.5
            );

            escritor.escribir(sample);

            break;
        }

        case 16:
        {
            constexpr double maxAmp = 32767.0;
            const std::int16_t sample = static_cast<std::int16_t>(clamped * maxAmp);

            escritor.escribir(sample);
            break;
        }

        case 24:
        {
            constexpr double maxAmp = 8388607.0;

            std::int32_t sample =
                static_cast<std::int32_t>(clamped * maxAmp);

            escritor.escribir24Bits(sample);
            break;
        }

        case 32:
        {
            constexpr double maxAmp = 2147483647.0;

            const std::int32_t sample =
                static_cast<std::int32_t>(clamped * maxAmp);

            escritor.escribir(sample);
            break;
        }

        default:
            throw std::runtime_error(
                "Bit profundidad no soportada"
            );
    }
}

void ConstructorArchivoWav::escribirFrame(
    EscrituraBinaria& escritor,
    const std::vector<double>& frame
) const
{
    // std::cout << "Esperados: " << m_canales << " Recibidos: " << frame.size() << std::endl;
    if (frame.size() != m_canales)
        throw std::runtime_error("Frame inconsistente");

    for (double muestra : frame)
    {
        const double clamped =
            std::clamp(muestra, -1.0, 1.0);

        escribirMuestra(escritor, clamped);
    }
}

std::uint16_t ConstructorArchivoWav::blockAlign() const noexcept
{
    return m_canales * (m_bitProfundidad / 8);
}

std::uint32_t ConstructorArchivoWav::byteRate() const noexcept
{
    return m_tasaMuestra * blockAlign();
}
