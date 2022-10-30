# Dungeon-Master-Computer-Graphics-Project
Projet de la matière synthèse d'image pour le Master 2 Informatique Sciences de l'Image

## A. Données du donjon

### 1. Structure du niveau

La structure du niveau sera chargé à partir d'une image ppm.
1 pixel = 1 tile.
Code couleur :
- noir : mur
- blanc : couloir / pièce vide
- marron (#AA7722) : porte
- bleu (#0000FF) : eau
- rouge : entrée
- vert : sortie 

### 2. Données d'un niveau

Pour gérer les données on partira d'un fichiers texte à parser suivant la logique ci-dessous :
- un commentaire qui commence par le signe "#"
- le chemin vers le fichiers ppm de la structure du niveau
- le nombre de trésors
- Sur chaque ligne suivante, la description du trésors sous cette forme :
    - id(uint):position.x(uint):position.y(uint):nom:type:valeur:(potentiellement d'autres infos):modèle 3D
- le nombre de monstres
- Sur chaque ligne suivante, la description du monstre sous cette forme :
    - id(uint):position.x(uint):position.y(uint):nom:type:atk:ca:pv:(potentiellement d'autres infos):modèle 3D

Exemple :
---
#Donjon naheulbeuk
naheulbeuk.ppm
4
1:3:5:tune:1:120:argent.obj
2:14:43:tune2:1:240:argent.obj
3:16:24:fiole:2:10:fiole.obj
4:35:14:gourdin:3:3:15:arme1.obj
3
1:2:5:groark:1:15:5:40:monster1.obj
2:14:42:bzzz:2:30:0:20:monster2.obj
3:18:28:bzz2:2:30:0:20:monster2.obj
---
