/* =========================
   ELEMENT
========================= */

const pages =
  document.querySelectorAll(".page");

const systemCards =
  document.querySelectorAll(".system-card");

const backButtons =
  document.querySelectorAll(".back-button");

const bankButton =
  document.getElementById("bankButton");


/* =========================
   PAGE NAVIGATION
========================= */

function showPage(pageId) {

  pages.forEach((page) => {

    page.classList.remove("active");

  });

  document
    .getElementById(pageId)
    .classList.add("active");

}


/* =========================
   SYSTEM NAVIGATION
========================= */

systemCards.forEach((card) => {

  card.addEventListener("click", () => {

    const pageId =
      card.dataset.page;

    showPage(pageId);

  });

});


/* =========================
   BACK BUTTON
========================= */

backButtons.forEach((button) => {

  button.addEventListener("click", () => {

    showPage("homePage");

  });

});


/* =========================
   BANK BUTTON
========================= */

bankButton.addEventListener("click", () => {

  alert("OPEN BANK PAGE");

});