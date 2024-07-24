#ifndef RECTANGLE_H
#define RECTANGLE_H

// Estrutura do retângulo
typedef struct {
    int x, y; // Coordenadas da ponta inferior esquerda
    int width, height; // Comprimento e largura
} Rectangle;

void init_rectangles(); // Inicia a contagem
void create_rectangle(int x, int y, int width, int height); // Cria um retângulo
void move_rectangle(int x, int y, int p, int direction); // Move o retângulo para a esquerda ou direita
void apply_gravity(); // Aplica o efeito da gravidade aos retângulos
Rectangle* find_rectangle(int x, int y); // Encontra um retângulo a partir de um ponto
Rectangle* get_rectangles(); // Retorna a lista de retângulos
int get_rectangle_count(); // Retorna o número de retângulos
int check_overlap(int x, int y, int width, int height, int ignore_index); // Verifica se há retângulos na mesma posição
int mergePossivel(Rectangle* rect1, Rectangle* rect2); // Verifica se pode haver merge entre dois retângulos
void alertaSobreposicao(); // Alerta o utilizador para retângulos adjacentes
void mergeRetangulos(Rectangle* rect1, Rectangle* rect2); // Função que une dois retângulos

#endif // RECTANGLE_H