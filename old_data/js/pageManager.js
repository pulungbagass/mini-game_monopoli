/* =========================
   PAGE MANAGER
========================= */

const pageContainer = document.getElementById("pageContainer");

/* =========================
   RENDER PAGE
========================= */

function renderPage(id) {
  showPage(id);
}

/* =========================
   CLEAR PAGE
========================= */

function clearPage() {
  pageContainer.innerHTML = "";
}

window.renderPage = renderPage;
window.clearPage = clearPage;
