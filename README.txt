1. Mettre des parametres (Si vous voulez)
Il y a deux simulateurs dans ce répertoire, qui ont la même comportement. 

La fonction nommé 'f' se trouve au milieux de code. 
Vous pouvez essayer de changer les parametres
- pump: k_ij dans le rapport, coefficients des vannes (les élements diagonals doivent être nuls) 
- leakage: alpha_i dans le rapport, coefficients de sortie positifs
- q: coeeficients d'entré
- s: section des bassins

Puis, vous mettez aussi la condition initiale qui se situe dans la première partie dans la fonction main.

2. Exécuter le calcul
Si vous avez un compilateur C++, je vous invite à compiler "simulation.cpp".
(Le code a été amélioré, vous pouvez exécuter dans dizaines de seconds même en python)

Sinon, executez "simulation.py".

Enfin, vous obtenez "data.csv" qui contient le résultat de la simulation.


2. Analyser le résultat
Ouvrir "analyse.ipynb".
