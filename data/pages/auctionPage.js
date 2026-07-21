/* ======================================================
   BANK: AUCTION LAUNCHER PAGE
   Daftar properti kosong yang bisa dilelang Bank.
====================================================== */

function renderAuctionPage() {
  setTimeout(initAuctionPage, 0);
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>🔨 AUCTION</h2>
      <p>Pilih properti kosong untuk dilelang ke semua player.</p>

      <div
        id="auctionLauncherStatus"
        style="margin-top:12px;"
      ></div>

      <div
        id="auctionLauncherList"
        class="property-list"
      >
        <p class="property-loading">Loading properties...</p>
      </div>
    </div>
  `;
}
registerPage("auction", renderAuctionPage);

function initAuctionPage() {
  loadPropertyRules().then(() => {
    renderAuctionLauncherList();
  });
}

function renderAuctionLauncherList() {
  const container = document.getElementById("auctionLauncherList");
  if (!container) return;

  const rules = window.appState.propertyRules || [];

  const available = rules.filter((rule) => {
    if (!rule.action || !rule.action.buyable) return false;
    const ownership = window.appState.properties[rule.assets_id];
    return !ownership || !ownership.owned;
  });

  if (auctionIsActive()) {
    container.innerHTML = `<p class="property-loading">Lelang sedang berjalan, lihat modal lelang di layar.</p>`;
    return;
  }

  if (available.length === 0) {
    container.innerHTML = `<p class="property-loading">Tidak ada properti kosong tersisa untuk dilelang.</p>`;
    return;
  }

  container.innerHTML = available
    .map((rule) => {
      const color =
        PROPERTY_COLORS[rule.color_group] ||
        PROPERTY_COLORS[rule.type] ||
        "#cccccc";

      return `
        <div class="property-item property-item-manage">
          <div class="property-item-top">
            <div class="property-color-chip" style="background:${color}"></div>
            <div class="property-info">
              <h4>${rule.asset_name}</h4>
              <p>$${rule.purchase_price}</p>
            </div>
          </div>
          <div class="property-actions">
            <button
              class="property-btn build"
              data-start-auction="${rule.assets_id}"
            >START AUCTION</button>
          </div>
        </div>
      `;
    })
    .join("");
}

document.addEventListener("click", (e) => {
  const btn = e.target.closest("[data-start-auction]");
  if (!btn) return;

  const assetId = btn.dataset.startAuction;
  const rule =
    typeof getPropertyRule === "function" ? getPropertyRule(assetId) : null;
  const label = rule ? rule.asset_name : assetId;

  if (!confirm(`Mulai lelang untuk "${label}"?`)) return;

  sendStartAuction(assetId);
});

/* ======================================================
   GLOBAL AUCTION MODAL (muncul di layar SIAPAPUN, player
   maupun bank, selama lelang aktif)
====================================================== */

const AUCTION_INCREMENTS = [5, 10, 50, 100];

function showAuctionOverlay() {
  const overlay = document.getElementById("auctionOverlay");
  if (overlay) overlay.classList.remove("hidden");
}

function hideAuctionOverlay() {
  const overlay = document.getElementById("auctionOverlay");
  if (overlay) overlay.classList.add("hidden");
}

function renderAuctionCountdown(seconds) {
  const el = document.getElementById("auctionTimer");
  if (!el) return;
  el.textContent = seconds;
  el.classList.toggle("auction-timer-warning", seconds <= 10);
}

function renderAuctionResult(title, message) {
  const highestEl = document.getElementById("auctionHighestRole");
  const bidButtons = document.getElementById("auctionBidButtons");
  const bankControls = document.getElementById("auctionBankControls");

  if (bidButtons) bidButtons.innerHTML = "";
  if (bankControls) bankControls.classList.add("hidden");

  const header = document.querySelector(".auction-modal-header .auction-badge");
  if (header) header.textContent = "🔨 " + title;

  if (highestEl) highestEl.textContent = message;
}

function renderAuctionModal() {
  const auction = window.appState.auction;
  if (!auction) return;

  const header = document.querySelector(".auction-modal-header .auction-badge");
  if (header) header.textContent = "🔨 LELANG";

  /* ------- property card ------- */
  const propertyCard = document.getElementById("auctionPropertyCard");
  if (propertyCard && auction.property) {
    const color =
      PROPERTY_COLORS[auction.property.colorGroup] ||
      PROPERTY_COLORS[auction.property.type] ||
      "#cccccc";

    propertyCard.innerHTML = `
      <div class="property-color-chip" style="background:${color}"></div>
      <div class="property-info">
        <h4>${auction.property.assetName || auction.property.assetId}</h4>
        <p>Harga normal: $${auction.property.purchasePrice || "-"}</p>
      </div>
    `;
  }

  /* ------- highest bid ------- */
  const highestBidEl = document.getElementById("auctionHighestBid");
  const highestRoleEl = document.getElementById("auctionHighestRole");

  if (highestBidEl) highestBidEl.textContent = "$" + auction.highestBid;

  if (highestRoleEl) {
    if (!auction.highestBidRole) {
      highestRoleEl.textContent = "Belum ada penawar";
    } else {
      const bidder =
        typeof getPlayer === "function" ? getPlayer(auction.highestBidRole) : null;
      highestRoleEl.textContent =
        (bidder ? bidder.name : auction.highestBidRole) + " unggul sementara";
    }
  }

  /* ------- my balance ------- */
  const myBalanceEl = document.getElementById("auctionMyBalance");
  if (myBalanceEl) {
    const me =
      typeof getPlayer === "function" ? getPlayer(window.appState.activeRole) : null;
    myBalanceEl.textContent = me
      ? `Saldo kamu: $${me.money}`
      : "";
  }

  /* ------- bid buttons (player only) ------- */
  const bidButtons = document.getElementById("auctionBidButtons");
  if (bidButtons) {
    const isPlayer =
      window.appState.activeRole && window.appState.activeRole !== "BANK";

    if (isPlayer) {
      bidButtons.innerHTML = AUCTION_INCREMENTS.map(
        (inc) =>
          `<button class="auction-bid-btn" data-bid="${inc}">+$${inc}</button>`,
      ).join("");
    } else {
      bidButtons.innerHTML = "";
    }
  }

  /* ------- bank controls ------- */
  const bankControls = document.getElementById("auctionBankControls");
  if (bankControls) {
    if (window.appState.activeRole === "BANK") {
      bankControls.classList.remove("hidden");
    } else {
      bankControls.classList.add("hidden");
    }
  }

  /* ------- history ------- */
  const historyEl = document.getElementById("auctionHistory");
  if (historyEl) {
    if (auction.history.length === 0) {
      historyEl.innerHTML = `<p class="property-loading">Belum ada penawaran.</p>`;
    } else {
      historyEl.innerHTML = auction.history
        .map((h) => {
          const bidder =
            typeof getPlayer === "function" ? getPlayer(h.role) : null;
          const name = bidder ? bidder.name : h.role;
          return `<div class="auction-history-item">[${name}] Uang taruhan menjadi $${h.amount} (+$${h.delta})</div>`;
        })
        .join("");
    }
  }
}

document.addEventListener("click", (e) => {
  const bidBtn = e.target.closest("[data-bid]");
  if (bidBtn) {
    const increment = parseInt(bidBtn.dataset.bid, 10);
    sendPlaceBid(increment);
    return;
  }

  const endBtn = e.target.closest("#auctionForceEndBtn");
  if (endBtn) {
    if (confirm("Akhiri lelang sekarang dan tetapkan pemenang saat ini?")) {
      sendEndAuction();
    }
  }
});
