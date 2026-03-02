#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"

#include "adsr.hpp"
#include "bld_archivo_wav.hpp"
#include "reloj.hpp"
#include "programador.hpp"

#include <cstdint>
#include <string>

class MotorRender final {
    private:
        IGeneradorMulticanal& m_generador;
        ADSR& m_env;
        ConstructorArchivoWav& m_wav;

        std::uint32_t m_tasaMuestra;
        std::uint32_t m_duracion;
        std::uint64_t m_totalFrames;

        Reloj m_reloj;
        Programador m_programador;
        
        void programarEventosIniciales(double bpm);
    public:
        MotorRender(
            IGeneradorMulticanal& generador,
            ADSR& envolvente,
            ConstructorArchivoWav& wav,
            std::uint32_t tasaMuestra,
            std::uint32_t duracionSegundos,
            double bpm
        );

        void renderizar(const std::string& archivo);

        void procesarAudio(
            EscrituraBinaria& escritor,
            std::uint32_t totalFrames
        );

};