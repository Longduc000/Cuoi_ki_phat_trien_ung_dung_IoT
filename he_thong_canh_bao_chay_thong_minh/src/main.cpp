#include <Arduino.h>
#include "secrets/wifi.h"
#include "wifi_connect.h"
#include <WiFiClientSecure.h>
#include "ca_cert.h"
#include "secrets/mqtt.h"
#include <PubSubClient.h>
#include <Ticker.h>
#include <ESP32Servo.h>

// Khai báo các chân kết nối
const int mq2Pin = 4;
const int buzzer_khoi = 14;
const int servo1Pin = 2;
const int relay_quat = 18;

const int cam_bien_lua= 34;  // Chân kết nối cảm biến lửa (input)
const int buzzer_lua =23 ;      // Chân kết nối còi buzzer (output)
const int relay_may_bom= 25 ;       // Chân kết nối relay điều khiển máy bơm (output)
// Giá trị ngưỡng cho mức khí độc
int smokeThreshold = 2000;
// Khởi tạo đối tượng động cơ servo
Servo servo; 

namespace
{
    const char *ssid = WiFiSecrets::ssid;
    const char *password = WiFiSecrets::pass;
    const char *mq2Pin_topic = "esp32/mq2Pin_sensor";
    const char *cam_bien_lua_topic = "esp32/cam_bien_lua";
    const char *canh_bao_khoi_topic = "esp32/canh_bao_khoi";  
    const char *canh_bao_lua_topic = "esp32/canh_bao_lua";    
    unsigned int publish_count = 0;
    
    uint16_t keepAlive = 15;    // seconds (default is 15)
    uint16_t socketTimeout = 5; // seconds (default is 15)
}

WiFiClientSecure tlsClient;
PubSubClient mqttClient(tlsClient);

Ticker mqttPulishTicker;

void mqttPublish()
{  
  // Đọc giá trị từ cảm biến MQ2
  int smoke = analogRead(mq2Pin);

  // In giá trị lên Serial Monitor để theo dõi
  Serial.println(smoke);
  mqttClient.publish(mq2Pin_topic, String(smoke).c_str(), false);
  // Kiểm tra nếu giá trị khí độc vượt quá ngưỡng



  if (smoke > smokeThreshold) {
    digitalWrite(buzzer_khoi, HIGH);  // Kích hoạt còi
    pinMode(relay_quat, OUTPUT);
    servo.write(0);  // Quay động cơ servo 1 về giữa
    mqttClient.publish(canh_bao_khoi_topic, String("Phát hiện có khói!").c_str(), false);   
  }
  else {
    digitalWrite(buzzer_khoi, LOW);  // Tắt còi
    pinMode(relay_quat, INPUT);  // Tắt quạt
    servo.write(90);  // Động cơ servo 1 ở vị trí ban đầu
  }

  // đọc giá trị cảm biến lửa
  int fire = digitalRead(cam_bien_lua);
  //in giá trị lên Serial monitor
  Serial.println(fire);
  mqttClient.publish(cam_bien_lua_topic , String(fire).c_str(), false);

  //kiểm tra cảm biến lửa
  if (fire == 0) {
    pinMode(relay_may_bom, OUTPUT);
    digitalWrite(buzzer_lua, HIGH);
    mqttClient.publish(canh_bao_lua_topic, String("Phát hiện có cháy!").c_str(), false);  
  }
  else {
    digitalWrite(buzzer_lua, LOW);
    pinMode(relay_may_bom, INPUT);
  }
  delay(1000);
}


void mqttCallback(char *topic, byte *payload, unsigned int length)
{
    Serial.printf("From %s:  ", topic);
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void mqttReconnect()
{
    while (!mqttClient.connected())
    {
        Serial.println("Attempting MQTT connection...");
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        if (mqttClient.connect(client_id.c_str(), MQTT::username, MQTT::password))
        {
            Serial.print(client_id);
            Serial.println(" connected");
            mqttClient.subscribe(mq2Pin_topic);
            mqttClient.subscribe(cam_bien_lua_topic);

        }
        else
        {
            Serial.print("MTTT connect failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 1 seconds");
            delay(1000);
        }
    }
}

void setup()
{
    Serial.begin(115200);
    delay(10);
    setup_wifi(ssid, password);
    tlsClient.setCACert(ca_cert);

    // mqttClient.setKeepAlive(keepAlive); // To see how long mqttClient detects the TCP connection is lost
    // mqttClient.setSocketTimeout(socketTimeout); // To see how long mqttClient detects the TCP connection is lost

    mqttClient.setCallback(mqttCallback);
    mqttClient.setServer(MQTT::broker, MQTT::port);
    mqttPulishTicker.attach(1, mqttPublish);
  // Khởi tạo chân kết nối cho các thiết bị
  pinMode(mq2Pin, INPUT);
  pinMode(buzzer_khoi, OUTPUT);
  pinMode(relay_quat, OUTPUT);
  pinMode(cam_bien_lua, INPUT);
  pinMode(buzzer_lua, OUTPUT);
  pinMode(relay_may_bom, OUTPUT);

  servo.attach(servo1Pin);

  // Đưa động cơ servo về vị trí ban đầu
  servo.write(90);
}

void loop()
{
    if (!mqttClient.connected())
    {
        mqttReconnect();
    }
    mqttClient.loop();
}

