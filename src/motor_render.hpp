#pragma once

#include "i_generador_muestra.hpp"
#include "adsr.hpp"
#include "bld_archivo_wav.hpp"

#include <cstdint>
#include <string>

class MotorRender final {
    private:
        IGeneradorMuestra& m_generador;
        ADSR& m_env;
        ConstructorArchivoWav& m_wav;
        std::uint32_t m_tasaMuestra;
        std::uint32_t m_duracion;

    public:
        MotorRender(
            IGeneradorMuestra& generador,
            ADSR& envolvente,
            ConstructorArchivoWav& wav,
            std::uint32_t tasaMuestra,
            std::uint32_t duracionSegundos
        );

        void renderizar(const std::string& archivo);
};