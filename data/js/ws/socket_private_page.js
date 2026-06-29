/* =========================
   OPEN PRIVATE PAGE
========================= */

function openPrivatePage() {
  const title = document.getElementById("privateRoleTitle");
  const info = document.getElementById("privateRoleInfo");
  const content = document.getElementById("privateContent");

  title.innerText = window.appState.activeRole;

  /* =====================================================
     BANK DASHBOARD
  ====================================================== */

  if (window.appState.activeRole === "BANK") {
    info.innerText = "BANK CONTROL PANEL";

    content.innerHTML = `
      <div class="bank-card">
        <div class="bank-left">
          <div class="bank-icon">
            🏦
          </div>
          <div class="bank-info">
            <h2>BANK</h2>
            <p>Game Administrator</p>
          </div>
        </div>
      </div>
      <div class="section-title">
        <h3>BANK MENU</h3>
      </div>
      <div class="system-grid">
        <div class="system-card" id="menuTransfer">
          💸
          <span>TRANSFER</span>
        </div>
        <div class="system-card" id="menuAuction">
          🔨
          <span>AUCTION</span>
        </div>
        <div class="system-card" id="menuLogs">
          📜
          <span>LOGS</span>
        </div>
        <div class="system-card" id="menuSettings">
          ⚙️
          <span>SETTINGS</span>
        </div>
      </div>
    `;
  } else {

  /* =====================================================
     PLAYER DASHBOARD
  ====================================================== */
    info.innerText = "PLAYER DASHBOARD";

    const player = getPlayer(window.appState.activeRole);

    content.innerHTML = `
      <div class="player-card">
        <div class="player-left">
          <div class="player-avatar">
            🧑
          </div>
          <div class="player-info">
            <h2>${player.name}</h2>
            <p>$ ${player.money}</p>
            <div class="player-uid">
              ${player.uid}
            </div>
          </div>
        </div>
      </div>
      <div class="section-title">
        <h3>PLAYER STATUS</h3>
      </div>
      <div class="system-grid">
        <div class="system-card">
          🏠
          <span>${player.property} PROPERTY</span>
        </div>
        <div class="system-card">
          🏘️
          <span>${player.house} HOUSE</span>
        </div>
        <div class="system-card">
          🏨
          <span>${player.hotel} HOTEL</span>
        </div>
      </div>
      <div class="section-title">
        <h3>PLAYER MENU</h3>
      </div>
      <div class="system-grid">

        <div class="system-card">
          💸
          <span>TRANSFER</span>
        </div>
        <div class="system-card">
          📜
          <span>HISTORY</span>
        </div>
      </div>

    `;
  }

  showPage("privatePage");
}
