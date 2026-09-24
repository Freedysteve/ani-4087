[c3-exo2_reponse.md](https://github.com/user-attachments/files/32587579/c3-exo2_reponse.md)
# Exercice — `jenga info` avant le build

## Commande lancée

```
cd MaSalle
jenga info
```

## Sortie complète

```
========================= Jenga Workspace: MaSalleWks ==========================

Location: /home/claude/MaSalle
Entry file: /home/claude/MaSalle/MaSalle.jenga
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
============================================
host-gcc   gcc      Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running
```

## Ce que cette sortie m'apprend, que le fichier `.jenga` ne disait pas

Mon fichier de projet ne fait que déclarer un espace de travail, un projet `windowedapp()` en C++17 et une liste de sources. Il ne dit rien sur la machine qui va réellement le construire. Or `jenga info` révèle des choses qui ne dépendent pas du fichier, mais de l'environnement où je travaille :

- **La seule chaîne de compilation disponible ici est `host-gcc`** (GCC, Linux, x86_64, environnement gnu). Rien dans mon fichier `.jenga` ne nomme ce compilateur : Jenga l'a détecté tout seul sur ma machine. Si je voulais un jour cibler Android ou Windows, il faudrait qu'une chaîne correspondante apparaisse dans cette liste — ce que le fichier de projet ne peut pas garantir à lui seul.
- **La ligne `Platforms: Windows` ne correspond pas à ce que je construis réellement.** Mon projet tourne et se lie sur Linux, avec `host-gcc`, et pourtant cette ligne affiche « Windows ». Comme je n'ai déclaré ni `targetoses()` ni `targetarchs()` dans mon fichier, Jenga affiche une valeur par défaut à cet endroit, indépendante de la machine réelle. Autrement dit, cette ligne du rapport reflète une valeur par défaut du système, pas un fait technique observé sur ma configuration — c'est un piège si on la lit trop vite en pensant qu'elle décrit l'environnement de build effectif.
- **Le daemon n'est pas démarré.** C'est une information d'état d'exécution (rien à voir avec le contenu du fichier de projet) : elle me dit que je n'ai pas de processus Jenga persistant en arrière-plan pour accélérer les prochains builds.

En résumé : le fichier `.jenga` décrit une *intention* (ce que je veux construire), alors que `jenga info` décrit une *situation* (ce que la machine devant moi est réellement capable de construire, là, maintenant). C'est exactement pour ça que le chapitre insiste pour lancer cette commande avant de supposer quoi que ce soit sur sa chaîne de compilation.
