#pragma once

void updateAuction();

// Watchdog 30 detik: kalau pemenang lelang tidak tap kartu
// NFC untuk klaim properti, batalkan otomatis + refund uang.
void updateAuctionClaim();
