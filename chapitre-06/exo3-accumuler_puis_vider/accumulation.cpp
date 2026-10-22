// Symptôme : la tête tourne toute seule, lentement, quand la souris est immobile, et l'on accuse sa souris.
// Cause : NkInput.MouseRawDeltaX() garde le déplacement du dernier événement brut et ne le remet jamais à zéro ; l'ajouter à chaque image rejoue ce dernier mouvement sans fin.
// Preuve : souris immobile, la valeur lue reste non nulle à chaque relevé et l'angle continue de varier ; le module voisin le confirme (NkEventState : OnRaw écrase, personne ne consomme).
// Correction : s'abonner aux événements bruts, les accumuler soi-même, lire le total une seule fois par image, puis le remettre à zéro.

#include "NKWindow/NKWindow.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKEvent/NkMouseEvent.h"
#include "NKTime/NkChrono.h"

#include <chrono>
#include <cstdio>
#include <thread>

using namespace nkentseu;

int main() {
    NkInitialise();

    NkWindowConfig cfg;
    cfg.title  = "Accumulation";
    cfg.width  = 1280;
    cfg.height = 720;

    NkWindow fenetre(cfg);
    if (!fenetre.IsValid()) {
        return 1;
    }

    fenetre.ShowMouse(false);
    fenetre.CaptureMouse(true);
    fenetre.ClipMouseToClient(true);

    const float SENSIBILITE = 0.002f;     // radians par compte du capteur
    const float DEGRES_PAR_RADIAN = 57.2957795f;

    // Trois lacets, tous nourris par les memes evenements.
    float lacetLu = 0.f;          // 1 : lecture directe du module (fautive)
    float lacetVide = 0.f;        // 2 : accumule, lu une fois par image, puis vide
    float lacetSansVidage = 0.f;  // 3 : accumule et lu, mais jamais vide

    // Un seul des trois pilote la camera : le deuxieme (lacetVide).
    // Dans ce programme il n'y a pas de salle, les deux autres sont seulement calcules.

    int accumVide = 0;            // accumulateur de la version 2
    int accumSansVidage = 0;      // accumulateur de la version 3

    NkChrono horloge;
    double prochainReleve = 1.0;
    bool quitter = false;

    while (fenetre.IsOpen() && !quitter) {
        // Les evenements arrivent quand ils veulent : plusieurs par image, ou aucun.
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (auto* brut = ev->As<NkMouseRawEvent>()) {
                accumVide += brut->GetDeltaX();
                accumSansVidage += brut->GetDeltaX();
            }
            if (auto* appui = ev->As<NkKeyPressEvent>()) {
                if (appui->GetKey() == NkKey::NK_ESCAPE) {
                    quitter = true;
                }
            }
        }

        // 1 : version fautive.
        lacetLu += NkInput.MouseRawDeltaX() * SENSIBILITE;

        // 2 : on lit l'accumulation une fois par image, PUIS on la vide.
        lacetVide += accumVide * SENSIBILITE;
        accumVide = 0;

        // 3 : meme lecture, mais on oublie de vider.
        lacetSansVidage += accumSansVidage * SENSIBILITE;

        const double t = horloge.Elapsed().ToMilliseconds() / 1000.0;
        if (t >= prochainReleve) {
            std::printf("t = %.1f s, lu = %.1f, vide = %.1f, sans vidage = %.1f\n", t,
                        lacetLu * DEGRES_PAR_RADIAN,
                        lacetVide * DEGRES_PAR_RADIAN,
                        lacetSansVidage * DEGRES_PAR_RADIAN);
            std::fflush(stdout);
            prochainReleve += 1.0;
        }

        // Environ 60 images par seconde.
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    fenetre.ClipMouseToClient(false);
    fenetre.CaptureMouse(false);
    fenetre.ShowMouse(true);

    NkClose();
    return 0;
}