/* =========================
   HANDLE SOCKET MESSAGE
========================= */

function handleSocketMessage(event) {
  console.log("MESSAGE : ", event.data);

  if (event.data === "CONNECTED TO ESP32") {
    return;
  }

  const data = JSON.parse(event.data);

  /* =========================
     GAME STATE
  ========================= */

  if (data.type === "game_state") {
    handleGameState(data);
  }

  /* =========================
     ACCESS GRANTED
  ========================= */

  if (data.type === "access_granted") {
    console.log("ACCESS GRANTED:", data.role);

    activeRole = data.role;

    openPrivatePage();
  }

  /* =========================
     ACCESS DENIED
  ========================= */

  if (data.type === "access_denied") {
    console.log("ACCESS DENIED:", data.role);

    alert("ACCESS DENIED");
  }

  /* =========================
     NEED CLAIM
  ========================= */

  if (data.type === "need_claim") {
    console.log("PLEASE TAP NFC:", data.role);

    alert("PLEASE TAP NFC CARD");

    testClaim(data.role);
  }
}
