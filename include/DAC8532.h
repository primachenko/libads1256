#ifndef DAC8532_H
#define DAC8532_H

#include "DEV_Config.h"

#define DAC8532_PD0 (0x01)
#define DAC8532_PD1 (0x02)
#define DAC8532_BUF (0x04)
#define DAC8532_LDA (0x10)
#define DAC8532_LDB (0x20)

#define DAC8532_CHANNEL_A (DAC8532_LDA)
#define DAC8532_CHANNEL_B (DAC8532_LDB | DAC8532_BUF)

#define DAC8532_CHANNEL_A_STR "A"
#define DAC8532_CHANNEL_B_STR "B"

#define DAC8532_REG_VALUE_MAX (0xFFFF)
#define DAC8532_VREF (5.0)

void DAC8532_Write(uint8_t reg_cmd, uint16_t reg_val);
void DAC8532_Set_Voltage(uint8_t channel, double voltage);

#endif /* DAC8532_H */

/*
+-----------------------------------------------------------+
|                       Register map                        |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

+-----+-----+-----------+
|  Power-Down Commands  |
+-----+-----+-----------+
| PD1 | PD0 | Impedance |
+-----+-----+-----------+
|  0  |  1  |    1k     |
+-----+-----+-----------+
|  1  |  0  |   100k    |
+-----+-----+-----------+
|  1  |  1  |   High    |
+-----+-----+-----------+

Examples

Write to DataBuffer A:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  0  |  0  |  0  |  0  |  0  |  0  |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write to DataBuffer B and Load DAC A and DAC B simultaneously:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  1  |  1  |  0  |  1  |  0  |  0  |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write to DataBuffer A and Load DAC A:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  0  |  1  |  0  |  0  |  0  |  0  |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write to DataBuffer B and Load DAC B:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  1  |  0  |  0  |  1  |  0  |  0  |    Data   |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write power-down to 1k command to DataBuffer A:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  0  |  0  |  0  |  0  |  0  |  1  | Dont care |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write power-down to 100k command to DataBuffer B
and Load DAC A and DAC B simultaneously:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  1  |  1  |  0  |  1  |  1  |  0  | Dont care |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write power-down to Hi-Z command to DataBuffer A and Load DAC A:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  0  |  1  |  0  |  0  |  1  |  1  | Dont care |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+

Write power-down to Hi-Z command to DataBuffer B and Load DAC B:
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| D23 | D22 | D21 | D20 | D19 | D18 | D17 | D16 | D15 .. D0 |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
| Reserved  | LDB | LDA |  X  | BUF | PD1 | PD0 |   Data    |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
|  0  |  0  |  1  |  0  |  0  |  1  |  1  |  1  | Dont care |
+-----+-----+-----+-----+-----+-----+-----+-----+-----------+
*/