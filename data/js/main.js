/* =========================
   INIT
========================= */

async function fetchPlayers() {
  alert("FETCH START");

  try {
    const response = await fetch("/api/players");

    const players = await response.json();

    console.log(players);
    alert(players.length);
    renderPlayers(players);
  } catch (error) {
    console.error("FAILED FETCH PLAYERS", error);
  }
}

fetchPlayers();
