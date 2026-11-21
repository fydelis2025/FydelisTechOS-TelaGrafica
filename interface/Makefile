CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -Iinclude
LDFLAGS = -lX11 -lm

SRC = src/main.c src/retangulo.c src/texto.c src/cores.c src/fonte.c \
      src/apps.c src/menu_iniciar.c src/barra_tarefas.c
BIN = fydelistechos

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(SRC) $(LDFLAGS)

clean:
	rm -f $(BIN)
