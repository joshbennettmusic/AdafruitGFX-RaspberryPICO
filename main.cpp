#include "pico/stdlib.h"
#include "hardware/spi.h"
//#include <Adafruit_SSD1306.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_ILI9341.h>
#include "fontsHelper.h"
#include "FreeMono12pt7b.h"
#include "FreeSans9pt7b.h"

#define CS 17
#define DC 22
#define RST 6
#define MISO PICO_DEFAULT_SPI_RX_PIN
#define MOSI PICO_DEFAULT_SPI_TX_PIN
#define SCLK PICO_DEFAULT_SPI_SCK_PIN
//#define SDA 18
// #define SCL 19
#define LCD_ON 20
#define BITRATE 32 * 1000 * 1000 //32 MHz eventually
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320



Adafruit_SPIDevice _spidev(CS, SCLK, MISO, MOSI, BITRATE, spi0);
Adafruit_ILI9341 _display(&_spidev, DC, CS, RST);
GFXcanvas16 _framebuff(DISPLAY_HEIGHT,DISPLAY_WIDTH);

int main()
{
    stdio_init_all();
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    gpio_init(LCD_ON);
    gpio_set_dir(LCD_ON, GPIO_OUT);
    gpio_put(LCD_ON, 1);

    _display.begin();
    //Shows splash screen


    _display.setRotation(1);
    _display.fillScreen(ILI9341_BLACK);

    _display.setTextColor(ILI9341_RED);
    _display.setFont(&FreeSans9pt7b);
    _display.print("Hi Josh!");


    uint32_t cnt = 0;
    uint8_t dec = 56;
    while (dec--)
    {
        gpio_put(25, 1);
        _display.print(cnt++);
        _display.print(" ");

    }
    sleep_ms(1000);

    gpio_put(25, 0);
    while (2 > 1)
    {
        for (uint8_t i = 0; i < DISPLAY_WIDTH/2; ++i)
        {
            _framebuff.fillCircle(DISPLAY_HEIGHT/2, DISPLAY_WIDTH/2, i, ILI9341_BLUE);
            //_display.WriteBuffer(_framebuff);
            _display.drawRGBBitmap(0,0,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

        }
        _framebuff.fillScreen(ILI9341_BLACK);

        for (uint8_t i = DISPLAY_WIDTH/2; i > 0; --i)
        {
            _display.fillScreen(ILI9341_BLACK);
            _framebuff.fillScreen(ILI9341_BLACK);
            _framebuff.fillCircle(DISPLAY_HEIGHT/2, DISPLAY_WIDTH/2, i, ILI9341_RED);
            _display.drawRGBBitmap(0,0,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

        }
        _framebuff.fillScreen(ILI9341_GREEN);
        _display.drawRGBBitmap(0,0,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

    }
}