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

  if (data.hasWinner) {
    const winner =
      typeof getPlayer === "function" ? getPlayer(data.winnerRole) : null;

    renderAuctionResult(
      `🎉 ${winner ? winner.name : data.winnerRole} MENANG`,
      `Memenangkan "${propertyName}" seharga $${data.winningBid}. Tap kartu NFC pemenang ke device Bank untuk finalisasi kepemilikan.`,
    );
  } else {
    renderAuctionResult(
      "LELANG BERAKHIR",
      `Tidak ada penawar untuk "${propertyName}". Properti tetap milik Bank.`,
    );
  }

  setTimeout(() => {
    window.appState.auction = null;
    hideAuctionOverlay();
  }, 4000);
}
