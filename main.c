#include <stdio.h>
#include "rectangle.h"
#include "commands.h"
#include "graphics.h"

int main() {
    init_rectangles(); // Começa a contagem de retângulos
    process_commands(); // Inicia os comandos
    return 0;
}
