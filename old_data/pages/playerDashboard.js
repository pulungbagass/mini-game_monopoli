/* =========================
   PLAYER DASHBOARD
========================= */

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
