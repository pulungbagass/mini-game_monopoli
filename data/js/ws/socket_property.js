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
}
