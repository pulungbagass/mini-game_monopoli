const pageContainer = document.getElementById("pageContainer");
function renderPage(id) {
  showPage(id);
}
function clearPage() {
  pageContainer.innerHTML = "";
}
window.renderPage = renderPage;
window.clearPage = clearPage;
