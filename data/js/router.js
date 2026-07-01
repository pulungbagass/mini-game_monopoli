/* =========================
   PAGE REGISTRY
========================= */

window.pageRegistry = {};

/* =========================
   REGISTER PAGE
========================= */

function registerPage(id, render) {
  window.pageRegistry[id] = render;
}

/* =========================
   SHOW PAGE
========================= */

function showPage(id, saveHistory = true) {
  const page = document.getElementById("pageContainer");

  if (!page) return;

  const current = page.dataset.currentPage;

  /* =========================
     SAVE HISTORY
  ========================= */

  if (saveHistory && current && current !== id) {
    window.appState.pageHistory.push(current);
  }

  page.dataset.currentPage = id;
  console.log("SHOW PAGE :", id);
  console.log(window.pageRegistry);
  const renderer = window.pageRegistry[id];

  if (!renderer) {
    page.innerHTML = `
      <button class="back-button">
        ← BACK
      </button>

      <div class="page-card">
        <h2>404</h2>
        <p>Page "${id}" not found.</p>
      </div>
    `;
    return;
  }
  clearPage();
  page.innerHTML = renderer();
  document.dispatchEvent(new Event("pageLoaded"));
}

/* =========================
   BACK PAGE
========================= */

function backPage() {
  const history = window.appState.pageHistory;

  if (history.length === 0) {
    showPage("home", false);
    return;
  }
  const previous = history.pop();
  showPage(previous, false);
}

window.showPage = showPage;
window.backPage = backPage;
window.registerPage = registerPage;

/* =========================
   GLOBAL CLICK
========================= */

document.addEventListener("click", (e) => {
  /* =========================
     BACK BUTTON
  ========================= */

  const backButton = e.target.closest(".back-button");
  if (backButton) {
    e.preventDefault();
    e.stopPropagation();
    backPage();
    return;
  }

  /* =========================
     PAGE NAVIGATION
  ========================= */

  const card = e.target.closest("[data-page]");
  if (!card) return;
  e.preventDefault();
  showPage(card.dataset.page);
});
