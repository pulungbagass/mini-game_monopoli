/* ======================================================
   SYNC_RES HANDLER (State Recovery pasca reconnect)
   ------------------------------------------------------
   Dipanggil begitu balasan sync_req dari ESP32 diterima.
   Tujuannya: kalau pemain sempat disconnect 1-2 detik saat
   lelang sedang berjalan, modal lelang WAJIB muncul lagi
   lengkap dengan bid tertinggi & tombol Bid -- tanpa pemain
   perlu melakukan apapun.
====================================================== */

function handleSyncRes(data) {
  console.log("SYNC_RES diterima:", data);

  if (data.current_state === "AUCTION_ACTIVE") {
    // Isi state ringkas dulu (kalau belum ada), supaya modal
    // bisa langsung tampil TANPA menunggu event "auction_state"
    // (snapshot detail: nama aset, color group, history bid)
    // yang menyusul lewat sendAuctionSnapshot() di backend.
    // handleAuctionState() nanti akan MELENGKAPI object ini,
    // bukan menggantinya dari nol -- jadi tidak ada "kedipan".
    if (!window.appState.auction) {
      window.appState.auction = {
        property: { assetId: data.target_property },
        highestBid: data.highest_bid,
        highestBidRole: data.highest_bidder,
        history: [],
      };
    }

    switchToAuctionBiddingMode();
    showAuctionOverlay();
    renderAuctionModal();

    if (data.remainingMs) {
      startAuctionCountdown(data.remainingMs);
    }

    return;
  }

  // current_state === "IDLE" -> tidak ada lelang aktif.
  // Kalau ternyata overlay lelang masih kebuka di layar client
  // (mis. karena race condition saat lelang berakhir tepat pas
  // disconnect), tutup supaya tidak nyangkut selamanya.
  if (window.appState.auction) {
    window.appState.auction = null;
    hideAuctionOverlay();
  }
}
