/* =========================
   CLAIM ROLE
========================= */

function claimRole(role) {
  window.appState.socket.send(
    JSON.stringify({
      type: "claim_role",

      role: role,

      deviceId: window.appState.deviceId,
    }),
  );
}

/* =========================
   REQUEST ACCESS
========================= */

function requestAccess(role) {
  window.appState.socket.send(
    JSON.stringify({
      type: "request_access",

      role: role,

      deviceId: window.appState.deviceId,
    }),
  );
}
