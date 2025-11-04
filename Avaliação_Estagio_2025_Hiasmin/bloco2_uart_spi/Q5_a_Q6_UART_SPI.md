---
## 🔄 Q6 — UART × SPI: Comparação Teórica

### 🟢 Vantagens do UART em relação ao SPI

1. **Menos fios/pinos em link ponto a ponto:** apenas `TX`, `RX` e referência de terra (2 linhas de dados), enquanto SPI exige pelo menos `SCLK`, `MOSI`, `MISO` e um `CS` por escravo.
2. **Assíncrono (sem clock dedicado):** simplifica cabeamento e isolamento; tolera variações moderadas de clock interno entre os lados quando o baud rate é compatível.
3. **Alcance típico maior com drivers apropriados:** via camadas físicas como **RS-232/RS-485**, pode cobrir distâncias maiores que SPI (normalmente pensado para curtas distâncias em placa).
---

### 🔴 Limitações do UART em relação ao SPI

1. **Menor taxa de dados máxima:** SPI opera em dezenas de MHz; UART geralmente fica em ordens de kbps a poucos Mbps.
2. **Overhead de enquadramento:** bits de start/stop (e opcional paridade) reduzem a eficiência — são 10+ bits transmitidos para 8 bits úteis no formato 8N1.
3. **Sem sincronismo de clock para dados determinísticos:** o SPI, por ser síncrono, oferece temporização mais precisa e previsível, útil para streams de alta taxa e baixa latência/jitter.

---

### ⚖️ Comparativo Técnico

| Critério            | **UART**                  | **SPI**                       |
| ------------------- | ------------------------- | ----------------------------- |
| Tipo de comunicação | Assíncrona (sem clock)    | Síncrona (com clock)          |
| Linhas de sinal     | 2 (TX, RX)                | 4+ (MOSI, MISO, SCK, CS)      |
| Topologia           | Ponto a ponto (1:1)       | Mestre e múltiplos escravos   |
| Velocidade típica   | Até ~1 Mbps               | Pode chegar a dezenas de Mbps |
| Eficiência          | Reduzida (start/stop)     | Alta (stream contínuo)        |
| Sincronização       | Por baud rate             | Por clock compartilhado       |
| Alcance físico      | Maior (com RS-232/RS-485) | Restrito a curtas distâncias  |

---

### ✅ Conclusão

O **UART** é simples, robusto e ideal para comunicações ponto a ponto ou links de debug, onde simplicidade e compatibilidade são prioridade.  
Já o **SPI** é mais indicado para periféricos rápidos e de alta precisão temporal, como sensores, memórias e displays.

A escolha entre os dois depende de:

- **Número de dispositivos conectados**
- **Taxa de dados desejada**
- **Distância física**
- **Complexidade de hardware disponível**

---

📄 Documento técnico elaborado por **Hiasmin** — Avaliação de Estágio Engenharia 2025.
