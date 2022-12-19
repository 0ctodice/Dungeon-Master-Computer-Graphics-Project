# Dungeon-Master-Computer-Graphics-Project

## Thomas DUMONT

Projet de la matière synthèse d'image pour le Master 2 Informatique Sciences de l'Image

## A. Données du donjon

### 1. Structure du niveau

La structure du niveau sera chargé à partir d'une image ppm qui n'est pas à modifié.
1 pixel = 1 tile.
Code couleur :

- noir : mur
- blanc : couloir / pièce vide
- bleu (#0000FF) : eau
- rouge (#FF0000) : entrée
- vert (#00FF00) : sortie

concernant la forme du fichiers PPM.
Le parser est basé sur le format fourmis en export par GIMP :

```txt
P3
# Created by GIMP version 2.10.30 PNM plug-in
5 4
255
0
0
0
0
...
```

### 2. Données d'un niveau

Pour gérer les données on partira d'un fichiers texte à parser suivant la logique ci-dessous :

- un commentaire qui commence par le signe "#"
- le nombre de niveaux
- sur chaque ligne suivante, la description d'un niveau sous cette forme :
  - nom du fichier ppm du niveau (à déposer dans le dossier assets/map):nombre de pièce à trouver
- le nombre de trésors
- Sur chaque ligne suivante, la description du trésors sous cette forme :
  - id(int):position.x(int):position.y(int):id du niveau:nom:type:valeur:texture2D(tout part du dossier assets/texture)
- le nombre de monstres
- Sur chaque ligne suivante, la description du monstre sous cette forme :
  - id(int):position.x(int):position.y(int):id du niveau:nom:type:atk:ca:pv:temps d'attente entre chaque action(float):nombre de pièce fournis à sa mort:texture2D(tout part du dossier assets/texture)

### Exemple :

```txt
#room
2
room.ppm:100
map.ppm:10
6
1:1:1:0:tune:1:120:dungeon/coin.png
2:1:3:0:sword:4:20:sword/sword004.png
3:2:1:0:shield:5:15:shield/shield020.png
4:2:3:0:popotte:2:10:dungeon/health.png
5:1:2:0:popotteMax:3:10:dungeon/maxhealth.png
6:2:2:0:poorKatana:4:999:sword/sword015.png
2
1:8:7:1:hand:2:0:10:1.0:10:monster/hand.png
2:8:6:1:octopus:2:0:10:1.0:10:monster/octopus.png
```

## B. Le personnage et sa mission

### Pour ce projet, le but du jeu est d'amasser une certaine somme d'argent, afin de pouvoir progresser entre les niveaux.

### Déscription des règles concernant le joueur :

- Le joueur possède 20 points de vie au début de la partie.
- Le joueur possède une valeur d'attaque (atk) de 1 à mains nue.
- Le joueur possède une classe d'armure (ca) de 0 sans protection.
- Le joueur commence avec 0 pièce d'or.
- Pour traverser une porte il faut avoir une certaine somme d'argent indiquer au joueur avant chaque niveaux.
- Tuer un monstre apporte une certaine somme.
- On peut ramasser des pièces, des armes, des boucliers ou des potions.
- chaque changement d'arme ou bouclier n'est pas définitif.

### Déscription des différents type d'objet :

1. Modification de l'argent posséder par le joueur
2. Modifie la santé du joueur
3. Modifie la santé MAX du joueur
4. Représente une arme de CAC
5. Représente une protection influant sur la CA
6. 
## 3. Monstres

L'intelligence artificielle des monstres sera très simple, tous les X temps soit ils avanceront vers le joueurs s'ils sentent sa présence à une certaines distance, soit ils attaqueront ce dernier au corps à corps, soit ils attendront.

Le temps entre chaque action pour un monstre donné est passer dans le fichier des données.

## 4. Représentation graphique

L'ensemble des textures du projet (mur, sol, plafond, porte, arme, interface, splashscreen) ont été généré par IA en utilisant Stable Diffusion : https://nmkd.itch.io/t2i-gui

Nous utiliseront pour l'ensemble du projet des quads texturés.

Pour l'illumination, nous utiliserons le modèle Lambert définie au niveau du joueur.

Pas de gestion des ombres.

## 5. Les spécifications implémentées

### 1. Chargement de la carte : détermination du point d'entrée et de sortie

- ***PPMParser** :
  - s'occupe de récupérer toutes les infos de la map.
- **MapGenerator** :
  - fait le tri parmis tout les pixels et dispatche les différentes tiles dans des sets.
  - nous allons stockons uniquement les murs (seulement ceux proche d'un couloirs, de l'eau, de la sortie ou l'entrée) dans 4 sets différents dependant de leur orientation.
  - uniformise les coordonnées des tiles selon la position de l'entrée et applique une multiplication par -1 sur la coordonnée x pour remettre la map dans le même sens que l'image.

### 2. Chargement des trésors et des monstres ainsi que leurs caractéristiques

- **DataParser** :
  - va récupérer l'ensemble des informations des fichiers data.
  - stocker les noms des map dans un vector de string.
  - va mettre à jour la position des monstres et des trésors selon la position du point de départ.
  
### 3. Affichage de la carte (des couloirs du donjon)

- **MapGenerator** :
  - la fonction *draw* s'occupe de mettre à jour la position des tiles et de les déssiner à chaque frame, en prenant soin de dessiner les tiles de même texture en même temps.
  - s'occupe aussi d'animer et dessiner la porte

### 4. Navigation simple dans le donjon

- **SixAdjacencyCamera** :
  - il y a une fonction par movement, ces dernière vont ajouter soit une rotation de 90 degrée soit une translation de 1 à la Modèle View Matrix générale.

### 5. Interaction avec les trésors : ramassage de trésors et modifications des caractéristiques du personnage

- **main** :
  - on utilise le pollEvent du **WindowManager** pour récupérer le clique gauche.
  - puis on va utilisé la fonction *findTreasure* qui va retourner un pointer sur trésor selon la position de la case devant le joueur, on récupère sa value et selon son **TreasureType** on va modifié la bonne caractéristique du joueur.

### 6. Intégration et visualisation des monstres dans le donjon

### 7. Comportement des monstres

### 8. Interaction avec les monstres : combat...

## 6. Les extensions proposées

## 7.  Résumé des classes développés pour le projet

- **Character** : classe mère pour **Player** et **Monster**
- **DataParser** : classe parsant les fichiers de données et stockant/gérant/affichant l'ensemble des **Entity** et infos des niveaux
- **Entity** : classe mère pour **Monster** et **Treasure**
- **HUD** : classe gérant les données de l'interface ainsi que son affichage
- **MapGenerator** : classe tockant/gérant/affichant l'ensemble des **Tile** du niveau courrant
- **MatrixManager** : classe gérant une Model View Matrix (donc gérant les translation/rotation/homothétie)
- **Monster** : classe gérant les infos et la temporisation des actions d'une instance de monstre
- **Player** : classe gérant les infos de l'instance de joueur
- **PPMParser** : classe pouvant parser un fichier ppm et stocker ses infos
- **SixAdjacencyCamera** : classe gérant les déplacement de caméra
- **Texture** : classe gérant le bind/debind de texture
- **Tile** : classe stockant la position d'une tile ainsi que son état (indiquant s'il doit être afficher ou non)
- **TileSet** : classe stockant un set de tile ainsi que l'orientation qu'elles doivent avoir, de plus gère leur affichage
- **Treasure** : classe gérant les infos d'un trésor.

## 8. Présentation de quelques assets utilisable

### Trésors

![](assets/textures/dungeon/health.png)
![](assets/textures/axe/axe001.png)
![](assets/textures/dungeon/coin.png)
![](assets/textures/hammer/hammer008.png)

### Monstres

![](assets/textures/monster/brain.png)
![](assets/textures/monster/hand.png)
![](assets/textures/monster/mimic.png)
![](assets/textures/monster/spider1.png)