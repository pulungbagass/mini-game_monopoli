#include "notification.h"

#include <Arduino.h>

// ======================================================
// Hardware Configuration
// ======================================================

#define BUZZER_PIN     26
#define LED_PIN        25
#define BUZZER_CHANNEL 0

// ======================================================
// Private Helper
// ======================================================

static void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
}

static void ledOff()
{
    digitalWrite(LED_PIN, LOW);
}

static void playTone(int frequency, int duration)
{
    ledOn();

    ledcWriteTone(BUZZER_CHANNEL, frequency);
    delay(duration);

    ledcWriteTone(BUZZER_CHANNEL, 0);

    ledOff();
}

static void blink(int times, int duration)
{
    for (int i = 0; i < times; i++)
    {
        ledOn();
        delay(duration);

        ledOff();
        delay(duration);
    }
}

// ======================================================
// Public
// ======================================================

void notificationBegin()
{
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    ledcSetup(BUZZER_CHANNEL, 2000, 8);
    ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);

    ledcWriteTone(BUZZER_CHANNEL, 0);
}

// ======================================================
// Card Scan
// ======================================================

void notifyCardScan()
{
    playTone(900, 120);
}

// ======================================================
// Claim Success
// ======================================================

void notifyClaimSuccess()
{
    playTone(700, 80);
    delay(40);
    playTone(1100, 150);

    delay(40);

    blink(2, 80);
}

// ======================================================
// Claim Failed
// ======================================================

void notifyClaimFailed()
{
    playTone(1100, 100);
    delay(40);
    playTone(500, 220);

    blink(3, 60);
}