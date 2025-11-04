

# Diário de Bordo – Projeto ESP32  
### Sistema de Monitoramento de Temperatura e Pressão via Bluetooth  

Período: 28/10/2025 a 04/11/2025  
Autora: Hiasmin Lorrane Cardoso  

--------------------------------------------------------------------------------------------------------------------------------------


## 28/10 – Início do desafio  
Comecei o desafio lendo todo o enunciado com calma e planejando como eu iria dividir as etapas.  
Decidi estruturar o projeto no VS Code, criando pastas separadas para cada bloco (ADC, UART, SPI, CAN e Projeto).  
Essa organização facilitou bastante na hora de programar, testar e documentar tudo depois.  

Tempo estimado: 4h  
Tempo real: 4h  


--------------------------------------------------------------------------------------------------------------------------------------


## 30/10 – Configuração do ambiente e primeiros testes  
Com a chegada da placa ESP32, iniciei a instalação da board e das bibliotecas necessárias na Arduino IDE.  
Conectei a placa via USB, fiz o upload de um código simples e confirmei que a comunicação estava funcionando corretamente.  
Essa etapa foi essencial para garantir que o ambiente estivesse pronto antes de começar o desenvolvimento principal.  

Tempo estimado: 1h50  
Tempo real: 1h50  


--------------------------------------------------------------------------------------------------------------------------------------


## 31/10 – Desenvolvimento do código principal  
Comecei a programar o sistema principal utilizando a biblioteca `BluetoothSerial.h`.  
Simulei leituras de temperatura e pressão com pequenas variações e configurei o envio dos dados em formato **JSON** via Bluetooth.  
Adicionei também um LED no pino 2 para indicar o status de transmissão.  
A estrutura do código ficou modular e fácil de entender, o que facilitou os testes posteriores.  

Tempo estimado: 4h  
Tempo real: 5h  


--------------------------------------------------------------------------------------------------------------------------------------

## 01/11 – Testes de comunicação e ajustes finais  
Realizei testes de transmissão com o aplicativo Serial Bluetooth Terminal no celular.  
Implementei comandos remotos como `START` e `STOP`, permitindo pausar e retomar o envio de dados diretamente pelo aplicativo.  
Após alguns ajustes, o sistema ficou estável e transmitindo corretamente as informações em tempo real.  

Tempo estimado: 3h  
Tempo real: 3h30  


--------------------------------------------------------------------------------------------------------------------------------------


## 02/11 – Diagrama elétrico  
Desenhei o esquema elétrico do projeto utilizando a ferramenta Circuit Diagram, mostrando o ESP32, o LED e as conexões representando sensores de temperatura e pressão.  
Esse diagrama ajudou a documentar visualmente o funcionamento do sistema e complementou o relatório técnico.  

Tempo estimado: 2h  
Tempo real: 2h  

--------------------------------------------------------------------------------------------------------------------------------------

## 03/11 – Montagem da maquete  
Montei uma maquete física com a ESP32 para demonstrar o funcionamento do projeto.  
Durante os testes, foi possível visualizar os dados de temperatura e pressão sendo enviados via Bluetooth para o aplicativo no celular, com o LED piscando a cada transmissão.  
Ver o sistema funcionando na prática foi um momento importante de validação do trabalho.  

Tempo estimado: 4h  
Tempo real: 5h  

--------------------------------------------------------------------------------------------------------------------------------------

## 04/11 – Documentação e fechamento do projeto  
Finalizei o projeto reunindo todo o material produzido: código, diagramas, imagens e relatórios.  
Criei o arquivo `diario_de_bordo.md`, organizei as pastas e gerei o relatório final em PDF com todos os anexos e resultados.  
Essa etapa encerrou oficialmente o desenvolvimento e consolidou todo o processo do desafio.  

Tempo estimado: 6h  
Tempo real: 6h  


--------------------------------------------------------------------------------------------------------------------------------------

## Observações gerais  
- O desenvolvimento foi feito no VS Code, com estrutura modular e organizada.  
- A comunicação Bluetooth foi testada e validada com o Serial Bluetooth Terminal, apresentando resposta estável.  
- Todo o código foi comentado e documentado para facilitar futuras manutenções.  
- O projeto foi executado entre 28/10 e 04/11, com dedicação quase diária, incluindo finais de semana.  


--------------------------------------------------------------------------------------------------------------------------------------

## Reflexão final  

Esse projeto foi uma excelente oportunidade para integrar conceitos teóricos e práticos.  
Trabalhar com o ESP32 me permitiu compreender melhor a integração entre sensores, comunicação serial e Bluetooth em um sistema embarcado funcional.  
Durante o processo, aprimorei muito minhas habilidades em organização, testes e documentação técnica.  
Concluir o projeto e ver o sistema operando de forma estável foi um resultado muito satisfatório para min.


--------------------------------------------------------------------------------------------------------------------------------------