#ifndef FYDELIS_ASSETS_H
#define FYDELIS_ASSETS_H
#include <stdint.h>
#include "gui.h"

// Logo do menu iniciar: 24x24 pixels, 1 bit por pixel (linha por linha, MSB à esquerda)
#define LOGO_W 24
#define LOGO_H 24
extern const uint8_t LOGO_FYDELIS[LOGO_H][3];

// Ícones 16x16, 1bpp — desenhados dentro do quadro do ícone
#define ICO_W 16
#define ICO_H 16
extern const uint8_t ICO_TERMINAL[ICO_H][2];
extern const uint8_t ICO_PASTA[ICO_H][2];
extern const uint8_t ICO_DOC[ICO_H][2];
extern const uint8_t ICO_CALC[ICO_H][2];
extern const uint8_t ICO_ENGRENAGEM[ICO_H][2];

// Renderiza um bitmap 1bpp na posição (x,y) com escala e cor
void desenhar_bitmap(int x, int y, int w, int h,
                     const uint8_t* dados, int stride_bytes,
                     Cor cor, int escala);

#endif
