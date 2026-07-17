/* =========================
   INIT
========================= */
window.addEventListener(
  "DOMContentLoaded",

  () => {
    showPage("home");
  },
);

// Menonaktifkan klik kanan pada seluruh halaman
document.addEventListener("contextmenu", function (e) {
  e.preventDefault();
});

