function handleGameState(data) {
  window.appState.gameState =
    data.players;
  renderPlayerList();
  if (typeof renderPlayerManagerListIfVisible === "function") {
    renderPlayerManagerListIfVisible();
  }
}
function getPlayer(role) {
  return window.appState.gameState.find(
    p => p.role === role
  );
}
function getPlayerMoney(role) {
  const player =
    getPlayer(role);
  return player ? player.money : 0;
}
