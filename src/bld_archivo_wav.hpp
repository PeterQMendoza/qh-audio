#pragma once

#include "i_generador_muestra.hpp"
#include "escritura_binaria.hpp"

#include <vector>
#include <cmath>
#include <cstdint>
#include <string>

class ConstructorArchivoWav {
    private:
        std::uint32_t m_tasaMuestra{44100};
        std::uint16_t m_bitProfundidad{16};
        std::uint16_t m_canales{1};
        std::uint32_t m_segundosDuracion{1};
        IGeneradorMuestra* m_generador{nullptr};
    public:
        ConstructorArchivoWav& setTasaMuestra(std::uint32_t tasa);
        
        ConstructorArchivoWav& setBitProfundidad(std::uint16_t profundidad);
        
        ConstructorArchivoWav& setCanales(std::uint16_t canales);

        ConstructorArchivoWav& setDuracion(std::uint32_t segundos);

        ConstructorArchivoWav& setGenerador(IGeneradorMuestra& generador);

        void construir(const std::string& filename);
};