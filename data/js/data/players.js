/* =========================
   GET PLAYER
========================= */

function getPlayer(role) {
  return window.appState.gameState.find(
    (player) => player.role === role,
  );
}

/* =========================
   GET MONEY
========================= */

function getPlayerMoney(role) {
  const player = getPlayer(role);

  return player ? player.money : 0;
}