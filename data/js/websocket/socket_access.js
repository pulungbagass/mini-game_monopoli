/* =========================
   CLAIM ROLE
========================= */

function testClaim(role) {
  socket.send(
    JSON.stringify({
      type: "claim_role",
      role: role,
      deviceId: deviceId,
    }),
  );
}

/* =========================
   ACCESS REQUEST
========================= */

function requestAccess(role) {
  socket.send(
    JSON.stringify({
      type: "request_access",
      role: role,
      deviceId: deviceId,
    }),
  );
}
