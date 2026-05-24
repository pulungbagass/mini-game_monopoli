function createPlayerCard(player, index) {
  const card = document.createElement("div");

  card.className = "player-card";

  card.innerHTML = `

    <div class="player-left">

      <div class="player-avatar">
        P${index + 1}
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

    </div>

  `;

  /* CLICK PLAYER */

  card.addEventListener("click", () => {
    alert(`OPEN PLAYER PAGE : ${player.name}`);
  });

  return card;
}
