# Sistema de Monitoramento de Irrigação Automatizada com ESP32

[Link para o Projeto Wokwi](https://wokwi.com/projects/412301184401222657)

Este projeto utiliza um **ESP32** para monitorar e controlar a irrigação automatizada de acordo com as leituras de sensores de umidade, nível de água e luminosidade. O sistema também pode detectar presença através de um sensor PIR.

## Funcionalidades Principais

1. **Monitoramento Climático (DHT22)**: Mede a umidade e a temperatura do ambiente.
2. **Controle de Nível de Água (HC-SR04)**: Verifica o nível de água no tanque para ativar/desativar a irrigação.
3. **Controle de Luminosidade (LDR)**: Ajusta a irrigação com base na quantidade de luz recebida (ensolarado ou nublado).
4. **Controle de Presença (PIR)**: Detecta movimento em áreas protegidas para desativar a irrigação se necessário.
5. **Controle da Irrigação (LED)**: Um LED simula o acionamento da irrigação, ativando ou desativando conforme as condições ambientais.

## Hardware Utilizado

- **ESP32 DevKit V4**
- **DHT22**: Sensor de temperatura e umidade.
- **HC-SR04**: Sensor ultrassônico para medir o nível de água.
- **LDR**: Sensor de luminosidade.
- **LED**: Simula o sistema de irrigação.
- **Resistores**: Utilizados para limitar a corrente nos LEDs e para o divisor de tensão do LDR.
- **Sensor PIR** (não implementado no código atual): Detecta movimento e desativa a irrigação se necessário.

## Conexões

- **DHT22**:
  - VCC: 3.3V (ESP32)
  - GND: GND (ESP32)
  - Data: GPIO 4 (ESP32)

- **HC-SR04**:
  - TRIG: GPIO 5
  - ECHO: GPIO 18

- **LDR**:
  - VCC: 3.3V
  - GND: GND (ESP32 via resistor de 10kΩ)
  - AO: GPIO 34 (Entrada Analógica)

- **LED**:
  - Anodo: GPIO 2
  - Catodo: GND via resistor de 220Ω

## Definições de Thresholds

Os thresholds definidos controlam o comportamento do sistema de irrigação:

- `UMIDADE_MINIMA`: Define o nível de umidade mínima para ativar a irrigação. Se a umidade estiver abaixo deste valor, a irrigação pode ser ligada.
- `NIVEL_AGUA_MINIMO`: Define o nível de água mínimo necessário para ativar a irrigação. Se o nível de água estiver abaixo deste valor, a irrigação será desligada.
- `NIVEL_AGUA_MAXIMO`: Define o nível de água máximo (não utilizado diretamente no código atual).
- `LDR_THRESHOLD_ENSOLARADO`: Define o valor de leitura do LDR abaixo do qual o sistema considera o dia como ensolarado.

## Lógica do Código

### 1. Inicialização

- O sistema inicializa todos os sensores e configura os pinos de controle do ESP32.
  
### 2. Função `measureDistance()`

- Utiliza o sensor HC-SR04 para medir a distância (nível de água no tanque) e retorna o valor em **cm**.

### 3. Condições de Irrigação

- **Desliga a irrigação** se:
  - A umidade estiver **acima** do limite `UMIDADE_MINIMA`.
  - O nível de água estiver **abaixo** de `NIVEL_AGUA_MINIMO`.
  - A leitura do LDR for **acima** de `LDR_THRESHOLD_ENSOLARADO` (dia nublado).
  - A umidade estiver **abaixo** de `UMIDADE_MINIMA` e o nível de água estiver **abaixo** de `NIVEL_AGUA_MINIMO`.

- **Liga a irrigação** se:
  - A umidade estiver **abaixo** de `UMIDADE_MINIMA`.
  - O nível de água estiver **acima** de `NIVEL_AGUA_MINIMO`.
  - A leitura do LDR for **abaixo** de `LDR_THRESHOLD_ENSOLARADO` (dia ensolarado).

### 4. Leitura dos Sensores e Controle

- A cada ciclo no loop principal:
  - A umidade e a temperatura são lidas usando o sensor **DHT22**.
  - O nível de água é medido com o **HC-SR04**.
  - A intensidade de luz é lida pelo **LDR**.
  - O sistema então verifica as condições e decide se deve **ligar ou desligar a irrigação**.

### 5. Exemplo de Saída no Serial

- `"Nível de água no tanque: 15 cm"`
- `"Intensidade de luz (LDR): 1400"`
- `"Condições adequadas, ativando irrigação."`

## Licença

Este código está disponível sob a licença [MIT](https://opensource.org/licenses/MIT). Sinta-se à vontade para modificar e melhorar conforme necessário.
