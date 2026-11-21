#include "../include/icones.h"

// Desenha ícone 64x64 com borda colorida, símbolo ">_" e rótulo abaixo
void desenhar_icone(Rect r, const char* nome, Cor cor) {
    Rect quadro = {r.x, r.y, 64, 64};
    desenhar_retangulo_borda(quadro, CINZA_ESCURO, cor, 2);

    // símbolo de terminal dentro do ícone
    int sw = largura_texto(">_", 16);
    desenhar_texto(r.x + (64 - sw) / 2, r.y + 24, ">_", cor, 16);

    // rótulo centralizado abaixo
    if (nome) {
        int tw = largura_texto(nome, 8);
        desenhar_texto(r.x + (64 - tw) / 2, r.y + 70, nome, BRANCO, 8);
    }
}
