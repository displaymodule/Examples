/**
 * @file DM-OLED12-667 Example Code
 * @author DisplayModule
 * @brief  code for  DM-OLED12-667  use 4-Wire SPI 
 * @version 0.1
 * @date 2022-09-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include “nrf_drv_spi.h”
#include “nrf_gpio.h”

#include “dxc_hal.h”
#include “dxc_halLcd.h”
#include “drv_rm67162.h”

#if 0

    static const nrfx_spim_t oled_spi = NRFX_SPIM_INSTANCE(3);

    /**
     * @brief spi init
     * 
     */

    static void rm6716x_spi_init(void)
    {
    nrfx_spim_config_t spi_config = NRFX_SPIM_DEFAULT_CONFIG;
    spi_config.ss_pin = RM6716X_SPI_CSN_PIN;
    spi_config.sck_pin = RM6716X_SPI_SCK_PIN;
    spi_config.mosi_pin = RM6716X_SPI_MOSI_PIN;
    spi_config.miso_pin = RM6716X_SPI_MISO_PIN;
    spi_config.irq_priority = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY;
    spi_config.frequency = NRF_SPIM_FREQ_8M;
    spi_config.mode = NRF_SPIM_MODE_0;
    spi_config.bit_order = NRF_SPIM_BIT_ORDER_MSB_FIRST;


    // Blocking mode
    APP_ERROR_CHECK(nrfx_spim_init(&oled_spi, &spi_config, NULL, NULL));

    }


    /**
     * @brief  send data, must be Blocking mode
     * 
     * @param in  :input data
     * @param inLen  :input data length
     * @param out    :out data
     * @param outLen   :out data length
     */

    void rm6716x_transfer(const uint8_t* in, uint8_t inLen, uint8_t* out, uint8_t outLen)
    {
    ret_code_t ret;
    nrfx_spim_xfer_desc_t spim_desc;
    spim_desc.p_rx_buffer = out;
    spim_desc.rx_length = outLen;
    spim_desc.p_tx_buffer = in;
    spim_desc.tx_length = inLen;

    //rm6716x_spi_csn_clr();
    ret = nrfx_spim_xfer(&oled_spi, &spim_desc, 0);
    //rm6716x_spi_csn_set();
    APP_ERROR_CHECK(ret);
    }


#else
 
    /**< SPI instance. */
    static const nrf_drv_spi_t oled_spi = NRF_DRV_SPI_INSTANCE(0);


    /**
     * @brief init spi
     * 
     */
    static void rm6716x_spi_init(void)
    {
    const nrf_drv_spi_config_t spi_config = {
        .ss_pin = NRF_DRV_SPI_PIN_NOT_USED,
        .sck_pin = RM6716X_SPI_SCK_PIN,
        .mosi_pin = RM6716X_SPI_MOSI_PIN,
        .miso_pin = RM6716X_SPI_MISO_PIN,
        .irq_priority = APP_IRQ_PRIORITY_MID,
        .orc          = 0xFF, 
        .frequency    = NRF_DRV_SPI_FREQ_8M,
        .mode         = NRF_DRV_SPI_MODE_0,
        .bit_order    = NRF_DRV_SPI_BIT_ORDER_MSB_FIRST,
    };

    nrf_gpio_cfg_output(RM6716X_SPI_CSN_PIN);
    rm6716x_spi_csn_set();

    APP_ERROR_CHECK(nrf_drv_spi_init(&oled_spi, &spi_config, NULL, NULL));

    }

    void rm6716x_transfer(const uint8_t* in, uint8_t inLen, uint8_t* out, uint8_t outLen)
    {
    ret_code_t ret;
    ret = nrf_drv_spi_transfer(&oled_spi, in, inLen, out, outLen);
    APP_ERROR_CHECK(ret);

    }

#endif


/**
 * @brief  set command mode
 * 
 * @return __INLINE 
 */
static __INLINE void rm6716x_set_command_mode(void)
{
    nrf_gpio_pin_clear(RM6716X_CMD_DATA_PIN);
    delay_us(22);
}

/**
 * @brief set data mode
 * 
 * @return __INLINE 
 */
static __INLINE void rm6716x_set_data_mode(void)
{
    nrf_gpio_pin_set(RM6716X_CMD_DATA_PIN);
    delay_us(22);
}

/**
 * @brief write data
 * 
 * @param data 
 * @param dataLen 
 */
void rm6716x_write_data(const uint8_t* data, uint16_t dataLen)
{
    rm6716x_spi_csn_clr();
    rm6716x_set_data_mode();
    rm6716x_transfer(data, dataLen, NULL, 0);
    rm6716x_spi_csn_set();
}

/**
 * @brief send command&data
 * 
 * @param cmd 
 * @param data 
 * @param dataLen 
 */
void rm6716x_send_command_data(uint8_t cmd, const uint8_t* data, uint16_t dataLen)
{
    rm6716x_spi_csn_clr();
    // send command
    rm6716x_set_command_mode();
    rm6716x_transfer(&cmd, 1, NULL, 0);

// send data
    if (data && dataLen > 0)
    {
        rm6716x_set_data_mode();
        rm6716x_transfer(data, dataLen, NULL, 0);
    }

    rm6716x_spi_csn_set();
}

/**
 * @brief send command & byte
 * 
 * @param cmd 
 * @param byte 
 * @return __INLINE 
 */
static __INLINE void rm6716x_send_command_byte(uint8_t cmd, uint8_t byte)
{
    rm6716x_send_command_data(cmd, &byte, 1);
}

/**
 * @brief send command
 * 
 * @param cmd 
 * @return __INLINE 
 */
static __INLINE void rm6716x_write_command(uint8_t cmd)
{
    rm6716x_send_command_data(cmd, NULL, 0);
}


uint16_t mem_start_address; 
int16_t mem_length = 390; 
int16_t mem_width = 390; 


/**
 * @brief who am i
 * 
 */
void rm6716x_who_am_i(void)
{
    uint8_t buff[8];
    memset(buff, 0, sizeof(buff));
    buff[0] = 0x04;
    //rm6716x_write_command(0x04);
    rm6716x_transfer(buff, 1, &buff[1], 3);

    Debug("buff: %02x-%02x-%02x-%02x-%02x-%02x", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5]);
}


/**
 * @brief x120bln init
 * 
 */
void rm6716x_x120bln_init(void)
{
    uint8_t buff[32];
    uint8_t offset;
    // pin init
    hal_gpio_cfg_output(RM6716X_POWER_ENABLE_PIN);
    hal_gpio_cfg_output(RM6716X_SPI_RESET_PIN);
    hal_gpio_cfg_output(RM6716X_CMD_DATA_PIN);

    // power enable
    hal_gpio_pin_set(RM6716X_POWER_ENABLE_PIN);
    delay_ms(15);

    // reset
    rm6716x_reset();

    // init
    rm6716x_spi_init();
    delay_ms(2);

    rm6716x_send_command_byte(0xfe, 0x01); // page 1
    rm6716x_send_command_byte(0x6c, 0x0a); // mipi turn off
    rm6716x_send_command_byte(0x04, 0xa0);// enable spi write ram

    rm6716x_send_command_byte(0xfe, 0x05);
    rm6716x_send_command_byte(0x05, 0x00);

    rm6716x_send_command_byte(0xfe, 0x00);
    rm6716x_send_command_byte(0x35, 0x00);
    rm6716x_send_command_byte(0x36, RM6716X_MADCTL_MY|RM6716X_MADCTL_MX|RM6716X_MADCTL_RGB);
    rm6716x_send_command_byte(RM6716X_CMD_SET_BRIGHTNESS, 200);
    rm6716x_send_command_byte(0x53, 0x20);
    rm6716x_send_command_byte(0xc4, 0x80);
    rm6716x_send_command_byte(0x3a, RM6716X_RGB_FORMAT_565);

    offset = 0;
    buff[offset++] = 0x00;
    buff[offset++] = 0x00;
    buff[offset++] = 0x01;          // 0x00ef = 239; 319 = 0x013f
    buff[offset++] = 0x85;
    rm6716x_send_command_data(RM6716X_CMD_COLUMN_ADDR_SET, buff, offset);
    offset = 0;
    buff[offset++] = 0x00;
    buff[offset++] = 0x00;
    buff[offset++] = 0x01;          // 0x00ef = 239; 319 = 0x013f
    buff[offset++] = 0x85;
    rm6716x_send_command_data(RM6716X_CMD_ROW_ADDR_SET, buff, offset);

    rm6716x_write_command(0x11);            // sleep out
    delay_ms(120);

    rm6716x_write_command(0x29);
    delay_ms(20);
    rm6716x_write_command(0x2C);
    delay_ms(20);
    rm6716x_show_block_color(0, 0, 389, 389, WHITE);
}


/**
 * @brief regsitor init
 * 
 */
void rm6716x_init(void)
{
    // gpio init
    //hal_gpio_cfg_output(RM6716X_BACK_LIGHT_PIN);
    hal_gpio_cfg_output(RM6716X_POWER_ENABLE_PIN);
    hal_gpio_cfg_output(RM6716X_SPI_RESET_PIN);
    hal_gpio_cfg_output(RM6716X_CMD_DATA_PIN);
    rm6716x_spi_init();
    //delay_ms(1);
    //nrf_gpio_pin_set(RM6716X_BACK_LIGHT_PIN);
    delay_ms(1);
    nrf_gpio_pin_clear(RM6716X_SPI_RESET_PIN);
    delay_ms(2);
    nrf_gpio_pin_set(RM6716X_SPI_RESET_PIN);
    delay_ms(2);

    // reg config
    rm6716x_write_command(RM6716X_CMD_SLEEP_OUT);
    delay_ms(10);
    //rm6716x_register_init();
}

/**
 * @brief power enable
 * 
 */
void rm6716x_power_enable(void)
{
    hal_gpio_cfg_output(RM6716X_SPI_RESET_PIN);
    hal_gpio_pin_clear(RM6716X_SPI_RESET_PIN);
    hal_gpio_cfg_output(RM6716X_CMD_DATA_PIN);


    hal_gpio_cfg_output(RM6716X_POWER_ENABLE_PIN);
    hal_gpio_pin_set(RM6716X_POWER_ENABLE_PIN);
}

/**
 * @brief init spi
 * 
 */
void rm6716x_spi_enable(void)
{
    rm6716x_spi_init();
}

/**
 * @brief rm6716x reset
 * 
 */
void rm6716x_reset(void)
{
    hal_gpio_cfg_output(RM6716X_SPI_RESET_PIN);
    delay_us(20);
    nrf_gpio_pin_set(RM6716X_SPI_RESET_PIN);
    delay_ms(4);
    nrf_gpio_pin_clear(RM6716X_SPI_RESET_PIN);
    delay_ms(4);
    nrf_gpio_pin_set(RM6716X_SPI_RESET_PIN);
    delay_ms(12);
}

/**
 * @brief sleep mode
 * 
 */
void rm6716x_enter_sleep(void)
{
    rm6716x_write_command(RM6716X_CMD_DISPLAY_OFF);
    //delay_ms(10);
    rm6716x_write_command(RM6716X_CMD_SLEEP_IN);
    // close backlight
    //nrf_gpio_pin_clear(RM6716X_BACK_LIGHT_PIN);
}

// @brief exit sleep mode
void rm6716x_exit_sleep(void)
{
    rm6716x_write_command(RM6716X_CMD_SLEEP_OUT);
    delay_ms(5);
    rm6716x_write_command(RM6716X_CMD_DISPLAY_ON);

}

/**
 * @brief set window addr
 * 
 * @param xs  ver left
 * @param ys  hor left
 * @param xe  ver right
 * @param ye  hor right
 */
void rm6716x_set_addr_window(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    uint8_t buff[4];
    buff[0] = xs >> 8;
    buff[1] = xs;
    buff[2] = xe >> 8;
    buff[3] = xe;
    rm6716x_send_command_data(RM6716X_CMD_COLUMN_ADDR_SET, buff, 4);

    buff[0] = ys >> 8;
    buff[1] = ys;
    buff[2] = ye >> 8;
    buff[3] = ye;
    rm6716x_send_command_data(RM6716X_CMD_ROW_ADDR_SET, buff, 4);

    rm6716x_write_command(RM6716X_CMD_MEM_WRITE);
}


// @brief Displays the color of a block
/**
 * @brief 
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @param color 
 * @return true 
 * @return false 
 */
bool rm6716x_show_block_color(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
    uint16_t i;
    uint16_t length, weight;
    uint8_t buff[256];
    if (x2 > mem_length - 1)
        x2 = mem_length - 1;
    if (y2 > mem_length - 1)
        y2 = mem_length - 1;
    if (x1 < 0)
        x1 = 0;
    if (y1 < 0)
        y1 = 0;

    if ((x1 > x2) || (y1 > y2))
    {
        //Log("show block color failed. x1:y1=(%d:%d), x2:y2=(%d:%d)", x1, y1, x2, y2);
        return FALSE;
    }

    length = x2-x1+1; 
    weight = y2-y1+1;

    for (i=0; i<=256;) 
    {
        buff[i++] = color >> 8;
        buff[i++] = color;
    }

    // Write to a region of memory
    rm6716x_set_addr_window(x1, y1, x2, y2);
    for(i=0; i<weight; i++)
    {
        if (length < 128)
        {
            rm6716x_write_data(buff, (length << 1));
        }
        else 
        {
            rm6716x_write_data(buff, length);
            rm6716x_write_data(buff, length);
        }
    }
    rm6716x_write_command(0x2C);
    delay_ms(20);
    return TRUE;
}

/**
 * @brief Display a part of a picture
 * 
 * @param x1 
 * @param y1 
 * @param xoft 
 * @param yoft 
 * @param data 
 * @return true   Image is displayed successfully
 * @return false  Image is displayed false
 */
bool rm6716x_show_picture(int16_t x1, int16_t y1, int16_t xoft, int16_t yoft, const uint8_t *data)
{
    int16_t i;
    int16_t length, width;
    uint8_t buf[256];
    uint32_t offset = 8;
    int16_t xLen, yLen; //
    // If the coordinates are less than 0, you have to do an offset
    if (x1 < 0)
    {
        xoft += (-x1);
        x1 = 0;
    }
    if (y1 < 0)
    {
        yoft += (-y1);
        y1 = 0;
    }

    length = ((data[2] << 8) | (data[3] & 0xFF));
    width = ((data[4] << 8) | (data[5] & 0xFF));
    if (xoft > length - 1 || yoft > width - 1)      //Offset out of picture size 
    {
        Log("The error picture position. xoft=%d, yoft=%d, width=%d, length=%d", xoft, yoft, width, length);
        return FALSE;
    }

    xLen = length - xoft;
    yLen = width - yoft;
    xoft = 0;
    if (x1 + xLen > mem_length - 1)
        xLen = mem_length - x1;
    else
        xoft = (length - xLen) * 2;
    length <<= 1;
    if (y1 + yLen > mem_width - 1)
        yLen = mem_width - y1;
    else
        offset += yoft * length;

    //Log("x1+xLen-1=%d, %d", x1+xLen-1, y1+yLen-1);
    rm6716x_set_addr_window(x1, y1, x1 + xLen - 1, y1 + yLen - 1);
    for (i=0; i<yLen; i++)
    {
        if (xLen < 128)
        {
            memcpy(buf, &data[offset + xoft], (xLen << 1));
            rm6716x_write_data(buf, (xLen << 1));
        }
        else 
        {
            memcpy(buf, &data[offset + xoft], xLen);
            rm6716x_write_data(buf, xLen);
            memcpy(buf, &data[offset+xLen + xoft], xLen);
            rm6716x_write_data(buf, xLen);
        }
        
        offset += length;
    }
    return TRUE;
}

/**
 * @brief Vertical scroll defines the command
 * 
 * @param tfix  Top fixed area
 * @param scoll Scroll area
 * @param bfix  Bottom fixed area
 */

void rm6716x_vertical_scrolling_defined(uint16_t tfix, uint16_t scoll, uint16_t bfix)
{
    uint8_t data[6];
    data[0] = tfix >> 8;
    data[1] = tfix;
    data[2] = scoll >> 8;
    data[3] = scoll;
    data[4] = bfix >> 8;
    data[5] = bfix;
    LCD_SendCmdData(RM6716X_CMD_VERTICAL_SCROLLING, data, 6);
}

/**
 * @brief Set the vertical scroll start address
 * 
 * @param addr 
 */
void rm6716x_set_mem_start_address(uint16_t addr)
{
    uint8_t data[2];
    if (addr == mem_start_address)
        return;
    mem_start_address = addr;
    data[0] = addr >> 8;
    data[1] = addr;
    LCD_SendCmdData(RM6716X_CMD_VER_SCRO_START_ADDR, data, 2);
}