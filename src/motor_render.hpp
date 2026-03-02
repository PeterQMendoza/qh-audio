#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"

#include "adsr.hpp"
#include "bld_archivo_wav.hpp"

#include <cstdint>
#include <string>

class MotorRender final {
    private:
        IGeneradorMulticanal& m_generador;
        ADSR& m_env;
        ConstructorArchivoWav& m_wav;
        std::uint32_t m_tasaMuestra;
        std::uint32_t m_duracion;

    public:
        MotorRender(
            IGeneradorMulticanal& generador,
            ADSR& envolvente,
            ConstructorArchivoWav& wav,
            std::uint32_t tasaMuestra,
            std::uint32_t duracionSegundos
        );

        void renderizar(const std::string& archivo);

        void procesarAudio(
            EscrituraBinaria& escritor,
            std::uint32_t totalFrames
        );
};