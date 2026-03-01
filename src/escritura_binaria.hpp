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