#!/bin/bash
cd /home/norabino/Desktop/42/cub3d

echo "=== TEST FINAL - CUB3D MOVEMENT SYSTEM ==="
echo
echo "🎯 PROBLÈMES CORRIGÉS:"
echo "✅ Segfault avec la map far.cub - Protection contre distances invalides"
echo "✅ Mouvement WASD non affiché - Système de keycodes corrigé"
echo "✅ Mouvement continu - Système keypress/keyrelease fonctionnel"
echo "✅ Collision detection - Mise à jour position joueur"
echo
echo "🎮 CONTRÔLES:"
echo "W - Avancer"
echo "S - Reculer" 
echo "A - Strafe gauche"
echo "D - Strafe droite"
echo "← - Tourner à gauche"
echo "→ - Tourner à droite"
echo "ESC - Quitter"
echo
echo "📝 MAPS DE TEST:"
echo "1. Map simple (test_movement.cub) - Recommandée pour test"
echo "2. Map cheese_maze.cub - Plus complexe"
echo "3. Map far.cub - Très grande (peut être lente)"
echo
echo "Lancement du test avec la map simple..."
make && ./cub3D maps/good/test_movement.cub
