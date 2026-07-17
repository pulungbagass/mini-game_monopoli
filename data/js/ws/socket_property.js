/* =========================
   LOAD PROPERTY RULES (STATIC)
========================= */

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

/* =========================
   GET PROPERTY RULE (STATIC)
========================= */

function getPropertyRule(assetId) {
  return (window.appState.propertyRules || []).find(
    (rule) => rule.assets_id === assetId,
  );
}

/* =========================
   HANDLE PROPERTY STATE (FULL SNAPSHOT)
========================= */

function handlePropertyState(data) {
  const map = {};

  (data.properties || []).forEach((property) => {
    map[property.assetId] = property;
  });

  window.appState.properties = map;

  refreshPropertyListIfVisible();
}

/* =========================
   HANDLE PROPERTY UPDATE (SINGLE ASSET)
========================= */

function handlePropertyUpdate(data) {
  window.appState.properties[data.assetId] = {
    assetId: data.assetId,
    owner: data.owner,
    owned: data.owned,
    mortgaged: data.mortgaged,
    house: data.house,
    hotel: data.hotel,
  };

  /* =========================
     DETEKSI SUKSES
     property_update untuk assetId yang sama
     dengan yang sedang diproses = aksi berhasil
  ========================= */

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

/* =========================
   RE-RENDER PROPERTY PAGE IF CURRENTLY OPEN
========================= */

function refreshPropertyListIfVisible() {
  const container = document.getElementById("propertyListContainer");

  if (container) {
    renderPropertyListContent();
  }

  refreshOwnedPropertyPagesIfVisible();
}

/* =========================
   REFRESH MY PROPERTY / PROPERTY MANAGER
   (kalau sedang terbuka)
========================= */

function refreshOwnedPropertyPagesIfVisible() {
  if (typeof renderMyPropertyList === "function") {
    renderMyPropertyList();
  }

  if (typeof renderPropertyManagerList === "function") {
    renderPropertyManagerList();
  }
}

/* =========================
   PROPERTY STATUS BANNER (generic, dipakai
   oleh myPropertyPage & propertyManagerPage)
========================= */

function renderPropertyStatus(containerId, title, message) {
  if (!containerId) return;

  const content = document.getElementById(containerId);

  if (!content) return;

  content.innerHTML = `
    <div class="page-card">
      <h3>${title}</h3>
      <br>
      <p>${message}</p>
    </div>
  `;
}

/* =========================
   START PROPERTY ACTION (dipanggil sebelum
   kirim WS supaya socket_ui.js tahu ini
   sesi property, bukan transfer uang)
========================= */

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

/* =========================
   CLEAR PROPERTY ACTION STATE
========================= */

function clearPropertyActionState() {
  window.appState.activeTransactionKind = null;

  window.appState.activePropertyStatusContainer = null;

  window.appState.activePropertyAssetId = null;
}

/* =========================
   SEND : BUY PROPERTY
========================= */

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

/* =========================
   SEND : SELL PROPERTY
========================= */

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

/* =========================
   SEND : MORTGAGE PROPERTY
========================= */

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

/* =========================
   SEND : RELEASE MORTGAGE
========================= */

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

/* =========================
   SEND : BUILD HOUSE
========================= */

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

/* =========================
   SEND : SELL HOUSE
========================= */

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

/* =========================
   SEND : BUILD HOTEL
========================= */

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

/* =========================
   SEND : SELL HOTEL
========================= */

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