// Referências aos elementos do DOM
const currentTempSpan = document.getElementById("currentTemp");
const currentPressSpan = document.getElementById("currentPress");
const connectBtn = document.getElementById("connectBtn");
const disconnectBtn = document.getElementById("disconnectBtn");
const connectionStatusDiv = document.getElementById("connectionStatus");
const ctx = document.getElementById("chart").getContext("2d");

let serialPort; // Variável global para armazenar a porta serial

// --- CORREÇÃO: Variáveis CSS lidas no início ---
const styles = getComputedStyle(document.documentElement);
const var_text = styles.getPropertyValue("--text").trim();
const var_accent = styles.getPropertyValue("--accent").trim();
const var_light_grey = styles.getPropertyValue("--light-grey").trim();
const var_temp_color = styles.getPropertyValue("--temp-color").trim();
const var_press_color = styles.getPropertyValue("--press-color").trim();
const var_grid_color = "#2a3440";

// Dados do gráfico
const chartData = {
  labels: [],
  datasets: [
    {
      label: "Temperatura (°C)",
      data: [],
      borderColor: var_temp_color,
      backgroundColor: var_temp_color + "33",
      fill: true,
      tension: 0.4,
      pointRadius: 0,
      pointHitRadius: 10,
      yAxisID: "yTemp", // <-- MELHORIA: Associar ao eixo Y de Temp
    },
    {
      label: "Pressão (hPa)",
      data: [],
      borderColor: var_press_color,
      backgroundColor: var_press_color + "33",
      fill: true,
      tension: 0.4,
      pointRadius: 0,
      pointHitRadius: 10,
      yAxisID: "yPress", // <-- MELHORIA: Associar ao eixo Y de Pressão
    },
  ],
};

// Instância do gráfico
const chart = new Chart(ctx, {
  type: "line",
  data: chartData,
  options: {
    responsive: true,
    maintainAspectRatio: false, // ESSENCIAL para o gráfico preencher o card alto
    plugins: {
      legend: {
        labels: {
          color: var_text, // Cor das legendas
          font: { size: 14 },
        },
      },
      tooltip: {
        mode: "index",
        intersect: false,
        backgroundColor: "#1f2733",
        titleColor: var_accent,
        bodyColor: var_text,
        borderColor: "#3a4a5a",
        borderWidth: 1,
        padding: 10,
        callbacks: {
          label: function (context) {
            let label = context.dataset.label || "";
            if (label) {
              label += ": ";
            }
            if (context.parsed.y !== null) {
              label += context.parsed.y.toFixed(2);
            }
            return label;
          },
        },
      },
    },
    // --- MELHORIA GRÁFICA: EIXOS DUPLOS ---
    scales: {
      x: {
        ticks: {
          color: var_light_grey,
          font: { size: 12 },
        },
        grid: {
          color: var_grid_color,
          drawBorder: false,
        },
      },
      // Eixo Y da Temperatura (Esquerda)
      yTemp: {
        type: "linear",
        position: "left",
        grace: "10%", // <-- CORREÇÃO: Adiciona 10% de margem para a "onda" não vazar
        title: {
          display: true,
          text: "Temperatura (°C)",
          color: var_temp_color,
          font: { size: 14 },
        },
        ticks: {
          color: var_temp_color,
          font: { size: 12 },
        },
        grid: {
          color: var_grid_color,
          drawBorder: false,
        },
      },
      // Eixo Y da Pressão (Direita)
      yPress: {
        type: "linear",
        position: "right",
        grace: "10%", // <-- CORREÇÃO: Adiciona 10% de margem para a "onda" não vazar
        title: {
          display: true,
          text: "Pressão (hPa)",
          color: var_press_color,
          font: { size: 14 },
        },
        ticks: {
          color: var_press_color,
          font: { size: 12 },
        },
        // Não desenha a grade de novo, para não poluir
        grid: {
          drawOnChartArea: false,
          drawBorder: false,
        },
      },
    },
    // --- FIM DA MELHORIA ---
  },
});

// Função para atualizar o status da conexão
function updateConnectionStatus(status, message) {
  connectionStatusDiv.innerHTML = message;
  connectionStatusDiv.className = `connection-status ${status}`;
}

// Event Listener para o botão Conectar
connectBtn.addEventListener("click", async () => {
  updateConnectionStatus(
    "pending",
    '<i class="fas fa-circle-notch fa-spin"></i> CONECTANDO...'
  );
  connectBtn.disabled = true;

  try {
    serialPort = await navigator.serial.requestPort();
    await serialPort.open({ baudRate: 115200 });

    updateConnectionStatus(
      "connected",
      '<i class="fas fa-check-circle"></i> CONECTADO AO ESP32!'
    );
    connectBtn.style.display = "none";
    disconnectBtn.style.display = "flex";

    readSerialData();
  } catch (err) {
    console.error("Erro na conexão serial:", err);
    updateConnectionStatus(
      "error",
      `<i class="fas fa-exclamation-triangle"></i> ERRO: ${err.message}`
    );
    connectBtn.disabled = false;
  }
});

// Event Listener para o botão Desconectar
disconnectBtn.addEventListener("click", async () => {
  if (serialPort && serialPort.readable) {
    try {
      if (reader) {
        await reader.cancel();
        await reader.releaseLock();
      }
      await serialPort.close();
      serialPort = null;
      updateConnectionStatus(
        "pending",
        '<i class="fas fa-circle-notch fa-spin"></i> AGUARDANDO CONEXÃO...'
      );
      connectBtn.style.display = "flex";
      disconnectBtn.style.display = "none";
      connectBtn.disabled = false;

      // Limpa os dados do gráfico e cards
      chartData.labels = [];
      chartData.datasets[0].data = [];
      chartData.datasets[1].data = [];
      chart.update();
      currentTempSpan.textContent = "--.--";
      currentPressSpan.textContent = "----.-";
    } catch (err) {
      console.error("Erro ao desconectar:", err);
      updateConnectionStatus(
        "error",
        `<i class="fas fa-exclamation-triangle"></i> ERRO AO DESCONECTAR: ${err.message}`
      );
    }
  }
});

let reader; // Global para o leitor
let lineBuffer = ""; // Buffer para dados parciais

// Função para ler dados da porta serial
async function readSerialData() {
  if (!serialPort || !serialPort.readable) return;

  reader = serialPort.readable.getReader();

  try {
    while (true) {
      const { value, done } = await reader.read();
      if (done) {
        break;
      }

      lineBuffer += new TextDecoder().decode(value, { stream: true });

      let lines = lineBuffer.split("\n");
      while (lines.length > 1) {
        const line = lines.shift();
        if (line.trim() === "") continue;

        try {
          const json = JSON.parse(line.trim());
          if (json.temp !== undefined && json.press !== undefined) {
            updateDashboard(json.temp, json.press);
          }
        } catch (e) {
          console.warn("Linha JSON inválida ou incompleta:", line, e);
        }
      }
      lineBuffer = lines[0];
    }
  } catch (error) {
    console.error("Erro na leitura da porta serial:", error);
    if (serialPort && serialPort.readable) {
      updateConnectionStatus(
        "error",
        `<i class="fas fa-exclamation-triangle"></i> CONEXÃO PERDIDA: ${error.message}`
      );
      connectBtn.style.display = "flex";
      disconnectBtn.style.display = "none";
      connectBtn.disabled = false;
      serialPort = null;
    }
  } finally {
    if (reader) {
      reader.releaseLock();
    }
  }
}

// Função para atualizar o Dashboard com novos dados
function updateDashboard(temp, press) {
  // Atualiza os cards
  currentTempSpan.textContent = temp.toFixed(2);
  currentPressSpan.textContent = press.toFixed(1);

  // Atualiza o gráfico
  const time = new Date().toLocaleTimeString("pt-BR", {
    hour: "2-digit",
    minute: "2-digit",
    second: "2-digit",
  });
  chartData.labels.push(time);
  chartData.datasets[0].data.push(temp);
  chartData.datasets[1].data.push(press);

  const maxDataPoints = 30; // Número máximo de pontos no gráfico
  if (chartData.labels.length > maxDataPoints) {
    chartData.labels.shift();
    chartData.datasets[0].data.shift();
    chartData.datasets[1].data.shift();
  }

  chart.update();
}
