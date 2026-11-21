#include "gui.h"
#include "../include/cores.h"

// Instanciação das cores globais
const Cor AZUL   = {0, 102, 204};
const Cor VERDE  = {46, 125, 50};
const Cor ROXO   = {94, 53, 177};
const Cor BRANCO = {255, 255, 255};
const Cor ESCURO = {20, 25, 35};
const Cor CINZA_CLARO = {200, 200, 200};
const Cor PRETO  = {0, 0, 0};

void desenhar_area_trabalho(void) {
    int larg = gui_obter_largura();
    int alt = gui_obter_altura();
    
    limpar_tela(ESCURO);
    
    // Barra superior
    Rect topo = {0, 0, larg, 36};
    // desenhar_retangulo(topo, AZUL);
    
    // Textos e elementos da interface...
}
