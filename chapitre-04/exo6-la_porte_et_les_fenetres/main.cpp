#include <iostream>
#include <string>

int main() {
    long long W = 0;
    long long H = 0;
    long long seuil = 0;
    std::cin >> W >> H >> seuil;

    int n = 0;
    std::cin >> n;

    int ok = 0;
    int aReprendre = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long u = 0;
        long long y = 0;
        long long l = 0;
        long long h = 0;
        long long e = 0;
        long long d = 0;
        std::cin >> nom >> u >> y >> l >> h >> e >> d;

        const long long saillie = d + e / 2;
        const long long faceArriere = d - e / 2;

        std::string verdict;
        if (2 * u - l < -W || 2 * u + l > W || 2 * y - h < 0 || 2 * y + h > 2 * H) {
            verdict = "DEBORDE";
        } else if (saillie <= 0) {
            verdict = "INVISIBLE";
        } else if (saillie < seuil) {
            verdict = "CLIGNOTE";
        } else if (faceArriere > seuil) {
            verdict = "DECOLLE";
        } else {
            verdict = "OK";
        }

        std::cout << nom << " " << saillie << " " << verdict << "\n";

        if (verdict == "OK") {
            ++ok;
        } else {
            ++aReprendre;
        }
    }

    std::cout << "OK " << ok << "\n";
    std::cout << "A REPRENDRE " << aReprendre << "\n";
    return 0;
}
