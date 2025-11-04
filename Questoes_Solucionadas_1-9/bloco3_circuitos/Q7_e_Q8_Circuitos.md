

## Resposta Pergunta 7

--------------------------------------------------------------------------------------------------------------------------------------
Para responder a essa questão, pesquisei sobre o funcionamento do amplificador operacional não inversor.  
Aprendi que, nesse tipo de configuração, o ganho de tensão (G) é determinado pela relação entre dois resistores conectados na malha de realimentação:


\[G = 1 + \frac{R_2}{R_1}\]


Como o ganho desejado é 10, basta escolher valores de resistores que satisfaçam essa relação.  
Por exemplo:

- R₁ = 1 kΩ  
- R₂ = 9 kΩ

Substituindo na fórmula:

G = 1 + \frac{9kΩ}{1kΩ} = 10

O diagrama seria o de um amplificador não inversor, onde:

- O sinal de entrada é aplicado ao terminal não inversor (+).  
- O terminal inversor (–) recebe a realimentação formada pelos resistores R₁ (ligado ao terra) e R₂ (ligado à saída).  
- A saída é conectada à carga e também retorna parte do sinal ao terminal (–) através de R₂.

Esse estudo me ajudou a entender melhor como o ganho depende da proporção entre R₂ e R₁** e como a realimentação negativa garante estabilidade e linearidade ao circuito.

--------------------------------------------------------------------------------------------------------------------------------------

## Resposta Pergunta 8

Durante o desenvolvimento deste circuito, montei o diagrama de força de uma partida estrela-triângulo para um motor trifásico. O sistema é composto por três contatores: K1 (principal), K2 (estrela) e K3 (triângulo).  
Na partida, o motor é ligado em estrela através dos contatores K1 e K2, o que reduz a corrente inicial. Após alguns segundos, o contator K2 desliga e o K3 é acionado, mudando a ligação para triângulo, permitindo que o motor opere em sua potência total.  
Essa sequência de operação garante uma partida mais suave, diminuindo o pico de corrente e protegendo tanto o motor quanto a rede elétrica.

--------------------------------------------------------------------------------------------------------------------------------------





