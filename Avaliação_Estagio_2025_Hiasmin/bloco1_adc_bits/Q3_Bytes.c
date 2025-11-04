#include <stdio.h>
#include <stdint.h>

/*
 * Questao 3 - Converter valor decimal de 32 bits em vetor de bytes (8 bits)
 *
 * Descricao:
 *   Este programa pega o valor decimal 10000000 (0x00989680 em hexadecimal)
 *   e o separa em 4 bytes individuais, armazenando-os em um vetor de 8 bits.
 */

int main()
{
    uint32_t valor = 10000000; // Valor em decimal (10.000.000)
    uint8_t bytes[4];          // Vetor para armazenar os bytes

    // Quebra o valor em 4 bytes (Big Endian)
    bytes[0] = (valor >> 24) & 0xFF;
    bytes[1] = (valor >> 16) & 0xFF;
    bytes[2] = (valor >> 8) & 0xFF;
    bytes[3] = valor & 0xFF;

    // Exibe os bytes resultantes
    printf("Valor original: %u\n", valor);
    printf("Bytes separados:\n");
    printf("Byte 0: 0x%02X\n", bytes[0]);
    printf("Byte 1: 0x%02X\n", bytes[1]);
    printf("Byte 2: 0x%02X\n", bytes[2]);
    printf("Byte 3: 0x%02X\n", bytes[3]);

    return 0;
}

/*
Explicacao:
- O valor 10000000 (decimal) equivale a 0x00989680 em hexadecimal.
- Cada byte e obtido deslocando o valor para a direita e aplicando uma mascara 0xFF.
- Resultado esperado:
    Byte 0 = 00
    Byte 1 = 98
    Byte 2 = 96
    Byte 3 = 80
- Esses bytes podem ser recombinados para formar novamente o valor original.
*/
