function openPrivatePage() {
  if (window.appState.activeRole === "BANK") {
    showPage("bankDashboard");
  } else {
    showPage("playerDashboard");
  }
}
