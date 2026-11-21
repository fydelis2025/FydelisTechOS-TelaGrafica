#ifndef FYDELIS_LOGO_H
#define FYDELIS_LOGO_H
#include <stdint.h>

#define LOGO_LARG 64
#define LOGO_ALT  64

// Logo FydelisTechOS 64x64 em cores RGBA (ou use índice + paleta)
#define LOGO_TAM_PIXELS (LOGO_LARG * LOGO_ALT)
extern const uint32_t LOGO_PIXELS[LOGO_TAM_PIXELS];

// Versão 1-bit (preto/transparente) se quiser logo menor/combinar com cores
#define LOGO_MINI_LARG 32
#define LOGO_MINI_ALT  32
extern const uint8_t LOGO_MINI_BITS[LOGO_MINI_ALT]; // 32 bits por linha

#endif
