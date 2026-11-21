#include "../include/menu_iniciar.h"
#include <stdio.h>
#include <math.h>      // <- cos/sin
#include <stdlib.h>    // <- abs

#define MENU_LARG 240
#define MENU_ITEM_ALT 32

static const AppId menu_apps[5] = {APP_WRITER, APP_CALC, APP_SLIDE, APP_TERM, APP_FILES};
static const char* menu_nomes[5] = {"Writer", "Calc", "Slide", "Terminal", "Arquivos"};

static Rect area_menu(void) {
    return (Rect){8, gui_obter_altura() - 42 - 5 * MENU_ITEM_ALT - 70,
                  MENU_LARG, 5 * MENU_ITEM_ALT + 70};
}

// "logo" do menu: escudo hexagonal com FT (fase 1 — programática)
static void desenhar_logo_menu(Rect cabecalho) {
    int cx = cabecalho.x + 28, cy = cabecalho.y + cabecalho.h / 2;
    int raio = 18;
    int px[6], py[6];
    for (int a = 0; a < 6; a++) {
        double ang = (a * 60 - 30) * 3.14159 / 180.0;
        px[a] = cx + (int)(raio * cos(ang));
        py[a] = cy + (int)(raio * sin(ang));
    }
    for (int a = 0; a < 6; a++) {
        int b = (a + 1) % 6;
        // linha de (px[a],py[a]) a (px[b],py[b]) — Bresenham simples
        int x0 = px[a], y0 = py[a], x1 = px[b], y1 = py[b];
        int dx = abs(x1 - x0), dy = abs(y1 - y0);
        int sx = x0 < x1 ? 1 : -1, sy = y0 < y1 ? 1 : -1;
        int err = dx - dy;
        for (;;) {
            desenhar_pixel(x0, y0, VERDE_NEON);
            if (x0 == x1 && y0 == y1) break;
            int e2 = 2 * err;
            if (e2 > -dy) { err -= dy; x0 += sx; }
            if (e2 <  dx) { err += dx; y0 += sy; }
        }
    }
    desenhar_texto(cx - 8, cy - 4, "FT", VERDE_NEON, 8);
    desenhar_texto(cabecalho.x + 56, cabecalho.y + cabecalho.h / 2 - 4,
                   "FydelisTech", VERDE_NEON, 8);
}

void menu_iniciar_render(EstadoUI* ui) {
    Rect m = area_menu();

    // sombra + painel
    desenhar_retangulo((Rect){m.x + 4, m.y + 4, m.w, m.h}, (Cor){5, 8, 12});
    desenhar_retangulo_borda(m, (Cor){18, 22, 30}, VERDE_NEON, 1);

    // cabeçalho com a logo
    Rect cab = {m.x, m.y, m.w, 60};
    desenhar_retangulo(cab, (Cor){10, 14, 20});
    desenhar_logo_menu(cab);
    desenhar_texto(m.x + 8, m.y + 44, "root@fydelis", CINZA_CLARO, 8);

    // itens
    for (int i = 0; i < 5; i++) {
        Rect item = {m.x + 1, m.y + 60 + i * MENU_ITEM_ALT,
                     m.w - 2, MENU_ITEM_ALT};
        if (ui->hover_menu == i)
            desenhar_retangulo(item, (Cor){35, 60, 45});
        else
            desenhar_retangulo(item, (Cor){18, 22, 30});

        // quadrado colorido do app
         desenhar_retangulo((Rect){item.x + 8, item.y + 8, 16, 16},
                           app_cor(menu_apps[i]));
        desenhar_texto(item.x + 34, item.y + 12, menu_nomes[i], BRANCO, 8);
    }
}

int menu_iniciar_item_em(int x, int y) {
    Rect m = area_menu();
    if (y < m.y + 60 || y >= m.y + m.h || x < m.x || x >= m.x + m.w)
        return -1;
    int i = (y - m.y - 60) / MENU_ITEM_ALT;
    if (i < 0 || i >= 5) return -1;
    return i;
}

int menu_iniciar_click(EstadoUI* ui, int x, int y) {
    int item = menu_iniciar_item_em(x, y);

    if (item < 0) {
        // clicou fora do menu → fecha
        Rect m = area_menu();
        if (x < m.x || x >= m.x + m.w || y < m.y || y >= m.y + m.h) {
            ui->menu_iniciar = 0;
            return 1;
        }
        return 0; // clicou no cabeçalho do menu: ignora
    }

    // abriu um app pelo menu
    AppId id = menu_apps[item];
    if (!ui->janelas[id].aberta) {
        ui->janelas[id].x = 160;
        ui->janelas[id].y = 80;
        ui->janelas[id].w = 520;
        ui->janelas[id].h = 360;
    }
    ui->janelas[id].aberta = 1;
    ui->foco = id;
    ui->menu_iniciar = 0;
    return 1;
}
