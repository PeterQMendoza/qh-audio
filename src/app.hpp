#pragma once

#include "i_generador_muestra.hpp"
#include "bld_archivo_wav.hpp"
#include "adsr.hpp"
#include "vca.hpp"
#include "motor_render.hpp"

#include <vector>
#include <memory>

class App {
    private:
        std::unique_ptr<IGeneradorMuestra> m_generador;
        std::unique_ptr<ConstructorArchivoWav> m_constuctor;
        std::unique_ptr<ADSR> m_env;
        std::unique_ptr<VCA> m_vca;
        std::unique_ptr<MotorRender> m_motor;

        const double m_tasaMuestra = 44100.0;
        const int m_duracion = 3;
    public:
        App();
        int ejecutar();
};