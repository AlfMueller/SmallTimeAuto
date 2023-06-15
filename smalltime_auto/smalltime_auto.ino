
#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>
#include <map>

const char* ssid = "XXX";
const char* password = "XXX";

struct Employee {
  IPAddress ip;
  String name;
  String url;
};

// Definieren Sie hier alle Mitarbeiter
Employee employees[] = {
  { IPAddress(10, 10, 82, 65), "Alf", "https://XXXXXX/idtime.php?id=afe70dde279f4657" },
  { IPAddress(10, 10, 82, 114), "Martina", "https://XXXXXX/idtime.php?id=4180c1f1590d6dfa" },
  // Fügen Sie hier weitere Mitarbeiter hinzu
};


std::map<IPAddress, Employee> employeeMap;
std::map<IPAddress, bool> employeeStatus;
std::map<IPAddress, int> employeeCounter;
bool firstLoop = true;

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

  // Füllen Sie die Maps mit den Mitarbeiterdaten
  for (const auto& employee : employees) {
    employeeMap[employee.ip] = employee;
    // Prüfen Sie den aktuellen Status und verwenden Sie diesen als Ausgangsstatus
    bool currentStatus = Ping.ping(employee.ip);
    employeeStatus[employee.ip] = currentStatus;
    // Initialisieren Sie den Counter mit 0
    employeeCounter[employee.ip] = 0;
  }
}

void loop() {
  for (auto& employee : employeeStatus) {
    IPAddress ip = employee.first;
    bool result = Ping.ping(ip);
    if (result == employee.second) {
      // Status is the same, increment counter
      if (employeeCounter[ip] < 5) {
        employeeCounter[ip]++;
      } else {
        // If status remains the same and counter reached 5, reset the counter
        employeeCounter[ip] = 0;
      }
    } else {
      // Status changed, reset counter
      employeeCounter[ip] = 1;
    }
    employee.second = result;

    // Check if status changed and counter reached 5
    if (employeeCounter[ip] == 5 && !firstLoop) {
      HTTPClient http;
      http.begin(employeeMap[ip].url);
      int httpCode = http.GET();
      if (httpCode > 0) {
        Serial.printf("URL called for %s, response: %d\n", employeeMap[ip].name.c_str(), httpCode);
      } else {
        Serial.printf("Failed to call URL for %s\n", employeeMap[ip].name.c_str());
      }
      http.end();

      // Reset counter after calling the URL
      employeeCounter[ip] = 0;
    }
  }

  // Set firstLoop to false after the first run
  if (firstLoop) {
    firstLoop = false;
  }

  printEmployeeStatus(); // Ausgabe des Mitarbeiterstatus im Monitor
  delay(30000); // Check every 30 seconds
}

void printEmployeeStatus() {
  Serial.println("Employee Status:");
  for (const auto& employee : employeeStatus) {
    Employee emp = employeeMap[employee.first];
    Serial.print("Name: ");
    Serial.print(emp.name);
    Serial.print(" - IP: ");
    Serial.print(emp.ip);
    Serial.print(" - URL: ");
    Serial.print(emp.url);
    Serial.print(" - Status: ");
    Serial.println(employee.second ? "Online" : "Offline");
  }
  Serial.println();
}