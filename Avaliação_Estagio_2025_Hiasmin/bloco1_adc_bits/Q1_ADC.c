#include <stdio.h>
#include <stdint.h>

int calcularTensao(uint16_t leituraAD)
{
    uint16_t valorADC = leituraAD >> 6;

    int tensao_mV = (valorADC * 5000) / 1023;

    return tensao_mV;
}

int main()
{

    uint16_t leitura = 0b1010000000000000;

    int tensao = calcularTensao(leitura);

    printf("Tensao lida: %d mV\n", tensao);

    return 0;
}

/*
Explicacao:
- O ADC de 10 bits gera valores de 0 a 1023.
- Como o resultado esta nos bits mais significativos, e preciso deslocar 6 bits a direita (>> 6).
- Depois, aplica-se a regra de proporcionalidade:
    tensao = (valorADC / 1023) * 5000
*/
