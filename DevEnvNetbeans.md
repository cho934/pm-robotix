# Netbeans #

## Pourquoi ? ##

Au choix :
> - parce que !
> - Java c'est bien ! Mangez-en ...
> - Meilleur que les autres !

## Installation ##

Les étapes d'installation qui suivent font références à une installation sous Ubuntu.
Pour une installation sur un autre système, les étapes restent les mêmes, mais c'est à vous de trouver comment les réaliser.

### 1. Installer un JDK ###

Utilisez le gestionnaire Synaptic pour installer le package `sun-java6-jdk`.
Au passage, vous pouvez vous faire plaisir et supprimer les packages gic et gck.
Alternative : http://java.sun.com/jdk

Pour java 7 : http://korben.info/installer-java-7-ubuntu.html

### 2. Installer le client SVN ###

Toujours grace au gestionnaire Synaptic, installer le package `subversion`.

Alternative : http://www.collab.net/netbeans

### 3. Installer Netbeans ###

Ici, le gestionnaire Synaptic ne sert à rien. En effet : il n'intègre 'que' Netbeans 5.5.

https://netbeans.org/downloads/
Télécharger "Netbeans 7.4 pour C++" et installer le dans le dossier qui vous plait.
Personnellement j'ai choisi `/home/pmx/downloads` mais ça ne regarde que moi.

### 4. Lancer Netbeans ###

Le script de lancement s'appelle `netbeans` est dans le dossier `bin/`. Facile.

## Configuration ##

### 1. Indentation ###

Voici comment configurer Netbeans pour réaliser une indentation du code simple mais efficace.

```
Tools > Options > Advanced Options (en bas à gauche)
Editing > Indentation Engines > C++ Indentation Engine
Sélectionnez 'Add Newline Before Brace'
```

Vous pouvez répéter l'opération pour d'autres 'Indentation Engine', celui pour le C en particulier.

Pour exploiter cette fonctionnalité ` Alt + Maj + F `.

### 2. Todo list ###

Netbeans intégre une todo list bien pratique mais qui doit être configuré pour tenir compte des tags de Doxygen.

```
Tools > Options > Miscellaneous > ToDo Tasks
Add '\todo'
Add '\bug'
Add '\test'
```

Enjoy !