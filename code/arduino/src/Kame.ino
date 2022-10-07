#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <Servo.h>
#include "minikame.h"

// Wifi Access Point configuration
const char *ssid = "kame";
const char *password = "12345678";

void parseData(String data);

MiniKame robot;
ESP8266WiFiMulti wifiMulti;
WiFiServer server(8266);
bool running = 0;
String input;

void setup()
{
    Serial.begin(115200); // 初始化串口，并开启调试信息
    Serial.println();
    Serial.print("Setting soft-AP ... ");

    IPAddress softLocal(192, 168, 1, 101); // IP地址
    IPAddress softGateway(192, 168, 1, 101);
    IPAddress softSubnet(255, 255, 255, 0);

    WiFi.softAPConfig(softLocal, softGateway, softSubnet);
    WiFi.softAP(ssid, password);

    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    server.begin();

    delay(1000);
    robot.init();
}

void loop()
{
    // 客户端需采用TCP通信协议
    WiFiClient client = server.available();
    if (!client)
    {
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
        delay(1000);
    }
    while (client.connected())
    {
        if (running)
        {
            Serial.println("running");
            if (client.available())
            {
                while (client.available())
                    input = client.readStringUntil('+');
                Serial.println(input);    
                parseData(input);
            }
            else
            {
                Serial.println("Keep Moving");
                parseData(input);
            }
        }
        else
        {
            Serial.println("Normal mode");
            if (client.available())
            {
                while (client.available())
                    input = client.readStringUntil('+');
                Serial.println(input);
                parseData(input);
            }
            else
                robot.home();
        }
    }
}

void parseData(String data)
{
    Serial.println("parseData");
    Serial.println(data);
    switch (data.toInt())
    {

    case 1: // Up
        robot.walk(1, 550);
        running = 1;
        break;

    case 2: // Down
        break;

    case 3: // Left
        robot.turnL(1, 550);
        running = 1;
        break;

    case 4: // Right
        robot.turnR(1, 550);
        running = 1;
        break;

    case 5: // STOP
        running = 0;
        break;

    case 6: // heart
        robot.pushUp(2, 2000);
        break;

    case 7: // fire
        robot.upDown(4, 250);
        break;

    case 8: // skull
        robot.jump();
        break;

    case 9: // cross
        robot.hello();
        break;

    case 10: // punch
        robot.frontBack(4, 200);
        break;

    case 11: // mask
        robot.dance(2, 1000);
        break;

    default:
        robot.home();
        break;
    }
}
