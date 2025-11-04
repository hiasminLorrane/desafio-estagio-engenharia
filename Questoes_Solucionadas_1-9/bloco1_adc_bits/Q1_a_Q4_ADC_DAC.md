

## Bloco 1 — ADC, RS-232, Bytes e DAC (Q1–Q4)

--------------------------------------------------------------------------------------------------------------------------------------

- Objetivo: documentar e explicar as soluções das questões 1 a 4 com foco em operações de bits, conversão A/D e D/A, e manipulação de bytes.
- Fontes associadas: `Q1_ADC.c:1`, `Q2_RS232.c:1`, `Q3_Bytes.c:1`, `Q4_DAC.c:1`.
- Binários prontos: `q1.exe`, `q2.exe`, `q3.exe`, `q4.exe`.

Execução Rápida (Windows)

- Rodar cada questão: `./q1.exe`, `./q2.exe`, `./q3.exe`, `./q4.exe`
- Compilar (opcional, se tiver GCC/MinGW): `gcc Q1_ADC.c -o q1.exe`, `gcc Q2_RS232.c -o q2.exe`, `gcc Q3_Bytes.c -o q3.exe`, `gcc Q4_DAC.c -o q4.exe`


--------------------------------------------------------------------------------------------------------------------------------------



Q1 — ADC 10 bits alinhado em 16 bits (MSB)

- Contexto: leitura de 16 bits contém os 10 bits úteis do ADC nos bits mais significativos (bits 15..6). É preciso “descompactar” o valor real e convertê-lo para mV considerando referência de 5 V.
- Fórmula: `V_mV = (N / 1023) * 5000`, onde `N ∈ [0, 1023]`.
- Implementação: `valorADC = leituraAD >> 6;` e `tensao_mV = (valorADC * 5000) / 1023;` em `Q1_ADC.c:1`.
- Exemplo usado no código: `leitura = 0b1010000000000000` → `valorADC = 0x0280 (640)` → `tensão ≈ 640*5000/1023 ≈ 3127 mV`.
- Saída esperada (ex.): `Tensao lida: 3127 mV`.


--------------------------------------------------------------------------------------------------------------------------------------


Q2 — Montagem de 4 bytes (RS232) em um `uint32`

- Objetivo: receber 4 bytes (b1..b4) e combiná-los em uma única variável de 32 bits.
- Convenção adotada: Big-endian lógico (b1 é o mais significativo). Construção: `(b1<<24) | (b2<<16) | (b3<<8) | b4` em `Q2_RS232.c:1`.
- Exemplo do código: `b1=0x12, b2=0x34, b3=0x56, b4=0x78` → resultado `0x12345678 (305419896)`.
- Saída esperada: `Bytes combinados: 0x12345678 (305419896)`.


--------------------------------------------------------------------------------------------------------------------------------------


Q3 — Quebra de um `uint32` (10.000.000) em 4 bytes

- Objetivo: decompor `valor = 10000000` (`0x00989680`) em 4 bytes em ordem Big-endian.
- Implementação: `bytes[0]=(valor>>24)&0xFF; bytes[1]=(valor>>16)&0xFF; bytes[2]=(valor>>8)&0xFF; bytes[3]=valor&0xFF;` em `Q3_Bytes.c:1`.
- Resultado esperado:
  - `Byte 0 = 0x00`
  - `Byte 1 = 0x98`
  - `Byte 2 = 0x96`
  - `Byte 3 = 0x80`
- Observação: a mesma convenção (Big-endian lógico) permite recompor exatamente o valor original.


--------------------------------------------------------------------------------------------------------------------------------------

Q4 — Conversor D/A (4 bits), Vref = 15 V

- Dados: `n = 4` bits, `Vref = 15 V`, `Vout_desejado = 8 V`.
- Fórmulas: `Vout = (D / (2^n - 1)) * Vref` e `Resolução = Vref / (2^n - 1)`.
- Cálculo: `2^4 - 1 = 15` níveis; `Resolução = 15/15 = 1 V/nível`.
- Para 8 V: `D ≈ round((8/15)*15) = 8` → binário de 4 bits: `1000` (ABCD) em `Q4_DAC.c:1`.
- Saída esperada inclui: número de bits, resolução e código `ABCD = 1000`.

Notas e Boas Práticas

- Endianness: documente sempre a convenção de bytes (Big vs Little) para evitar ambiguidades na integração.
- Saturação/validação: em conversões A/D e D/A, avalie limitar entradas (ex.: [0,1023]) e tratar arredondamentos.
- Portabilidade: use tipos fixos de `<stdint.h>` (`uint8_t`, `uint16_t`, `uint32_t`) como feito neste bloco.

Como Testar Rápido

- Q1: `./q1.exe` → confirma mV conforme entrada simulada no código.
- Q2: `./q2.exe` → valida composição como `0x12345678`.
- Q3: `./q3.exe` → confere bytes `00 98 96 80`.
- Q4: `./q4.exe` → confere resolução `1 V` e código `1000`.
