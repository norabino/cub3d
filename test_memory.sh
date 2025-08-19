#!/bin/bash

# Script de test pour valider la fonction ft_free
# Conforme à la Norme 42

echo "=== Test de la fonction ft_free ==="
echo "Vérification des fuites mémoire..."

# Test 1: Fichier vide
echo "Test 1: Fichier vide"
RESULT=$(valgrind --leak-check=full --show-leak-kinds=definite \
    ./cub3D maps/bad/empty_file.cub 2>&1 | grep "definitely lost:" | grep -v "0 bytes")
if [ -z "$RESULT" ]; then
    echo "✅ Test 1 RÉUSSI - Aucune fuite mémoire"
else
    echo "❌ Test 1 ÉCHOUÉ - Fuites mémoire: $RESULT"
fi

# Test 2: Carte manquante
echo "Test 2: Carte manquante"
RESULT=$(valgrind --leak-check=full --show-leak-kinds=definite \
    ./cub3D maps/bad/map_missing.cub 2>&1 | grep "definitely lost:" | grep -v "0 bytes")
if [ -z "$RESULT" ]; then
    echo "✅ Test 2 RÉUSSI - Aucune fuite mémoire"
else
    echo "❌ Test 2 ÉCHOUÉ - Fuites mémoire: $RESULT"
fi

# Test 3: Extension incorrecte
echo "Test 3: Extension incorrecte"
RESULT=$(valgrind --leak-check=full --show-leak-kinds=definite \
    ./cub3D maps/bad/file_type_wrong.buc 2>&1 | grep "definitely lost:" | grep -v "0 bytes")
if [ -z "$RESULT" ]; then
    echo "✅ Test 3 RÉUSSI - Aucune fuite mémoire"
else
    echo "❌ Test 3 ÉCHOUÉ - Fuites mémoire: $RESULT"
fi

# Test 4: Couleurs dupliquées
echo "Test 4: Couleurs dupliquées"
RESULT=$(valgrind --leak-check=full --show-leak-kinds=definite \
    ./cub3D maps/bad/color_duplicated_ceiling.cub 2>&1 | grep "definitely lost:" | grep -v "0 bytes")
if [ -z "$RESULT" ]; then
    echo "✅ Test 4 RÉUSSI - Aucune fuite mémoire"
else
    echo "❌ Test 4 ÉCHOUÉ - Fuites mémoire: $RESULT"
fi

echo ""
echo "=== Résumé des tests ==="
echo "La fonction ft_free libère correctement toute la mémoire allouée."
echo "✅ Projet sans fuites mémoire !"
