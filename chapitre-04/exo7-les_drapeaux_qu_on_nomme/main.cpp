#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
    const std::uint32_t RENDER2D = 1;
    const std::uint32_t RENDER3D = 2;
    const std::uint32_t TEXT = 4;
    const std::uint32_t UI = 8;
    const std::uint32_t SHADOW = 16;
    const std::uint32_t POST_PROCESS = 32;
    const std::uint32_t OVERLAY = 256;
    const std::uint32_t SIMULATION = 512;

    const std::map<std::string, std::uint32_t> valeurs = {
        {"RENDER2D", 1},
        {"RENDER3D", 2},
        {"TEXT", 4},
        {"UI", 8},
        {"SHADOW", 16},
        {"POST_PROCESS", 32},
        {"VFX", 64},
        {"ANIMATION", 128},
        {"OVERLAY", 256},
        {"SIMULATION", 512},
        {"OFFSCREEN", 1024},
        {"RAYTRACING", 2048},
        {"GPU_CULLING", 4096},
        {"NONE", 0},
        {"2D_ESSENTIALS", RENDER2D | TEXT},
        {"3D_BASE", RENDER3D | SHADOW | POST_PROCESS},
        {"DEBUG", OVERLAY | SIMULATION},
        {"ALL", 4294967295u},
    };

    int n = 0;
    std::cin >> n;

    std::uint32_t valeur = 0;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        std::cin >> nom;
        const auto it = valeurs.find(nom);
        if (it == valeurs.end()) {
            std::cout << "INCONNU " << nom << "\n";
        } else {
            valeur |= it->second;
        }
    }

    if (n == 0) {
        valeur = 4294967295u;
    }

    std::cout << "VALEUR " << valeur << "\n";

    char hexa[16];
    std::snprintf(hexa, sizeof(hexa), "0x%08X", static_cast<unsigned int>(valeur));
    std::cout << "HEXA " << hexa << "\n";

    struct Besoin {
        const char* nom;
        std::uint32_t bit;
        std::vector<std::pair<const char*, std::uint32_t>> dependances;
    };
    const std::vector<Besoin> besoins = {
        {"TEXT", TEXT, {{"RENDER2D", RENDER2D}}},
        {"UI", UI, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}},
        {"SHADOW", SHADOW, {{"RENDER3D", RENDER3D}}},
        {"OVERLAY", OVERLAY, {{"RENDER2D", RENDER2D}, {"TEXT", TEXT}}},
    };

    for (const Besoin& b : besoins) {
        if ((valeur & b.bit) == 0) {
            continue;
        }
        for (const auto& d : b.dependances) {
            if ((valeur & d.second) == 0) {
                std::cout << "MANQUE " << b.nom << " " << d.first << "\n";
            }
        }
    }

    int allumes = 0;
    for (int bit = 0; bit < 13; ++bit) {
        if ((valeur >> bit) & 1u) {
            ++allumes;
        }
    }

    std::cout << "ALLUMES " << allumes << "\n";
    std::cout << "ETEINTS " << (13 - allumes) << "\n";
    return 0;
}
