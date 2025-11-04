#include <stdio.h>
#include <stdint.h>

/*
 * Questao 4 - Conversor D/A (Digital-Analogico)
 *
 * Dados:
 *   Vref = 15 V
 *   Numero de bits = 4
 *
 * Objetivo:
 *   a) Calcular o valor binario ABCD para que a saida seja 8 V.
 *   b) Determinar o numero de bits do conversor.
 *   c) Calcular a resolucao (em V por passo).
 *
 * Formula:
 *   Vout = (D / (2^n - 1)) * Vref
 *   Resolucao = Vref / (2^n - 1)
 */

int main()
{
    // Dados do problema
    float Vref = 15.0;         // tensao de referencia (V)
    int n = 4;                 // numero de bits de entrada
    float Vout_desejado = 8.0; // tensao de saida desejada (V)

    // Calculos
    int niveis = (1 << n) - 1; // 2^n - 1
    float resolucao = Vref / niveis;
    int codigo_decimal = (int)((Vout_desejado / Vref) * niveis + 0.5); // arredondado
    int D = codigo_decimal;                                            // codigo digital equivalente

    // Impressao dos resultados
    printf("Questao 4 - Conversor D/A (4 bits)\n");
    printf("----------------------------------\n");
    printf("Tensao de referencia (Vref): %.2f V\n", Vref);
    printf("Numero de bits: %d bits\n", n);
    printf("Resolucao: %.2f V por nivel\n", resolucao);
    printf("Saida desejada: %.2f V\n", Vout_desejado);
    printf("Codigo decimal correspondente: %d\n", D);

    // Mostra em binario (4 bits)
    printf("Codigo binario (ABCD): ");
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d", (D >> i) & 1);
    }
    printf("\n");

    return 0;
}

/*
Explicacao:
- O conversor tem 4 bits, portanto 2^4 = 16 niveis.
- O valor maximo (15) representa Vref = 15 V.
- A resolucao e: 15 V / 15 = 1 V por nivel.
- Para obter 8 V: (8 / 15) * 15 ≈ 8 -> codigo = 8 (decimal).
- Codigo binario ABCD = 1000.
*/
