#ifndef FYDELIS_WIDGETS_H
#define FYDELIS_WIDGETS_H
#include "gui.h"
#include "assets.h"

#define MAX_WIDGETS 32

typedef enum {
    WIDGET_ICON_DESKTOP,   // ícone com bitmap + rótulo
    WIDGET_BOTAO_MENU,     // botão da barra (logo + texto)
    WIDGET_BOTAO_TAREFA,   // botão de janela aberta
} WidgetTipo;

typedef struct {
    WidgetTipo tipo;
    Rect       area;          // área clicável
    const uint8_t* icone;     // bitmap (pode ser NULL)
    const char*   rotulo;
    Cor           cor;
    int           hover;      // estado visual (mouse em cima)
    void (*ao_clicar)(struct Widget* self);  // callback
    void*         dados;      // dado livre do app
} Widget;

// Gerencia a lista de widgets da tela atual
void widgets_limpar(void);
Widget* widgets_adicionar(WidgetTipo tipo, Rect area,
                          const uint8_t* icone, const char* rotulo, Cor cor);
void widgets_desenhar_todos(void);
void widgets_mouse_mover(int x, int y);        // atualiza hover
Widget* widgets_mouse_clique(int x, int y);    // retorna o widget clicado (ou NULL)

#endif
