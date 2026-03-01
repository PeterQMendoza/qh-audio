#include "bld_archivo_wav.hpp"

#include <stdexcept>

ConstructorArchivoWav& ConstructorArchivoWav::setTasaMuestra(
    std::uint32_t tasa
){
    m_tasaMuestra = tasa;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setBitProfundidad(
    std::uint16_t profundidad
){
    m_bitProfundidad = profundidad;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setCanales(
    std::uint16_t canales
){
    m_canales = canales;
    return *this;
}

ConstructorArchivoWav& ConstructorArchivoWav::setDuracion(
    std::uint32_t duracion
){
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
    const std::uint32_t tasaByte = m_tasaMuestra * alinearBloque;
    const std::uint32_t sizeFragmentoDato = totalMuestras * alinearBloque;
    const std::uint32_t sizeFragmentoRiff = 36 + sizeFragmentoDato;

    // === Cabecera RIFF==
    escritor.escribirCadena("RIFF");
    escritor.escribir(sizeFragmentoRiff);
    escritor.escribirCadena("WAVE");

    // === FORMATO CHUNK ===
    escritor.escribirCadena("fmt ");
    escritor.escribir<std::uint32_t>(16);// tama;o de cabecera PCM
    escritor.escribir<std::uint16_t>(1);// formato PCM
    escritor.escribir(m_canales);
    escritor.escribir(m_tasaMuestra);
    escritor.escribir(tasaByte);
    escritor.escribir(alinearBloque);
    escritor.escribir(m_bitProfundidad);

    // === Fragmento de datos ===
    escritor.escribirCadena("data");
    escritor.escribir(sizeFragmentoDato);

    const double maxAmplitud = std::pow(2, m_bitProfundidad - 1) - 1;

    for (std::uint32_t i =0; i < totalMuestras; ++i){
        double muestra = m_generador->siguienteMuestra();
        std::int16_t intMuestra = static_cast<std::int16_t>(muestra * maxAmplitud);

        escritor.escribir(intMuestra);
    }
}