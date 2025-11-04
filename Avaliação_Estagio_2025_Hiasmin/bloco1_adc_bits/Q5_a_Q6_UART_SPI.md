Q5 e Q6 — UART e SPI (guia direto e humano)

- O que você encontra aqui: uma explicação simples da Q5 com pseudocódigo e a saída gerada pelo programa `Q5_UART.c`, além de uma comparação prática entre UART e SPI (Q6).
- Fonte associada: `Q5_UART.c:1`.

Q5 — UART 8N1, do jeito que a gente enxerga

- Ideia geral: um quadro 8N1 tem 1 bit de start (0), 8 bits de dados enviados do menos significativo para o mais significativo (LSB-first) e 1 bit de stop (1). É o “pacote” básico que viaja no fio.
- Exemplo usado: byte `0x4B` (o caractere 'K') a 9600 bps.
- Tempo de bit (só para referência): `Tbit = 1 / baud` → a 9600 bps, `Tbit ≈ 104,17 µs`.
- Implementação: em `Q5_UART.c:1`, a gente monta um vetor com os 10 bits e imprime a sequência para visualizar o quadro.

Pseudocódigo (8N1, LSB-first)

- Entrada: `dado` (byte), `baud` (inteiro)
- Criar `bits[10]`
- `bits[0] = 0`  // start
- Para `i` de 0 a 7: `bits[1+i] = (dado >> i) & 1`
- `bits[9] = 1`  // stop
- `tbit_us = 1e6 / baud`
- Imprimir cabeçalho (dado, baud, Tbit) e a sequência `bits[0..9]`

Saída esperada (com dado = 0x4B e baud = 9600)

- `Questao 5 - UART 8N1`
- `Dado: 0x4B (75, 'K')`
- `Baud rate: 9600 bps, Tbit: 104.17 us`
- `Frame (LSB first): 0 1 1 0 1 0 0 1 0 1`  (start, 8 dados, stop)

Q6 — UART × SPI, na prática

Vantagens do UART sobre o SPI

- Cabeamento simples: só `TX`, `RX` e GND (2 linhas de dados). SPI pede `SCLK`, `MOSI`, `MISO` e um `CS` por escravo.
- Sem clock dedicado: por ser assíncrono, facilita a vida no hardware e na fiação quando os dois lados concordam no baud rate.
- Bom alcance com drivers certos: usando camadas físicas como RS‑232/RS‑485, o UART costuma ir mais longe que SPI (que é tipicamente “on‑board”).

Limitações do UART frente ao SPI

- Velocidade: SPI atinge dezenas de MHz; UART geralmente fica entre kbps e poucos Mbps.
- Overhead por quadro: start/stop (e, se houver, paridade) reduzem a eficiência — em 8N1 são 10 bits para cada 8 de dado útil.
- Menos determinismo temporal: sem clock de referência, o timing é menos rígido que no SPI, o que impacta fluxos de alta taxa/baixa latência.

