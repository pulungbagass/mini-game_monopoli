/* =========================
   GLOBAL STATE
========================= */

window.appState = {
  /* =========================
     DEVICE
  ========================= */

  deviceId: null,

  /* =========================
     ROLE
  ========================= */

  activeRole: null,

  /* =========================
     GAME STATE
  ========================= */

  gameState: [],

  /* =========================
     SOCKET
  ========================= */

  socket: null,

   /* =========================
       PAGE HISTORY  
   ========================= */

  pageHistory: [],

   /* =========================
         TRANSACTION
   ========================= */

   sender: "",

   receiver: "",

   amount: 0,

   state: "idle",

  /* =========================
     PROPERTY
  ========================= */

  properties: {},

  propertyRules: null,

  /* =========================
     ACTIVE TRANSACTION TRACKING
     (shared session di backend dipakai
     bareng oleh transfer uang & property,
     jadi frontend perlu tahu sedang
     menangani yang mana)
  ========================= */

  activeTransactionKind: null, // "transfer" | "property" | null

  activePropertyStatusContainer: null,

  activePropertyAssetId: null
};