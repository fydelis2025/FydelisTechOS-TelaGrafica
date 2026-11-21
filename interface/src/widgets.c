#include "../include/widgets.h"
#include <string.h>
#include <stdlib.h>

static Widget lista[MAX_WIDGETS];
static int total = 0;

void widgets_limpar(void) { total = 0; }

Widget* widgets_adicionar(WidgetTipo tipo, Rect area,
                          const uint8_t* icone, const char* rotulo, Cor cor) {
    if (total >= MAX_WIDGET
