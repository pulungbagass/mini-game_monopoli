/* =========================
   COLOR MAP
========================= */

const PROPERTY_COLORS = {
  brown: "#955436",
  "light blue": "#aae0fa",
  pink: "#d93a96",
  orange: "#f7941d",
  red: "#ed1b24",
  yellow: "#fef200",
  green: "#1fb25a",
  "dark blue": "#0072bb",
  Railroad: "#1a1a1a",
  Utility: "#8c8c8c",
};

/* =========================
   REGISTER PAGE
========================= */

function renderPropertyPage() {
  setTimeout(initPropertyPage, 0);

  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>ALL PROPERTY</h2>
      <p>Status kepemilikan seluruh petak properti.</p>

      <div
        id="propertyListContainer"
        class="property-list"
      >
        <p class="property-loading">Loading properties...</p>
      </div>
    </div>
  `;
}

registerPage("property", renderPropertyPage);

/* =========================
   INIT
========================= */

function initPropertyPage() {
  loadPropertyRules().then(() => {
    renderPropertyListContent();
  });
}

/* =========================
   RENDER LIST CONTENT
========================= */

function renderPropertyListContent() {
  const container = document.getElementById("propertyListContainer");

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

    html += renderPropertyItem(rule);
  });

  container.innerHTML = html;
}

/* =========================
   RENDER SINGLE ITEM
========================= */

function renderPropertyItem(rule) {
  const ownership = window.appState.properties[rule.assets_id];

  const owned = ownership ? ownership.owned : false;
  const ownerRole = ownership ? ownership.owner : "";
  const mortgaged = ownership ? ownership.mortgaged : false;
  const house = ownership ? ownership.house : 0;
  const hotel = ownership ? ownership.hotel : false;

  const color =
    PROPERTY_COLORS[rule.color_group] ||
    PROPERTY_COLORS[rule.type] ||
    "#cccccc";

  /* STATUS */

  let statusBadge = `<span class="property-status available">AVAILABLE</span>`;

  if (owned) {
    const ownerPlayer =
      typeof getPlayer === "function" ? getPlayer(ownerRole) : null;

    const ownerName = ownerPlayer ? ownerPlayer.name : ownerRole;

    statusBadge = `<span class="property-status owned">${ownerName}</span>`;
  }

  /* MORTGAGE */

  const mortgageBadge = mortgaged
    ? `<span class="property-status mortgaged">MORTGAGED</span>`
    : "";

  /* DEVELOPMENT */

  let devBadge = "";

  if (hotel) {
    devBadge = `<span class="property-dev">🏨</span>`;
  } else if (house > 0) {
    devBadge = `<span class="property-dev">🏠 x${house}</span>`;
  }

  return `
    <div class="property-item">
      <div
        class="property-color-chip"
        style="background:${color}"
      ></div>

      <div class="property-info">
        <h4>${rule.asset_name}</h4>
        <p>$${rule.purchase_price}</p>
      </div>

      <div class="property-right">
        ${statusBadge}
        ${mortgageBadge}
        ${devBadge}
      </div>
    </div>
  `;
}
