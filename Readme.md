# TP QLog

*Ce TP sera réalisé sous Linux. Il nécessite l'accès à un compte GitHub.*

L'objectif de ce TP est de manipuler et comprendre quelques fonctionnalités avancées de Git. Pour cela, un projet Git est disponible au lien suivant: [https://github.com/QLOG-5EII/sobel_morpho](https://github.com/QLOG-5EII/sobel_morpho).

Le code contenu dans le dossier `src` applique un filtre de Sobel/Dilation/Erosion à une vidéo. Il est accompagné de fichiers CMake qui permettent de le compiler sur Linux ou Windows.

### Mise en place

Vous n'avez pas les droits d'accès au projet sur GitHub, ainsi il vous est possible de le cloner (puisque le projet est public), le modifier localement, mais pas de pousser vos modifications.

Pour pouvoir travailler sur le projet, vous devez faire un [fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo).

Une fois le fork créé, vous pouvez cloner le projet sur votre machine et créer une branche de travail (avec le nom que vous souhaitez).

### Récupérer le travail d'une autre branche

Cela peut arriver que deux personnes travaillent sur des modifications nécessitant une correction similaire pour pouvoir avancer. Le mieux dans ce cas est de créer une branche spécifiquement pour cette correction et de la merger dans `main` afin que les deux puissent récupérer les modifications (avec un rebase) et avancer sur leurs tâches respectives.

Malheureusement, il arrive souvent que l'un d'eux ait déjà fait le correctif sur sa branche. Dans ce cas, l'autre peut attendre que la branche avec le correctif soit mergée dans `main`, mais cela peut prendre du temps. Une autre possibilité est de faire une copie des modifications d'une branche à l'autre. C'est cette seconde possibilité qui sera illustrée ici.

1. Le projet comporte une branche avec une modification à récupérer. La première étape consiste donc à lister les branches pour trouver son nom. Il ne devrait y avoir que trois branches : main, votre branche et la branche avec la modification. Une fois la branche identifiée, vous pouvez utiliser la fonction [`git log`](https://git-scm.com/docs/git-log) (avec les bons paramètres) pour afficher la liste des commits de cette branche.
1. Une fois que vous avez identifié le commit que vous souhaitez copier, vous pouvez utiliser la fonction [`git cherry-pick`](https://git-scm.com/docs/git-cherry-pick) pour effectuer la copie.
1. Le commit s'appelle *temp*, ce qui n'est pas terrible. Pour ce faire, on va utiliser la commande [`git rebase -i`](https://git-scm.com/docs/git-rebase) pour modifier l'historique de notre branche et changer le nom du commit. *Il peut être intéressant de noter que `HEAD~1` permet de pointer sur le commit précédent*

> **Note:** Les points 2 et 3 pourraient être effectués simultanément en utilisant l'option `--edit` de `git cherry-pick`. L'idée ici était d'avoir un exemple d'application avec `git rebase -i`.

### Modification du Sobel

À présent, on souhaite apporter des modifications au code. Comme évoqué précédemment, n'ayant pas le statut développeur sur le projet, vous ne pouvez pas pousser les modifications directement sur le projet original. C'est la raison pour laquelle le projet a été `fork`.

Pour proposer des modifications depuis un `fork`, il faut faire une pull request. C'est précisément ce que nous allons voir dans cette partie.

1. La fonction responsable d'appliquer le filtre de Sobel se trouve dans le fichier `src/sobel.c`. Modifiez cette fonction afin qu'elle applique un autre filtre que celui de Sobel (filtre moyenneur par exemple).
2. Créez un commit avec vos modifications.
3. Utilisez `git push` pour transférer vos modifications sur votre fork dans GitHub.
4. Sur le projet original, créez une pull request.

### Hooks

Certains projets sont développés par des centaines de personnes, chacune ayant son style de programmation. Il peut être difficile de s'y retrouver dans un code qui change sans cesse de style, c'est pourquoi certains projets imposent que les développeurs utilisent le même formateur de code afin d'unifier le style dans l'ensemble du projet.

En général, les IDE sont capables d'appeler ce genre de formateur et donc de gérer automatiquement le formattage (après chaque sauvegarde par exemple). Cependant comment être certain que l'ensemble des développeurs utilise bien le formateur et de la bonne façon ? Pour cela, une possibilité est d'utiliser les `git hooks`.

L'idée de cette section est de créer un hook qui vérifie que l'ensemble des fichiers sont correctement formatés et d'empêcher un commit le cas échéant.

1. Écrire un script bash qui vérifie que chaque fichier ajouté (en préparation d'un commit) est bien formaté. Pour cela, les commandes suivantes peuvent vous être utiles :
    - La commande `root=$(git rev-parse --show-toplevel)` permet de récupérer le chemin absolu du dossier git.
    - La commande `list=$(git diff --name-only --cached)` permet de récupérer la liste des fichiers ajoutés (staged).
    - La commande `clang-format $file` renvoie le contenu du fichier `$file` formaté.
    - Effectuer une boucle while itérant sur l'ensemble des lignes d'une variable `$list` se fait de la façon suivante:
    ```bash 
    while IFS= read -r line; do
    	echo "$line"
    done <<< "$list"
    ```

3. Renommez le fichier `.git/hooks/pre-commit.sample` par `.git/hooks/pre-commit` et remplacez son contenu par votre script. Pour empêcher un commit (dans le cas où un ou plusieurs fichiers ne sont pas bien formatés, le script doit renvoyer -1, en utilisant la commande `exit -1`, sinon, pour accepter l'exécution du commit, le script doit renvoyer 0.
4. Les hooks se trouvent dans le dossier .git et ne sont par conséquent pas versionnés dans le projet sur GitHub. Proposez et implémentez des solutions pour que votre hook soit présent sur l'ensemble des clones de votre projet. Faites une pull request avec votre proposition. 

# Copier le hook dans .git/hooks
cp scripts/hooks/pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit




## GitHub Actions

*Ce TP sera réalisé sous Linux. Il nécessite l'accès à un compte GitHub.*

Réutilisez le [projet git](https://github.com/QLOG-5EII/sobel_morpho) de la fin du TP précédent ou alors faites un nouveau [fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo).

Les workflows Github Actions sont des documents au format `yaml` à mettre dans le répertoire `.github/workflows/` du répo git.

Vous pouvez trouver un rappel de la syntax des workflow dans la [GitHub Actions Cheat Sheet](https://resources.github.com/actions/github-actions-cheat/).

### Workflow Github Actions pour CI dans un environnement Ubuntu.

Voici un exemple de workflow :

```yaml
name: <workflow name>
on: 
  <trigger event>

jobs:
  <job name>:
    runs-on: <environment>
    steps:
    - name: <step1 name>
      uses: <action from marketplace>
      
    - name: <step2 name>
      run: |
        <command1>
        <command2>
        <command3>
```

Mettez en place un premier workflow pour lancer la CI dans un environement Ubuntu pour chaque **push** ainsi que sur un déclenchement manuel, en remplacant les champs de texte indiqués par des `<...>`.

Ce premier workflow doit récupérer les sources de Github, les compiler et exécuter le programme compilé.

Le résultat et les logs d'exécution du workflow sont disponibles dans l'onglet **Actions** de votre répo Github.

## Modification du workflow pour tester sous Windows

Une fois que le workflow Ubuntu fonctionne, étendez la CI pour également lancer la chaine.

Il y a 2 manières d'ajouter un job pour lancer une CI sous Windows :
 1. Un job discret.
 2. Une matrice de job.

L'utilisation d'un job discret ajouté dans la liste de job permet de définir un comportement spécifique au prix un workflow plus gros et plus verbeux.

A l'inverse, si les opérations à lancer ne sont pas spécifique à un OS, par exemple en utilisant un build manager, alors l'utilisation d'une matrice de job est recommendée.

Mettez en place le choix 1, puis le 2.
    
## Ajout de tests unitaires

Maintenant que la chaine de CI fonctionne sur des environnements Linux et Windows, ajoutez des tests unitaires pour valider le bon fonctionnement des fonctions `dilation`, `erosion` et `sobel` de manière à valider le bon fonctionnement de ces fonctions sur des vecteurs d'entrées prédéterminés.

Une fois les tests unitaires écrits et testés, modifier le `CMakeLists.txt` pour générer l'exécutable de test.

Ajoutez un step dans le workflow Github Actions pour que ces tests unitaires fassent parti de la CI.
