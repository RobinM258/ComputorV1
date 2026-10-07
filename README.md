# 🧮 Computorv1

> Un solveur d'équations polynomiales développé dans le cadre du cursus de l'école 42.

---

## 📖 À propos

**Computorv1** est un projet de mathématiques et de programmation. L'objectif est de concevoir un programme capable de analyser, simplifier et résoudre des polynômes de forme réduite, en gérant aussi bien les solutions réelles que les nombres complexes (via le calcul du discriminant $\Delta$).

---

## ⚙️ Fonctionnalités

*   🔍 **Analyse syntaxique (Parsing) :** Lecture et validation de la ligne de commande représentant une équation (ex: `5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0`).
*   📉 **Réduction de l'équation :** Regroupement des termes de même degré pour obtenir la forme canonique (ex: `ax^2 + bx + c = 0`).
*   🔢 **Gestion des degrés :**
    *   **Degré 0 :** Équation triviale / impossible.
    *   **Degré 1 :** Résolution linéaire simple ($x = -c / b$).
    *   **Degré 2 :** Résolution quadratique avec calcul du discriminant ($\Delta = b^2 - 4ac$), incluant la gestion des racines complexes.
    *   **Degré > 2 :** Message d'erreur.

---

## 🚀 Installation & Utilisation

Clone le dépôt sur ta machine et compile/exécute le projet :

```bash
# Cloner le dépôt
git clone https://github.com/RobinM258/computorv1.git
cd computorv1

make
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
