#include "app.hpp"
#include "generador_seno.hpp"

#include <iostream>

App::App(){
    m_generador = std::make_unique<GeneradorSeno>(440.0, 0.5, 44100.0);
    m_constuctor = std::make_unique<ConstructorArchivoWav>();

}

int App::ejecutar(){
    try{
        m_constuctor->setTasaMuestra(44100);
        m_constuctor->setBitProfundidad(16);
        m_constuctor->setCanales(1);
        m_constuctor->setDuracion(3);
        m_constuctor->setGenerador(*m_generador);
        m_constuctor->construir("waveform.wav");

        return EXIT_SUCCESS;
    }
    catch(const std::exception& e){
        std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

