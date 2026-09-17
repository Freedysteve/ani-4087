# Exercice 8 :Le champ de vision asymétrique

## Les quatre angles, œil gauche
Source des données: discussion SteamVR Developer Hardware, « Verification of the FOV properties of HTC Vive Pro » — https://steamcommunity.com/app/358720/discussions/0/4766584846445428818/
Casque : HTC Vive Pro mesuré via la fonction officielle `IVRSystem::GetProjectionRaw()` de l'API SteamVR (OpenVR), qui renvoie les tangentes des quatre demi-angles du frustum de chaque œil.

Valeurs brutes (tangentes) relevées pour l'œil gauche : tan_left = -1,349 ; tan_right = 1,202 ; tan_bot = -1,413 ; tan_top = 1,425.

Converties en degrés (angle = arctan(tangente)) :

 Angle | Valeur (œil gauche) 

 angleLeft  -53,4° 
 angleRight +50,2° 
 angleUp +54,9° 
 angleDown  -54,7° 

Ces angles donnent un FOV horizontal de 103,7° (50,2 + 53,4) et un FOV vertical de 109,7° (54,9 + 54,7).

## Champ symétrique de même surface

Employer à la place un champ symétrique de même surface obligerait à agrandir la cible de rendu  réellement visible par la lentille.
