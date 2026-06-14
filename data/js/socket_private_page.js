/* =========================
   OPEN PRIVATE PAGE
========================= */

function openPrivatePage() {
  const title = document.getElementById("privateRoleTitle");

  const info = document.getElementById("privateRoleInfo");

  const content = document.getElementById("privateContent");

  title.innerText = window.appState.activeRole;

  /* =========================
     BANK
  ========================= */

  if (window.appState.activeRole === "BANK") {
    info.innerText = "BANK CONTROL PANEL";

    content.innerHTML = `

      <div class="system-grid">

        <div class="system-card">
          💰
          <span>TRANSFER</span>
        </div>

        <div class="system-card">
          🔨
          <span>AUCTION</span>
        </div>

        <div class="system-card">
          📜
          <span>LOGS</span>
        </div>

        <div class="system-card">
          ⚙️
          <span>SETTINGS</span>
        </div>

      </div>

    `;
  } else {
    /* =========================
     PLAYER
  ========================= */
    info.innerText = "PLAYER DASHBOARD";

    content.innerHTML = `

      <div class="player-card">

        <div class="player-left">

          <div class="player-avatar">
            🧑
          </div>

          <div class="player-info">

            <h2>
              ${window.appState.activeRole}
            </h2>

            <p>
              Money :
              $${getPlayerMoney(window.appState.activeRole)}
            </p>

          </div>

        </div>

      </div>

    `;
  }

  showPage("privatePage");
}
