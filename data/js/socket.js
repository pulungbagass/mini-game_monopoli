/* =========================
   DEVICE ID
========================= */

let deviceId = localStorage.getItem(
    "deviceId"
);


/* =========================
   GENERATE DEVICE ID
========================= */

if (!deviceId) {

    deviceId =
        "DEV-" +
        Math.random()
            .toString(36)
            .substring(2, 10);

    localStorage.setItem(
        "deviceId",
        deviceId
    );

}


/* =========================
   DEBUG
========================= */

console.log(
    "DEVICE ID : ",
    deviceId
);


/* =========================
   WEBSOCKET
========================= */

const socket = new WebSocket(
    `ws://${window.location.host}/ws`
);


/* =========================
   CONNECT
========================= */

socket.onopen = () => {

    console.log(
        "WEBSOCKET CONNECTED"
    );


    /* =========================
       REGISTER DEVICE
    ========================= */

    socket.send(

        JSON.stringify({

            type: "register",

            deviceId: deviceId

        })

    );

};


/* =========================
   MESSAGE
========================= */

socket.onmessage = (event) => {

    console.log(
        "MESSAGE : ",
        event.data
    );

};


/* =========================
   CLOSE
========================= */

socket.onclose = () => {

    console.log(
        "WEBSOCKET CLOSED"
    );

};