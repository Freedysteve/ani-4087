# Exercice — Le define qui manque

## Mon en-tête

```cpp
#pragma once

#ifdef FEATURE_COMPLETE

class Module {
public:
    Module() : m_etat(0) {}
    int Calculer(int x, int y) const {
        return x + y + m_etat;
    }
private:
    int m_etat;
};

#else

class Module {
public:
    Module() : m_etat(0) {}
private:
    int m_etat;
};

#endif
```

Avec `FEATURE_COMPLETE`, la classe a sa méthode `Calculer`. Sans, c'est la coquille : juste un constructeur, rien d'autre.

## Mon programme

```cpp
#include "module.h"
#include <iostream>

int main() {
    Module m;
    std::cout << m.Calculer(3, 4) << "\n";
    return 0;
}
```

## Compilation avec le define

```
g++ -std=c++17 -DFEATURE_COMPLETE main.cpp -o prog_avec
```

Aucun message, ça compile et ça tourne, et le programme affiche `7`.

## Compilation sans le define

```
g++ -std=c++17 main.cpp -o prog_sans
```

```
main.cpp: In function 'int main()':
main.cpp:6:20: error: 'class Module' has no member named 'Calculer'
    6 |     std::cout << m.Calculer(3, 4) << "\n";
      |                    ^~~~~~~~
```

## Lequel des deux j'aurais su diagnostiquer sans cet exercice

Sans hésiter : le second, `has no member named 'Calculer'`. C'est un message que j'ai déjà croisé une bonne dizaine de fois en TD, dès qu'on tape mal le nom d'une méthode ou qu'on oublie un include. Même sans savoir qu'un `#ifdef` est en cause, le réflexe est le même : aller voir la déclaration de la classe pour comprendre pourquoi le membre n'existe pas.

Ce que je n'aurais pas vu venir, c'est le vrai piège du chapitre : ici, l'erreur saute aux yeux parce que mon `main.cpp` inclut le même en-tête, dans la même compilation, avec le mauvais define. Mais dans un vrai projet à plusieurs fichiers, la bibliothèque peut être compilée quelque part AVEC le define (donc avec la vraie classe), et mon propre fichier peut inclure ce même en-tête SANS jamais reposer le define, sans que rien ne me préviennes au moment d'écrire mon code. Si mon code ne cherche pas directement `Calculer` mais utilise la classe autrement (juste un pointeur, une taille, une copie), rien ne m'arrêterait à la compilation ni même à l'édition de liens : les deux versions de la classe ne portent pas la différence dans le nom de leurs symboles. Ça peut compiler, se lier, et planter — ou pire, ne pas planter du tout et donner un résultat faux. C'est cette partie-là, invisible, que je n'aurais pas su reconnaître avant.
