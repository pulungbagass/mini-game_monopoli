/* =========================
   CREATE PLAYER CARD
========================= */

function createPlayerCard(player, index) {
  const card = document.createElement("div");

  card.className = "player-card";

  card.innerHTML = `
    <div class="player-left">
      <div class="player-avatar">
        P${index + 1}
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

    <div class="player-right">
      <div class="property-count house">
        🏠 ${player.house}
      </div>

      <div class="property-count hotel">
        🏨 ${player.hotel}
      </div>
    </div>
  `;

  card.addEventListener("click", () => {
    requestAccess(player.role);
  });

  return card;
}

/* =========================
   RENDER PLAYER LIST
========================= */

function renderPlayerList() {
  const container = document.getElementById("playerCard");

  if (!container) return;

  container.innerHTML = "";

  window.appState.gameState
    .filter((player) => player.role !== "BANK")
    .forEach((player, index) => {
      container.appendChild(createPlayerCard(player, index));
    });
}
