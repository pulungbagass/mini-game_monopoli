/* =========================
   RENT CALCULATOR
   (meniru persis formula calculateRent() di
   property_transaction_service.cpp backend)
========================= */

function ownsFullColorGroup(ownerRole, colorGroup) {
  if (!colorGroup) return false;
  const groupAssets = (window.appState.propertyRules || []).filter(
    (r) => r.color_group === colorGroup,
  );
  if (groupAssets.length === 0) return false;
  return groupAssets.every((r) => {
    const o = window.appState.properties[r.assets_id];
    return o && o.owned && o.owner === ownerRole;
  });
}

function countOwnedByType(ownerRole, type) {
  return (window.appState.propertyRules || []).filter((r) => {
    if (r.type !== type) return false;
    const o = window.appState.properties[r.assets_id];
    return o && o.owned && o.owner === ownerRole;
  }).length;
}

function calculateCurrentRent(rule) {
  const ownership = window.appState.properties[rule.assets_id];

  if (!ownership || !ownership.owned) return null;
  if (ownership.mortgaged) return 0;

  const ownerRole = ownership.owner;
  const rent = rule.rent || {};

  if (rule.type === "Property") {
    if (ownership.hotel) return rent.hotel || 0;
    if (ownership.house === 4) return rent.house4 || 0;
    if (ownership.house === 3) return rent.house3 || 0;
    if (ownership.house === 2) return rent.house2 || 0;
    if (ownership.house === 1) return rent.house1 || 0;

    if (ownsFullColorGroup(ownerRole, rule.color_group)) {
      return rent.monopoly_set || 0;
    }
    return rent.base || 0;
  }

  if (rule.type === "Railroad") {
    const owned = countOwnedByType(ownerRole, "Railroad");
    return rent["owned" + owned] || 0;
  }

  if (rule.type === "Utility") {
    const owned = countOwnedByType(ownerRole, "Utility");
    return owned >= 2 ? "10x dadu" : "4x dadu";
  }

  return null;
}

function renderPropertyActionRow(rule, mode, containerId) {
  const assetId = rule.assets_id;
  const ownership = window.appState.properties[assetId];
  const owned = ownership ? ownership.owned : false;
  const ownerRole = ownership ? ownership.owner : "";
  const mortgaged = ownership ? ownership.mortgaged : false;
  const house = ownership ? ownership.house : 0;
  const hotel = ownership ? ownership.hotel : false;
  const color =
    PROPERTY_COLORS[rule.color_group] ||
    PROPERTY_COLORS[rule.type] ||
    "#cccccc";
  const ownerPlayer =
    typeof getPlayer === "function" ? getPlayer(ownerRole) : null;
  const ownerName = ownerPlayer ? ownerPlayer.name : ownerRole;
  let buttons = "";
  if (mode === "manager" && !owned) {
    const players = (window.appState.gameState || []).filter(
      (p) => p.role !== "BANK",
    );
    const options = players
      .map((p) => `<option value="${p.role}">${p.name}</option>`)
      .join("");
    buttons = `
      <select
        class="transfer-input property-buyer-select"
        id="buyer-${assetId}"
        style="padding:6px;font-size:12px;"
      >
        ${options}
      </select>
      <button
        class="property-btn buy"
        data-property-action="buy"
        data-asset-id="${assetId}"
        data-container="${containerId}"
        data-buyer-select="buyer-${assetId}"
      >BUY</button>
    `;
  }
  if (owned && (mode === "manager" || ownerRole === window.appState.activeRole)) {
    if (mortgaged) {
      buttons += `
        <button
          class="property-btn release"
          data-property-action="release_mortgage"
          data-asset-id="${assetId}"
          data-owner-role="${ownerRole}"
          data-container="${containerId}"
        >RELEASE MORTGAGE</button>
      `;
    } else {
      if (house === 0 && !hotel) {
        buttons += `
          <button
            class="property-btn mortgage"
            data-property-action="mortgage_property"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >MORTGAGE</button>

          <button
            class="property-btn sell"
            data-property-action="sell_property"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >SELL</button>
        `;
      }
      if (!hotel && house < 4) {
        buttons += `
          <button
            class="property-btn build"
            data-property-action="build_house"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >BUILD HOUSE</button>
        `;
      }
      if (house > 0 && !hotel) {
        buttons += `
          <button
            class="property-btn sell"
            data-property-action="sell_house"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >SELL HOUSE</button>
        `;
      }
      if (house === 4 && !hotel) {
        buttons += `
          <button
            class="property-btn build"
            data-property-action="build_hotel"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >BUILD HOTEL</button>
        `;
      }
      if (hotel) {
        buttons += `
          <button
            class="property-btn sell"
            data-property-action="sell_hotel"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >SELL HOTEL</button>
        `;
      }
    }

    /* =========================
       BANK EMERGENCY ACTIONS
       (force mortgage / force sell tanpa perlu tap kartu
       NFC owner -- dipakai kalau player membandel)
    ========================= */
    if (mode === "manager") {
      if (!mortgaged && house === 0 && !hotel) {
        buttons += `
          <button
            class="property-btn force"
            data-property-action="force_mortgage"
            data-asset-id="${assetId}"
            data-owner-role="${ownerRole}"
            data-container="${containerId}"
          >⚠ FORCE MORTGAGE</button>
        `;
      }
      buttons += `
        <button
          class="property-btn force"
          data-property-action="force_sell"
          data-asset-id="${assetId}"
          data-owner-role="${ownerRole}"
          data-container="${containerId}"
        >⚠ FORCE SELL</button>
      `;
    }
  }
  let devBadge = "";
  if (hotel) {
    devBadge = `<span class="property-dev">🏨</span>`;
  } else if (house > 0) {
    devBadge = `<span class="property-dev">🏠 x${house}</span>`;
  }
  const mortgageBadge = mortgaged
    ? `<span class="property-status mortgaged">MORTGAGED</span>`
    : "";
  const rentValue = owned && !mortgaged ? calculateCurrentRent(rule) : null;

  const rentText =
    rentValue === null
      ? ""
      : typeof rentValue === "number"
        ? `<p class="property-rent">💰 Sewa saat ini: $${rentValue}</p>`
        : `<p class="property-rent">💰 Sewa saat ini: ${rentValue}</p>`;

  return `
    <div class="property-item property-item-manage">
      <div class="property-item-top">
        <div
          class="property-color-chip"
          style="background:${color}"
        ></div>

        <div class="property-info">
          <h4>${rule.asset_name}</h4>
          <p>$${rule.purchase_price}${owned ? " · " + ownerName : ""}</p>
          ${rentText}
        </div>

        <div class="property-right">
          ${mortgageBadge}
          ${devBadge}
        </div>
      </div>

      ${buttons ? `<div class="property-actions">${buttons}</div>` : ""}
    </div>
  `;
}
document.addEventListener("click", (e) => {
  const button = e.target.closest("[data-property-action]");
  if (!button) return;
  const action = button.dataset.propertyAction;
  const assetId = button.dataset.assetId;
  const containerId = button.dataset.container;
  const rule =
    typeof getPropertyRule === "function" ? getPropertyRule(assetId) : null;
  const label = rule ? rule.asset_name : assetId;
  if (action === "buy") {
    const select = document.getElementById(button.dataset.buyerSelect);
    const buyerRole = select ? select.value : null;
    if (!buyerRole) {
      alert("Pilih pemain terlebih dahulu.");
      return;
    }
    const buyerPlayer =
      typeof getPlayer === "function" ? getPlayer(buyerRole) : null;
    const confirmMsg = `Beli "${label}" untuk ${
      buyerPlayer ? buyerPlayer.name : buyerRole
    } seharga $${rule ? rule.purchase_price : "?"}?`;
    if (!confirm(confirmMsg)) return;
    sendBuyProperty(containerId, buyerRole, assetId);
    return;
  }
  const ownerRole = button.dataset.ownerRole;
  const confirmLabels = {
    sell_property: `Jual "${label}" ke bank?`,
    mortgage_property: `Gadaikan (mortgage) "${label}"?`,
    release_mortgage: `Tebus (release mortgage) "${label}"?`,
    build_house: `Bangun 1 rumah di "${label}"?`,
    sell_house: `Jual 1 rumah di "${label}"?`,
    build_hotel: `Bangun hotel di "${label}"?`,
    sell_hotel: `Jual hotel di "${label}"?`,
  };

  if (action === "force_mortgage" || action === "force_sell") {
    const ownerPlayer =
      typeof getPlayer === "function" ? getPlayer(ownerRole) : null;
    const ownerName = ownerPlayer ? ownerPlayer.name : ownerRole;

    const actionLabel =
      action === "force_mortgage" ? "MENGGADAIKAN PAKSA" : "MENJUAL PAKSA";

    const warning =
      `⚠ EKSEKUSI DARURAT BANK ⚠\n\n` +
      `Bank akan ${actionLabel} "${label}" milik ${ownerName} ` +
      `TANPA perlu tap kartu ${ownerName}.\n\n` +
      `Gunakan ini hanya kalau player membandel / tidak bisa ` +
      `mengonfirmasi sendiri. Lanjutkan?`;

    if (!confirm(warning)) return;

    if (action === "force_mortgage") {
      sendForceMortgage(containerId, ownerRole, assetId);
    } else {
      sendForceSell(containerId, ownerRole, assetId);
    }
    return;
  }

  if (!confirm(confirmLabels[action] || `Lanjutkan aksi pada "${label}"?`)) {
    return;
  }
  switch (action) {
    case "sell_property":
      sendSellProperty(containerId, ownerRole, assetId);
      break;
    case "mortgage_property":
      sendMortgageProperty(containerId, ownerRole, assetId);
      break;
    case "release_mortgage":
      sendReleaseMortgage(containerId, ownerRole, assetId);
      break;
    case "build_house":
      sendBuildHouse(containerId, ownerRole, assetId);
      break;
    case "sell_house":
      sendSellHouse(containerId, ownerRole, assetId);
      break;
    case "build_hotel":
      sendBuildHotel(containerId, ownerRole, assetId);
      break;
    case "sell_hotel":
      sendSellHotel(containerId, ownerRole, assetId);
      break;
  }
});
