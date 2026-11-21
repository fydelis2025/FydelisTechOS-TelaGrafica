/*
 * FydelisTechOS — Ponto de entrada do shell gráfico
 *
 * Responsabilidades do main.c:
 *   1. Configurar a janela X11 e o canal de vídeo (framebuffer -> tela)
 *   2. Rodar o loop de eventos (mouse/teclado)
 *   3. Delegar toda a lógica de UI para apps.c (EstadoUI)
 *
 * Nada de desenho ou regra de interface vive aqui.
 */

#include "../include/gui.h"
#include "../include/apps.h"

#include <X11/Xutil.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* Estado global do processo                                           */
/* ------------------------------------------------------------------ */

uint32_t fb_tela[LARG_TELA * ALT_TELA];

typedef struct {
    Display*  dpy;
    Window    janela;
    GC        gc;
    XImage*   img;
    int       ok;
} Video;

static EstadoUI ui;
static Video    video;

/* ------------------------------------------------------------------ */
/* Camada de vídeo (X11)                                               */
/* ------------------------------------------------------------------ */

static int video_iniciar(void) {
    video.ok = 0;

    video.dpy = XOpenDisplay(NULL);
    if (!video.dpy) {
        fprintf(stderr, "[fydelis] erro: nao foi possivel abrir o display X11\n");
        return 0;
    }

    const int scr = DefaultScreen(video.dpy);

    video.janela = XCreateSimpleWindow(
        video.dpy, DefaultRootWindow(video.dpy),
        50, 50, LARG_TELA, ALT_TELA, 0,
        BlackPixel(video.dpy, scr), 0x10141C);

    XStoreName(video.dpy, video.janela, "FydelisTechOS - Area de Trabalho");
    XSelectInput(video.dpy, video.janela,
                 ExposureMask | StructureNotifyMask |
                 PointerMotionMask | ButtonPressMask | KeyPressMask);

    video.gc = XCreateGC(video.dpy, video.janela, 0, NULL);

    video.img = XCreateImage(
        video.dpy, DefaultVisual(video.dpy, scr),
        24, ZPixmap, 0,
        (char*)fb_tela, LARG_TELA, ALT_TELA, 32, LARG_TELA * 4);

    if (!video.img) {
        fprintf(stderr, "[fydelis] erro: falha ao criar XImage\n");
        XFreeGC(video.dpy, video.gc);
        XDestroyWindow(video.dpy, video.janela);
        XCloseDisplay(video.dpy);
        return 0;
    }

    video.ok = 1;
    XMapWindow(video.dpy, video.janela);
    return 1;
}

static void video_apresentar(void) {
    XPutImage(video.dpy, video.janela, video.gc, video.img,
              0, 0, 0, 0, LARG_TELA, ALT_TELA);
    XFlush(video.dpy);
}

static void video_encerrar(void) {
    if (!video.ok) return;
    video.img->data = NULL;   /* nao deixar o X11 liberar nosso fb estatico */
    XDestroyImage(video.img);
    XFreeGC(video.dpy, video.gc);
    XDestroyWindow(video.dpy, video.janela);
    XCloseDisplay(video.dpy);
}

/* ------------------------------------------------------------------ */
/* Loop de eventos                                                     */
/* ------------------------------------------------------------------ */

static void processar_evento(const XEvent* e, int* precisa_render) {
    switch (e->type) {

    case Expose:
    case ConfigureNotify:
        *precisa_render = 1;
        break;

    case MotionNotify:
        apps_hover(&ui, e->xmotion.x, e->xmotion.y);
        *precisa_render = 1;
        break;

    case ButtonPress:
        if (e->xbutton.button == Button1) {
            apps_click(&ui, e->xbutton.x, e->xbutton.y);
            *precisa_render = 1;
        }
        break;

    case KeyPress:
        /* TODO: rotear teclas para a UI (apps_tecla()) no futuro */
        ui.sair = 1;
        break;
    }
}

static void loop_principal(void) {
    apps_render(&ui);   /* primeiro frame: janela nasce com a tela pronta */
    video_apresentar();

    for (;;) {
        XEvent e;
        XNextEvent(video.dpy, &e);

        int precisa_render = 0;
        processar_evento(&e, &precisa_render);

        if (ui.sair) break;

        if (precisa_render) {
            apps_render(&ui);
            video_apresentar();
        }
    }
}

/* ------------------------------------------------------------------ */
/* main                                                                */
/* ------------------------------------------------------------------ */

int main(void) {
    memset(&ui, 0, sizeof(ui));
    memset(fb_tela, 0, sizeof(fb_tela));
    gui_inicializar(fb_tela, LARG_TELA, ALT_TELA);

    if (!video_iniciar()) {
        fprintf(stderr, "[fydelis] falha na inicializacao do video\n");
        return EXIT_FAILURE;
    }

    loop_principal();

    video_encerrar();
    return EXIT_SUCCESS;
}
