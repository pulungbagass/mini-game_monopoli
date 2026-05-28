/* =========================
   GAME STATE
========================= */

function handleGameState(data) {
  console.log("GAME STATE:");

  console.log(data.players);

  gameState = data.players;
}

/* =========================
   GET PLAYER MONEY
========================= */

function getPlayerMoney(role) {
  const player = gameState.find((p) => p.role === role);

  if (!player) {
    return 0;
  }

  return player.money;
}
