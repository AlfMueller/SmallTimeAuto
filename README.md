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

ESP32ping Bibliothek: https://github.com/marian-craciunescu/ESP32Ping

Konfigurieren Sie die Mitarbeiterinformationen.
Erstellen Sie für jeden Mitarbeiter, den Sie überwachen möchten, einen Eintrag in der employeeMap-Variable, die die IP-Adresse, den Namen und die URL des Mitarbeiters enthält.

Info: auf dem Router eine Fixe IP dem Gerät zuweisen.

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


Funktion:

Das in diesem Projekt implementierte Anwesenheitssystem basiert auf der Überprüfung der Netzwerkverfügbarkeit eines bestimmten Geräts (z.B. eines Mobiltelefons oder Computers), das einem Mitarbeiter zugeordnet ist.


Initialisierung: Beim Start des ESP32 wird der aktuelle Status (Anwesenheit oder Abwesenheit) eines jeden Mitarbeiters erfasst und als sein grundlegender Status festgelegt. Dabei wird eine Zählvariable mit 5 für Anwesenheit oder 0 für Abwesenheit initialisiert.


Überprüfung der Anwesenheit: Der ESP32 sendet in regelmäßigen Abständen Ping-Anfragen an die IP-Adresse jedes Mitarbeiters. Der Status jeder IP-Adresse wird dann auf der Grundlage der Antwort aktualisiert.


Statusänderung und URL-Aufruf: Wenn der Mitarbeiter anwesend ist und seine IP-Adresse nicht gefunden wird, wird die Zählvariable um eins verringert. Wenn der Mitarbeiter abwesend ist und seine IP-Adresse gefunden wird, wird die Zählvariable um eins erhöht. Sobald die Zählvariable entweder 5 (für Anwesenheit) oder 0 (für Abwesenheit) erreicht, wird der zugehörige URL-Aufruf ausgeführt und der grundlegende Status wird entsprechend geändert.

Sicherheitsüberprüfung: Um Fehlalarme zu vermeiden (z.B. wenn das Gerät eines Mitarbeiters kurzzeitig das Netzwerk verlässt), wird der URL-Aufruf erst ausgeführt, wenn die An- oder Abwesenheit des Mitarbeiters fünf aufeinanderfolgende Male bestätigt wurde.


Insgesamt bietet dieses System eine einfache, automatisierte Methode zur Überwachung der Anwesenheit von Mitarbeitern und zur Durchführung bestimmter Aktionen (wie z.B. das Aufrufen einer URL) bei Änderungen des Anwesenheitsstatus.


Lizenz
Dieses Projekt steht unter der MIT-Lizenz. Weitere Informationen finden Sie in der Datei LICENSE.


Kann als Addon für SmallTime verwendet werden. (Zeiterfassung für kleinbetriebe auf PHP Basis)
https://github.com/it-m-h/SmallTime
