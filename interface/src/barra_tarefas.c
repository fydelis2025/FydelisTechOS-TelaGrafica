#include "../include/barra_tarefas.h"
#include <stdio.h>

static void botao(Rect r, const char* texto, Cor fundo, Cor texto_cor) {
    desenhar_retangulo_borda(r, fundo, BRANCO, 1);
    int tw = largura_texto(texto, 8);
    desenhar_texto(r.x + (r.w - tw) / 2, r.y + (r.h - 8) / 2, texto, texto_cor, 8);
}

void barra_tarefas_render(EstadoUI* ui) {
    int larg = gui_obter_largura();
    int alt  = gui_obter_altura();

    desenhar_retangulo((Rect){0, alt - 40, larg, 40}, PRETO);
    desenhar_retangulo((Rect){0, alt - 42, larg, 2}, AZUL);

    // botão MENU (logo será inserida aqui)
    Cor fundo_menu = ui->menu_iniciar ? VERDE_NEON : (Cor){30, 38, 52};
    Cor cor_txt    = ui->menu_iniciar ? PRETO : BRANCO;
    botao((Rect){10, alt - 34, 90, 28}, "MENU", fundo_menu, cor_txt);

    // botões dos apps, com destaque de hover e "aberto"
    static const AppId apps[5] = {APP_WRITER, APP_CALC, APP_SLIDE, APP_TERM, APP_FILES};
    for (int i = 0; i < 5; i++) {
        AppId id = apps[i];
        Rect r = {110 + i * 140, alt - 34, 130, 28};

        Cor fundo = (ui->hover == id) ? (Cor){55, 65, 85} : CINZA_ESCURO;
        if (ui->janelas[id].aberta) {
            // barra de "task aberta" embaixo do botão
            desenhar_retangulo((Rect){r.x, r.y + r.h - 3, r.w, 3}, VERDE_NEON);
        }
        if (ui->foco == id && ui->janelas[id].aberta)
            fundo = (Cor){45, 70, 55};

        botao(r, app_nome(id), fundo, BRANCO);
    }

    // relógio
    const char* hora = "12:00";
    desenhar_texto(larg - largura_texto(hora, 16) - 14, alt - 28, hora, BRANCO, 16);
}
