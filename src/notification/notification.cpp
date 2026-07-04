#include "notification.h"

#include <Arduino.h>

// ======================================================
// Hardware Configuration
// ======================================================

#define BUZZER_PIN     26
#define LED_PIN        25
#define BUZZER_CHANNEL 0

// ======================================================
// Pulse Structure
// ======================================================

struct Pulse
{
    bool on;
    uint16_t duration;
    bool led;
};

#define PULSE_COUNT(x) (sizeof(x) / sizeof(Pulse))

// ======================================================
// Notification Pattern
// ======================================================

// Card Scan
static const Pulse CARD_SCAN[] =
{
    {true, 150, true},
    {false,120,false}
};

// Claim Success
static const Pulse CLAIM_SUCCESS[] =
{
    {true,120,true},
    {false,120,false},
    {true,120,true},
    {false,120,false},
    {true,500,true}
};

// Claim Failed
static const Pulse CLAIM_FAILED[] =
{
    {true,600,true},
    {false,150,false},
    {true,600,true}
};

// Transaction Success
static const Pulse TRANSACTION_SUCCESS[] =
{
    {true,100,true},
    {false,80,false},
    {true,100,true},
    {false,80,false},
    {true,100,true},
    {false,80,false},
    {true,800,true}
};

// Transaction Failed
static const Pulse TRANSACTION_FAILED[] =
{
    {true,1000,true},
    {false,250,false},
    {true,400,true},
    {false,150,false},
    {true,1000,true}
};

// Money Received
static const Pulse MONEY_RECEIVED[] =
{
    {true,120,true},
    {false,80,false},
    {true,120,true},
    {false,80,false},
    {true,120,true}
};

// Money Paid
static const Pulse MONEY_PAID[] =
{
    {true,500,true},
    {false,120,false},
    {true,180,true}
};

// ======================================================
// Private Helper
// ======================================================

static void buzzerOn()
{
    ledcWriteTone(BUZZER_CHANNEL, 2000);
}

static void buzzerOff()
{
    ledcWriteTone(BUZZER_CHANNEL, 0);
}

static void ledOn()
{
    digitalWrite(LED_PIN, HIGH);
}

static void ledOff()
{
    digitalWrite(LED_PIN, LOW);
}

static void playPulse(const Pulse& pulse)
{
    if (pulse.on)
        buzzerOn();
    else
        buzzerOff();

    if (pulse.led)
        ledOn();
    else
        ledOff();

    delay(pulse.duration);

    buzzerOff();
    ledOff();
}

static void playPattern(
    const Pulse pattern[],
    size_t length
)
{
    for (size_t i = 0; i < length; i++)
    {
        playPulse(pattern[i]);
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

    ledcSetup(
        BUZZER_CHANNEL,
        2000,
        8
    );

    ledcAttachPin(
        BUZZER_PIN,
        BUZZER_CHANNEL
    );

    buzzerOff();
}

// ======================================================
// Notification Event
// ======================================================

void notifyCardScan()
{
    playPattern(
        CARD_SCAN,
        PULSE_COUNT(CARD_SCAN)
    );
}

void notifyClaimSuccess()
{
    playPattern(
        CLAIM_SUCCESS,
        PULSE_COUNT(CLAIM_SUCCESS)
    );

    blink(2,80);
}

void notifyClaimFailed()
{
    playPattern(
        CLAIM_FAILED,
        PULSE_COUNT(CLAIM_FAILED)
    );

    blink(3,70);
}

void notifyTransactionSuccess()
{
    playPattern(
        TRANSACTION_SUCCESS,
        PULSE_COUNT(TRANSACTION_SUCCESS)
    );

    blink(2,100);
}

void notifyTransactionFailed()
{
    playPattern(
        TRANSACTION_FAILED,
        PULSE_COUNT(TRANSACTION_FAILED)
    );

    blink(3,80);
}

void notifyMoneyReceived()
{
    playPattern(
        MONEY_RECEIVED,
        PULSE_COUNT(MONEY_RECEIVED)
    );
}

void notifyMoneyPaid()
{
    playPattern(
        MONEY_PAID,
        PULSE_COUNT(MONEY_PAID)
    );
}