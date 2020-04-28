#define LED645 3
#define LED660 6
#define inPin 0

void read_multiple(float &bright_mean, float &bright_var, int &repeats);

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
    int repeats = 10;

    // Process variables
    String outspace = " ";

    float bright_mean, bright_var;

    bool LED645status=false;
    bool LED660status=false;

    // 645nm LED
    LED645status = true;
    digitalWrite(LED645, LED645status);
    delay(delayTime);

    read_multiple(bright_mean, bright_var, repeats);
    Serial.println(LED645status + outspace + LED660status +
        outspace + bright_mean + outspace + bright_var);

    // Off
    LED645status = false;
    digitalWrite(LED645, LED645status);    
    delay(delayTime);

    read_multiple(bright_mean, bright_var, repeats);
    Serial.println(LED645status + outspace + LED660status +
                   outspace + bright_mean + outspace + bright_var);

    // 660nm LED
    LED660status = true;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    read_multiple(bright_mean, bright_var, repeats);
    Serial.println(LED645status + outspace + LED660status +
                   outspace + bright_mean + outspace + bright_var);

    // Off
    LED660status = false;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    read_multiple(bright_mean, bright_var, repeats);
    Serial.println(LED645status + outspace + LED660status +
                   outspace + bright_mean + outspace + bright_var);
}

void read_multiple(float &bright_mean, float &bright_var, int &repeats)
{
    float brightout;

    bright_mean = 0;
    bright_var = 0;
    for (int i = 0; i < repeats; i++)
    {
        brightout = analogRead(inPin);
        // Serial.println(brightout);
        bright_mean += brightout;
        bright_var += brightout * brightout;
    }
    // Serial.println(bright_var);
    bright_mean /= repeats;
    bright_var = bright_var / repeats - bright_mean * bright_mean;
}
