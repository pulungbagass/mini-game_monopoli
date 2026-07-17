/* =========================
   DEVICE ID
========================= */

let savedId = localStorage.getItem("deviceId");

/* =========================
   GENERATE DEVICE ID
========================= */

if (!savedId) {
  savedId = "DEV-" + Math.random().toString(36).substring(2, 10);

  localStorage.setItem("deviceId", savedId);
}

/* =========================
   SAVE TO STATE
========================= */

window.appState.deviceId = savedId;

console.log("DEVICE ID:", savedId);

/* =========================
   CREATE SOCKET
========================= */

const socket = new WebSocket(`ws://${window.location.host}/ws`);

/* =========================
   SAVE SOCKET
========================= */

window.appState.socket = socket;

/* =========================
   CONNECT
========================= */

socket.onopen = () => {
  console.log("WEBSOCKET CONNECTED");

  socket.send(
    JSON.stringify({
      type: "register",
      deviceId: window.appState.deviceId,
    }),
  );
};

/* =========================
   MESSAGE
========================= */

socket.onmessage = (event) => {
  handleSocketMessage(event);
};

/* =========================
   CLOSE
========================= */

socket.onclose = () => {
  console.log("WEBSOCKET CLOSED");
};
