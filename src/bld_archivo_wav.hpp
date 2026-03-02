#pragma once

#include "i_generador_muestra.hpp"
#include "i_generador_multicanal.hpp"
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
        IGeneradorMulticanal* m_generador{nullptr};

        
    public:
        ConstructorArchivoWav& setTasaMuestra(std::uint32_t tasa);
        
        ConstructorArchivoWav& setBitProfundidad(std::uint16_t profundidad);
        
        ConstructorArchivoWav& setCanales(std::uint16_t canales);
        
        ConstructorArchivoWav& setDuracion(std::uint32_t segundos);
        
        ConstructorArchivoWav& setGenerador(IGeneradorMulticanal& generador);

        void construir(const std::string& filename);

        [[nodiscard]]
        std::uint16_t blockAlign() const noexcept;

        [[nodiscard]]
        std::uint32_t byteRate() const noexcept;
        
        void escribirCabecera(
            EscrituraBinaria& escritor,
            std::uint32_t sizeData
        ) const;

        void escribirMuestra(
            EscrituraBinaria& escritor,
            double muestra
        ) const;

        void escribirDatos(
            EscrituraBinaria& escritor,
            std::uint32_t totalFrames
        ) const;

        void escribirFrame(
            EscrituraBinaria& escritor,
            const std::vector<double>& frame
        ) const;
};