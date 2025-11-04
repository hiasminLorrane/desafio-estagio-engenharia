// Q5_UART.c — Comunicação UART com eco incrementado

#include <stdio.h>

void UART_Init(int baudrate)
{
    printf("UART inicializada a %d bps\n", baudrate);
}

char UART_Read()
{
    char c;
    printf("Digite um caractere recebido via UART: ");
    scanf(" %c", &c);
    return c;
}

void UART_Write(char c)
{
    printf("Transmitido: %c\n", c);
}

int main()
{
    UART_Init(9600);

    while (1)
    {
        char recebido = UART_Read();
        char enviado = recebido + 1;
        UART_Write(enviado);
    }

    return 0;
}
