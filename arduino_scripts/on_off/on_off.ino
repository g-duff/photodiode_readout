#define LED645 3
#define LED660 6
#define inPin 0

void setup()
{
    // put your setup code here, to run once:
    pinMode(LED645, OUTPUT);
    pinMode(LED660, OUTPUT);
    pinMode(inPin, INPUT);
    Serial.begin(9600);
}

void loop()
{
    // Control variables
    int delayTime = 250;
    int repeats = 3;

    // Process variables
    int brightout, i;

    String outspace = " ";

    bool LED645status = false;
    bool LED660status = false;

    // 645nm LED
    LED645status = true;
    digitalWrite(LED645, LED645status);
    delay(delayTime);
    
    for (i=0; i<repeats; i++) {
        brightout = analogRead(inPin);
        Serial.println(LED645status + outspace + LED660status + outspace + brightout);
    }

    // Off
    LED645status = false;
    digitalWrite(LED645, LED645status);
    delay(delayTime);

    for (i=0; i<repeats; i++) {
        brightout = analogRead(inPin);
        Serial.println(LED645status + outspace + LED660status + outspace + brightout);
    }

    // 660nm LED
    LED660status = true;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    for (i=0; i<repeats; i++) {
        brightout = analogRead(inPin);
        Serial.println(LED645status + outspace + LED660status + outspace + brightout);
    }

    // Off
    LED660status = false;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    for (i=0; i<repeats; i++) {
        brightout = analogRead(inPin);
        Serial.println(LED645status + outspace + LED660status + outspace + brightout);
    }
}
