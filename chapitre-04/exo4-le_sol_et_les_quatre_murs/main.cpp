#include <iostream>
#include <string>
#include <vector>

struct Emprise {
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

struct Angle {
    const char* nom;
    long long xmin;
    long long xmax;
    long long zmin;
    long long zmax;
};

int main() {
    long long L = 0;
    long long e = 0;
    std::cin >> L >> e;

    int n = 0;
    std::cin >> n;

    std::vector<Emprise> murs;
    for (int i = 0; i < n; ++i) {
        std::string nom;
        long long cx = 0;
        long long cz = 0;
        long long sx = 0;
        long long sz = 0;
        std::cin >> nom >> cx >> cz >> sx >> sz;

        Emprise m;
        m.xmin = cx - sx / 2;
        m.xmax = cx + sx / 2;
        m.zmin = cz - sz / 2;
        m.zmax = cz + sz / 2;
        murs.push_back(m);

        std::cout << nom << " " << m.xmin << " " << m.xmax << " " << m.zmin << " " << m.zmax << "\n";
    }

    const long long h = L / 2;
    const Angle angles[4] = {
        {"FOND_GAUCHE", -h - e, -h, -h - e, -h},
        {"FOND_DROIT", h, h + e, -h - e, -h},
        {"ENTREE_GAUCHE", -h - e, -h, h, h + e},
        {"ENTREE_DROIT", h, h + e, h, h + e},
    };

    int trous = 0;
    for (const Angle& a : angles) {
        bool bouche = false;
        for (const Emprise& m : murs) {
            if (m.xmin <= a.xmin && m.xmax >= a.xmax && m.zmin <= a.zmin && m.zmax >= a.zmax) {
                bouche = true;
                break;
            }
        }
        std::cout << a.nom << " " << (bouche ? "BOUCHE" : "TROU") << "\n";
        if (!bouche) {
            ++trous;
        }
    }

    std::cout << "TROUS " << trous << "\n";
    return 0;
}
