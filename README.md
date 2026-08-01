# OthelloBot

J'ai créé un algorithme qui joue tout seul au jeu Othello/reversi.
Il y a une implémentation du jeu avec des fonction pour placer des pions.
Une fonction *calcul* qui va simuler des coups à une certaine profondeur pour trouver le meilleur coup en fonction de l'heuristique implémentée.
Un algorithme génétique pour la fonction d'heuristique, qui cherche la meilleure matrice de poids.

**A faire :**
- Implémenter le jeu en python avec ma Librairie [NNL](https://github.com/maiths-cvl/NNL) pour regarder les résultats de réseaux de neurones sur ce jeux
- Optimiser la création des copies de la grille du jeu dans la fonction *calcul*, pour l'instant il y a des *malloc* sur le *tas* à chaque itération mais il faut créer des copies sur le pile et copier directement la grille plutot que de créer un nouveau tableau dynamique (libère beaucoup de temps d'éxécution)
- ~Supprimer des *printf* qui ralentissent le temps d'éxécution~
- Implémenter un système d'écriture dans des fichiers pour sauvegarder les parties ou au moins simplement le score et les paramètres de l'heuristique utilisés pour la partie
