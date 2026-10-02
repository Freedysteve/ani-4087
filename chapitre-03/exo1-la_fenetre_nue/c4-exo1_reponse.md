# Exercice — La fenêtre nue

## Mon main.cpp (les quinze lignes du chapitre)

```cpp
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
```

## Mon fichier de projet (MaSalleFenetre.jenga)

Voir le fichier joint. Il déclare un `windowedapp()` en C++17, lié à NKWindow, NKEvent et à leurs fondations (NKMath, NKCore, NKMemory, NKLogger, NKPlatform, NKContainers, NKThreading, NKTime, NKStream, NKFileSystem), avec les bibliothèques système X11 nécessaires sous Linux (X11, Xext, Xrandr, Xinerama, Xcursor, Xi, Xfixes, Xss, GL).

## La capture

Fenêtre « Ma salle », 1280×720, vide (aucun rendu n'est demandé par ce programme, donc elle est uniformément noire . c'est le comportement attendu, pas un bug). J'ai vérifié avec `xwininfo` que la fenêtre existait bien côté serveur, avec le bon titre et les bonnes dimensions, avant de la capturer.

## Combien de temps ça m'a pris, honnêtement

Beaucoup plus que quinze lignes ne le laissent penser. Écrire le `main.cpp` lui-même a pris quarante minutes. c'est littéralement l'exemple du chapitre. Mais le faire *compiler* a demandé de comprendre toute la mécanique du dépôt : récupérer les sous-modules externes du moteur, installer un compilateur (clang) et toute une série de bibliothèques de développement X11/OpenGL qui manquaient une par une (`GL/glx.h`, puis Xrandr, puis Xinerama, Xcursor, Xi, Xfixes, Xss), avant que l'édition de liens n'aboutisse enfin. Rien de tout ça n'est dans le chapitre : c'est exactement le genre de friction d'installation dont il parle sans la détailler.

Au total, la vraie durée pour moi a tourné autour de cinq heures et demie, l'essentiel du temps n'étant pas passé sur le code mais sur l'environnement de compilation. Je garde ce chiffre comme référence de départ : je m'attends à ce que les prochains chapitres, avec l'environnement déjà en place, aillent nettement plus vite.
