/* =========================
   ROUTER
========================= */

const pages = document.querySelectorAll(".page");

function showPage(pageId) {
  pages.forEach((page) => {
    page.classList.remove("active");
  });

  document.getElementById(pageId).classList.add("active");
}

/* =========================
   SYSTEM CARD
========================= */

document.addEventListener(
  "click",

  (e) => {
    const card = e.target.closest(".system-card");

    if (!card) return;

    const pageId = card.dataset.page;

    if (!pageId) return;

    showPage(pageId);
  },
);

/* =========================
   BACK BUTTON
========================= */

const backButtons = document.querySelectorAll(".back-button");

backButtons.forEach((button) => {
  button.addEventListener("click", () => {
    showPage("homePage");
  });
});

window.showPage = showPage;
