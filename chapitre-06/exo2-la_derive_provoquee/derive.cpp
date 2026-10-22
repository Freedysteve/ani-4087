// derive.cpp : la tete fautive, ecrite expres.
// A chaque image, on ajoute au lacet le deplacement brut que garde le module
// d'entrees, SANS rien accumuler ni vider nous-memes. Quand la souris s'arrete,
// le module garde sa derniere valeur et la tete continue de tourner seule.

#include "NKWindow/NKWindow.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkEventDispatcher.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKTime/NkChrono.h"

#include <chrono>
#include <cstdio>
#include <thread>

using namespace nkentseu;

int main() {
    NkInitialise();

    NkWindowConfig config;
    config.title  = "Derive";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    fenetre.ShowMouse(false);
    fenetre.CaptureMouse(true);
    fenetre.ClipMouseToClient(true);

    const float SENSIBILITE = 0.002f;   // radians par compte du capteur
    const float RAD_VERS_DEG = 57.2957795f;

    float lacet = 0.f;
    float tangage = 0.f;
    int images = 0;
    int secondeAffichee = 0;
    bool fin = false;

    NkChrono chrono;

    while (fenetre.IsOpen() && !fin) {
        while (NkEvent* ev = NkEvents().PollEvent()) {
            if (auto* touche = ev->As<NkKeyPressEvent>()) {
                if (touche->GetKey() == NkKey::NK_ESCAPE) {
                    fin = true;
                }
            }
        }

        // Version fautive : on lit le brut a chaque image et on l'ajoute.
        lacet   += NkInput.MouseRawDeltaX() * SENSIBILITE;
        tangage += NkInput.MouseRawDeltaY() * SENSIBILITE;
        ++images;

        const double t = chrono.Elapsed().ToMilliseconds() / 1000.0;
        if (static_cast<int>(t) > secondeAffichee) {
            secondeAffichee = static_cast<int>(t);
            std::printf("t = %.1f s, images = %d, brut = %d, lacet = %.1f deg\n",
                        t, images, NkInput.MouseRawDeltaX(), lacet * RAD_VERS_DEG);
            std::fflush(stdout);
        }

        // Cadence d'environ 120 images par seconde.
        std::this_thread::sleep_for(std::chrono::milliseconds(8));
    }

    (void)tangage;

    fenetre.ClipMouseToClient(false);
    fenetre.CaptureMouse(false);
    fenetre.ShowMouse(true);

    NkClose();
    return 0;
}