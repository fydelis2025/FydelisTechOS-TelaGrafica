#ifndef FYDELIS_GUI_H
#define FYDELIS_GUI_H

#include <stdint.h>
#include <stddef.h>
#include "cores.h"

typedef struct { int x, y, w, h; } Rect;

// Núcleo / framebuffer
void gui_inicializar(uint32_t* framebuffer, int larg, int alt);
uint32_t* gui_obter_framebuffer(void);
int gui_obter_largura(void);
int gui_obter_altura(void);

// Primitivas
void limpar_tela(Cor cor);
void desenhar_pixel(int x, int y, Cor cor);      // <- NOVO
void desenhar_linha(int x1, int y1, int x2, int y2, Cor cor); // <- NOVO
void desenhar_retangulo(Rect r, Cor cor);
void desenhar_retangulo_borda(Rect r, Cor fundo, Cor borda, int esp);
void desenhar_texto(int x, int y, const char* texto, Cor cor, int tam);
int  largura_texto(const char* texto, int tam);

// Componentes
void desenhar_icone(Rect r, const char* nome, Cor cor);
void desenhar_barra_tarefas(void);
void desenhar_desktop(void);   // tela completa

#define LARG_TELA 1024
#define ALT_TELA  768
extern uint32_t fb_tela[LARG_TELA * ALT_TELA];

#endif
