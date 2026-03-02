#include <cstdint>
#include <function>

struct Evento {
    std::uint64_t tiempoMuestra;
    std::function<void()> accion;

    bool operator>(const Evento& otro) const {
        return tiempoMuestra > otro.tiempoMuestra;
    }
};