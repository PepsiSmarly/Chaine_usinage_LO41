# Projet LO41
## Modélisation d'une chaine d'usinage

Ce Projet consiste en la modélisation du comportement d'une chaine d'usinage
qui suit des comportements données et sait réagir en foncition des événements
qui peuvent survenir lors du cycle de production. La modélisation se fera
grâce aux différents outils proposé par les système unix comme les mécanismes
de synchronisation, les processus légés, la norme POSIX, ...etc.

### Les objets

Les différents objets présent sur la ligne de production sont les suivants:
- Superviseur
- Robot alimentation/retrait
- Table (d'usinage des pièces)
- pièces
- convoyeur

#### Les différentes fonctions des objets

Les objets possèdent différentes fonctions qui sont les suivantes:
- Superviseur:
    - Reçoit des ordres de l'opérateur
    - Détermine la machine qui traite une nouvelle pièce
    (une pièce annoncé par l'opérateur)
    - Demande au Robot d'alimentation de poser la pièce
    sur le Convoyeur
    - Demande à la machine de traitement concerné par l'arrivée
    de la pièce de se préparer
