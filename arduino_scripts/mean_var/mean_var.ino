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

    bool LED645status[4] = {true, false, false, false};
    bool LED660status[4] = {false, false, true, false};

    for (int i=0; i<4; i++) {
        digitalWrite(LED645, LED645status[i]);
        digitalWrite(LED660, LED660status[i]);
        delay(delayTime);

        read_multiple(bright_mean, bright_var, repeats);
        Serial.println(LED645status[i] + outspace + LED660status[i] +
            outspace + bright_mean + outspace + bright_var);
    }
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
