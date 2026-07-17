/* =========================
   REGISTER PAGE
========================= */

function renderPropertyManagerPage() {
  setTimeout(initPropertyManagerPage, 0);

  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>PROPERTY MANAGER</h2>
      <p>Kelola pembelian & aksi properti seluruh pemain.</p>
      <p style="font-size:11px;color:#888;margin-top:4px;">
        ⚠️ Auction belum tersedia di backend — kalau saldo pembeli
        tidak cukup, aksi BUY akan gagal (bukan otomatis lelang).
      </p>

      <div
        id="propertyManagerStatusContainer"
        style="margin-top:16px;"
      ></div>

      <div
        id="propertyManagerListContainer"
        class="property-list"
      >
        <p class="property-loading">Loading properties...</p>
      </div>
    </div>
  `;
}

registerPage("propertyManager", renderPropertyManagerPage);

/* =========================
   INIT
========================= */

function initPropertyManagerPage() {
  loadPropertyRules().then(() => {
    renderPropertyManagerList();
  });
}

/* =========================
   RENDER LIST (semua properti, grup per warna)
========================= */

function renderPropertyManagerList() {
  const container = document.getElementById(
    "propertyManagerListContainer",
  );

  if (!container) return;

  const rules = window.appState.propertyRules || [];

  if (rules.length === 0) {
    container.innerHTML = `<p class="property-loading">Loading properties...</p>`;
    return;
  }

  let currentGroup = null;
  let html = "";

  rules.forEach((rule) => {
    const groupKey = rule.color_group || rule.type;

    if (groupKey !== currentGroup) {
      currentGroup = groupKey;

      html += `<div class="property-group-title">${groupKey.toUpperCase()}</div>`;
    }

    html += renderPropertyActionRow(
      rule,
      "manager",
      "propertyManagerStatusContainer",
    );
  });

  container.innerHTML = html;
}
