#include "gui.h"
#include "../include/fonte.h"
#include <string.h>

void desenhar_texto(int x, int y, const char* texto, Cor cor, int tam) {
    int escala = tam / 8;
    if (escala < 1) escala = 1;

    while (*texto) {
        unsigned char c = (unsigned char)*texto;
        if (c >= 32 && c < 128) {
            const uint8_t* glyph = FONTE_8X8[c - 32];
            for (int i = 0; i < 8; i++) {
                uint8_t linha = glyph[i];
                for (int j = 0; j < 8; j++) {
                    // Leitura direta corrigida para alinhar as letras corretamente
                    if (linha & (1 << j)) {
                        for (int sy = 0; sy < escala; sy++) {
                            for (int sx = 0; sx < escala; sx++) {
                                desenhar_pixel(x + (j * escala) + sx, 
                                               y + (i * escala) + sy, cor);
                            }
                        }
                    }
                }
            }
        }
        x += (8 * escala);
        texto++;
    }
}

int largura_texto(const char* texto, int tam) {
    int escala = tam / 8;
    if (escala < 1) escala = 1;
    return (int)strlen(texto) * 8 * escala;
}
