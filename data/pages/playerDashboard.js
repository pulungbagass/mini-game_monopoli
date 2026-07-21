function renderPlayerDashboard() {
  const player = getPlayer(window.appState.activeRole);
  if (!player) {
    return `
    <div class="page-card">
        Player not found
    </div>
    `;
  }
  return `

        <button class="back-button">
            ← BACK
        </button>
        <div class="page-card">
            <h2>
                PLAYER DASHBOARD
            </h2>
            <br>
            <div class="player-dashboard-card">
                <div class="player-left">
                    <div class="player-avatar">
                        👤
                    </div>
                    <div class="player-info">
                        <h2>${player.name}</h2>
                        <p>
                            Money : $${player.money}
                        </p>
                        <span class="player-uid">
                            UID : ${player.uid}
                        </span>
                    </div>
                </div>
                <div class="player-dashboard-stats">
                    <div class="player-dashboard-stat house">
                        <div>🏠</div>
                        <strong>${player.house}</strong>
                        <small>HOUSE</small>
                    </div>
                    <div class="player-dashboard-stat hotel">
                        <div>🏨</div>
                        <strong>${player.hotel}</strong>
                        <small>HOTEL</small>
                    </div>
                    <div class="player-dashboard-stat">
                        <div>🏘</div>
                        <strong>${player.property}</strong>
                        <small>PROPERTY</small>
                    </div>
                </div>
            </div>

            <div class="section-title">
                <h3>PLAYER MENU</h3>
            </div>
            <div class="system-grid">
                <div
                    class="system-card"
                    data-page="transferPage">
                    💸
                    <span>
                        TRANSFER
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="myProperty">
                    🏠
                    <span>
                        MY PROPERTY
                    </span>
                </div>
                <div
                    class="system-card"
                    data-draw-card="community_chest">
                    📦
                    <span>
                        COMMUNITY CHEST
                    </span>
                </div>
                <div
                    class="system-card"
                    data-draw-card="chance">
                    ❓
                    <span>
                        CHANCE
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="history">
                    📜
                    <span>
                        HISTORY
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="profile">
                    👤
                    <span>
                        PROFILE
                    </span>
                </div>
            </div>
        </div>
    `;
}
registerPage("playerDashboard", renderPlayerDashboard);

/* ======================================================
   HISTORY (personal log - hanya event yang melibatkan
   player ini)
====================================================== */

function renderHistoryPage() {
  setTimeout(renderHistoryList, 0);
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>📜 HISTORY</h2>
      <p>Transaksi & event yang melibatkan kamu.</p>

      <div id="historyTerminal" class="log-terminal">
        <p class="property-loading">Loading history...</p>
      </div>
    </div>
  `;
}
registerPage("history", renderHistoryPage);

function renderHistoryListIfVisible() {
  if (document.getElementById("historyTerminal")) {
    renderHistoryList();
  }
}

function renderHistoryList() {
  const container = document.getElementById("historyTerminal");
  if (!container) return;

  const myRole = window.appState.activeRole;

  const entries = (window.appState.gameLog || []).filter(
    (e) => e.roleA === myRole || e.roleB === myRole,
  );

  if (entries.length === 0) {
    container.innerHTML = `<p class="property-loading">Belum ada transaksi yang melibatkan kamu.</p>`;
    return;
  }

  container.innerHTML = entries
    .slice()
    .reverse()
    .map((entry) => {
      const meta = gameLogCategoryMeta(entry.category);
      return `
        <div class="log-line ${meta.cls}">
          <span class="log-time">${formatLogTime(entry.timestamp)}</span>
          <span class="log-tag">${meta.label}</span>
          <span class="log-message">${entry.message}</span>
        </div>
      `;
    })
    .join("");
}

/* ======================================================
   PROFILE (ringkasan singkat role aktif)
====================================================== */

function renderProfilePage() {
  const me =
    typeof getPlayer === "function"
      ? getPlayer(window.appState.activeRole)
      : null;

  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>👤 PROFILE</h2>
      ${
        me
          ? `
            <p><b>Nama:</b> ${me.name}</p>
            <p><b>Role:</b> ${me.role}</p>
            <p><b>Saldo:</b> $${me.money}</p>
            <p><b>Properti:</b> ${me.property} (${me.house} rumah, ${me.hotel} hotel)</p>
          `
          : `<p>Data player belum tersedia.</p>`
      }
    </div>
  `;
}
registerPage("profile", renderProfilePage);
