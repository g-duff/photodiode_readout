#define delayTime 500
#define LED645 3
#define LED660 6
#define inPin 0
int repeats = 3;

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
    String outspace = " ";

    float brightout;
    float brightout_sum = 0;
    float brightout_sq = 0;
    float brightout_mean;
    float brightout_var;

    bool LED645status;
    bool LED660status;
    int i;

    // 645nm LED
    LED645status = true;
    digitalWrite(LED645, LED645status);
    delay(delayTime);
    
    for (i=0; i<repeats; i++)
    {
        Serial.println(i);
        brightout = analogRead(inPin);
        Serial.println(brightout);
        brightout_sum += brightout;
        brightout_sq += brightout*brightout;
    }
    brightout_mean = brightout_sum/repeats;
    brightout_var = brightout_sq/repeats - brightout_mean*brightout_mean;
    Serial.println(LED645status + outspace + LED660status +
        outspace + brightout_mean + outspace + brightout_var);
    brightout_sum = 0;
    brightout_sq = 0;

    // Off
    LED645status = false;
    digitalWrite(LED645, LED645status);    
    delay(delayTime);

    for (i = 0; i < repeats; i++)
    {
        brightout = analogRead(inPin);
        brightout_sum += brightout;
        brightout_sq += brightout * brightout;
    }
    brightout_mean = brightout_sum / repeats;
    brightout_var = brightout_sq / repeats - brightout_mean * brightout_mean;
    Serial.println(LED645status + outspace + LED660status +
                   outspace + brightout_mean + outspace + brightout_var);
    brightout_sum = 0;
    brightout_sq = 0;

    // 645nm LED
    LED660status = true;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    for (i = 0; i < repeats; i++)
    {
        brightout = analogRead(inPin);
        brightout_sum += brightout;
        brightout_sq += brightout * brightout;
    }
    brightout_mean = brightout_sum / repeats;
    brightout_var = brightout_sq / repeats - brightout_mean * brightout_mean;
    Serial.println(LED645status + outspace + LED660status +
                   outspace + brightout_mean + outspace + brightout_var);
    brightout_sum = 0;
    brightout_sq = 0;

    // Off
    LED660status = false;
    digitalWrite(LED660, LED660status);
    delay(delayTime);

    for (i = 0; i < repeats; i++)
    {
        brightout = analogRead(inPin);
        brightout_sum += brightout;
        brightout_sq += brightout * brightout;
    }
    brightout_mean = brightout_sum / repeats;
    brightout_var = brightout_sq / repeats - brightout_mean * brightout_mean;
    Serial.println(LED645status + outspace + LED660status +
                   outspace + brightout_mean + outspace + brightout_var);
    brightout_sum = 0;
    brightout_sq = 0;
}
