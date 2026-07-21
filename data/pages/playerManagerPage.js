/* ======================================================
   BANK: PLAYER MANAGER
   Monitor status koneksi & kondisi tiap player.
====================================================== */

function renderPlayerManagerPage() {
  setTimeout(renderPlayerManagerList, 0);
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>👥 PLAYER MANAGER</h2>
      <p>Status koneksi & kondisi setiap player.</p>

      <div id="playerManagerList" class="player-manager-list">
        <p class="property-loading">Loading players...</p>
      </div>
    </div>
  `;
}
registerPage("playerManager", renderPlayerManagerPage);

function renderPlayerManagerListIfVisible() {
  if (document.getElementById("playerManagerList")) {
    renderPlayerManagerList();
  }
}

function renderPlayerManagerList() {
  const container = document.getElementById("playerManagerList");
  if (!container) return;

  const players = window.appState.gameState || [];

  if (players.length === 0) {
    container.innerHTML = `<p class="property-loading">Belum ada data player.</p>`;
    return;
  }

  container.innerHTML = players
    .map((p) => {
      const isBankrupt = p.money <= 0;
      const statusLabel = isBankrupt
        ? "BANKRUPT"
        : p.online
          ? "ONLINE"
          : "OFFLINE";
      const statusClass = isBankrupt
        ? "player-status-bankrupt"
        : p.online
          ? "player-status-online"
          : "player-status-offline";

      return `
        <div class="player-manager-row">
          <div class="player-manager-info">
            <h4>${p.name || p.role}</h4>
            <p>${p.role} · $${p.money} · ${p.property} properti (${p.house} rumah, ${p.hotel} hotel)</p>
          </div>
          <span class="player-status-badge ${statusClass}">${statusLabel}</span>
        </div>
      `;
    })
    .join("");
}
