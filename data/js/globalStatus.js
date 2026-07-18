/* =========================
   SHOW GLOBAL STATUS
   type: "info" | "success" | "error" | "warning"
========================= */

function showGlobalStatus(title, message, type) {
  const banner = document.getElementById("globalStatusBanner");
  const titleEl = document.getElementById("globalStatusTitle");
  const msgEl = document.getElementById("globalStatusMessage");

  if (!banner || !titleEl || !msgEl) return;

  titleEl.textContent = title;
  msgEl.textContent = message;

  banner.classList.remove(
    "hidden",
    "status-info",
    "status-success",
    "status-error",
    "status-warning",
  );

  banner.classList.add("status-" + (type || "info"));
}

/* =========================
   HIDE GLOBAL STATUS
========================= */

function hideGlobalStatus() {
  const banner = document.getElementById("globalStatusBanner");

  if (banner) {
    banner.classList.add("hidden");
  }
}

/* =========================
   CLOSE BUTTON
========================= */

document.addEventListener("DOMContentLoaded", () => {
  const closeBtn = document.getElementById("globalStatusClose");

  if (closeBtn) {
    closeBtn.addEventListener("click", hideGlobalStatus);
  }
});
