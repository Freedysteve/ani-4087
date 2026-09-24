# Exercice — jenga info avant le build

## Ce que j'ai fait

Dans le dossier de mon projet (`D:\Users\FS\Desktop\devoir vr`), j'ai lancé :

```
jenga info
```

## Sortie obtenue

```
========================= Jenga Workspace: MaSalleWks ==========================

Location: D:\Users\FS\Desktop\devoir vr
Entry file: D:\Users\FS\Desktop\devoir vr\MaSalle (1).jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: 
Target Architectures: 


Projects
------------------------------------------------------------
Name      Kind          Language   Test   External
==================================================
MaSalle   WindowedApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name       Family   Target OS   Arch     Env  
==============================================
host-gcc   gcc      Windows     x86_64   mingw
mingw      gcc      Windows     x86_64   mingw


Daemon
------------------------------------------------------------
Status: Not running
```

## Ce que ça m'apprend en plus du fichier .jenga

Mon fichier de projet dit juste "voilà mon projet, en C++17, avec ces sources". Il ne dit rien sur la machine qui va le compiler. `jenga info` complète ça avec des trucs que je n'avais écrits nulle part :

- Chez moi il y a deux chaînes de compilation disponibles, `host-gcc` et `mingw`, toutes les deux du GCC pour Windows en environnement mingw. Je n'ai déclaré aucune des deux dans mon fichier, Jenga les a trouvées toute seule sur ma machine. Si un jour je veux cibler autre chose (Android par exemple), il faudra qu'une chaîne pour ça apparaisse ici, sinon ça ne marchera pas, peu importe ce que dit mon fichier de projet.
- La ligne `Platforms: Windows` correspond bien cette fois à ma vraie machine, alors que je n'ai mis ni `targetoses()` ni `targetarchs()` dans mon fichier. C'est en fait la valeur par défaut que Jenga affiche quand on ne précise rien — ça tombe juste sur "Windows" parce que je construis effectivement sous Windows, mais ce n'est pas mon fichier qui l'a demandé.
- Le daemon est arrêté, ça n'a rien à voir avec mon fichier non plus, c'est juste l'état du moment.
- Petit détail que je n'avais pas remarqué avant de relire la sortie : mon fichier s'appelle en fait `MaSalle (1).jenga`, avec un " (1)" — sûrement un doublon téléchargé deux fois sur mon Bureau. Ça ne casse rien, mais je devrais le renommer proprement.

Bref : le fichier .jenga dit ce que je veux construire, `jenga info` dit ce que ma machine peut vraiment construire là maintenant. C'est pour ça que le chapitre insiste pour lancer cette commande avant de se lancer dans un build.
