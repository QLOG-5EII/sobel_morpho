#!/bin/bash

# Script permettant de copier les hooks modifée dans le repo git 

# A faire pour chaque hook modifié
rm .git/hooks/pre-commit.sample
cp hooks/pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit

#Fin :)
echo "Hook pre-commit installé avec succès."