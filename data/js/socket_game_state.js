/* =========================
   GAME STATE
========================= */

function handleGameState(data) {
  console.log("GAME STATE");

  window.appState.gameState = data.players;
}

/* =========================
   GET PLAYER MONEY
========================= */

function getPlayerMoney(role) {
  const player = window.appState.gameState.find((p) => p.role === role);

  if (!player) {
    return 0;
  }

  return player.money;
}
