/* ======================================================
   AUCTION STATE (client side)
====================================================== */

window.appState.auction = null; // null = tidak ada lelang aktif
let auctionCountdownTimer = null;

function auctionIsActive() {
  return !!window.appState.auction;
}

/* ======================================================
   SEND ACTIONS
====================================================== */

function sendStartAuction(assetId) {
  window.appState.socket.send(
    JSON.stringify({
      type: "start_auction",
      role: "BANK",
      assetId: assetId,
    }),
  );
}

function sendPlaceBid(increment) {
  window.appState.socket.send(
    JSON.stringify({
      type: "place_bid",
      role: window.appState.activeRole,
      increment: increment,
    }),
  );
}

function sendEndAuction() {
  window.appState.socket.send(
    JSON.stringify({
      type: "end_auction",
      role: "BANK",
    }),
  );
}

/* ======================================================
   COUNTDOWN (client-side tick, disinkronkan tiap pesan
   dari server lewat field remainingMs)
====================================================== */

function startAuctionCountdown(remainingMs) {
  stopAuctionCountdown();

  let secondsLeft = Math.ceil(remainingMs / 1000);
  renderAuctionCountdown(secondsLeft);

  auctionCountdownTimer = setInterval(() => {
    secondsLeft -= 1;
    if (secondsLeft < 0) secondsLeft = 0;
    renderAuctionCountdown(secondsLeft);
    if (secondsLeft <= 0) {
      stopAuctionCountdown();
    }
  }, 1000);
}

function syncAuctionCountdown(remainingMs) {
  const secondsLeft = Math.ceil(remainingMs / 1000);
  startAuctionCountdown(remainingMs > 0 ? remainingMs : 0);
}

function stopAuctionCountdown() {
  if (auctionCountdownTimer) {
    clearInterval(auctionCountdownTimer);
    auctionCountdownTimer = null;
  }
}

/* ======================================================
   HANDLERS (dipanggil dari socket_ui.js)
====================================================== */

function handleAuctionStarted(data) {
  window.appState.auction = {
    property: data.property,
    highestBid: data.highestBid,
    highestBidRole: data.highestBidRole,
    history: [],
  };

  switchToAuctionBiddingMode();
  showAuctionOverlay();
  renderAuctionModal();
  startAuctionCountdown(data.durationMs);
}

function handleAuctionState(data) {
  // snapshot saat client baru connect di tengah lelang aktif
  window.appState.auction = {
    property: data.property,
    highestBid: data.highestBid,
    highestBidRole: data.highestBidRole,
    history: (data.history || []).slice().reverse(),
  };

  switchToAuctionBiddingMode();
  showAuctionOverlay();
  renderAuctionModal();
  startAuctionCountdown(data.remainingMs);
}

function handleAuctionBid(data) {
  if (!window.appState.auction) return;

  window.appState.auction.highestBid = data.highestBid;
  window.appState.auction.highestBidRole = data.role;

  window.appState.auction.history.unshift({
    role: data.role,
    amount: data.highestBid,
    delta: data.delta,
  });

  renderAuctionModal();
  syncAuctionCountdown(data.remainingMs);
}

function handleAuctionRejected(data) {
  if (data.role === window.appState.activeRole) {
    showGlobalStatus(
      "SALDO TIDAK CUKUP",
      "Saldo kamu tidak cukup untuk menaikkan taruhan ini.",
      "error",
    );
  }

  // pastikan semua layar tetap sinkron ke highest bid asli
  if (window.appState.auction) {
    window.appState.auction.highestBid = data.highestBid;
    window.appState.auction.highestBidRole = data.highestBidRole;
    renderAuctionModal();
  }
}

function handleAuctionEnded(data) {
  stopAuctionCountdown();

  const propertyName =
    window.appState.auction &&
    window.appState.auction.property &&
    window.appState.auction.property.assetName
      ? window.appState.auction.property.assetName
      : data.assetId;

  if (!data.hasWinner) {
    // tidak ada penawar -> tampilkan sebentar lalu tutup,
    // tidak ada yang perlu tap kartu
    showAuctionClaimPanel({
      icon: "🏦",
      title: "LELANG BERAKHIR",
      message: `Tidak ada penawar untuk "${propertyName}". Properti tetap milik Bank.`,
      showTapHint: false,
    });

    setTimeout(() => {
      window.appState.auction = null;
      hideAuctionOverlay();
    }, 4000);
    return;
  }

  // ADA PEMENANG: overlay TIDAK ditutup otomatis. Modal
  // berpindah ke "claim mode" dan menunggu broadcast
  // auction_claim_pending (dikirim backend begitu sesi
  // transaksi klaim berhasil dibuka) untuk instruksi final.
  window.appState.auctionPendingWinner = data.winnerRole;
  window.appState.auctionPendingAmount = data.winningBid;
  window.appState.auctionPendingProperty = propertyName;
}

/* ======================================================
   CLAIM PENDING - instruksi tap yang jelas & PERSISTEN
   (tidak auto-hilang, baru hilang setelah claim_result
   atau claim_timeout diterima)
====================================================== */

function handleAuctionClaimPending(data) {
  const winner =
    typeof getPlayer === "function" ? getPlayer(data.winnerRole) : null;
  const winnerName = winner ? winner.name : data.winnerRole;
  const isMe = data.winnerRole === window.appState.activeRole;

  showAuctionClaimPanel({
    icon: "🎉",
    title: `${winnerName} MENANG LELANG!`,
    message: `"${data.assetName}" dimenangkan seharga $${data.amount} (sudah dibayar otomatis). Silakan TAP kartu ${winnerName} ke mesin Bank untuk menerima properti.`,
    showTapHint: true,
  });

  startAuctionCountdown(data.durationMs);

  if (isMe) {
    showGlobalStatus(
      "SELAMAT!",
      `Kamu menang lelang "${data.assetName}". Tap kartu kamu ke mesin Bank sekarang untuk menerima properti.`,
      "success",
    );
  }
}

/* ======================================================
   CLAIM RESULT (tap sudah diproses)
====================================================== */

function handleAuctionClaimResult(data) {
  stopAuctionCountdown();

  const winner =
    typeof getPlayer === "function" ? getPlayer(data.winnerRole) : null;
  const winnerName = winner ? winner.name : data.winnerRole;

  if (data.success) {
    showAuctionClaimPanel({
      icon: "✅",
      title: "PROPERTI BERPINDAH TANGAN",
      message: `${winnerName} resmi memiliki "${data.assetName}".`,
      showTapHint: false,
    });
  } else {
    showAuctionClaimPanel({
      icon: "⚠️",
      title: "KLAIM GAGAL",
      message: `Serah terima "${data.assetName}" gagal diproses. Uang $${data.amount} sudah dikembalikan ke ${winnerName}.`,
      showTapHint: false,
    });
  }

  clearAuctionPendingState();

  setTimeout(() => {
    window.appState.auction = null;
    hideAuctionOverlay();
  }, 4000);
}

/* ======================================================
   CLAIM TIMEOUT (watchdog 30 detik, tidak tap sama sekali)
====================================================== */

function handleAuctionClaimTimeout(data) {
  stopAuctionCountdown();

  const winner =
    typeof getPlayer === "function" ? getPlayer(data.winnerRole) : null;
  const winnerName = winner ? winner.name : data.winnerRole;

  showAuctionClaimPanel({
    icon: "⏱️",
    title: "WAKTU HABIS",
    message: `${winnerName} tidak tap kartu dalam 30 detik. Lelang dibatalkan, uang $${data.amount} sudah dikembalikan.`,
    showTapHint: false,
  });

  clearAuctionPendingState();

  setTimeout(() => {
    window.appState.auction = null;
    hideAuctionOverlay();
  }, 4000);
}

function clearAuctionPendingState() {
  window.appState.auctionPendingWinner = null;
  window.appState.auctionPendingAmount = null;
  window.appState.auctionPendingProperty = null;
}
