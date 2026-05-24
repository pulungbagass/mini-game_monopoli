/* =========================
   ELEMENT
========================= */

const playerList = document.getElementById("playerList");

/* =========================
   RENDER PLAYERS
========================= */

function renderPlayers(players) {
  playerList.innerHTML = "";

  players.forEach((player, index) => {
    const card = createPlayerCard(player, index);

    playerList.appendChild(card);
  });
}
