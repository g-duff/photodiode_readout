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
    int repeatTime = 100;
    int repeats = 25;

    // Process variables
    int brightout;

    String outspace = " ";

    bool LED645status[4] = {true, false, false, false};
    bool LED660status[4] = {false, false, true, false};
    
    for (int i=0; i<4; i++) {

        digitalWrite(LED645, LED645status[i]);
        digitalWrite(LED660, LED660status[i]);

        for (int j=0; j<repeats; j++) {
            brightout = analogRead(inPin);
            Serial.println(LED645status[i] + outspace + LED660status[i] + outspace + brightout);
            delay(repeatTime);
        }
    }
}
