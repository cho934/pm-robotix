# Formatage du code #

## Règles de formatage ##

Le formatage du code est simple :
> - L'indentation des éléments se fait à l'aide de tabulation ou d'espace,
> - L'alignement des éléments se fait à l'aide d'espace,
> - les blocs sont indentés.
> - les { sont placés sur une nouvelle ligne.

## Comment formater ? ##

Les solutions testés ne sont pas toujours très effective. Néanmoins une commande `make format` est disponible, elle se base sur l'utilisation de indent et astyle pour obtenir un résultat satisfaisant.

La meilleure solution reste d'utiliser le formatage automatique de [Netbeans](DevEnvNetbeans.md).

## Outils de formatage testé ##

### GNU indent ###

Version de référence : 2.2.9

Site web : http://www.gnu.org/software/indent/

Indent est un programme prévu pour le formatage de code C.

Une tentative d'intégrer le formatage de code C++ a été faite mais au final, seul des fichiers simples peuvent être traités (voir la documentation pour plus de détails).

### Artistic Style - astyle ###

Version de référence : 1.18

Site web : http://astyle.sourceforge.net/

Astyle intègre l'indentation et/ou le formatage du code C++.

Contrairement à indent, astyle ne corrige pas les commentaires.