#define delayTime 250
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
    // Declare variables
    int brightout;
    String outspace = " ";
    bool LED645status;
    bool LED660status;

    // 645nm LED
    LED645status = true;
    digitalWrite(LED645, LED645status);
    delay(delayTime);
    
    brightout = analogRead(inPin);
    Serial.println(LED645status + outspace + LED660status + outspace + brightout);

    LED645status = false;
    digitalWrite(LED645, LED645status);
    delay(delayTime);

    // Off
    brightout = analogRead(inPin);
    Serial.println(LED645status + outspace + LED660status + outspace + brightout);

    // 660nm LED
    LED660status = true;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    brightout = analogRead(inPin);
    Serial.println(LED645status + outspace + LED660status + outspace + brightout);

    LED660status = false;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    // Off
    brightout = analogRead(inPin);
    Serial.println(LED645status + outspace + LED660status + outspace + brightout);
}
