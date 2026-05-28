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

    /* =========================
       ROLE MAPPING
    ========================= */

    const role = "PLAYER" + (index + 1);

    /* =========================
       CLICK ACCESS
    ========================= */

    card.addEventListener(
      "click",

      () => {
        requestAccess(role);
      },
    );

    playerList.appendChild(card);
  });
}
