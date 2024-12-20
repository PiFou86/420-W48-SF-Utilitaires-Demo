# Utilitaires pour le cours 420-W48-SF

Les codes suivants peuvent être réutilisés. Simplement spécifier en commentaire la provenance.

Et ne faites pas comme :

![Pas de temps pour prendre du recul !](https://github.com/user-attachments/assets/028c8de4-8e1b-4f86-b890-d7c6353383a8)

## Interprétation des erreurs dans la console (port série)

L'ESP32 peut afficher des informations babares et redémarrer. Pour décoder ses informations vous pouvez ajouter les couples clefs/valeurs suivantes dans votre configuration platformio.ini :

```ini
monitor_filters = esp32_exception_decoder
build_type = debug
```

## Journalisation

L'objet global ```Logger``` permet de journaliser les messages. Ces messages peuvent avoir plusieurs niveaux de priorités : error, warning, info, verbose. Voir méthode ```Program::demoLogger()``` pour un exemple.

L'objet global ```Logger``` doit être initialisé avant d'être utilisé avec la méthode ```begin(Stream *)```.

```cpp
Program::Program() {
  Serial.begin(SERIAL_SPEED);
  Logger.begin(&Serial);

  // ...
}

void Program::loop() {
  // ...
}
```

Pour utiliser la journalisation vous avez accès aux méthodes :

```cpp
  void error(const String &value, bool writePrefix = true);
  void errorln(const String &value, bool writePrefix = true);
  void error(const char *value, bool writePrefix = true);
  void errorln(const char *value, bool writePrefix = true);

  void warning(const String &value, bool writePrefix = true);
  void warningln(const String &value, bool writePrefix = true);
  void warning(const char *value, bool writePrefix = true);
  void warningln(const char *value, bool writePrefix = true);

  void info(const String &value, bool writePrefix = true);
  void infoln(const String &value, bool writePrefix = true);
  void info(const char *value, bool writePrefix = true);
  void infoln(const char *value, bool writePrefix = true);

  void verbose(const String &value, bool writePrefix = true);
  void verboseln(const String &value, bool writePrefix = true);
  void verbose(const char *value, bool writePrefix = true);
  void verboseln(const char *value, bool writePrefix = true);

  void print(const String &value, bool writePrefix = true);
  void println(const String &value, bool writePrefix = true);
```

Le niveau de journalisation est défini par la méthode ```Logger::setLoggerLevel(LogLevel)```.

```cpp
  Logger::setLoggerLevel(LoggerLevel::Error);
```

## Interpréteur de commandes sur le port série

La classe ```BasicCommandInterpreter``` permet d'interpréter les commandes entrées sur un ```Stream```. L'objet ```Serial``` est un ```Stream``` qui utilise le circuit intégré qui transforme le port USB de votre carte de développement en un port série.

La class ```SpecialCommandInterpreter``` montre comment étendre la classe ```BasicCommandInterpreter``` pour interpréter des commandes spécifiques.

Les commandes disponibles dans l'exemple sont différentes pour une plaquette Arduino Uno et pour une plaquette ESP32.

Afin de pouvoir interpréter des commandes, il faut créer un objet de la classe ```SpecialCommandInterpreter```et appeler la méthode ```tick()``` dans la boucle principale du programme.

```cpp
Program::Program() : m_basicCommandInterpretor(nullptr) {
  Serial.begin(SERIAL_SPEED);

  this->m_basicCommandInterpretor = new SpecificCommandInterpretor(Serial);

  // ...
}

void Program::loop() {
  this->m_basicCommandInterpretor->tick();
}
```

Affichage sur le port série :

```
00:02:15.005 - > help 
00:02:15.005 - 
00:02:15.006 -   specific
00:02:15.006 - 
00:02:15.006 - Available commands:
00:02:15.006 -   hello
00:02:15.017 -   id
00:02:15.017 -   set <key> <value>
00:02:15.017 -   get <key>
00:02:15.017 -   scan i2c|wifi
00:02:15.017 -   reboot
00:02:15.028 -   flash
00:02:15.028 -   network
00:02:15.028 - 
00:02:15.028 -   help
00:02:35.117 - > network 
00:02:35.117 - Network: 
00:02:35.117 -   - SSID: 
00:02:35.117 -   - IP: 0.0.0.0
00:02:35.118 -   - MAC: CC:DB:A7:15:8F:6C
00:02:35.129 -   - RSSI: 0 dBm
00:02:35.129 -   - Channel: 0
00:02:35.129 -   - DNS: 0.0.0.0
00:02:35.129 -   - DNS: 0.0.0.0
00:02:35.140 -   - SSID:
00:03:59.407 - > id 
00:03:59.407 - ID: 15a7dbcc
00:04:19.505 - > reboot 
00:04:19.506 - INFO: Rebooting...
```

## Gestion du temps

La classe ```Timer``` permet de gérer un timer qui appelle une procedure tous les ```interval``` millisecondes.

Afin de pouvoir effectuer cette action, il faut créer un objet de la classe ```Timer``` et appeler la méthode ```tick()``` dans la boucle principale du programme.

```cpp
Program::Program()
    : m_demoTimer(nullptr) {
  Serial.begin(SERIAL_SPEED);
  Logger.begin(&Serial);

  this->m_demoTimer =
      new Timer(10_secondes, []() { 
        Logger.println(F("Hello, world!")); 
      });
}

void Program::loop() {
  this->m_demoTimer->tick();
}
```

## Autres classes utiles

La classe ```Device```contient quelques méthodes utiles afin de déboguer vos montages en recherchant les périphériques I2C, en affichant ce qui est détecté sur l'interface WiFi, etc.

La classe ```SimpleCollection``` permet de gérer une collection de données avec un minimum de code et de fonctionnalités. Cette classe est utile si vous avez besoin d'une collection sur Arduino Uno qui ne permet pas d'utiliser la bibliotèque standard de C++.
