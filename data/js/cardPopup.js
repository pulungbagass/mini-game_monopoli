/* =========================
   SEND DRAW REQUEST
========================= */

function drawCommunityChest() {
  window.appState.socket.send(
    JSON.stringify({
      type: "draw_community_chest",
      role: window.appState.activeRole,
    }),
  );
}

function drawChance() {
  window.appState.socket.send(
    JSON.stringify({
      type: "draw_chance",
      role: window.appState.activeRole,
    }),
  );
}

/* =========================
   SHOW CARD POPUP
========================= */

function showCardPopup(kind, cardId, cardText, drawerRole) {
  const overlay = document.getElementById("cardPopupOverlay");
  const header = document.getElementById("cardPopupHeader");
  const text = document.getElementById("cardPopupText");
  const meta = document.getElementById("cardPopupMeta");

  if (!overlay || !header || !text || !meta) return;

  header.textContent =
    kind === "chance" ? "❓ CHANCE" : "📦 COMMUNITY CHEST";

  text.textContent = cardText;

  const drawer =
    typeof getPlayer === "function" ? getPlayer(drawerRole) : null;

  meta.textContent = `Diambil oleh: ${drawer ? drawer.name : drawerRole} · ${cardId}`;

  overlay.classList.remove("hidden", "popup-chance", "popup-chest");
  overlay.classList.add(kind === "chance" ? "popup-chance" : "popup-chest");
}

/* =========================
   HIDE CARD POPUP
========================= */

function hideCardPopup() {
  const overlay = document.getElementById("cardPopupOverlay");

  if (overlay) {
    overlay.classList.add("hidden");
  }
}

/* =========================
   BIND EVENTS
========================= */

document.addEventListener("DOMContentLoaded", () => {
  const closeBtn = document.getElementById("cardPopupCloseBtn");

  if (closeBtn) {
    closeBtn.addEventListener("click", hideCardPopup);
  }
});

document.addEventListener("click", (e) => {
  const el = e.target.closest("[data-draw-card]");

  if (!el) return;

  const kind = el.dataset.drawCard;

  if (kind === "community_chest") {
    drawCommunityChest();
  } else if (kind === "chance") {
    drawChance();
  }
});
