let savedId = localStorage.getItem("deviceId");
if (!savedId) {
  savedId = "DEV-" + Math.random().toString(36).substring(2, 10);
  localStorage.setItem("deviceId", savedId);
}
window.appState.deviceId = savedId;
console.log("DEVICE ID:", savedId);
const socket = new WebSocket(`ws://${window.location.host}/ws`);
window.appState.socket = socket;
socket.onopen = () => {
  console.log("WEBSOCKET CONNECTED");
  socket.send(
    JSON.stringify({
      type: "register",
      deviceId: window.appState.deviceId,
    }),
  );
};
socket.onmessage = (event) => {
  handleSocketMessage(event);
};
socket.onclose = () => {
  console.log("WEBSOCKET CLOSED");
};
