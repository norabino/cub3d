#!/bin/bash

echo "=== Test de compilation CUB3D avec nouveau système ==="
echo "Compilation en cours..."

# Compilation
make clean
make

if [ $? -eq 0 ]; then
    echo "✅ Compilation réussie !"
    echo ""
    echo "🎮 Test avec une carte simple..."
    timeout 5s ./cub3D maps/good/works.cub
    
    if [ $? -eq 124 ]; then
        echo "✅ Programme lancé avec succès (timeout normal)"
    else
        echo "⚠️ Programme terminé rapidement - vérifier les erreurs"
    fi
else
    echo "❌ Erreurs de compilation détectées"
fi

echo ""
echo "🎯 Contrôles disponibles :"
echo "  W/S   : Avancer/Reculer"
echo "  A/D   : Déplacement latéral (strafe)"
echo "  ←/→   : Rotation gauche/droite"
echo "  ESC   : Quitter"
