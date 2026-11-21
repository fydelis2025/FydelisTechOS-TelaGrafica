#ifndef FYDELIS_MENU_INICIAR_H
#define FYDELIS_MENU_INICIAR_H
#include "gui.h"
#include "apps.h"

void menu_iniciar_render(EstadoUI* ui);
int  menu_iniciar_item_em(int x, int y);
int  menu_iniciar_click(EstadoUI* ui, int x, int y);   // <- era "int x, y"

#endif
