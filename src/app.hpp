#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"

#include "generador_binaural.hpp"
#include "bld_archivo_wav.hpp"
#include "adsr.hpp"
#include "vca.hpp"
#include "motor_render.hpp"
#include "mezclador.hpp"

#include <vector>
#include <memory>

class App {
    private:
        std::shared_ptr<IGeneradorMuestra> m_generador1;
        std::unique_ptr<IGeneradorMuestra> m_generador2;
        std::unique_ptr<IGeneradorMuestra> m_generador3;
        std::unique_ptr<IGeneradorMuestra> m_generador4;

        std::unique_ptr<GeneradorBinaural> m_binaural;

        std::unique_ptr<IGeneradorMulticanal> m_stereo;
        // std::unique_ptr<IGeneradorMulticanal> m_generador_quad;

        std::unique_ptr<Mezclador> m_mezclador;
        
        std::unique_ptr<ConstructorArchivoWav> m_constuctor;
        std::unique_ptr<ADSR> m_env;
        std::unique_ptr<VCA> m_vca;
        std::unique_ptr<MotorRender> m_motor;

        const std::uint32_t m_tasaMuestra = 44100;
        const int m_duracion = 3;
    public:
        App();
        int ejecutar();
};