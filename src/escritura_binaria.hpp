#pragma once

#include <fstream>
#include <cstdint>
#include <stdexcept>

class EscrituraBinaria {
    private:
        std::ofstream m_archivo;

    public:
        explicit EscrituraBinaria(const std::string& ruta){
            m_archivo.open(ruta, std::ios::binary);
            if (!m_archivo){
                throw std::runtime_error("No se pudo abrir el archivo");
            }
        }

        void escribirCadena(const std::string& texto){
            m_archivo.write(texto.c_str(), texto.size());
        }

        template<typename T>
        void escribir(T valor){
            m_archivo.write(reinterpret_cast<const char*>(&valor), sizeof(T));
        }

        void escribir24Bits(std::int32_t valor){
            // Asegurar rango 24-bit signed
            valor = std::clamp(valor, -8388608, 8388607);

            std::uint8_t buffer[3];

            buffer[0] = static_cast<std::uint8_t>( valor & 0xFF);
            buffer[1] = static_cast<std::uint8_t>((valor >> 8) & 0xFF);
            buffer[2] = static_cast<std::uint8_t>((valor >> 16) & 0xFF);

            m_archivo.write(reinterpret_cast<const char*>(buffer), 3);

            if (!m_archivo){
                throw std::runtime_error("Error escribiendo muestra 24-bit");
            }
        }

        std::streampos posicion(){
            return m_archivo.tellp();
        }

        void buscar(std::streampos posicion){
            m_archivo.seekp(posicion);
        }

        void buscar(
            std::streamoff desplazamiento,
            std::ios_base::seekdir directorio
        ){
            m_archivo.seekp(desplazamiento, directorio);
        }
};