// pointeur.cpp : tout ce qui touche au pointeur de la souris.
//
// A declarer dans main.cpp (pas d'en-tete, les fichiers rendus sont fixes) :
//     void PointeurPrendre(nkentseu::NkWindow& fenetre);
//     void PointeurRendre(nkentseu::NkWindow& fenetre);
//     int  PointeurTraiter(nkentseu::NkEvent* ev, nkentseu::NkWindow& fenetre);
//
// Dans main.cpp :
//     - PointeurPrendre(fenetre) juste apres l'ouverture de la fenetre ;
//     - PointeurTraiter(ev, fenetre) pour chaque evenement de la pompe ;
//     - PointeurRendre(fenetre) apres la boucle, quoi qu'il arrive.

#include "NKWindow/Core/NkWindow.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkKeyboardEvent.h"

using namespace nkentseu;

// Cache le pointeur, capture la souris et la garde dans la fenetre.
void PointeurPrendre(NkWindow& fenetre) {
    fenetre.ShowMouse(false);
    fenetre.CaptureMouse(true);
    // Sans cette ligne, CaptureMouse seul ne retient pas le pointeur :
    // c'est ClipMouseToClient qui demande au systeme de le confiner.
    fenetre.ClipMouseToClient(true);
}

// Rend le pointeur : visible, libre, non confine.
// Le confinement survit au processus s'il n'est pas relache (voir NkWindow.h).
void PointeurRendre(NkWindow& fenetre) {
    fenetre.ClipMouseToClient(false);
    fenetre.CaptureMouse(false);
    fenetre.ShowMouse(true);
}

// Echap rend le pointeur, F1 le reprend.
// Rend 1 si le pointeur vient d'etre pris, 2 s'il vient d'etre rendu, 0 sinon.
int PointeurTraiter(NkEvent* ev, NkWindow& fenetre) {
    if (auto* touche = ev->As<NkKeyPressEvent>()) {
        if (touche->GetKey() == NkKey::NK_ESCAPE) {
            PointeurRendre(fenetre);
            return 2;
        }
        if (touche->GetKey() == NkKey::NK_F1) {
            PointeurPrendre(fenetre);
            return 1;
        }
    }
    return 0;
}
