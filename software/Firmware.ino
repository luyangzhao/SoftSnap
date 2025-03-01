#include <WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>

#define INA219_ADDR 0x40

static const char *ssid = "BotTest";
static const char *password = "123456789";

// Set web server port number to 80
WiFiServer server(80);
// Variable to store the HTTP request
String header;

#define tolerance 30

#define MA 0
#define MB 1
#define MEA 6
#define MEB 7
#define OPT 8
#define LED_B 5
#define LED_G 21
#define KEY 20
#define POW_EN 10
#define SDA 3
#define SCL 4
volatile bool pause_bot = false;

volatile int32_t M_target = 0;
volatile int32_t M_current = 0;
volatile int32_t M_error = 0;
volatile uint8_t M_power = 0;

volatile uint8_t M_rec;

struct PowerData {
    float shunt_voltage;
    float bus_voltage;
    float current;
    float power;
};

volatile uint16_t VBAT_array[8] = { 0 };
volatile uint16_t VPOW_array[256] = { 0 };
volatile int vbat_index = 0;
volatile int vpow_index = 0;

uint32_t lastADCTime = 0;

void initADC() {
    Wire.begin(SDA, SCL);

    delay(10);

    // 配置INA219寄存器设置
    // BRNG = 0 (16V范围)
    // PGA = 01 (PGA = /2, ±80mV量程)
    // BADC = 1111 (12位, 128样本平均)
    // SADC = 1111 (12位, 128样本平均)
    // MODE = 111 (分流和总线连续测量)
    uint16_t config = 0b0001011111110111;
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x00);
    Wire.write((config >> 8) & 0xFF);   // 高字节
    Wire.write(config & 0xFF);          // 低字节
    if (Wire.endTransmission() != 0) {
        Serial.println("Power Monitor INA219 Init - Fail");
    }
    
    // 校准寄存器设置
    // 对于15毫欧分流电阻，±80mV量程：
    // 最大电流 = 4A (80mV/15mΩ ≈ 5.33A，保守取4A)
    // Current_LSB = 4A/32768 = 122.0703125μA
    // Cal = 0.04096/(Current_LSB * RSHUNT)
    // Cal = 0.04096/(0.0001220703125 * 0.015) = 22395 (0x5775)
    uint16_t calibration = 0x5775;
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x05);
    Wire.write((calibration >> 8) & 0xFF);   // 高字节
    Wire.write(calibration & 0xFF);          // 低字节
    if (Wire.endTransmission() == 0) {
        Serial.println("Power Monitor INA219 Init - Success");
    }
}

PowerData readADC() {
    PowerData data;
    uint16_t raw_value;
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x02);  // 总线电压寄存器
    Wire.endTransmission();
    Wire.requestFrom(INA219_ADDR, 2);
    raw_value = Wire.read() << 8 | Wire.read();
    data.bus_voltage = (raw_value >> 3) * 0.004f;
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x01);  // 分流电压寄存器
    Wire.endTransmission();
    Wire.requestFrom(INA219_ADDR, 2);
    raw_value = Wire.read() << 8 | Wire.read();
    data.shunt_voltage = raw_value * 0.00488f;  // 单位: mV (4.88μV/bit = 0.00488mV/bit)
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x04);  // 电流寄存器
    Wire.endTransmission();
    Wire.requestFrom(INA219_ADDR, 2);
    raw_value = Wire.read() << 8 | Wire.read();
    data.current = raw_value * 0.1220703125f;  // 单位: mA (122.07μA/bit = 0.1220703125mA/bit)
    
    Wire.beginTransmission(INA219_ADDR);
    Wire.write(0x03);  // 功率寄存器
    Wire.endTransmission();
    Wire.requestFrom(INA219_ADDR, 2);
    raw_value = Wire.read() << 8 | Wire.read();
    data.power = raw_value * 2.44140625f;  // 单位: mW (2.44mW/bit)

    // Serial.println(data.bus_voltage);
    // Serial.println(data.shunt_voltage);
    // Serial.println(data.current);
    // Serial.println(data.power);
    return data;
}

void motor() {
  if (M_target - tolerance > M_current && !pause_bot) {
    if (M_target - tolerance * 2 > M_current) {
      digitalWrite(POW_EN, HIGH);
    }
    else if (digitalRead(POW_EN) == HIGH) {
      digitalWrite(POW_EN, LOW);
    }
    ledcWrite(MA, M_power);
    ledcWrite(MB, 0);
  } else if (M_target + tolerance < M_current && !pause_bot) {
    if (M_target + tolerance * 2 < M_current) {
      digitalWrite(POW_EN, HIGH);
    }
    else if (digitalRead(POW_EN) == HIGH) {
      digitalWrite(POW_EN, LOW);
    }
    ledcWrite(MA, 0);
    ledcWrite(MB, M_power);
  } else {
    digitalWrite(POW_EN, LOW);
    ledcWrite(MA, 0);
    ledcWrite(MB, 0);
  }
}

void IRAM_ATTR isr() {
  uint8_t M_now = (digitalRead(MEA) << 1) | digitalRead(MEB);

  // 00,01,11,10
  if ((M_rec == 0b00 && M_now == 0b01) || (M_rec == 0b01 && M_now == 0b11) || (M_rec == 0b11 && M_now == 0b10) || (M_rec == 0b10 && M_now == 0b00))
    M_current++;
  else if ((M_rec == 0b10 && M_now == 0b11) || (M_rec == 0b11 && M_now == 0b01) || (M_rec == 0b01 && M_now == 0b00) || (M_rec == 0b00 && M_now == 0b10))
    M_current--;
  else if (M_rec != M_now)
    M_error++;

  M_rec = M_now;

  motor();
}

float getBattery() {
  int temp = 0;
  for (int i = 0; i < 8; i++)
    temp += VBAT_array[i];
  return temp / 8 / 10000.0;
}

String getPower() {
  String result = "";
  for (int i = 0; i < 256; i++) {
    int index = (vpow_index + i) % 256;
    char hexStr[5];
    snprintf(hexStr, sizeof(hexStr), "%04X", VPOW_array[index]);
    result += hexStr;
  }
  return result;
}

long HexToLong(String s) {
  char arr[13] = { 0 };
  s.toCharArray(arr, sizeof(arr));
  volatile long result = 0;
  for (uint8_t i = 0; i < 12 && arr[i] != 0; i++) {
    if (arr[i] >= '0' && arr[i] <= '9') {
      result <<= 4;
      result |= (arr[i] - '0');
    } else if (arr[i] >= 'A' && arr[i] <= 'F') {
      result <<= 4;
      result |= (arr[i] - 'A' + 10);
    }
  }
  return result;
}

String inputString = "";         // 用于存储接收到的字符串

void setup() {
  digitalWrite(OPT, LOW);
  pinMode(OPT, OUTPUT);
  digitalWrite(OPT, LOW);

  Serial.begin(115200);
  Serial.println("Serial");

  delay(1000);

  pinMode(LED_B, OUTPUT);
  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_B, HIGH);
  digitalWrite(LED_G, HIGH);

  Serial.println("IND Inited");

  pinMode(KEY, INPUT_PULLUP);
  Serial.println("KEY Inited");


  pinMode(POW_EN, OUTPUT);
  digitalWrite(POW_EN, LOW);

  Serial.println("POW Inited");

  ledcAttach(MA, 50000, 8);
  ledcAttach(MB, 50000, 8);
  Serial.println("LEDC Inited");

  initADC();
  Serial.println("Power Sensor Inited");

  attachInterrupt(MEA, isr, CHANGE);
  attachInterrupt(MEB, isr, CHANGE);
  pinMode(MEA, INPUT_PULLUP);
  pinMode(MEB, INPUT_PULLUP);

  M_rec = (digitalRead(MEA) << 1) | digitalRead(MEB);
  delay(500);
  digitalWrite(LED_B, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(LED_B, !digitalRead(LED_B));
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  server.begin();
}

void loop() {

  uint32_t currentTime = millis();
  
  if (currentTime - lastADCTime >= 50) {
    PowerData data = readADC();
    lastADCTime = currentTime;
    for (int i=1; i<8; i++) {
      VBAT_array[i] = VBAT_array[i-1];
    }
    for (int i=1; i<256; i++) {
      VPOW_array[i] = VPOW_array[i-1];
    }
    VBAT_array[0] = data.bus_voltage * 10000;
    VPOW_array[0] = data.power * 10;
  }

  // // 检查是否有可用的串口数据
  // if (Serial.available()) {
  //   char inChar = (char)Serial.read();
    
  //   if (inChar == '\n') {
  //     // 收到换行符,处理完整的输入
  //     int number = inputString.toInt();
      
  //     Serial.print("接收到的数字是: ");
  //     Serial.println(number);
  //     M_target = (int32_t)number;
  //     M_power = (uint8_t)80;
  //     motor();
      
  //     // 在这里可以添加其他对数字的处理逻辑
      
  //     // 清空字符串,为下一次接收做准备
  //     inputString = "";
  //   } else {
  //     // 将新字符添加到输入字符串
  //     inputString += inChar;
  //   }
  // }

  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {                      // If a new client connects,
    Serial.println("New Request.");  // print a message out in the serial port
    String currentLine = "";         // make a String to hold incoming data from the client
    while (client.connected()) {     // loop while the client's connected
      if (client.available()) {      // if there's bytes to read from the client,
        char c = client.read();      // read a byte, then
        Serial.write(c);             // print it out the serial monitor
        header += c;
        if (c == '\n') {  // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            Serial.println(header);
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:application/json");
            client.println("Connection: close");
            client.println();

            // GET /?status HTTP/1.1
            if (header.indexOf("status") >= 0) {
              Serial.println("status requested");
              // Get the status of the system
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else if (header.indexOf("set") >= 0) {
              Serial.println("set requested");
              // Set the target and power of motors
              // Format: `{"M1_trajectory": [[...], [...], ...], "M2_trajectory": [[...], [...], ...], "totalTime": 1000}`
              int pos = header.indexOf('=');
              String M_pos = header.substring(pos + 1, pos + 9);
              String M_pow = header.substring(pos + 9, pos + 11);
              M_target = (int32_t)HexToLong(M_pos);
              M_power = (uint8_t)HexToLong(M_pow);
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else if (header.indexOf("calibrate") >= 0) {
              Serial.println("run requested");
              M_target = M_current = 0;
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else if (header.indexOf("pause") >= 0) {
              Serial.println("pause requested");
              pause_bot = true;
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else if (header.indexOf("resume") >= 0) {
              Serial.println("resume requested");
              pause_bot = false;
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else if (header.indexOf("reach") >= 0) {
              Serial.println("resume requested");
              M_target = M_current;
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            } else {
              Serial.println("error requested");
              client.println("{\"status\":\"ok\", \"ip\":\"" + WiFi.localIP().toString() + "\", \"mac\":\"" + String(WiFi.macAddress()) + "\", \"m_current\":" + M_current + ", \"m_power\": " + M_power + ", \"m_error\": " + M_error + ", \"battery\": " + getBattery() + ", \"pause\":" + (pause_bot ? String("true") : String("false")) + ", \"power\": \"" + getPower() + "\"}");
            }
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else {  // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
    motor();
  }
}
