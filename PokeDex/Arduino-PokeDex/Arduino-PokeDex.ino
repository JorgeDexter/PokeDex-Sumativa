#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM




#define LED_RED_PIN 21
#define LED_GREEN_PIN 22
#define LED_BLUE_PIN 23

// Conexión a red WiFi
const char* WIFI_SSID = "a";
const char* WIFI_PASSWORD = "jorgeluis";

//Recursos de Firebase
const char* API_KEY = "AIzaSyDHMVtprNjgOYMWzHpSDrxQPihTk5EysB0";
const char* FIREBASE_PROJECT_ID = "sumativa-pokedex";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "jorgecalderon20062411@gmail.com";
const char* USER_PASSWORD = "JORGELUIS";

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Conectando a la red WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado a la red WiFi!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupFirebase();
  
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
}

void controlLED(String pokemonType) {
  if (pokemonType.equals("electric")) {
    // Enciende el LED rojo y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("bug")) {
    // Enciende el LED verde y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("water")) {
    // Enciende el LED azul y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("fire")) {
    // Enciende el LED amarillo y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("ice")) {
    // Enciende el LED blanco y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("psychic")) {
    // Enciende el LED morado y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("fighting")) {
    // Enciende el LED naranja y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("poison")) {
    // Enciende el LED morado y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("rock")) {
    // Enciende el LED marrón y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("flying")) {
    // Enciende el LED celeste y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("bicho")) {
    // Enciende el LED verde y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("ghost")) {
    // Enciende el LED blanco y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("dragon")) {
    // Enciende el LED azul y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("siniestro")) {
    // Enciende el LED negro y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("steel")) {
    // Enciende el LED plateado y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else if (pokemonType.equals("ground")) {
    // Enciende el LED marrón y apaga los otros colores
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  } else if (pokemonType.equals("normal")) {
    // Enciende el LED blanco y apaga los otros colores
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_BLUE_PIN, HIGH);
  } else {
    // Si no coincide con ningún tipo conocido, apaga todos los LED
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_BLUE_PIN, LOW);
  }
}

void loop() {
  String path = "Pokemons/Pokemon";
  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      JsonObject pokemon = doc["fields"];
      const char* pokemonType = pokemon["tipo"]["stringValue"];

      Serial.print("Tipo de Pokémon obtenido: ");
      Serial.println(pokemonType);

      controlLED(pokemonType);
    } else {
      Serial.println("Error al obtener el tipo de Pokémon");
    }
  } else {
    Serial.println("Error al obtener el documento de Firebase");
  }
  
  delay(5000); // Espera 5 segundos antes de volver a consultar Firebase
}