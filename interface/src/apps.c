#include "../include/apps.h"
#include "../include/barra_tarefas.h"
#include "../include/menu_iniciar.h"
#include <string.h>
#include <stdio.h> 

static const AppId apps_na_barra[5] = {
    APP_WRITER, APP_CALC, APP_SLIDE, APP_TERM, APP_FILES
};

const char* app_nome(AppId a) {
    switch (a) {
    case APP_WRITER: return "Writer";
    case APP_CALC:   return "Calc";
    case APP_SLIDE:  return "Slide";
    case APP_TERM:   return "Term";
    case APP_FILES:  return "Files";
    default:         return "";
    }
}

// ---------- posições clicáveis ----------

static Rect area_botao_menu(void) {
    return (Rect){10, gui_obter_altura() - 34, 90, 28};
}

static Rect area_botao_app(int i) {
    return (Rect){110 + i * 140, gui_obter_altura() - 34, 130, 28};
}

static int ponto_no_rect(int x, int y, Rect r) {
    return x >= r.x && x < r.x + r.w && y >= r.y && y < r.y + r.h;
}

// ---------- eventos ----------

void apps_hover(EstadoUI* ui, int x, int y) {
    ui->hover = APP_NENHUM;
    ui->hover_menu = -1;

    if (ui->menu_iniciar) {
        ui->hover_menu = menu_iniciar_item_em(x, y);
        if (ui->hover_menu >= 0) return;
    }

    for (int i = 0; i < 5; i++)
        if (ponto_no_rect(x, y, area_botao_app(i))) {
            ui->hover = apps_na_barra[i];
            return;
        }
}

void apps_click(EstadoUI* ui, int x, int y) {
    // 1) clique no menu (se aberto) — trata itens / fecha
    if (ui->menu_iniciar && menu_iniciar_click(ui, x, y))
        return;

    // 2) botão MENU
    if (ponto_no_rect(x, y, area_botao_menu())) {
        ui->menu_iniciar = !ui->menu_iniciar;
        return;
    }

    // 3) botões de apps da barra
    for (int i = 0; i < 5; i++) {
        Rect r = area_botao_app(i);
        AppId id = apps_na_barra[i];
        if (ponto_no_rect(x, y, r)) {
            if (ui->janelas[id].aberta && ui->foco == id) {
                ui->janelas[id].aberta = 0;          // toggle: abre/fecha
            } else {
                if (!ui->janelas[id].aberta) {       // posição inicial em cascata
                    ui->janelas[id].x = 140 + i * 30;
                    ui->janelas[id].y = 70 + i * 30;
                    ui->janelas[id].w = 520;
                    ui->janelas[id].h = 360;
                }
                ui->janelas[id].aberta = 1;
                ui->foco = id;
            }
            ui->menu_iniciar = 0;
            return;
        }
    }

    // 4) clique no desktop fecha o menu
    ui->menu_iniciar = 0;
}

// ---------- render ----------

static void render_janela_app(AppId id, Janela j, int focada) {
    Cor fundo     = {18, 22, 33};
    Cor barra     = focada ? (Cor){35, 25, 52} : (Cor){24, 28, 40};
    Cor borda     = focada ? ROXO_NEON : (Cor){51, 65, 85};

    // Sombra suave da janela
    desenhar_retangulo((Rect){j.x + 6, j.y + 6, j.w, j.h}, (Cor){4, 6, 10});
    // Borda principal da janela
    desenhar_retangulo_borda((Rect){j.x, j.y, j.w, j.h}, fundo, borda, 1);

    // Barra de título
    desenhar_retangulo((Rect){j.x, j.y, j.w, 26}, barra);
    {
        char titulo[48];
        snprintf(titulo, sizeof(titulo), "%s — FydelisTechOS", app_nome(id));
        desenhar_texto(j.x + 10, j.y + 9, titulo, BRANCO, 8);
    }
    
    // Botões de controle de janela estilo moderno (Fechar vermelho, Minimizar/Maximizar neutros)
    desenhar_retangulo((Rect){j.x + j.w - 22, j.y + 6, 14, 14}, VERMELHO);
    desenhar_retangulo((Rect){j.x + j.w - 42, j.y + 6, 14, 14}, CINZA_ESCURO);
    desenhar_retangulo((Rect){j.x + j.w - 62, j.y + 6, 14, 14}, CINZA_ESCURO);

    // Área interna de conteúdo
    desenhar_retangulo((Rect){j.x + 8, j.y + 34, j.w - 16, j.h - 42},
                       (Cor){11, 13, 20});
    {
        char linha[64];
        snprintf(linha, sizeof(linha), "> %s pronto e carregado.", app_nome(id));
        desenhar_texto(j.x + 16, j.y + 48, linha, LILAS, 8);
    }
}

void apps_render(EstadoUI* ui) {
    // ===== fundo =====
    int larg = gui_obter_largura();
    int alt  = gui_obter_altura();

    limpar_tela(ESCURO);
    Cor grade = {24, 30, 42};
    for (int x = 0; x < larg; x += 32)
        desenhar_retangulo((Rect){x, 0, 1, alt}, grade);
    for (int y = 0; y < alt; y += 32)
        desenhar_retangulo((Rect){0, y, larg, 1}, grade);

    // ===== barra superior =====
    desenhar_retangulo((Rect){0, 0, larg, 36}, PRETO);
    desenhar_retangulo((Rect){0, 34, larg, 2}, VERDE_NEON);
    desenhar_texto(12, 12, "FydelisTechOS", VERDE_NEON, 16);
    desenhar_texto(larg - largura_texto("12:00:00", 16) - 12, 12,
                   "12:00:00", BRANCO, 16);

    // ===== janelas (não focadas primeiro, focada por cima) =====
    for (int i = 0; i < 5; i++) {
        AppId id = apps_na_barra[i];
        Janela* j = &ui->janelas[id];
        if (j->aberta && id != ui->foco)
            render_janela_app(id, *j, 0);
    }
    if (ui->foco != APP_NENHUM && ui->janelas[ui->foco].aberta)
        render_janela_app(ui->foco, ui->janelas[ui->foco], 1);

    // ===== barra de tarefas (sempre por cima das janelas) =====
    barra_tarefas_render(ui);

    // ===== menu iniciar (o mais alto) =====
    if (ui->menu_iniciar)
        menu_iniciar_render(ui);
}

Cor app_cor(AppId id) {
    switch (id) {
    case APP_WRITER: return AZUL;
    case APP_CALC:   return VERDE;
    case APP_SLIDE:  return ROXO_NEON;   // Atualizado para roxo neon
    case APP_TERM:   return ROXO_NEON;   // Terminal usando o destaque moderno
    case APP_FILES:  return AMARELO;
    default:         return BRANCO;
    }
}
