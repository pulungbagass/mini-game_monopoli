/* =========================
   GAME STATE
========================= */

function handleGameState(data) {
  console.log(data.players);

  window.appState.gameState = data.players;
}

/* =========================
   GET PLAYER
========================= */

function getPlayer(role) {
  return window.appState.gameState.find((p) => p.role === role);
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
