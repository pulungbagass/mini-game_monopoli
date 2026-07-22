function loadPropertyRules() {
  if (window.appState.propertyRules) {
    return Promise.resolve(window.appState.propertyRules);
  }
  return fetch("/monopoly_rules.json")
    .then((res) => res.json())
    .then((data) => {
      window.appState.propertyRules = data.monopoly_assets || [];
      return window.appState.propertyRules;
    })
    .catch((err) => {
      console.error("FAILED TO LOAD PROPERTY RULES", err);
      window.appState.propertyRules = [];
      return window.appState.propertyRules;
    });
}
function getPropertyRule(assetId) {
  return (window.appState.propertyRules || []).find(
    (rule) => rule.assets_id === assetId,
  );
}
function handlePropertyState(data) {
  const map = {};
  (data.properties || []).forEach((property) => {
    map[property.assetId] = property;
  });
  window.appState.properties = map;
  refreshPropertyListIfVisible();
}
function handlePropertyUpdate(data) {
  window.appState.properties[data.assetId] = {
    assetId: data.assetId,
    owner: data.owner,
    owned: data.owned,
    mortgaged: data.mortgaged,
    house: data.house,
    hotel: data.hotel,
  };
  if (
    window.appState.activeTransactionKind === "property" &&
    window.appState.activePropertyAssetId === data.assetId
  ) {
    renderPropertyStatus(
      window.appState.activePropertyStatusContainer,
      "SUCCESS",
      "Property action completed.",
    );
    const container = window.appState.activePropertyStatusContainer;
    clearPropertyActionState();
    setTimeout(() => {
      renderPropertyStatus(container, "READY", "Pilih properti untuk aksi berikutnya.");
    }, 2000);
  }
  refreshPropertyListIfVisible();
}
function refreshPropertyListIfVisible() {
  const container = document.getElementById("propertyListContainer");
  if (container) {
    renderPropertyListContent();
  }
  refreshOwnedPropertyPagesIfVisible();
}
function refreshOwnedPropertyPagesIfVisible() {
  if (typeof renderMyPropertyList === "function") {
    renderMyPropertyList();
  }
  if (typeof renderPropertyManagerList === "function") {
    renderPropertyManagerList();
  }
}
function renderPropertyStatus(containerId, title, message) {
  const t = title.toUpperCase();
  let type = "info";
  if (t === "SUCCESS") type = "success";
  else if (t.includes("FAILED") || t.includes("TIMEOUT")) type = "error";
  else if (t.includes("BUSY")) type = "warning";
  showGlobalStatus(title, message, type);
}
function startPropertyAction(containerId, assetId) {
  window.appState.activeTransactionKind = "property";
  window.appState.activePropertyStatusContainer = containerId;
  window.appState.activePropertyAssetId = assetId;
  renderPropertyStatus(
    containerId,
    "PROCESSING",
    "Waiting confirmation...",
  );
}
function clearPropertyActionState() {
  window.appState.activeTransactionKind = null;
  window.appState.activePropertyStatusContainer = null;
  window.appState.activePropertyAssetId = null;
}
function sendBuyProperty(containerId, buyerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "buy_property",
      buyerRole: buyerRole,
      assetId: assetId,
    }),
  );
}
function sendSellProperty(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "sell_property",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
function sendMortgageProperty(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "mortgage_property",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
function sendReleaseMortgage(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "release_mortgage",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}

/* ======================================================
   BANK EMERGENCY ACTIONS
   Beda dengan mortgage/sell biasa: TIDAK menunggu tap NFC
   owner. Dieksekusi langsung begitu Bank menekan tombol.
====================================================== */

function sendForceMortgage(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  renderPropertyStatus(
    containerId,
    "PROCESSING",
    "Bank sedang mengeksekusi force mortgage...",
  );
  window.appState.socket.send(
    JSON.stringify({
      type: "force_mortgage_property",
      role: "BANK",
      assetId: assetId,
    }),
  );
}

function sendForceSell(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  renderPropertyStatus(
    containerId,
    "PROCESSING",
    "Bank sedang mengeksekusi force sell...",
  );
  window.appState.socket.send(
    JSON.stringify({
      type: "force_sell_property",
      role: "BANK",
      assetId: assetId,
    }),
  );
}
function sendBuildHouse(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "build_house",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
function sendSellHouse(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "sell_house",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
function sendBuildHotel(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "build_hotel",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
function sendSellHotel(containerId, ownerRole, assetId) {
  startPropertyAction(containerId, assetId);
  window.appState.socket.send(
    JSON.stringify({
      type: "sell_hotel",
      ownerRole: ownerRole,
      assetId: assetId,
    }),
  );
}
