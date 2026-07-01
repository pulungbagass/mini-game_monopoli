/* =========================
   PRIVATE ROUTER
========================= */

document.addEventListener("click", (e) => {
    const card = e.target.closest(".system-card");
    if (!card) return;
    const page = card.dataset.page;
    if (!page) return;
    renderPage(page);
});