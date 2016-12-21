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

#### Questions !?
- [ ] Faut-il mettre les tables d'usinage dans le Superviseur ?
- [ ] Faut-il créer un conteneur (Liste chainée), pour les table d'usinage ?

- [ ] Faut-il conserver les méthodes des tables d'usinage dans leur structure ?

- [ ] Créer une sorte de super Structure portant le nom de System et contenant
      tout le système pour pouvoir l'orchestrer

#### Algo
- FactoryTable -> prendre pièce sur convoyeur :
    - Vérifier la disponibilité du tapis :
        - Si le tapis n'est pas disponible au bout de 50 secondes, un signal
        d'erreur est envoyé au Superviseur
    - Vérifier si la capacité max du tapis est atteinte pour le transport de
    pièces
    - Si non poser la pièce sur le convoyeur
    - Si non passer son tour
    - Demander au convoyeur de déplacer la pièce vers le robot de retrait
    - Libérer l'utilisation du tapis aux autres éléments du système
