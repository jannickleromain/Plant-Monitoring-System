#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>

Adafruit_BMP280 bmp;
Adafruit_AHTX0 aht;

#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

void setup() {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(500);

  // Clear the buffer.
  display.clearDisplay();
   bmp.begin();
  //Konfigurieren des BMP280 Sensors
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
  
  //beginn der Kommunikation mit dem AHT20 Sensor
  aht.begin();
  

}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  
  display.clearDisplay();        // clear old text
  display.setTextSize(1);        // set font size
  display.setTextColor(WHITE);   // set text color
  display.setCursor(0, 0);       // set cursor position

  int val = analogRead(0);
  Serial.println(val);
  display.print("Temp: ");
  display.print(bmp.readTemperature(), 2);
  display.println(" C");
  
  display.print("Pressure: ");
  display.print(bmp.readPressure(), 2);
  display.println(" Pa");

  display.print("Humidity: ");
  display.print(humidity.relative_humidity,2);
  display.println(" %");
  
display.print("Soil: ");

if (val < 277) {
  display.print("wet");
}
else if (val >= 277 && val <= 380) {
  display.print("perfect");
}
else if (val > 380) {
  display.print("dry");
}
else {
  display.print("Error!");
}

  
  
  
  display.display();



  // Wait for 1 second before the next reading
  delay(1000);
}