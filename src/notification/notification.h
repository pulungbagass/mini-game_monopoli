#pragma once

// ======================================================
// Notification Module
// Monopoly Cyber-Physical Board Game
//
// Mengatur seluruh feedback hardware:
// - Passive Buzzer
// - LED Indicator
//
// Semua module cukup memanggil fungsi notifyXXX()
// tanpa mengakses buzzer / LED secara langsung.
// ======================================================

// Inisialisasi hardware notification
void notificationBegin();

// ======================================================
// Notification Event
// ======================================================

// NFC Card berhasil terbaca
void notifyCardScan();

// Claim Role berhasil
void notifyClaimSuccess();

// Claim Role gagal
void notifyClaimFailed();

// ======================================================
// Transaction
// ======================================================

void notifyTransactionSuccess();

void notifyTransactionFailed();

void notifyMoneyReceived();

void notifyMoneyPaid();