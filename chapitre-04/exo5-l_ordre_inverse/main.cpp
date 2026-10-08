#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>

int main() {
    int n = 0;
    std::cin >> n;

    int deplaces = 0;
    long long pire = 0;

    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long tx = 0;
        long long ty = 0;
        long long tz = 0;
        long long sx = 0;
        long long sy = 0;
        long long sz = 0;
        std::cin >> nom >> tx >> ty >> tz >> sx >> sy >> sz;

        const long long x = sx * tx / 1000;
        const long long y = sy * ty / 1000;
        const long long z = sz * tz / 1000;

        const long long ecart = std::max({std::llabs(tx - x), std::llabs(ty - y), std::llabs(tz - z)});

        std::cout << nom << " " << x << " " << y << " " << z << " " << ecart << "\n";

        if (ecart != 0) {
            ++deplaces;
        }
        if (ecart > pire) {
            pire = ecart;
        }
    }

    std::cout << "DEPLACES " << deplaces << "\n";
    std::cout << "PIRE " << pire << "\n";
    return 0;
}
