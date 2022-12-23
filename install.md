# Procédure d'installation

Nous présentons ici les procédures d'installation sur les environnements `Linux`/`MacOS` et `Windows`.  Nous vous proposons d’utiliser l’IDE
`Eclipse` avec le plugin `CDT` (*C/C++ Development Tooling*).

## Linux et MacOS

### Outils GNU

Les outils GNU nécessaires au projet (`GCC`, `GDB`, `make`) et la bibliothèque standard C (`libc`) peuvent être installés avec les paquets `build-essential` et `gdb` sous Linux, et par l’installation de `XCode Command Line Tools` sous MacOS. Depuis la version `Mountain Lion`, `lldb` a remplacé `GDB` pour le débogage. Le débogage en mode graphique sous Eclipse n’est néanmoins possible qu’avec GDB.

### SDL

Le projet utilise les bibliothèque `SDL` et `SDL image` en version 1.2
(non compatible avec la version 2) pour l’interface utilisateur et le
dessin 2D. Sous Linux, SDL et SDL image peuvent être installés via le
gestionnaire de paquet de votre distribution
(`sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev`) sous
Debian/Ubuntu/Mint). 

Sous MacOS vous devez installer dans un premier temps le gestionnaire de paquets `homebrew`. Taper ensuite les commandes suivantes dans un terminal

```
$ brew install sdl
$ brew install sdl_image
```

## Windows

Sous Windows, `MinGW` (*Minimalist GNU for Windows*) offre une solution
pour disposer d’un environnement GNU.

-   Télécharger la dernière version du netinstaller de `MinGW` :
    <http://www.mingw.org> =&gt;
    `mingw-get-setup.exe`
-   Lancer l’installateur et installer `mingw32-base`, `msys-base`. De
    préférence, laisser l’emplacement par défaut (`C:/MinGW`). Si vous
    préférez un emplacement alternatif, **éviter les dossiers parents
    avec des noms contenant des espaces**.
-   Extraire le contenu de l’archive `SDL-mingw32.zip`  dans le dossier MinGW (ajout des
    include, des bibliothèques SDL et de l’utilitaire `sdl-config` dans
    les dossiers `include`, `lib` et `bin` de MinGW).

### cmd & Path

La compilation et le lancement du projet dans une invite de commande
Windows nécessite l’ajout des répertoires contenant les outils GNU et
les bibliothèques dynamiques nécessaires à l’exécution du projet à la
variable d’environnement `Path`. Pour ce faire, accéder aux
`Propriétés systèmes`, puis aux `Paramètres système avancés`. Ajouter le
dossier `bin` et `msys/1.0/bin` de `MinGW`.

## Eclipse

### Windows : Eclipse et MinGW

Sous Windows, `Eclipse CDT` détecte automatiquement `MinGW` si le
répertoire d’installation est celui par défaut (`C:/MinGW`). Si un autre
répertoire d’installation a été utilisé, la création d’un lien
symbolique est une solution. Il faut ouvrir une invite de commande, se
placer à la racine de `C:` et exécuter la commande
`mklink /J MinGW C:/chemin/vers/MinGW`.

### Importation du projet

-   Lancer Eclipse CDT et choisir un chemin vers un nouveau workspace
    dédié au projet (ex. `~/workspaces/bombeirb`)
-   Menu `File` / `Import` / `Existing Code as Makefile Project`
-   Renseigner un nom de projet -`Project Name`-, le chemin vers le
    dossier du projet -`Existing Code Location`-. Sélectionner
    `GNU Autotools Toolchain`. Sur les
    **machines de l’Enseirb**, sélectionner `Cross GCC`.



### Run configuration

Après avoir lancé la compilation du projet, l’exécutable `bombeirb`
doit apparaitre dans le dossier `bin`. Afin de pouvoir lancer son
exécution depuis l’interface d’Eclipse, il faut ajouter une
configuration de lancement au projet : clic droit sur le projet,
`Run AS, Run configuration...`, clic droit sur `C/C++ Application` puis
`New`. Renseigner le path vers le binaire : `bin/bombeirb`. `Apply` pour
appliquer.
