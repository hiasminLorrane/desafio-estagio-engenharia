#include <stdio.h>
#include <stdint.h>

/*
 * Questao 2 - Armazenar 4 bytes recebidos via RS232 em uma variavel de 32 bits
 *
 * Descricao:
 *   Este programa simula a recepcao de 4 bytes (8 bits cada) via comunicacao serial
 *   e os combina em uma unica variavel de 32 bits (uint32_t).
 */

// Funcao que junta 4 bytes em uma unica variavel de 32 bits
uint32_t juntarBytes(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4)
{
    uint32_t valor = 0;

    valor |= ((uint32_t)b1 << 24); // byte mais significativo
    valor |= ((uint32_t)b2 << 16);
    valor |= ((uint32_t)b3 << 8);
    valor |= ((uint32_t)b4); // byte menos significativo

    return valor;
}

int main()
{
    // Simulacao de 4 bytes recebidos pela RS232
    uint8_t byte1 = 0x12;
    uint8_t byte2 = 0x34;
    uint8_t byte3 = 0x56;
    uint8_t byte4 = 0x78;

    // Combina os 4 bytes em um unico valor de 32 bits
    uint32_t resultado = juntarBytes(byte1, byte2, byte3, byte4);

    // Exibe o valor combinado em hexadecimal e decimal
    printf("Bytes combinados: 0x%08X (%u)\n", resultado, resultado);

    return 0;
}

/*
Explicacao:
- Cada byte e deslocado para a posicao correta usando operadores de deslocamento (<<)
- Exemplo:
    byte1 << 24 -> bits 31 a 24
    byte2 << 16 -> bits 23 a 16
    byte3 << 8  -> bits 15 a 8
    byte4       -> bits 7 a 0
- O operador bitwise OR (|) junta os valores deslocados.
Resultado final: 0x12345678
*/
