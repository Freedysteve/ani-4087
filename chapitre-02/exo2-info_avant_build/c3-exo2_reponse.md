# Exercice — `jenga info` avant le build

## Commande utilisée

bash
cd MaSalle
jenga info


## Résultat

```text
Jenga Workspace: MaSalleWks 

Location: /home/claude/MaSalle
Entry file: /home/claude/MaSalle/MaSalle.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: 
Target Architectures: 


Projects

Name      Kind          Language   Test   External

MaSalle   WindowedApp   C++        No     No


Available Toolchains

Name       Family   Target OS   Arch     Env

host-gcc   gcc      Linux       x86_64   gnu


Daemon

Status: Not running
```

## Analyse et ## Conclusion

La commande `jenga info` permet de voir les informations liées au projet et à l'environnement de travail.

Dans mon cas, le projet **MaSalle** est une application graphique en C++ Les configurations disponibles sont **Debug** et **Release**.

La chaîne de compilation détectée est `host-gcc`. Elle utilise GCC sur Linux x86_64 Cela montre que Jenga a trouvé automatiquement le compilateur disponible sur la machine.

On remarque aussi que `Platforms` affiche **Windows**, alors que la chaîne de compilation détectée fonctionne sous Linux. Cette valeur ne correspond donc pas directement à l'environnement réel de compilation. Elle semble venir de la configuration par défaut puisque les systèmes et architectures cibles ne sont pas précisés dans le fichier `.jenga`.

Enfin, le daemon Jenga n'est pas lancé. Cela signifie simplement qu'aucun processus Jenga ne fonctionne actuellement en arrière-plan.

## Conclusion

Pour moi, la différence principale est simple : le fichier `.jenga` décrit ce que je veux construire, tandis que `jenga info` me montre ce que mon environnement peut actuellement utiliser pour construire le projet**.

La commande est donc utile avant le build pour vérifier rapidement la configuration disponible et éviter de partir sur une mauvaise configuration.
