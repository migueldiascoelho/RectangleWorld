#include "commands.h"
#include "rectangle.h"
#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_commands() {
    char *command = NULL;
    size_t len = 100;
    command = malloc(len * sizeof(char));

    if (command == NULL) {
        fprintf(stderr, "Alocacao de memoria falhou\n");
        return;
    }

    printf("Escreva um comando valido. Pressione Enter numa linha em branco para sair do programa.\n");

    while (1) {
        printf("> ");
        if (fgets(command, len, stdin) == NULL || command[0] == '\n') {
            break;
        }

        // Remove o caracter de nova linha
        size_t command_len = strlen(command);
        if (command[command_len - 1] == '\n') {
            command[command_len - 1] = '\0';
        }

        int x1, y1, x2, y2, l, h, p;
        if (sscanf(command, "create %d,%d+%d,%d", &x1, &y1, &l, &h) == 4) {
            printf("Criado retangulo em (%d, %d) com largura %d e altura %d\n", x1, y1, l, h);
            create_rectangle(x1, y1, l, h);
        } else if (sscanf(command, "moveleft %d,%d+%d", &x1, &y1, &p) == 3) {
            printf("Movido retangulo em (%d, %d) para a esquerda por %d\n", x1, y1, p);
            move_rectangle(x1, y1, p, -1); // Mover para a esquerda passando a direção -1
        } else if (sscanf(command, "moveright %d,%d+%d", &x1, &y1, &p) == 3) {
            printf("Movido retangulo em (%d, %d) para a direita por %d\n", x1, y1, p);
            move_rectangle(x1, y1, p, 1); // Mover para a direita passando a direção 1
        } else if (sscanf(command, "merge %d,%d+%d,%d", &x1, &y1, &x2, &y2) == 4) {
            printf("Retangulos unidos em (%d, %d) e (%d, %d)\n", x1, y1, x2, y2);
            Rectangle* rect1 = find_rectangle(x1, y1);
            Rectangle* rect2 = find_rectangle(x2, y2);
            if (rect1 && rect2) {
                mergeRetangulos(rect1, rect2);
            } else {
                printf("Erro: Nao foi possivel encontrar um ou ambos os retangulos nas posicoes especificadas.\n");
            }
        } else {
            printf("Erro: Comando invalido.\n");
        }

        // Exibe o mundo após cada comando *NOVO EfolioB*
        display_world();
    }

    free(command);
}
