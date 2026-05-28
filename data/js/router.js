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

document
  .querySelectorAll(".system-card")

  .forEach((card) => {
    card.addEventListener(
      "click",

      () => {
        const pageId = card.dataset.page;

        showPage(pageId);
      },
    );
  });

/* =========================
   BACK BUTTON
========================= */

document
  .querySelectorAll(".back-button")

  .forEach((button) => {
    button.addEventListener(
      "click",

      () => {
        showPage("homePage");
      },
    );
  });
