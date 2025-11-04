// Q5_UART.c — Comunicação UART com eco incrementado

#include <stdio.h>

// Função de inicialização da UART
void UART_Init(int baudrate)
{
    // Configura baud rate, bits de dados, paridade e stop bits
    printf("UART inicializada a %d bps\n", baudrate);
}

// Função para ler um caractere recebido
char UART_Read()
{
    char c;
    printf("Digite um caractere recebido via UART: ");
    scanf(" %c", &c);
    return c;
}

// Função para enviar um caractere pela UART
void UART_Write(char c)
{
    printf("Transmitido: %c\n", c);
}

// Programa principal
int main()
{
    UART_Init(9600); // Exemplo: 9600 bps

    while (1)
    {
        char recebido = UART_Read(); // Aguarda um caractere
        char enviado = recebido + 1; // Incrementa em 1
        UART_Write(enviado);         // Envia de volta
    }

    return 0;
}
