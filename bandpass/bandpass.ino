// Arduino Nano Every Timer/Counter A example for band-pass
// =========================================================
// There is one type A timer/counter (TCA0) and it has three
// compare channels (CMP0, CMP1, CMP2).
//
// The clock prescaler (bits 3:1 of CTRLA register) is set to
// 64 by default and changing it breaks delay() and
// millis() (and maybe other things, not checked):
// increasing/decreasing it increases/decreases the length
// of "a second" proportionally. It also changes the PWM
// frequency of pins 5, 9, and 10, although they will still
// do PWM (increasing/decreasing the prescaler value
// decreases/increases the frequency proportionally).
//
// The period value (PER register) is set to 255 by default.
// Changing it affects the duty cycle of PWM pins (i.e. the
// range 0-255 in analogWrite no longer corresponds to a
// 0-100% duty cycle).
//
// PWM pin 5 uses compare channel 2 (CMP2), pin 9 channel
// 0 (CMP0), and pin 10 channel 1 (CMP1).
//
// If you don't mind losing PWM capability (or at least
// changing the frequency and messing up the duty cycle)
// on pins 5, 9, or 10, you can set up these channels for
// your own use.
//
// If you don't mind messing up delay() and millis(), you
// can change the prescaler value to suit your needs. In
// principle, since the prescaler affects millis() and
// delay() in an inversely proportional manner, this could
// be compensated for in your sketch, but this is getting
// messy.
//
// If the prescaler is not changed, the lowest interrupt
// frequency obtainable (by setting PER and CMPn to 65535)
// is about 3.8 Hz.
//
// The interrupt frequency (Hz) given a prescaler value
// and PER value is:
// f = 16000000 / (PER + 1) / prescaler
//
// The PER value for a required frequency f is:
// PER = (16000000 / prescaler / f) - 1
//
// The prescaler can take a setting of 1, 2, 4, 8,
// 16, 64, 256, or 1024. See the ATmega 4809 datasheet
// for the corresponding bit patterns in CTRLA.
//
// http://ww1.microchip.com/downloads/en/DeviceDoc/megaAVR-0-series-Family-Data-Sheet-40002015C.pdf
//
// The program below demonstrates TCA0 interrupts on
// compare channel 1, with and without changing the
// prescaler (change the value of CHANGE_PRESCALER
// from 0 to 1).
//
// PER is the TOP value for the counter. When it
// reaches this value it is reset back to 0. The
// CMP1 value is set to the same value, so that an
// interrupt is generated at the same time that the
// timer is reset back to 0. If you use more than
// one compare channels at the same time, all CMPn
// registers must have a value smaller or equal to PER or
// else they will not generate an interrupt. The
// smallest obtainable frequency is governed by the
// value of PER.
//
// With CHANGE_PRESCALER left at 0, the prescale
// factor is left at its default value of 64, and the
// value of PER is set to the maximum (65535). The
// interrupts fire approx 3.8 times per second while
// the main program prints text to the terminal
// exactly once per second using millis().
//
// When CHANGE_PRESCALER is changed to 1, the prescaler
// factor is changed to 256. The value of PER is calculated
// so that the interrupts will fire exactly once per
// second. The main program still uses millis() to
// print text to the terminal once every 1000 milliseconds
// but now a "second" takes four seconds. This could be
// compensated for by waiting for only 250 milliseconds.
//
// Change CMP1 to CMP0 or CMP2 as required. Change indicated
// bit values too.

#define anaPin 0
#define Nsamples 480

unsigned int ledPin = 2;
unsigned int anaIn = 0;
unsigned int d = 0;
unsigned int dataArray[Nsamples];
bool ledArray[Nsamples];

void setup()
{

  // Sampling parameters
  unsigned int ledp = 6; // Period of LED 1 oscillation in sampling cycles
  unsigned int per_value;
  //    per_value = 499;    // Corresponds to 0.500KHz sampling
  //    per_value = 399;    // Corresponds to 0.625Khz sampling
  per_value = 249; // Corresponds to 1.000Khz sampling
                   //    per_value = 199;    // Corresponds to 1.250KHz sampling
                   //    per_value = 124;     // Corresponds to 2.000KHz sampling
                   //    per_value = 99;    // Corresp onds to 2.500KHz sampling
                   //    per_value = 49;    // Corresponds to 5.000KHz sampling

  // Set read and write pins and settings
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(anaPin, INPUT);

  // Assign array values for LED signals
  bool onoff = 0;

  ledp >>= 1; // 50% duty cycle

  for (int i = 2; i < Nsamples + 2; i++)
  {
    ledArray[i - 2] = onoff;
    if (i % ledp == 0)
    {
      onoff = onoff ^ 1;
    }
  }

  // Interrupt settings
  cli();
  TCA0.SINGLE.CTRLA = B00001011; // Clock prescale value
  TCA0.SINGLE.PER = per_value;   // Interrupt period
  TCA0.SINGLE.CMP1 = per_value;  // Interrupt compare point
  TCA0.SINGLE.INTCTRL |= bit(5); // Enable channel 1 compare match interrupt.
  // Use bit(4) for CMP0, bit(5) CMP1, bit(6) CMP2
  sei();
}

void loop()
{
  digitalWrite(2, 0);
  digitalWrite(3, 0);

  // Every 2s, send the array to a laptop
  delay(2000);

  if (d == Nsamples)
  {

    cli();
    String outStr;
    outStr += String(ledPin) + ' ';
    for (int i = 0; i < d; i++)
    {
      outStr += String(dataArray[i]) + ' ';
    }
    Serial.println(outStr);
    d = 0;
    sei();

    if (ledPin == 2)
    {
      ledPin = 3;
    }
    else
    {
      ledPin = 2;
    }
  }
}

ISR(TCA0_CMP1_vect)
{

  cli();

  // Clears the interrupt flag. Rather confusingly, this is done by setting a bit in the register to 1.
  TCA0.SINGLE.INTFLAGS |= bit(5);

  // Read photodiode and write LEDs
  anaIn = analogRead(anaPin);
  digitalWrite(ledPin, ledArray[d]);

  if (d < Nsamples)
  {
    dataArray[d] = anaIn;
    d++;
  }
  else
  {
    digitalWrite(2, 0);
    digitalWrite(3, 0);
  }

  sei();
}