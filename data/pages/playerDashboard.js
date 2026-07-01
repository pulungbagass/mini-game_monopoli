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
            <div class="player-card">
                <div class="player-left">
                    <div class="player-avatar">
                        👤
                    </div>
                    <div class="player-info">
                        <h2>
                            ${player.name}
                        </h2>
                        <p>
                            Money : $${player.money}
                        </p>
                        <span class="player-uid">
                            UID : ${player.uid}
                        </span>
                    </div>
                </div>
                <div class="player-right">
                    <div class="property-count house">
                        🏠 ${player.house}
                    </div>
                    <div class="property-count hotel">
                        🏨 ${player.hotel}
                    </div>
                    <div class="property-count property">
                        🏘 ${player.property}
                    </div>
                </div>
            </div>
            <div class="section-title">
                <h3>PLAYER MENU</h3>
            </div>
            <div class="system-grid">
                <div
                    class="system-card"
                    data-page="transfer">
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
