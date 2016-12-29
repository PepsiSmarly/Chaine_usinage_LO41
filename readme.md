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
- [ ] ~~Faut-il mettre les tables d'usinage dans le Superviseur ?~~
- [ ] ~~Faut-il créer un conteneur (Liste chainée), pour les table d'usinage ?~~

- [ ] ~~Faut-il conserver les méthodes des tables d'usinage dans leur structure ?~~

- [X] Créer une sorte de super Structure portant le nom de System et
contenant tout le système pour pouvoir l'orchestrer !? (Nommé Network dans
la pratique)

- [X] Passer les éléments de synchronisation directement dans les structures
des objets pour une question de logique et de facilité d'accès (Sinon
accessible seulement dans un seul thread...)

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

- Arriver d'une nouvelle pièce dans le système :
    - Le Superviseur vérifie quelle table d'usinage va accueillir la pièce
    pour sont traitement :
        - Regarder le code d'usinage de la pièce
        - Parcourir les tables présentent et faire le lien entre le code
        d'usinage de la pièce et la table d'usinage
        - Notifier la table pour qu'elle se prépare à recevoir la pièce
        - Donner l'ordre au robot d'alimentation de charger la pièce sur
        le convoyeur

- Fonctionnement du Convoyeur :
    - tourner en permanence, c'est tout

- Table qui à été notifié de l'arrivée d'une pièce :
    - attente active en scrutant le convoyeur
    - quand la pièce sur le convoyeur se trouve au niveau de la table
    d'usinage, ramassage de la pièce (laisser une fourchette pour le
    ramassage)
    - traiter la pièce
    - remettre la pièce sur le tapis
    - se rendormir en attendant d'être de nouveau réveillé par le Superviseur

- Robot chargeur :
    - Etre endormi tant qu'il n'a pas de travail
    - Réveillé par le superviseur car une pièce arrive dans le système:
        - Ce qui pour effet de faire entrer le superviseur dans un état de
        de sommeil dans l'attente de la réponse du robot de chargement
    - Il monopolise donc le convoyeur
    - il dépose la pièce sur le convoyeur:
        - Si au bout de 20 secondes la pièce n'est pas déposée sur le
        le convoyeur alors une erreur est levée
    - Il libère le convoyeur pour que les autres puissent s'en servir:
        - Il réveille le superviseur en lui faisant un compte rendu
    - Il retourne dans un état endormi jusqu'à être réveillé

- Robot déchargeur :
    - Etre endormi tant que pas de travail disponible
    - Réveillé par le superviseur lorsque qu'une pièce sort d'une table
    d'usinage
    - Attendre que la pièce se présente à hauteur du robot de déchargement
    - Décharger la pièce du convoyeur :
        - Si au bout de 30 secondes la pièce n'est toujours pas ôtée du
        convoyeur alors un le robot signal une erreur au superviseur qui
        passe le système en défaillance
    - Envoyer un rapport au Superviseur
    - Retourner dans l'état d'attente de travail

- Usinage d'une pièce sur une table d'usinage :
    - Attendre que la pièce soit en bonne position sur le convoyeur :
        - Si la pièce n'est pas récupéré au bout de 50 secondes, alors
        une erreur est levé au Superviseur
    - Déterminer un temps d'usinage aléatoire
    - Attendre le temps déterminé
    - Marquer la pièce comme étant usiné
    - Envoyer un rapport positif au Superviseur
    - Attendre son accord pour poser la pièce sur convoyeur
    - Poser la pièce sur le convoyeur
    - Revenir dans un état d'attente de travail

- Table qui a fini l'usinage d'une pièce et qui doit la remettre sur le
convoyeur :
    - Fin de l'usinage de la pièce
    - Envoi d'un compte rendu de l'usinage au Superviseur
    - Réponse du Superviseur (attend que le convoyeur soit libre):
        - Chargement de la pièce sur le convoyeur
        - Ou pas... (Pas de cas donné)
    - Retour dans l'état d'attente de nouvelle pièce
    - ATTENTION : Si l'usinage n'est pas terminé au bout de 10 minutes
    alors le Superviseur déclare la machine en panne mais ne stop pas le
    système pour autant !
    - Dans le cas ou la machine est en panne et qu'une pièce arrive pour
    être traité par cette dernière alors cette fois le système est passé
    dans un état de déffaillance par le Superviseur

### TODO
- [ ] Mettre en place les signaux (SIGQUIT, SIGSTOP, voir si autres)
    - [ ] Pour les threads regarder du côté de pthread_kill()
- [ ] voire quoi mettre dans le fichier de configuration
- [X] Finir la méthode factoryTable_WaitPiece
- [X] Repenser la méthode supervisor_AppendPiece, pour donner la pièce au
bras puis lui dire de faire son travail plutôt que de le lui faire faire
directement.
- [X] Faire une méthode pour le Superviseur qui permette de le notifier
de la fin du chargement de la pièce sur le Convoyeur que se soit un
succès ou un échec, il devra ensuite agir en conséquence
- [X] Trouver le problème de la fuite de mémoire lié vraisemblablement
aux threads... (explications: cette "Fuite mémoire" n'en est pas vraiment
une, il ne faut donc pas s'en inquiéter !)
- [X] Trouver la solution pour terminer les threads des robots de
chargement/déchargement qui reste bloqué par leur monitor
- [X] Faire le thread du robot de déchargment (assez proche de
celui de chargement)
- [ ] Faire le thread des tables d'usinage
- [X] Faire le thread du convoyeur

### Notes à moi-même
- Pour le débug de programme :
http://perso.ens-lyon.fr/daniel.hirschkoff/C_Caml/docs/doc_gdb.pdf
- Pour les fuites mémoires utiliser valgrind :
    - sudo apt-get install valgrind (sur Ubuntu)
    - utilisation simple :
    http://alexandre-laurent.developpez.com/articles/debogage-application/
