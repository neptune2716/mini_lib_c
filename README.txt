Exercice 5 :

En initialisant le buffer avec des '\0' avant de le renvoyer, on s'assure que toute la mémoire allouée est mise à zéro. Cela évite d'avoir des données résiduelles ou indésirables dans le buffer, ce qui peut provoquer des comportements imprévisibles ou des failles de sécurité. C'est particulièrement important pour les chaînes de caractères, car cela garantit qu'elles sont correctement terminées par un caractère nul.

Exercice 6 :

La fonction free en C libère la mémoire précédemment allouée avec malloc, calloc ou realloc. Elle marque cette mémoire comme disponible pour de futures allocations au sein du programme. Cependant, elle ne rend pas nécessairement cette mémoire au système d'exploitation immédiatement. La mémoire reste généralement dans le tas (heap) du programme et peut être réutilisée par celui-ci, mais elle n'est pas restituée au système tant que le programme n'est pas terminé.

Exercice 12 :

Pour tester mini_calloc et mini_free, j'ai commencé par allouer trois blocs de mémoire de tailles différentes. Ensuite, j'ai libéré le deuxième bloc avec mini_free. Après cela, j'ai alloué un nouveau bloc de même taille que le bloc que je viens de libérer. Si la gestion de la mémoire fonctionne correctement, le nouveau bloc devrait réutiliser l'espace mémoire du bloc libéré. Pour vérifier cela, j'ai comparé les adresses des pointeurs. Si les adresses du deuxième bloc libéré et du nouveau bloc sont identiques, cela signifie que la mémoire a été réutilisée avec succès.

Exercice 17 :

En testant mini_printf avec une chaîne qui ne contient pas de saut de ligne, je me suis rendu compte que le texte ne s'affiche pas immédiatement à l'écran. Le problème vient du fait que mini_printf utilise un tampon pour stocker les données avant de les écrire. Ce tampon n'est vidé que lorsqu'il est plein ou lorsqu'un saut de ligne est rencontré. Si le programme se termine avant que le tampon soit vidé, le contenu n'est jamais affiché. Il faut donc trouver un moyen de s'assurer que le tampon est vidé avant la fin du programme pour que toutes les données soient bien affichées.

Exercice 18 :

Pour résoudre le problème précédent, j'ai modifié la fonction mini_exit pour qu'elle vide le tampon avant de quitter le programme. J'ai ajouté un appel à une fonction flush_buffer qui s'occupe de vider le tampon de mini_printf. En exécutant le programme avec strace, on peut voir que l'appel système write est bien effectué juste avant la fin du programme, ce qui confirme que le tampon a été correctement vidé et que les données sont affichées à l'écran.

Exercice 20 :

Si le nombre de caractères saisis est égal à la taille du buffer dans mini_scanf, il n'y a pas de place pour ajouter le caractère nul '\0' qui termine la chaîne. Cela peut entraîner un dépassement de buffer et des comportements indéfinis. Pour éviter ce problème, j'ai modifié la fonction pour qu'elle ne lise au maximum que size_buffer - 1 caractères, laissant ainsi de la place pour le '\0'. De plus, si l'utilisateur entre plus de caractères que le buffer ne peut en contenir, je lis et j'ignore les caractères supplémentaires pour qu'ils n'affectent pas les lectures suivantes.

Exercice 22 :

Les fonctions mini_strlen, mini_strcpy et mini_strcmp présentaient des problèmes de sécurité. Par exemple, elles ne vérifiaient pas si les pointeurs passés en paramètres étaient NULL, ce qui pouvait provoquer des plantages du programme. De plus, mini_strcpy ne vérifiait pas si le buffer de destination était assez grand pour accueillir la chaîne source, ce qui pouvait entraîner des dépassements de buffer. Pour corriger ces problèmes, j'ai ajouté des vérifications pour m'assurer que les pointeurs ne sont pas NULL et que les opérations de copie ou de comparaison se font dans les limites des buffers alloués.

Exercice 34 :

Si le programme se termine alors que le buffer d'écriture n'est pas plein, les données restantes dans le buffer risquent de ne pas être écrites sur le disque, ce qui peut entraîner une perte de données. Pour éviter cela, j'ai modifié mini_exit pour qu'il parcoure la liste des fichiers ouverts et qu'il appelle mini_fflush sur chacun d'eux. Cela force l'écriture des données en attente dans les buffers avant que le programme ne se termine, garantissant ainsi que toutes les données sont bien sauvegardées.