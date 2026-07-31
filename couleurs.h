#ifndef COULEURS_H
#define COULEURS_H

// Réinitialisation de la couleur par défaut
#define RESET       "\033[0m"
#define BOLD        "\033[1m"

// Couleurs du texte
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Couleurs de texte vives / brillantes
#define BRIGHT_BLACK  "\033[90m" // Gris
#define BRIGHT_RED    "\033[91m"
#define BRIGHT_GREEN  "\033[92m"
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE   "\033[94m"

// Couleurs de fond (arrière-plan)
#define BG_GREEN    "\033[42m"  // Fond vert (style plateau d'Othello !)
#define BG_BLACK    "\033[40m"

#endif