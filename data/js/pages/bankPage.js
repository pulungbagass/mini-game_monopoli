/* =========================
   BANK BUTTON
========================= */

const bankButton =
  document.getElementById(
    "bankButton"
  );

bankButton.addEventListener(
  "click",

  () => {

    requestAccess(
      "BANK"
    );

  }

);