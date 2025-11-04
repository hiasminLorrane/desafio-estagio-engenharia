// Questao 5 - UART: montar quadro 8N1 (start, 8 bits LSB-first, stop)
// ASCII-only comments (sem acentos) para evitar problemas de codificacao.

#include <stdio.h>
#include <stdint.h>

// Gera e imprime o quadro UART 8N1 para um byte dado (LSB first)
void imprimir_quadro_uart_8N1(uint8_t dado, int baud)
{
    int bits[10]; // start + 8 dados + stop

    // start bit
    bits[0] = 0;
    // 8 bits de dados (LSB primeiro)
    for (int i = 0; i < 8; i++)
        bits[1 + i] = (dado >> i) & 0x01;
    // stop bit
    bits[9] = 1;

    // tempo de bit em microssegundos
    double tbit_us = 1000000.0 / (double)baud;

    printf("Questao 5 - UART 8N1\n");
    printf("----------------------\n");
    printf("Dado: 0x%02X (%u, '%c')\n", dado, (unsigned)dado, (dado >= 32 && dado <= 126) ? (char)dado : '.');
    printf("Baud rate: %d bps, Tbit: %.2f us\n", baud, tbit_us);

    printf("Frame (LSB first): ");
    for (int i = 0; i < 10; i++)
        printf("%d%s", bits[i], (i < 9 ? " " : ""));
    printf("\n");

    printf("Legenda: [start]=0, [dados]=8 bits, [stop]=1\n");
}

int main(void)
{
    // Exemplo: caractere 'K' (0x4B = 75 decimal)
    uint8_t dado = 0x4B;
    int baud = 9600; // 9600 bps

    imprimir_quadro_uart_8N1(dado, baud);
    return 0;
}

