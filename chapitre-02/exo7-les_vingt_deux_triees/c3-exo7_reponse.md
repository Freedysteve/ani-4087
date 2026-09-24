# Exercice — Les vingt-trois dépendances triées

J'ai pris la liste `nkentseudependson` de `NKXRDemo.jenga`, la vraie démo XR du dépôt :

NKXR, NKRenderer, NKRHI, NKSL, NKGLSlang, NKSPIRVCross, NKSerialization, NKReflection, NKFileSystem, NKFont, NKImage, NKGlad, NKEvent, NKWindow, NKMath, NKTime, NKLogger, NKStream, NKContainers, NKMemory, NKCore, NKPlatform, NKThreading.

## Groupe 1 — le nom suffit à deviner le rôle

NKXR (réalité étendue), NKRenderer (le rendu), NKWindow (la fenêtre), NKMath (les maths, vecteurs/quaternions), NKTime (le temps), NKLogger (les journaux), NKMemory (la gestion mémoire), NKEvent (les événements), NKImage (les images), NKFont (les polices), NKFileSystem (le système de fichiers), NKContainers (les conteneurs de données), NKThreading (les threads), NKCore (les types de base du moteur).

## Groupe 2 — une idée, sans certitude

- **NKSerialization** : je devine que ça sert à transformer des données en un format qu'on peut sauvegarder ou envoyer, mais sans savoir dans quel format précis (JSON, binaire...).
- **NKPlatform** : je pense que c'est la couche qui isole les différences entre systèmes d'exploitation, un peu comme NKWindow mais plus bas niveau.
- **NKStream** : j'imagine que ça concerne la lecture/écriture de flux de données, mais je ne sais pas si c'est pour des fichiers, un réseau, ou autre chose.

## Groupe 3 — je ne sais rien, alors j'ai ouvert l'en-tête

- **NKRHI** : `NkRHI.h` inclut des fichiers comme `NkGraphicsApi.h`, `NkIDevice.h`, `NkCommandPool.h` — et le wiki du module confirme que le sigle veut dire *Render Hardware Interface* : c'est la couche qui parle directement à la carte graphique.
- **NKSL** : `NKSL.h` se décrit lui-même en commentaire comme l'en-tête parapluie du module NKSL (*Nkentseu Shader Language*), qui compile du GLSL vers du SPIR-V puis vers d'autres langages de shader.
- **NKGLSlang** : ce n'est pas un module écrit par les auteurs du moteur mais un habillage Jenga autour de la bibliothèque externe *glslang* de Khronos, le compilateur de référence pour le langage GLSL.
- **NKSPIRVCross** : même chose, mais pour *SPIRV-Cross*, l'outil officiel de Khronos qui traduit du bytecode SPIR-V vers d'autres langages de shader.
- **NKReflection** : son en-tête dit noir sur blanc qu'il s'agit du point d'entrée pour enregistrer et interroger des métadonnées sur les classes du moteur au moment de l'exécution (des types comme `NkType`, `NkProperty`, `NkClass`).
- **NKGlad** : c'est un habillage Jenga de la bibliothèque *glad*, un générateur de chargeur de fonctions OpenGL/EGL/GLES, d'après son propre README.
