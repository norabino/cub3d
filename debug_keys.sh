#!/bin/bash

echo "=== Test des keycodes WASD ==="
echo "Tapez une touche et voyez son code..."

# Test simple pour voir les keycodes
./cub3D maps/good/works.cub &
PID=$!

sleep 2
echo "Programme lancé avec PID: $PID"
echo "Utilisez les touches WASD et vérifiez la console"
echo "Tuez le processus avec: kill $PID"
