#ifndef FYDELIS_CORES_H
#define FYDELIS_CORES_H
#include <stdint.h>

typedef struct { uint8_t r, g, b; } Cor;

extern const Cor AZUL;
extern const Cor ROXO_NEON;    
extern const Cor LILAS;        
extern const Cor ROSA_NEON;    
extern const Cor BRANCO;
extern const Cor ESCURO;       
extern const Cor CINZA_CLARO;
extern const Cor CINZA_ESCURO;
extern const Cor CINZA_PAINEL; 
extern const Cor PRETO;
extern const Cor VERMELHO;
extern const Cor AMARELO;
extern const Cor VERDE;

// Macros de compatibilidade para evitar erros nos arquivos antigos
#define VERDE_NEON ROXO_NEON
#define ROXO       ROXO_NEON

#endif
