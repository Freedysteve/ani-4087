#include "NKWindow/NKWindow.h"
#include "NKEvent/NkEventSystem.h"

using namespace nkentseu;

int main() {
    NkInitialise();

    NkWindowConfig config;
    config.title  = "Ma salle";
    config.width  = 1280;
    config.height = 720;

    NkWindow fenetre(config);
    if (!fenetre.IsValid()) {
        return 1;
    }

    while (fenetre.IsOpen()) {
        NkEvents().PollEvents();
    }

    NkClose();
    return 0;
}
