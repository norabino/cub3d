#!/bin/bash

echo "🌟 CONFIGURATION ULTRA-SMOOTH 🌟"
echo ""
echo "Voulez-vous appliquer les paramètres ultra-fluides?"
echo "(Mouvement très lent mais ultra-doux)"
echo ""
echo "Configuration proposée:"
echo "  • move_speed: 0.003 (très lent et fluide)"
echo "  • rot_speed: 0.003 (rotation très douce)"
echo ""
read -p "Appliquer? (y/n): " choice

if [[ $choice == "y" || $choice == "Y" ]]; then
    echo "Application des paramètres ultra-smooth..."
    
    # Modifier les vitesses dans hook.c
    sed -i 's/move_speed = 0.008/move_speed = 0.003/g' src/raycasting/hook.c
    sed -i 's/rot_speed = 0.008/rot_speed = 0.003/g' src/raycasting/hook.c
    
    echo "✅ Paramètres ultra-smooth appliqués!"
    echo "Recompilation..."
    make
    
    if [ $? -eq 0 ]; then
        echo "✅ Compilation réussie!"
        echo "🎮 Test avec: ./cub3D maps/good/test_movement.cub"
    else
        echo "❌ Erreur de compilation"
    fi
else
    echo "Configuration annulée."
fi
