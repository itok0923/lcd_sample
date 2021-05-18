#include <Wire.h>
#define LCD_ADRS 0x3E
char moji[]="AQM1602XA-RN-GBW";
//SDA=PB7,SCL=PB6,/RES=PB5

void setup() {
  Wire.begin();
  init_LCD();
}

void loop() {
  for(int i=0;i<16;i++){
    writeData(moji[i]);
  }
  writeCommand(0x40+0x80);//2LINE TOP
  for(int i=0;i<16;i++){
    writeData(i+0xb1);
  }
  while(1){}//stop
}
//データ書き込み
void writeData(byte t_data){
  Wire.beginTransmission(LCD_ADRS);
  Wire.write((uint8_t)0x40);
  Wire.write((uint8_t)t_data);
  Wire.endTransmission();
  delay(1);
}
//コマンド書き込み
void writeCommand(byte t_command){
  Wire.beginTransmission(LCD_ADRS);
  Wire.write((uint8_t)0x00);
  Wire.write((uint8_t)t_command);
  Wire.endTransmission();
  delay(10);
}
//液晶初期化
void init_LCD(){
  delay(100);
  writeCommand((uint8_t)0x38); //FunctionSet IS=0    0011 1000(2)
  delay(20);
  writeCommand((uint8_t)0x39); //FunctionSet IS=1    0011 1001(2)
  //拡張コマンドここから
  delay(20);
  writeCommand((uint8_t)0x14); //Internal OSC freq   0001 0100(2)
  delay(20);
  writeCommand((uint8_t)0x73); //Contrast set        0111 0011(2)
  delay(20);
  writeCommand((uint8_t)0x56); //Pow/ICONctl/CT ctl  0101 0110(2)
  delay(20);
  writeCommand((uint8_t)0x6C); //Follower control    0110 1100(2)
  delay(20);
  //拡張コマンドここまで
  writeCommand((uint8_t)0x38); //Function Set IS=0   0011 1000(2)
  delay(20);
  writeCommand((uint8_t)0x01); //Clear Display       0000 0001(2)
  delay(20);
  writeCommand((uint8_t)0x0C); //Display ON/OFF ctl  0000 1100(2)
  delay(20);
}
