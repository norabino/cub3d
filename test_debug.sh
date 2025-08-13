#!/bin/bash

echo "=== Test Debug CUB3D ==="
echo "Lancement du programme avec capture des messages debug..."

# Lance le programme en arrière-plan et capture les messages
./cub3D maps/good/works.cub > debug_output.txt 2>&1 &
PID=$!

echo "Programme lancé avec PID: $PID"
echo "Pressez quelques touches WASD puis ESC"
echo "Attendez 10 secondes..."

sleep 10

# Tue le processus s'il est encore en cours
if kill -0 $PID 2>/dev/null; then
    echo "Arrêt du programme..."
    kill $PID 2>/dev/null
fi

echo ""
echo "=== Messages debug capturés ==="
if [ -f debug_output.txt ]; then
    cat debug_output.txt | head -30
    echo ""
    echo "Fichier complet: debug_output.txt"
else
    echo "Aucun fichier de debug créé"
fi
