#pragma once
#include <vector>
#include <cstdint>

class IGeneradorMulticanal {
    public:
        virtual ~IGeneradorMulticanal() = default;

        virtual std::vector<double> siguienteFrame() = 0;
        virtual std::uint16_t canales() const = 0;
};