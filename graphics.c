#include "rectangle.h"
#include "graphics.h"
#include "commands.h"
#include <stdio.h>

void display_world() {
    int rows = 10;  // Número de linhas da grelha
    int cols = 25;  // Número de colunas da grelha
    char grid[10][25] = {0};  // Inicializa a grelha com espaços

    // Inicializa a grelha com espaços
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = ' ';
        }
    }

    Rectangle* rectangles = get_rectangles();  // Obtém a lista de retângulos
    int rectangle_count = get_rectangle_count();  // Obtém o número de retângulos

    // Preenche a grelha com as bordas e interiores dos retângulos
    for (int i = 0; i < rectangle_count; ++i) {
        Rectangle rect = rectangles[i];
        int left = rect.x;
        int right = rect.x + rect.width - 1;
        int top = rect.y;
        int bottom = rect.y + rect.height - 1;

        // Desenha as bordas superiores e inferiores
        for (int x = left; x <= right; ++x) {
            if (top >= 0 && top < rows) grid[rows - 1 - top][x] = 'X';  // Borda superior
            if (bottom >= 0 && bottom < rows) grid[rows - 1 - bottom][x] = 'X';  // Borda inferior
        }

        // Desenha as bordas esquerda e direita
        for (int y = top; y <= bottom; ++y) {
            if (left >= 0 && left < cols) grid[rows - 1 - y][left] = 'X';  // Borda esquerda
            if (right >= 0 && right < cols) grid[rows - 1 - y][right] = 'X';  // Borda direita
        }

        // Preenche o interior do retângulo com 'O' *NOVO EfolioB*
        for (int y = top + 1; y < bottom; ++y) {
            for (int x = left + 1; x < right; ++x) {
                if (y >= 0 && y < rows && x >= 0 && x < cols) {
                    grid[rows - 1 - y][x] = 'O';  // Interior
                }
            }
        }
    }

    // Imprime os cabeçalhos das colunas
    printf("   ");
    for (int i = 0; i < cols; i++) {
        printf("%d ", (i + 1) % 10);  // Simplifica os cabeçalhos das colunas para melhor legibilidade
    }
    printf("\n");

    // Imprime a borda superior da grelha
    printf("  +");
    for (int i = 0; i < cols; i++) {
        printf("--");
    }
    printf("+\n");

    // Imprime a grelha com cabeçalhos das linhas, linhas verticais e horizontais
    for (int i = 0; i < rows; i++) {
        printf("%2d|", rows - i);  // Cabeçalho da linha
        for (int j = 0; j < cols; j++) {
            printf("%c ", grid[i][j]);
        }
        printf("|\n");
    }

    // Imprime a borda inferior da grelha
    printf("  +");
    for (int i = 0; i < cols; i++) {
        printf("--");
    }
    printf("+\n");
}
