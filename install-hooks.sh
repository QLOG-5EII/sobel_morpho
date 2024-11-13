#!/bin/bash

# Script permettant de copier les hooks modifée dans le repo git 

# A faire pour chaque hook modifié
cp hooks/pre-commit .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit

#Fin :)
echo "Hook pre-commit installé avec succès."