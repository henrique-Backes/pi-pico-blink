# Pi Pico Blink - Stream Deck Basico

Firmware basico de Stream Deck para Raspberry Pi Pico com TinyUSB HID.

## Visao Geral

Keypad matricial 4x4 que envia comandos HID de media control (volume, play/pause) via USB. Inclui LED de feedback visual.

## Hardware

- Raspberry Pi Pico (RP2040)
- Keypad matricial 4x4
- LED (GP22) - feedback visual

## Pinos

| Sinal   | GPIO |
|---------|------|
| ROW 1   | GP9  |
| ROW 2   | GP8  |
| ROW 3   | GP7  |
| ROW 4   | GP6  |
| COL 1   | GP5  |
| COL 2   | GP4  |
| COL 3   | GP3  |
| COL 4   | GP2  |
| LED     | GP22 |

## Funcionalidades

| Tecla | Acao |
|-------|------|
| A (col 4, row 1) | Volume Up |
| B (col 4, row 2) | Volume Down |
| C (col 4, row 3) | Play/Pause |

## USB

TinyUSB composite device com HID Consumer Control. Plug-and-play, sem drivers necessarios.

## Build

Requer Pico SDK 2.2.0 + ARM toolchain 14_2_Rel1 (instalados via Pico VS Code extension).

```bash
cmake -G Ninja -B build
ninja -C build
```

## Flash

```bash
# USB BOOTSEL mode
picotool load build/blink.uf2 -fx
```

Ou arraste `blink.uf2` para o drive RPI-RP2 que aparece no modo BOOTSEL.

## Padrao de Codigo

Barr-C: Allman braces, Yoda conditions, fixed-width types, suffixes `u`/`f`, `for (;;)` loops.

## Dependencias

- Pico SDK 2.2.0
- TinyUSB (incluida no Pico SDK)
- ARM GCC toolchain
