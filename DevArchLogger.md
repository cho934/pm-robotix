# Architecture - Logger #

## Introduction ##

Le système de Log mis en place à deux objectifs :
  * Permettre le suivi des tests grace à des affichages sur la sortie standard
  * Permettre le suivi du robot et de ses erreurs grace à un fichier de log

L'architecture du système repose sur 4 classes :
  * `LoggerFactory` - Assure la création des instances de la classe `Logger` ;
  * `Appender` - Qui permet de définir un mode de sortie pour les traces ;
  * `Logger` - Qui permet de tracer l'information ;
  * `Level` - Définit les niveaux de trace existants.

https://sites.google.com/site/pmrobotix/home/wiki-img/DevArchLogger_ArchLoggerClasses.png?attredirects=0

## Les niveaux de trace ##

4 niveaux de trace ont été mis en place :

| DEBUG | Debuggage du code, ne sert que pour les tests |
|:------|:----------------------------------------------|
| INFO  | Information sur l'état du système             |
| WARN  | Information sur une erreur non critique       |
| ERROR | Information sur une erreur critique           |

2 niveaux spéciaux de configuration ont été créé :

| NONE | Désactivation de toutes les traces pour un Log |
|:-----|:-----------------------------------------------|
| ALL  | Activation de toutes les traces pour un Log    |

## Configuration ##

Le système de Log est configuré dans le fichier `LoggerInitialize.cpp`.

Ce fichier contient l'implémentation de la méthode `LoggerFactory::initialize()` qui est appelée lors de la premiere utilisation d'un `Logger`

Dans la pratique, cette méthode doit contenir un code de ce type :
```
void
utils::LoggerFactory::initialize()
{
    // Initialisation des appenders
    add("console", new ConsoleAppender());

    // Initialisation du logger principal
    add(utils::Level::ERROR, "", "console"));

    // Initialisation des loggers supplémentaires
    add(utils::Level::ALL, "test", "console"));
    add(utils::Level::INFO, "utils::Thread", "console"));
}
```

En fait cette méthode définit les différents `Logger` de base du système.

Si un `Logger` non connu est demandé au système, celui-ci utilise la configuration propre au '`RootLogger`'.

## Utilisation ##

Voici quelques exemples sur l'utilisation de ce système.

### Création du `Logger` associé à une classe ###

Méthode 1 - code générique :
```
const Logger & logger_ = utils::LoggerFactory::logger("pmx::Robot");
```

Méthode 2 - méthode statique de création :
```
static inline const utils::Logger & logger()
{
    return utils::LoggerFactory::logger("test::UnitTest");
}
```

Méthode 3 - méthode statique de création (évoluée) :
```
static inline const utils::Logger & logger()
{
    static const utils::Logger & instance = utils::LoggerFactory::logger("test::UnitTest");
    return instance;
}
```

### Utilisation de ce `Logger` dans une méthode ###

Le système permet deux utilisations.

Première utilisation - la méthode `Logger::info(string)`
```
logger_.info("Lancement du robot");
```
Cette méthode permet d'envoyer dans le suivi des traces un message simple.

Seconde utilisation - la méthode `Logger::info()`
```
logger_.info() << "[param:" << param1 << "]" << utils::end;
```
Cette méthode facilite l'envoi d'éléments variés et repose sur les opérateurs `<<` existants pour la classe `std::ostringstream`. Autant dire qu'il y a possibilité de mixer pas mal de choses :)

A noter : le code `<< utils:end` est obligatoire car c'est lui qui valide la fin du message. Sans lui le message n'apparaitra pas.