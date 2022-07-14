#include "pico/stdlib.h"
#include "hardware/spi.h"
//#include <Adafruit_SSD1306.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_ILI9341.h>
#include "fontsHelper.h"
#include "FreeSansBold12pt7b.h"
#include "FreeSans9pt7b.h"
#include "FreeMono9pt7b.h"
#include "OpenSansBold12pt.h"
#include "RobotoBlack13pt.h"
#include "RobotoBold16pt.h"
#include "BigNumbers.h"


#define CS 17
#define DC 22
#define RST 6
#define MISO PICO_DEFAULT_SPI_RX_PIN
#define MOSI PICO_DEFAULT_SPI_TX_PIN
#define SCLK PICO_DEFAULT_SPI_SCK_PIN
//#define SDA 18
// #define SCL 19
#define LCD_ON 20
#define BITRATE 32 * 1000 * 1000 //31.25 MHz is max from testing eventually, but setting it higher doesn't hurt
#define DISPLAY_WIDTH 240
#define DISPLAY_HEIGHT 320



Adafruit_SPIDevice _spidev(CS, SCLK, MISO, MOSI, BITRATE, spi0);
Adafruit_ILI9341 _display(&_spidev, DC, CS, RST);
GFXcanvas16 _framebuff(DISPLAY_HEIGHT-8,DISPLAY_WIDTH-8);
char textBuf[100];

int main()
{
    stdio_init_all();
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);

    gpio_init(LCD_ON);
    gpio_set_dir(LCD_ON, GPIO_OUT);
    gpio_put(LCD_ON, 1);

    _display.begin(BITRATE);
    //Shows splash screen
    strcpy(textBuf,"Hi Josh!\nHow's Things?");

    _display.setRotation(1);
    _display.fillScreen(ILI9341_BLACK);

    _display.setTextColor(ILI9341_WHITE);
    _display.setFont(&Roboto_Bold_16);

    _framebuff.setTextColor(ILI9341_MAGENTA);
    _framebuff.setFont(&FreeSans9pt7b);

    // TEST
    _display.setTextBox(0,4,320,70);
    _display.setParaAlignment(alignCenter, alignTop);
    _display.setFont(&FreeSansBold12pt7b);
    _display.print("Adjust IR EQ Low");

    _display.setTextBox(0,70,320,70);
    _display.setParaAlignment(alignCenter, alignTop);
    _display.setFont(&BigNumbers);
    _display.print(5);
    _display.setParaAlignment(alignCenter, alignBottom);
    _display.setFont(&Roboto_Bold_16);
    _display.print("Martin D18 - KM84");       
    
    _display.setParaAlignment(alignCenter, alignBottom);
    _display.setTextBox(4,236,104,-50);
    _display.print("Gain\n+3dB");

    _display.setTextBox(108,236,104,-50);
    _display.print("Freq\n1.2kHz");

    _display.setTextBox(212,236,104,-50);
    _display.print("Type\nBell");

    _display.setTextBox(4,40,312,50);
    _display.setParaAlignment(alignLeft, alignMiddle);    
    _display.print("HPF Freq\n80Hz");
    _display.setParaAlignment(alignRight, alignMiddle);    
    _display.print("Back");

    _display.setTextBox(4,150,312,50);
    _display.setParaAlignment(alignLeft, alignMiddle);    
    _display.print("HPF Order\n2nd");
    _display.setParaAlignment(alignRight, alignMiddle);    
    _display.print("Help");

    // _display.setParaAlignment(alignLeft, alignMiddle);
    // _display.print("Middle\nLeft");

    // _display.setParaAlignment(alignCenter, alignMiddle);
    // _display.print("Middle\nCenter");

    // _display.setParaAlignment(alignRight, alignMiddle);
    // _display.print("Middle\nRight");

    // _display.setParaAlignment(alignLeft, alignBottom);
    // _display.print("Bottom\nLeft");

    // _display.setParaAlignment(alignCenter, alignBottom);
    // _display.print("Bottom\nCenter");

    // _display.setParaAlignment(alignRight, alignBottom);
    // _display.print("Bottom\nRight");

    sleep_ms(1000);
    _display.fillRect(0,0,_display.width(),2,ILI9341_RED);
    _display.fillRect(0,_display.height(),_display.width(),-2,ILI9341_RED);
    _display.fillRect(0,0,2,_display.height(),ILI9341_RED);
    _display.fillRect(_display.width(),0,-2,_display.height(),ILI9341_RED);
    _framebuff.fillScreen(ILI9341_BLACK);

    gpio_put(25, 0);
    while (2 > 1)
    {

        for (uint8_t i = 0; i < DISPLAY_WIDTH/2; ++i)
        {
            _framebuff.fillCircle(DISPLAY_HEIGHT/2, DISPLAY_WIDTH/2, i, ILI9341_BLUE);
            //_display.WriteBuffer(_framebuff);
            _display.drawRGBBitmap(4,4,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

        }
        _framebuff.fillScreen(ILI9341_BLACK);

        for (uint8_t i = DISPLAY_WIDTH/2; i > 0; --i)
        {
            //_display.fillScreen(ILI9341_BLACK);
            _framebuff.fillScreen(ILI9341_BLACK);
            _framebuff.fillCircle(DISPLAY_HEIGHT/2, DISPLAY_WIDTH/2, i, ILI9341_RED);
            _display.drawRGBBitmap(4,4,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

        }
        _framebuff.fillScreen(ILI9341_BLACK);
        _framebuff.setParaAlignment(alignLeft, alignTop);
        _framebuff.print("Top\nLeft");

        _framebuff.setParaAlignment(alignCenter, alignTop);
        _framebuff.print("Top\nCenter");

        _framebuff.setParaAlignment(alignRight, alignTop);
        _framebuff.print("Top\nRight");

        _framebuff.setParaAlignment(alignLeft, alignMiddle);
        _framebuff.print("Middle\nLeft");

        _framebuff.setParaAlignment(alignCenter, alignMiddle);
        _framebuff.print("Middle\nCenter");

        _framebuff.setParaAlignment(alignRight, alignMiddle);
        _framebuff.print("Middle\nRight");

        _framebuff.setParaAlignment(alignLeft, alignBottom);
        _framebuff.print("Bottom\nLeft");

        _framebuff.setParaAlignment(alignCenter, alignBottom);
        _framebuff.print("Bottom\nCenter");

        _framebuff.setParaAlignment(alignRight, alignBottom);
        _framebuff.print("Bottom\nRight");
        _display.drawRGBBitmap(4,4,_framebuff.getBuffer(),_framebuff.width(), _framebuff.height());

    }
}