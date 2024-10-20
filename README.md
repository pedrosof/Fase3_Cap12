# FIAP - Faculdade de Informática e Administração Paulista
[![FIAP Logo](images/logo-fiap.png)](https://www.fiap.com.br)

## Fase 3 Cap 12 – A Eletrônica de uma IA
[GitHub](https://github.com/pedrosof/Fase3_Cap1)
### Grupo 18

👨‍🎓 **Integrantes**:
- [Fabio Marcos Pedroso Filho](https://www.linkedin.com/in/pedrosof/)

👩‍🏫 **Professores**:

**Tutor(a)**:
- [Lucas Gomes Moreira](https://www.linkedin.com/in/lucas-gomes-moreira-15a8452a/)

**Coordenador(a)**:
- [Andre Godoi, PhD](https://www.linkedin.com/in/profandregodoi/)

---

# Sistema de Irrigação Automatizada com ESP32

[Link para o Projeto Wokwi](https://wokwi.com/projects/412301184401222657)

Este projeto utiliza um **ESP32** para controlar a irrigação automaticamente com base em sensores de umidade (DHT22), nível de água (HC-SR04), luminosidade (LDR) e detecção de movimento (PIR).

## Funcionalidades

1. **DHT22**: Mede temperatura e umidade.
2. **HC-SR04**: Verifica o nível de água.
3. **LDR**: Ajusta a irrigação conforme a luz (ensolarado/nublado).
4. **PIR**: Desativa a irrigação ao detectar movimento.
5. **Segurança**: Desativa a irrigação se o nível de água exceder o máximo.

## Conexões de Hardware

- **DHT22**: VCC (3.3V), GND, Data (GPIO 4)
- **HC-SR04**: Trigger (GPIO 5), Echo (GPIO 18)
- **LDR**: VCC (3.3V), GND (com resistor de 10kΩ), AO (GPIO 34)
- **PIR**: OUT (GPIO 27)
- **LED**: Anodo (GPIO 2), Catodo (GND via resistor de 220Ω)

## Lógica de Operação

- **Irrigação ativada**: Umidade abaixo de `UMIDADE_MINIMA`, água acima de `NIVEL_AGUA_MINIMO`, e luz indicando ensolarado.
- **Irrigação desativada**: Umidade acima de `UMIDADE_MINIMA`, água abaixo de `NIVEL_AGUA_MINIMO`, luz indicando nublado, ou movimento detectado pelo PIR.

## Mensagens de Erro

- **Erro na leitura do DHT22**.
- **Nível de água excede o máximo**.

