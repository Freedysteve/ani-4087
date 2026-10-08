#include <iostream>
#include <string>
#include <cstdlib>

int main() {
    int n = 0;
    std::cin >> n;

    int aCorriger = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long e = 0;
        long long y = 0;
        std::cin >> nom >> e >> y;

        const long long demiHauteur = e / 2;
        const long long bas = y - demiHauteur;
        const long long haut = y + demiHauteur;

        std::string verdict;
        if (haut <= 0) {
            verdict = "SOUS LE SOL";
        } else if (bas < 0) {
            verdict = "ENTERRE";
        } else if (bas == 0) {
            verdict = "POSE";
        } else {
            verdict = "FLOTTE";
        }

        std::cout << nom << " " << bas << " " << haut << " " << verdict << " " << demiHauteur << "\n";

        if (verdict != "POSE") {
            ++aCorriger;
        }

        const long long ecart = std::llabs(bas);
        if (ecart > pire) {
            pire = ecart;
        }
    }

    std::cout << "A CORRIGER " << aCorriger << "\n";
    std::cout << "PIRE " << pire << "\n";

    return 0;
}
