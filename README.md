Employee Presence Tracker for ESP32

Mitarbeiter Anwesenheits tracker für den ESP32

Dieses Projekt verwendet einen ESP32 und das ESP32Ping- und HTTPClient-Modul, um die Anwesenheit von Mitarbeitern anhand der IP-Adressen ihrer Geräte zu überwachen. Sobald der Status eines Mitarbeiters (online oder offline) geändert wird, ruft das System eine URL auf, die für den Mitarbeiter spezifisch ist.

Voraussetzungen
ESP32 Dev Board
Arduino IDE
Zugang zum WLAN, in dem sich die Geräte der Mitarbeiter befinden
Die URLs, die aufgerufen werden sollen, wenn der Status eines Mitarbeiters geändert wird
Setup
Installieren Sie die erforderlichen Bibliotheken
Fügen Sie die folgenden Bibliotheken zu Ihrem Arduino IDE hinzu:
```cpp
#include <WiFi.h>
#include <ESP32Ping.h>
#include <HTTPClient.h>
#include <map>
```

Konfigurieren Sie die Mitarbeiterinformationen
Erstellen Sie für jeden Mitarbeiter, den Sie überwachen möchten, einen Eintrag in der employeeMap-Variable, die die IP-Adresse, den Namen und die URL des Mitarbeiters enthält.


```cpp
std::map<IPAddress, Employee> employeeMap = {
  { IPAddress(10, 10, 82, 65), {"Alf", "https://domain.ch/idtime.php?id=265a14da"}}, 
  { IPAddress(10, 10, 82, 114), {"Martina", "https://domain.ch/idtime.php?id=125f5ae873"}}
};

```


Konfigurieren Sie die WLAN-Informationen
Aktualisieren Sie die ssid und password Variablen mit den Informationen Ihres WLANs.

```cpp
const char* ssid = "yourSSID";
const char* password = "yourPassword";
```
Nutzung
Laden Sie den Code auf Ihren ESP32 hoch. Der ESP32 beginnt dann mit der Überwachung der Anwesenheit der Mitarbeiter anhand der festgelegten IP-Adressen und ruft die entsprechende URL auf, sobald sich der Status eines Mitarbeiters ändert.

Lizenz
Dieses Projekt steht unter der MIT-Lizenz. Weitere Informationen finden Sie in der Datei LICENSE.


Kann als Addon für SmallTime verwendet werden. (Zeiterfassung für kleinbetriebe auf PHP Basis)
https://github.com/it-m-h/SmallTime
