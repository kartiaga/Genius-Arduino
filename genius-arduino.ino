#define NOTE_RED 294
#define NOTE_GREEN 392
#define NOTE_BLUE 440
#define NOTE_YELLOW 880

int tons[] = { NOTE_RED, NOTE_GREEN, NOTE_BLUE, NOTE_YELLOW };
int leds[] = { 2, 4, 6, 8 };
int botoes[] = { 3, 5, 7, 9 };
int audio = 12;
int sequencia[100];
int rodada = 0;
bool perdeu = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(botoes[i], INPUT_PULLUP);
  }
  pinMode(audio, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  if (perdeu) {
    piscarTodos(3);
    rodada = 0;
    perdeu = false;
    delay(1000);
  }

  sequencia[rodada] = random(4);
  reproduzir();

  for (int i = 0; i <= rodada; i++) {
    if (esperarBotao() != sequencia[i]) {
      perdeu = true;
      return;
    }
  }

  rodada++;
  delay(500);
}

void reproduzir() {
  for (int i = 0; i <= rodada; i++) {
    int n = sequencia[i];
    digitalWrite(leds[n], HIGH);
    tone(audio, tons[n], 300);
    delay(300);
    digitalWrite(leds[n], LOW);
    delay(100);
  }
}

int esperarBotao() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(botoes[i]) == LOW) {
        digitalWrite(leds[i], HIGH);
        tone(audio, tons[i], 300);
        delay(300);
        digitalWrite(leds[i], LOW);
        while (digitalRead(botoes[i]) == LOW); // Aguarda soltar
        delay(100);
        return i;
      }
    }
  }
}

void piscarTodos(int vezes) {
  for (int i = 0; i < vezes; i++) {
    for (int j = 0; j < 4; j++) digitalWrite(leds[j], HIGH);
    tone(audio, 100, 300);
    delay(300);
    for (int j = 0; j < 4; j++) digitalWrite(leds[j], LOW);
    delay(300);
  }
}
