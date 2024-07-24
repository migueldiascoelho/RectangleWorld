#include "rectangle.h"
#include "graphics.h"
#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_RECTANGLES 20

static Rectangle rectangles[MAX_RECTANGLES];
static int rectangle_count = 0;

void init_rectangles() {
    rectangle_count = 0; // Inicializa a contagem a 0
}

void create_rectangle(int x, int y, int width, int height) {
    if (rectangle_count < MAX_RECTANGLES) {
        // Primeiro verifica se há retângulos na mesma posição
        if (check_overlap(x, y, width, height, -1)) { // -1 para ignorar qualquer índice, pois é um novo retângulo
            printf("Erro: Não se consegue colocar retângulo em (%d, %d), já existe outro retângulo nesse espaço.\n", x, y);
            return;
        }
        Rectangle new_rect = {x - 1, y - 1, width, height}; // Ajusta as coordenadas por -1 considerando índices a começar em 0
        rectangles[rectangle_count++] = new_rect;
        apply_gravity(); // Aplica o efeito da gravidade depois de criar um retângulo
        alertaSobreposicao(); // Verifica se pode haver merge
    } else {
        printf("Erro: Número máximo de retângulos atingido.\n");
    }
}

int check_overlap(int x, int y, int width, int height, int ignore_index) {
    // X e Y ajustados para índice 0
    x -= 1;
    y -= 1;
    for (int i = 0; i < rectangle_count; ++i) {
        // Ignora o retângulo que está a ser movido
        if (i == ignore_index) continue;
        
        Rectangle rect = rectangles[i];
        if (x < rect.x + rect.width &&
            x + width > rect.x &&
            y < rect.y + rect.height &&
            y + height > rect.y) {
            return 1; // Retângulo na mesma posição encontrado
        }
    }
    return 0; // Sem retângulo na mesma posição
}

Rectangle* find_rectangle(int x, int y) {
    // Ajusta as coordenadas x e y para um índice baseado em 0
    x -= 1;
    y -= 1;
    
    // Percorre todos os retângulos na lista
    for (int i = 0; i < rectangle_count; ++i) {
        // Verifica se o ponto (x, y) está dentro dos limites do retângulo atual
        if (rectangles[i].x <= x && x < rectangles[i].x + rectangles[i].width &&
            rectangles[i].y <= y && y < rectangles[i].y + rectangles[i].height) {
            // Se o ponto estiver dentro do retângulo, retorna um ponteiro para este retângulo
            return &rectangles[i];
        }
    }
    
    // Se nenhum retângulo contiver o ponto (x, y), retorna NULL
    return NULL;
}

void move_rectangle(int x, int y, int p, int direction) {
    Rectangle* rect = find_rectangle(x, y);
    if (rect) {
        // Calcular a nova posição do retângulo
        int new_x = rect->x + direction * p;
        int rect_index = rect - rectangles; // Obtém o índice do retângulo

        // Verificar se já existe outro retângulo na nova posição, ignorando o próprio retângulo
        if (check_overlap(new_x + 1, rect->y + 1, rect->width, rect->height, rect_index)) {
            printf("Erro: Nao se consegue mover retangulo para (%d, %d) porque ja existe outro no mesmo espaco.\n", new_x + 1, rect->y + 1);
            return;
        }

        // Atualizar a posição do retângulo
        rect->x = new_x;
        apply_gravity(); // Aplica o efeito da gravidade depois de mover
        alertaSobreposicao(); // Verifica se pode ocorrer merge
    } else {
        printf("Erro: Retangulo nao encontrado em (%d, %d).\n", x, y);
    }
}

void apply_gravity() {
    for (int i = 0; i < rectangle_count; ++i) {
        int can_fall = 1;  // Define a variável para verificar se o retângulo pode cair
        while (can_fall && rectangles[i].y > 0) {
            can_fall = 1;
            for (int j = 0; j < rectangle_count; ++j) {
                // Se o retângulo atual (i) colidir com qualquer outro retângulo (j) logo abaixo dele
                if (i != j &&
                    rectangles[i].x < rectangles[j].x + rectangles[j].width && // Verifica se já existe retângulo nesse espaço horizontal
                    rectangles[i].x + rectangles[i].width > rectangles[j].x &&
                    // Verifica se já existe retângulo nesse espaço vertical
                    rectangles[i].y - 1 == rectangles[j].y + rectangles[j].height - 1) {
                    can_fall = 0; // O retângulo não pode cair mais
                    break;
                }
            }
            if (can_fall) {
                rectangles[i].y--; // O retângulo cai uma unidade
            }
        }
    }
}

Rectangle* get_rectangles() {
    return rectangles; // Retorna o array de retângulos
}

int get_rectangle_count() {
    return rectangle_count; // Retorna o número de retângulos
}

// Verifica se é possível unir retângulos *NOVO EfolioB*
int mergePossivel(Rectangle* rect1, Rectangle* rect2) {
    // Verifica se rect1 e rect2 são adjacentes horizontalmente
    if ((rect1->y == rect2->y && rect1->height == rect2->height && 
        (rect1->x + rect1->width == rect2->x || rect2->x + rect2->width == rect1->x)) ||
        // Verifica se rect1 e rect2 são adjacentes verticalmente
        (rect1->x == rect2->x && rect1->width == rect2->width && 
        (rect1->y + rect1->height == rect2->y || rect2->y + rect2->height == rect1->y))) {
        return 1; // Fusão possível
    }
    return 0; // Fusão não possível
}

// Aviso quando retângulos podem ser unidos *NOVO EfolioB*
void alertaSobreposicao() {
    // Percorre todos os retângulos
    for (int i = 0; i < rectangle_count; ++i) {
        for (int j = i + 1; j < rectangle_count; ++j) {
            if (mergePossivel(&rectangles[i], &rectangles[j])) {
                printf("Merge possivel entre retangulos em (%d, %d) e (%d, %d)\n", rectangles[i].x + 1, rectangles[i].y + 1, rectangles[j].x + 1, rectangles[j].y + 1);
                return; // Encontra a primeira fusão possível e sai
            }
        }
    }
}

// Função que une retângulos *NOVO EfolioB*
void mergeRetangulos(Rectangle* rect1, Rectangle* rect2) {
    // Verifica se a fusão é possível
    if (!mergePossivel(rect1, rect2)) {
        printf("Erro: A fusao entre retangulos em (%d, %d) e (%d, %d) nao e possivel.\n", rect1->x + 1, rect1->y + 1, rect2->x + 1, rect2->y + 1);
        return;
    }

    // Determina os limites do novo retângulo
    int new_x = rect1->x < rect2->x ? rect1->x : rect2->x;
    int new_y = rect1->y < rect2->y ? rect1->y : rect2->y;
    int new_width = (rect1->x + rect1->width > rect2->x + rect2->width ? rect1->x + rect1->width : rect2->x + rect2->width) - new_x;
    int new_height = (rect1->y + rect1->height > rect2->y + rect2->height ? rect1->y + rect1->height : rect2->y + rect2->height) - new_y;

    // Atualiza o primeiro retângulo com os novos limites
    rect1->x = new_x;
    rect1->y = new_y;
    rect1->width = new_width;
    rect1->height = new_height;

    // Remove o segundo retângulo deslocando os retângulos subsequentes para trás
    int index = rect2 - rectangles;
    for (int i = index; i < rectangle_count - 1; ++i) {
        rectangles[i] = rectangles[i + 1];
    }
    rectangle_count--; // Reduz a contagem de retângulos
    alertaSobreposicao(); // Verifica se pode haver outro merge
}
