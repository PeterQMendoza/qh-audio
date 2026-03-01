#pragma once

class IGeneradorMuestra {
    // Interfaz que permite cambiar el tipo de oscilador
    public:
        virtual ~IGeneradorMuestra() = default;
        virtual double siguienteMuestra() = 0;
};