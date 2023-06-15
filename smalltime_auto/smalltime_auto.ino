#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>
#include <map>

struct Employee {
  String name;
  String url;
};

const char* ssid = "XXXX";
const char* password = "XXXX";

std::map<IPAddress, Employee> employeeMap = {
  { IPAddress(10, 10, 82, 65), {"Alf", "https://XXXXX.ch/idtime.php?id=afe70dde279f4657"}},    // IP name und URL ersetzten
  { IPAddress(10, 10, 82, 114), {"Martina", "https://XXXX.ch/idtime.php?id=4180c1f1590d6dfa"}}
};

std::map<IPAddress, bool> employeeStatus;
std::map<IPAddress, int> employeeCounter;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  for (const auto& employee : employeeMap) {
    IPAddress ip = employee.first;
    bool result = Ping.ping(ip);
    employeeStatus[ip] = result;
    employeeCounter[ip] = result ? 5 : 0;
  }
}

void loop() {
  for (auto& employee : employeeMap) {
    IPAddress ip = employee.first;
    bool result = Ping.ping(ip);

    if(result){
      if(!employeeStatus[ip]) {
        employeeCounter[ip]++;
      }
    }
    else{
      if(employeeStatus[ip]){
        employeeCounter[ip]--;
      }
    }

    if((!employeeStatus[ip] && employeeCounter[ip] >= 5) || 
       (employeeStatus[ip] && employeeCounter[ip] <= 0)) {
      // Change status and reset counter
      employeeStatus[ip] = !employeeStatus[ip];
      employeeCounter[ip] = employeeStatus[ip] ? 5 : 0;

      // Call the URL
      HTTPClient http;
      http.begin(employee.second.url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("URL called for %s, response: %d\n", employee.second.name.c_str(), httpCode);
      } else {
        Serial.printf("Failed to call URL for %s\n", employee.second.name.c_str());
      }
      http.end();
    }
  }

  printEmployeeStatus(); 
  delay(30000); // Check every 30 seconds
}

void printEmployeeStatus() {
  Serial.println("Employee Status:");
  for (const auto& employee : employeeStatus) {
    Serial.print("Name: ");
    Serial.print(employeeMap[employee.first].name);
    Serial.print(" - IP: ");
    Serial.print(employee.first);
    Serial.print(" - Status: ");
    Serial.println(employee.second ? "Online" : "Offline");
  }
  Serial.println();
}
