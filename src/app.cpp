#include "app.hpp"
#include "generador_seno.hpp"
#include "generador_stereo.hpp"

#include "generador_quad.hpp"

#include <iostream>

App::App(){
    m_generador1 = std::make_shared<GeneradorSeno>(440.0, 0.5, m_tasaMuestra);
    m_generador2 = std::make_unique<GeneradorSeno>(442.0, 0.5, m_tasaMuestra);
    // m_generador3 = std::make_unique<GeneradorSeno>(420.0, 0.5, m_tasaMuestra);
    // m_generador4 = std::make_unique<GeneradorSeno>(452.0, 0.5, m_tasaMuestra);
    
    m_stereo = std::make_unique<GeneradorStereo>(*m_generador1, *m_generador2);
    // m_generador_quad = std::make_unique<GeneradorQuad>(*m_generador1, *m_generador2,*m_generador3, *m_generador4);

    m_binaural = std::make_unique<GeneradorBinaural>(m_generador1, m_tasaMuestra);
    m_binaural->setAzimuth(-45.0);

    m_mezclador= std::make_unique<Mezclador>();
    m_mezclador->agregarEntrada(*m_generador1);
    m_mezclador->agregarEntrada(*m_generador2);

    m_env = std::make_unique<ADSR>(0.1, 0.2, 0.7, 0.3, m_tasaMuestra);

    m_vca = std::make_unique<VCA>(2); // 4
    m_vca->setEntradaAudio(*m_mezclador);
    m_vca->setModulador(*m_env);

    m_constuctor = std::make_unique<ConstructorArchivoWav>();
    m_motor = std::make_unique<MotorRender>(*m_vca, *m_env, *m_constuctor, m_tasaMuestra, m_duracion);

}

int App::ejecutar(){
    try{
        m_constuctor->setTasaMuestra(m_tasaMuestra);
        m_constuctor->setBitProfundidad(16);
        m_constuctor->setCanales(2);
        m_constuctor->setDuracion(m_duracion);
        m_constuctor->setGenerador(*m_binaural);
        
        m_motor->renderizar("waveform.wav");

        return EXIT_SUCCESS;
    }
    catch(const std::exception& e){
        std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

