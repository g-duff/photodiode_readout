// With help from this forum post:
// https : //forum.arduino.cc/index.php?topic=668204.0

#define anaPin 0
#define Nsamples 1000

        int anaIn = 0;
int d = 0;
int dataArray[Nsamples];

void setup()
{
  Serial.begin(115200);

  pinMode(anaPin, INPUT);

  unsigned int per_value;

  cli();
  TCA0.SINGLE.CTRLA = B00001011;

  per_value = 499;
  TCA0.SINGLE.PER = per_value;
  TCA0.SINGLE.CMP1 = per_value;
  TCA0.SINGLE.INTCTRL |= bit(5); // Enable channel 1 compare match interrupt.
  // Use bit(4) for CMP0, bit(5) CMP1, bit(6) CMP2
  sei();
}

void loop()
{

  // Every ns, send the array to a laptop
  delay(5000);
  if (d == Nsamples)
  {
    cli();
    String outStr;
    for (int i = 0; i < d; i++)
    {
      outStr += String(dataArray[i]) + ' ';
    }
    Serial.println(outStr);
    sei();
    d = 0;
  }
}

ISR(TCA0_CMP1_vect)
{
  // Take an analogue reading

  cli();

  TCA0.SINGLE.INTFLAGS |= bit(5); // Clears the interrupt flag. Rather confusingly, this is done by setting a bit in the register to 1.
  anaIn = analogRead(anaPin);

  if (d < Nsamples)
  {
    dataArray[d] = anaIn;
    d++;
  }

  sei();
}