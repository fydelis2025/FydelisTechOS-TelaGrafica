#ifndef FYDELIS_APPS_H
#define FYDELIS_APPS_H
#include "gui.h"

typedef enum {
    APP_NENHUM = 0, APP_WRITER, APP_CALC, APP_SLIDE, APP_TERM, APP_FILES,
    APP_QTD
} AppId;

typedef struct {
    int aberta;
    int x, y, w, h;
} Janela;

typedef struct {
    Janela janelas[APP_QTD];
    AppId  foco;
    int    menu_iniciar;
    AppId  hover;            // botão da barra sob o mouse
    int    hover_menu;       // item do menu sob o mouse (-1 = nenhum)
    int    sair; 
} EstadoUI;

void apps_render(EstadoUI* ui);
void apps_hover(EstadoUI* ui, int x, int y);
void apps_click(EstadoUI* ui, int x, int y);
void apps_arrastar(EstadoUI* ui, int x, int y);  // arrastar janela (futuro)
void apps_render(EstadoUI* ui);

const char* app_nome(AppId a);

Cor app_cor(AppId id);

#endif
