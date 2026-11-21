#include "../include/gui.h"
#include "../include/icones.h"
#include "../include/barra_tarefas.h"

// grade de fundo sutil (estilo hacker)
static void desenhar_grade(void) {
    int larg = gui_obter_largura();
    int alt  = gui_obter_altura();
    Cor linha = {20, 24, 38}; // Grade sutil e limpa
    for (int x = 0; x < larg; x += 40)
        desenhar_retangulo((Rect){x, 0, 1, alt}, linha);
    for (int y = 0; y < alt; y += 40)
        desenhar_retangulo((Rect){0, y, larg, 1}, linha);
}

static void desenhar_barra_superior(void) {
    int larg = gui_obter_largura();
    desenhar_retangulo((Rect){0, 0, larg, 36}, PRETO);
    // Linha de destaque inferior da barra superior em Roxo Neon
    desenhar_retangulo((Rect){0, 34, larg, 2}, ROXO_NEON);
    desenhar_texto(14, 12, "FydelisTechOS", ROXO_NEON, 16);
    desenhar_texto(larg - largura_texto("[ SECURE ]", 8) - 150, 12,
                   "[ SECURE ]", LILAS, 8);
    desenhar_texto(larg - largura_texto("12:00:00", 16) - 12, 12,
                   "12:00:00", BRANCO, 16);
}

static void desenhar_dock_lateral(void) {
    int alt = gui_obter_altura();
    desenhar_retangulo_borda((Rect){12, 60, 84, 480},
                             CINZA_ESCURO, (Cor){30, 38, 52}, 2);
    desenhar_icone((Rect){22, 72,  64, 64}, "Writer", AZUL);
    desenhar_icone((Rect){22, 152, 64, 64}, "Calc",   VERDE);
    desenhar_icone((Rect){22, 232, 64, 64}, "Slide",  ROXO);
    desenhar_icone((Rect){22, 312, 64, 64}, "Term",   VERDE_NEON);
    desenhar_icone((Rect){22, 392, 64, 64}, "Files",  AMARELO);
}

static void desenhar_painel_terminal(void) {
    int larg = gui_obter_largura();
    Rect term = {120, 60, larg - 250, 480};
    desenhar_retangulo_borda(term, (Cor){10, 14, 20}, VERDE_NEON, 2);

    // barra de título do "terminal"
    desenhar_retangulo((Rect){term.x, term.y, term.w, 20}, (Cor){25, 32, 44});
    desenhar_texto(term.x + 6, term.y + 6, "root@fydelis:~", VERDE_NEON, 8);

    desenhar_texto(term.x + 10, term.y + 34,
                   "> sistema iniciado... OK", BRANCO, 8);
    desenhar_texto(term.x + 10, term.y + 50,
                   "> modulos carregados : gui / fs / net", BRANCO, 8);
    desenhar_texto(term.x + 10, term.y + 66,
                   "> aguardando comando_", VERDE_NEON, 8);
}

void desenhar_desktop(void) {
    limpar_tela(ESCURO);
    desenhar_grade();
    desenhar_barra_superior();
    desenhar_dock_lateral();
    desenhar_painel_terminal();
    desenhar_barra_tarefas();
}
