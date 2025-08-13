#!/bin/bash
cd /home/norabino/Desktop/42/cub3d

echo "=== TEST MOUVEMENT ULTRA-FLUIDE ANTI-SAUT ==="
echo
echo "🎯 CORRECTIONS APPORTÉES:"
echo "✅ Pas fins (0.02 au lieu de 0.15) = plus de sauts"
echo "✅ Mouvement continu = positions intermédiaires visibles"
echo "✅ Rafraîchissement à chaque micro-mouvement"
echo "✅ Système keypress/keyrelease réactif"
echo
echo "🎮 TESTEZ MAINTENANT:"
echo "- Maintenez W/A/S/D pour un mouvement fluide continu"
echo "- Maintenez ←/→ pour une rotation douce"
echo "- Observez: plus de sauts, transitions parfaitement fluides"
echo
echo "Lancement..."
./cub3D maps/good/test_movement.cub
