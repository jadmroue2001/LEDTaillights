#include <FastLED.h>
#define LED_PIN 4
// const int NUM_LEDS = 256; // 1 long
const int NUM_LEDS = 320; // 1 long 1 small
CRGB leds[NUM_LEDS];

// PINS
// 5,14,12,13
const int INPUTBrake = 5;
const int INPUTSignal = 14;
const int INPUTReverse = 12;
const int INPUTNight = 13;
// const int extra = 7;
// const int ledOne =  13;

const int sensorPin = A0;

// variables will change:
int Brakes = 0; // variable for reading the pushbutton status
int Signal = 0;
int Reverse = 0;
int Night = 0; // this is for day time or night time car lights

int anolog = 0;

void setup()
{
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  // initialize the pushbutton pin as an input:
  pinMode(INPUTBrake, INPUT);
  pinMode(INPUTSignal, INPUT);
  pinMode(INPUTNight, INPUT);
  pinMode(INPUTNight, INPUT);
}

void loop()
{

  //  read the state of the pushbutton value:

  Brakes = digitalRead(INPUTBrake);
  Signal = digitalRead(INPUTSignal);
  Reverse = digitalRead(INPUTReverse);
  Night = digitalRead(INPUTNight);

  char IBrakes = Brakes == HIGH;
  char ISignal = Signal == HIGH;
  char IReverse = Reverse == HIGH;
  char INight = Night == HIGH;

  /// NIGHTTIME SETTINGS
  if (INight)
  {
     if (IBrakes && IReverse)
    {
      reversebrake1();
    }
    else if(IBrakes)
    {
      BrightRed();
    }
    else if (ISignal)
    {
      turn1();
    }
    else if (IReverse)
    {
      reverse1(100, 100, 100);
    }
    else
    {
      DimRed();
    }
  }

  // DAY TIME SETTINGS
  if (!INight)
  {
    if (IBrakes && IReverse)
    {
      reversebrake1();
    }
    else if(IBrakes)
    {
      BrightRed();
    }
    else if (ISignal)
    {
      turn1();
    }
    else if (IReverse)
    {
      reverse1(100, 100, 100);
    }
    else
    {
      turnOffAll();
    }
  }
}

// BEGIN SOLID COLOURS
// 10,10,90 nice colour
// SOLID COLOURS
void BrightRed()
{
  turnOnAll(255, 0, 0);
}

void DimRed()
{
  turnOnAll(5, 0, 0);
}

void green()
{
  turnOnAll(0, 10, 0);
}

void blue()
{
  turnOnAll(0, 0, 255);
}

void white()
{
  turnOnAll(100, 100, 100);
}

// turns on all leds
int turnOnAll(int r, int g, int b)
{
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}

// turns off all leds
int turnOffAll()
{
  for (size_t i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  return 0;
}
// END

// BEGIN ANIMATIONS

// TURN SIGNALS
void turn1()
{
  int x, y;
  for (size_t x = 0; x < 40; x = x + 5)
  {
    y = x + 5;
    turnOffAll();
    multiCol(x, y, 200, 200, 0);
    delay(2);
  }
}

// Reverse
void reverse1(int r, int g, int b)
{
  populateRange(0, 48, 0, 0, 0);
  populateRange(48, 88, r, g, b);
  populateRange(88, 320, 0, 0, 0);
}

void reversebrake1()
{
  populateRange(0, 48, 100, 0, 0);
  populateRange(48, 88, 100, 100, 100);
  populateRange(88, 320, 100, 0, 0);
}

// END

// BEGIN COLOMNS AND ROW SETUPS

// COLUMNS
int calcColRange(int colNum, int r, int g, int b)
{
  int start, end;
  end = colNum * 8;
  start = end - 8;

  populateRange(start, end, r, g, b);
  return 0;
}

int populateRange(int startLed, int endLed, int r, int g, int b)
{
  for (size_t i = startLed; i < endLed; i++)
  {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}

// Muliple cols at once
int multiCol(int startCol, int endCol, int r, int g, int b)
{
  for (size_t i = startCol; i <= endCol; i++)
  {
    calcColRange(i, r, g, b);
    // leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}

int multiColR(int startCol, int endCol, int r, int g, int b)
{
  for (size_t i = endCol; i >= startCol; i--)
  {
    calcColRange(i, r, g, b);
    // leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}

/////////////////////////

// ROWS
int multiRow(int startRow, int endRow, int r, int g, int b)
{
  for (size_t i = startRow; i <= endRow; i++)
  {
    row(i, r, g, b);
    // leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}

int row(int rowNum, int r, int g, int b)
{
  for (size_t i = rowNum; i < 320; i = i + 16)
  {
    leds[i] = CRGB(r, g, b);
    rowA(rowNum, r, g, b);
  }
  FastLED.show();
  return 0;
}

int rowA(int rowNum, int r, int g, int b)
{
  int calc1, calc2, newRow;
  calc1 = 15 - rowNum;
  calc2 = calc1 - rowNum;
  newRow = rowNum + calc2;

  for (size_t i = newRow; i < 320; i = i + 16)
  {
    leds[i] = CRGB(r, g, b);
  }
  FastLED.show();
  return 0;
}
// END


/*
NOTES

Power:
Arduino Constant: 3.3-5v
All "inputs": 
< 1.5 = off
1.5 - 3.3 = on
> 3.3 = explosion

*/