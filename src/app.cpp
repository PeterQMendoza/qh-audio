#include "app.hpp"
#include "generador_seno.hpp"

#include <iostream>

App::App(){
    m_generador = std::make_unique<GeneradorSeno>(440.0, 0.5, m_tasaMuestra);
    m_env = std::make_unique<ADSR>(0.1, 0.2, 0.7, 0.3, m_tasaMuestra);
    m_vca = std::make_unique<VCA>(*m_generador, *m_env);

    m_constuctor = std::make_unique<ConstructorArchivoWav>();
    m_motor = std::make_unique<MotorRender>(*m_vca, *m_env, *m_constuctor, m_tasaMuestra, m_duracion);

}

int App::ejecutar(){
    try{
        m_constuctor->setTasaMuestra(m_tasaMuestra);
        m_constuctor->setBitProfundidad(16);
        m_constuctor->setCanales(1);
        m_constuctor->setDuracion(m_duracion);
        // m_constuctor->setGenerador(*m_generador);
        
        m_motor->renderizar("waveform.wav");

        return EXIT_SUCCESS;
    }
    catch(const std::exception& e){
        std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

