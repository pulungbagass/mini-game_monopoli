/* =========================
   REGISTER PAGE
========================= */

function renderMyPropertyPage() {
  setTimeout(initMyPropertyPage, 0);

  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>MY PROPERTY</h2>
      <p>Properti yang kamu miliki.</p>

      <div
        id="myPropertyStatusContainer"
        style="margin-top:16px;"
      ></div>

      <div
        id="myPropertyListContainer"
        class="property-list"
      >
        <p class="property-loading">Loading properties...</p>
      </div>
    </div>
  `;
}

registerPage("myProperty", renderMyPropertyPage);

/* =========================
   INIT
========================= */

function initMyPropertyPage() {
  loadPropertyRules().then(() => {
    renderMyPropertyList();
  });
}

/* =========================
   RENDER LIST (hanya milik activeRole)
========================= */

function renderMyPropertyList() {
  const container = document.getElementById("myPropertyListContainer");

  if (!container) return;

  const rules = window.appState.propertyRules || [];
  const myRole = window.appState.activeRole;

  const owned = rules.filter((rule) => {
    const ownership = window.appState.properties[rule.assets_id];

    return ownership && ownership.owned && ownership.owner === myRole;
  });

  if (owned.length === 0) {
    container.innerHTML = `<p class="property-loading">Kamu belum memiliki properti apapun.</p>`;
    return;
  }

  container.innerHTML = owned
    .map((rule) =>
      renderPropertyActionRow(rule, "my", "myPropertyStatusContainer"),
    )
    .join("");
}