/* =========================
   GAME STATE
========================= */

function handleGameState(data) {

  window.appState.gameState =
    data.players;

  renderPlayerList();

}

/* =========================
   GET PLAYER
========================= */

function getPlayer(role) {

  return window.appState.gameState.find(
    p => p.role === role
  );

}

/* =========================
   GET PLAYER MONEY
========================= */

function getPlayerMoney(role) {

  const player =
    getPlayer(role);

  return player ? player.money : 0;

}