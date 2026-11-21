#include "../include/gui.h"

static uint32_t* fb_base = NULL;
static int fb_larg = 0;
static int fb_alt  = 0;

void gui_inicializar(uint32_t* framebuffer, int larg, int alt) {
    fb_base = framebuffer;
    fb_larg = larg;
    fb_alt  = alt;
}

uint32_t* gui_obter_framebuffer(void) { return fb_base; }
int gui_obter_largura(void) { return fb_larg; }
int gui_obter_altura(void)  { return fb_alt; }

static inline uint32_t cor_para_pixel(Cor c) {
    return (0xFFu << 24) | ((uint32_t)c.r << 16) | ((uint32_t)c.g << 8) | (uint32_t)c.b;
}

void limpar_tela(Cor cor) {
    if (!fb_base) return;
    uint32_t pixel = cor_para_pixel(cor);
    size_t total = (size_t)fb_larg * (size_t)fb_alt;
    for (size_t i = 0; i < total; i++) fb_base[i] = pixel;
}

void desenhar_retangulo(Rect r, Cor cor) {
    if (!fb_base) return;

    int x1 = r.x, y1 = r.y;
    int x2 = r.x + r.w, y2 = r.y + r.h;

    // clip completo ANTES de desenhar
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 > fb_larg) x2 = fb_larg;
    if (y2 > fb_alt)  y2 = fb_alt;
    if (x1 >= x2 || y1 >= y2) return;

    uint32_t pixel = cor_para_pixel(cor);
    for (int y = y1; y < y2; y++) {
        uint32_t* linha = fb_base + (size_t)y * fb_larg + x1;
        for (int x = x1; x < x2; x++) *linha++ = pixel;
    }
}

void desenhar_retangulo_borda(Rect r, Cor fundo, Cor borda, int esp) {
    if (esp < 1) esp = 1;
    desenhar_retangulo(r, borda);
    Rect interno = {r.x + esp, r.y + esp, r.w - esp * 2, r.h - esp * 2};
    if (interno.w > 0 && interno.h > 0)
        desenhar_retangulo(interno, fundo);
}

void desenhar_pixel(int x, int y, Cor cor) {
    if (!fb_base || x < 0 || y < 0 || x >= fb_larg || y >= fb_alt) return;
    fb_base[y * fb_larg + x] = cor_para_pixel(cor);
}

void desenhar_linha(int x1, int y1, int x2, int y2, Cor cor) {
    int dx = x2 - x1, dy = y2 - y1;
    int sx = dx < 0 ? -1 : 1, sy = dy < 0 ? -1 : 1;
    dx = dx < 0 ? -dx : dx; dy = dy < 0 ? -dy : dy;
    int err = (dx > dy ? dx : -dy) / 2;
    for (;;) {
        desenhar_pixel(x1, y1, cor);
        if (x1 == x2 && y1 == y2) break;
        int e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 <  dy) { err += dx; y1 += sy; }
    }
}
