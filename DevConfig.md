# Environnement de développement #

## Compilation ##

Le programme est écrit en C/C++. (C pour son ancienne version, C++ pour la nouvelle).
La compilation est réalisée à l'aide d'un compilateur C++ qui doit pouvoir intégrer la bibliothèque de thread POSIX.

## Développement ##

Le développement n'impose pas d'outils spécifiques, il est donc possible d'éditer le code "from scratch".
Néanmoins celui-ci doit respecter les [règles de codage](DevStandards.md).

Pour faciliter le travail de développement, je conseille d'utiliser les outils suivants :

> - Le code source peut être compilé via [GCC / G++](DevEnvCompilation.md),
> - La documentation est générée à l'aide de [Doxygen](DevEnvDocumentation.md) et respecte les standards de QT,
> - La génération peut se faire via [make](DevEnvGeneration.md),
> - ~~Les fichiers sources peuvent être formatés grace à [indent et astyle](EnvFormatting.md)~~

Mis à part cela, je n'ai pas mis en place un système contraignant nécessitant ABSOLUMENT un certain IDE pour fonctionner.
Donc tout est possible et aucun fichier de configuration propre à un environnement de développement n'est uploadé sur le serveur.


Donc pour information, et uniquement pour information, voici ma configuration de développement :

> - Système d'exploitation : Ubuntu 7.10
> > choisi pour son côté "user-friendly".

> - Environnement de développement : [DevEnvNetbeans Netbeans 6.0
> > Le plus simple et facile à utiliser d'autant qu'il integre Subversion.

> - Schéma des classes : [Argo UML](http://argouml.tigris.org/)