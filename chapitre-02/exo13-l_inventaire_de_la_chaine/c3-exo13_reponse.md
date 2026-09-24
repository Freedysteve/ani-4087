# Exercice — L'inventaire de la chaîne

## Commande lancée

```
jenga info -v
```

## Le tableau Available Toolchains, en entier

```
Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env
============================================
host-gcc   gcc      Windows       x86_64   gnu
```

## Ce qui est présent, ce qui manque

Une seule chaîne est trouvée : `host-gcc`, GCC pour Linux x86_64. J'ai vérifié directement sur ma machine, `gcc` et `g++` (version 13.3.0) sont bien installés, ce qui correspond à cette unique ligne.

Ce qui manque, et que le tableau ne liste donc pas du tout :

- **Clang** : pas installé (la commande `clang` est introuvable), donc aucune chaîne clang n'apparaît.
- **Android** : aucune chaîne Android (NDK) n'est configurée. Je n'ai ni le SDK ni le NDK Android installés, donc impossible de faire `jenga build` pour un casque autonome ou un téléphone tant que je n'aurai pas installé et déclaré cette chaîne.
- **Windows (MSVC)** : je suis sous une machine Linux, donc pas de chaîne MSVC, logique.
- **macOS/iOS** : idem, aucune chaîne Apple, normal en dehors d'un Mac.

Si je voulais suivre la suite du chapitre 3 (déployer sur un téléphone Android), la première chose à faire ne serait pas de relancer `jenga build`, mais d'installer le NDK Android et de vérifier qu'une ligne `Android` apparaît bien dans ce tableau avant de tenter quoi que ce soit d'autre.
