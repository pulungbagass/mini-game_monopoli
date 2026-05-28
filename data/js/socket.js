/* =========================
   DEVICE ID
========================= */

let deviceId = localStorage.getItem("deviceId");

/* =========================
   GENERATE DEVICE ID
========================= */

if (!deviceId) {
  deviceId = "DEV-" + Math.random().toString(36).substring(2, 10);

  localStorage.setItem("deviceId", deviceId);
}

/* =========================
   DEBUG
========================= */

console.log("DEVICE ID : ", deviceId);

/* =========================
   WEBSOCKET
========================= */

const socket = new WebSocket(`ws://${window.location.host}/ws`);

/* =========================
   CONNECT
========================= */

socket.onopen = () => {
  console.log("WEBSOCKET CONNECTED");

  /* =========================
       REGISTER DEVICE
    ========================= */

  socket.send(
    JSON.stringify({
      type: "register",
      deviceId: deviceId,
    }),
  );
};

/* =========================
   MESSAGE
========================= */

socket.onmessage = (event) => {
  console.log("MESSAGE : ", event.data);
  const data = JSON.parse(event.data);
  if (data.type === "access_granted") {
    console.log("ACCESS GRANTED:", data.role);
    activeRole = data.role;
    openPrivatePage();
  }

  if (data.type === "access_denied") {
    console.log("ACCESS DENIED:", data.role);
  }
};

/* =========================
   CLOSE
========================= */

socket.onclose = () => {
  console.log("WEBSOCKET CLOSED");
};

/* =========================
   TEST CLAIM
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

/* =========================
   PRIVATE PAGE
========================= */

function openPrivatePage() {
  const title = document.getElementById("privateRoleTitle");

  const info = document.getElementById("privateRoleInfo");

  title.innerText = activeRole;

  info.innerText = "PRIVATE ACCESS GRANTED";

  showPage("privatePage");
}
