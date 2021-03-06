#include "DAC8532.h"
#include "debug.h"

void DAC8532_Write(uint8_t reg_cmd, uint16_t reg_data)
{
    DEV_Digital_Write(DEV_CS1_PIN, 1);
    DEV_Digital_Write(DEV_CS1_PIN, 0);
    DEV_SPI_WriteByte(reg_cmd);
    DEV_SPI_WriteByte((reg_data >> 8));
    DEV_SPI_WriteByte((reg_data & 0xff));
    DEV_Digital_Write(DEV_CS1_PIN, 1);
}

void DAC8532_Set_Voltage(uint8_t channel, double voltage)
{
    if (DAC8532_VREF < voltage)
    {
        DAC8532_ERR("invalid voltage value");
        return;
    }

    uint16_t reg_data = (uint16_t) (voltage * DAC8532_REG_VALUE_MAX / DAC8532_VREF);
    DAC8532_Write(channel, reg_data);
}