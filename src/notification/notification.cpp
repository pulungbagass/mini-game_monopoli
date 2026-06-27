#include "notification.h"

#include <Arduino.h>

// ======================================================
// Hardware Configuration
// ======================================================

#define BUZZER_PIN     26
#define LED_PIN        25
#define BUZZER_CHANNEL 0

// ======================================================
// Melody Structure
// ======================================================

struct Note
{
    uint16_t frequency;
    uint16_t duration;
    bool led;
};

#define NOTE_COUNT(x) (sizeof(x) / sizeof(Note))

// ======================================================
// Notification Melody
// ======================================================

// Card Scan
static const Note CARD_SCAN[] =
{
    {900, 120, true}
};

// Claim Success
static const Note CLAIM_SUCCESS[] =
{
    {700, 80, true},
    {0,   40, false},
    {1100,150, true}
};

// Claim Failed
static const Note CLAIM_FAILED[] =
{
    {1100,100,true},
    {0,   40,false},
    {500,220,true}
};

// Transfer Success
static const Note TRANSACTION_SUCCESS[] =
{
    {800, 80, true},
    {1000, 80, true},
    {1300, 150, true}
};

// Transfer Failed
static const Note TRANSACTION_FAILED[] =
{
    {1200, 120, true},
    {600, 250, true}
};

// Money Received
static const Note MONEY_RECEIVED[] =
{
    {1200, 70, true},
    {1500, 120, true}
};

// Money Paid
static const Note MONEY_PAID[] =
{
    {900, 70, true},
    {600, 120, true}
};

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

static void playNote(const Note& note)
{
    if (note.led)
        ledOn();
    else
        ledOff();

    if (note.frequency > 0)
        ledcWriteTone(BUZZER_CHANNEL, note.frequency);
    else
        ledcWriteTone(BUZZER_CHANNEL, 0);

    delay(note.duration);

    ledcWriteTone(BUZZER_CHANNEL, 0);
    ledOff();
}

static void playMelody(const Note melody[], size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        playNote(melody[i]);
    }
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
// Notification Event
// ======================================================

void notifyCardScan()
{
    playMelody(
        CARD_SCAN,
        NOTE_COUNT(CARD_SCAN)
    );
}

void notifyClaimSuccess()
{
    playMelody(
        CLAIM_SUCCESS,
        NOTE_COUNT(CLAIM_SUCCESS)
    );

    blink(2, 80);
}

void notifyClaimFailed()
{
    playMelody(
        CLAIM_FAILED,
        NOTE_COUNT(CLAIM_FAILED)
    );

    blink(3, 60);
}

void notifyTransactionSuccess()
{
    playMelody(
        TRANSACTION_SUCCESS,
        NOTE_COUNT(TRANSACTION_SUCCESS)
    );

    blink(2, 70);
}

void notifyTransactionFailed()
{
    playMelody(
        TRANSACTION_FAILED,
        NOTE_COUNT(TRANSACTION_FAILED)
    );

    blink(3, 50);
}

void notifyMoneyReceived()
{
    playMelody(
        MONEY_RECEIVED,
        NOTE_COUNT(MONEY_RECEIVED)
    );
}

void notifyMoneyPaid()
{
    playMelody(
        MONEY_PAID,
        NOTE_COUNT(MONEY_PAID)
    );
}