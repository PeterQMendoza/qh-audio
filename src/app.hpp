#pragma once

#include "i_generador_muestra.hpp"
#include "bld_archivo_wav.hpp"

#include <vector>
#include <memory>

class App {
    private:
        std::unique_ptr<IGeneradorMuestra> m_generador;
        std::unique_ptr<ConstructorArchivoWav> m_constuctor;
    public:
        App();
        int ejecutar();
};