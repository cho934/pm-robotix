# Documentation du code #

Tout un programme :)

## Les bases ##

Mieux qu'un long discours, voici un exemple (un long exemple quand même).
Cet exemple nous permettra de faire 2 constats :
> - Le wiki aime les tags qui commencent par un `\` et ça : c'est beau !
> - Les blocs de documentation commencent par **`/*!`** ce qui est aussi important.

```
#!cpp
namespace utils
{
    /*!
     * \brief Cette classe représente un niveau de trace.
     *
     * 4 niveaux sont définis par défaut :
     * - DEBUG : Pour les messages destinés à faciliter le debuggage de l'application ;
     * - INFO  : Pour les messages d'informations sur l'état de l'objet et du système ;
     * - WARN  : Pour les messages d'avertissements ;
     * - ERROR : Pour les messages d'erreurs.
     */
    class Level
    {
    public:
        
        /*!
         * \brief Niveau pour les messages destinés à faciliter le debuggage de l'application.
         */
        static Level DEBUG;
        
        /*!
         * \brief Niveau pour les messages d'informations sur l'état de l'objet
         * et du système.
         */
        static Level INFO;
        
    private:
        
        /*!
         * \brief Valeur associé au niveau.
         *
         * Cette valeur permet de comparer les niveaux de trace entre eux.
         * Plus le niveau est bas, moins le niveau et les messages associés
         * à ce niveau sont importants.
         */
        short value_;
        
    public:
        
        /*!
         * \brief Constructeur de la classe.
         * \param value
         *        Valeur associé au niveau.
         * \param name
         *        Nom associée à ce niveau.
         */
        Level(short value, const std::string & name): value_(value),
                name_(name)
        {}
        
        /*!
         * \brief Cette méthode retourne le nom de ce niveau.
         * \return Le nom de ce niveau.
         */
        inline const std::string & name() const
        {
            return name_;
        }
        
        /*!
         * \brief Comparateur de supériorité.
         * \param level
         *        Niveau à comparer.
         * \retval true
         *         Si l'objet courant est supérieur ou égal à \c level.
         * \retval false
         *         Si l'objet courantest inférieur à \c level.
         */
        inline bool operator >= (const Level & level) const
        {
            return value_ >= level.value_;
        }
    };
};
```

Cet exemple utilise les principaux tags a exploiter pour documenter le code. Nous allons revenir sur ces tags.

### `\brief` ###

Permet de définir la description 'courte' de l'élément. Cette description est certainement la plus importante de toute la documentation et est donc obligatoire.
La description courte prend fin lorsque vous sautez une ligne ou lorsqu'un autre tag est rencontré (voir les blocs de `value_` ou `Logger`).

Le texte qui suit la description courte compose la description 'longue'. Cette dernière n'est visible qu'à un endroit dans la documentation : lorsque l'élément est détaillé.

### `\param` ###

Permet de détailler la valeur attendue pour un paramètre.

### `\return` et `\retval` ###

Permettent de définir la valeur de retour. `\return` est le tag standard et `\retval` permet de définir les valeurs de retour possible et leur signification.

### `\c` ###

Permet de définir le mot suivant comme un élément de 'code' devant être écrit avec une police particulière. Particulièrement utile pour mettre en avant les noms d'éléments ou de constantes (true, false).

## Les 'Advanced Features' ##

La documentation de Doxygen est, et reste, une référence **à avoir lu** pour connaitre toutes les possibilités de formattage (liste, tableau, liens, ...) et les tags existants.

Bonne lecture.

## FAQ ##

'''Pourquoi utilisez les notations `/*!` et `\tag` alors que `/**` et `@tag` sont prises en charge par Doxygen ?'''

Parce que les notations ~~`/**`~~ et ~~`@tag`~~ correspondent à du code Java.

Les notations `/*!` et `\tag` sont les standards de documentation des programmes Qt ... écrit en C++.