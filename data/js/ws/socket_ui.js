function handleSocketMessage(event) {
  console.log("MESSAGE : ", event.data);
  if (event.data === "CONNECTED TO ESP32") {
    return;
  }
  const data = JSON.parse(event.data);
  if (data.type === "transaction_busy") {
    if (window.appState.activeTransactionKind === "property") {
      renderPropertyStatus(
        window.appState.activePropertyStatusContainer,
        "BUSY",
        "Another transaction is running.",
      );
    } else {
      showGlobalStatus(
        "SIBUK",
        "Ada transaksi lain sedang berjalan, coba lagi sebentar.",
        "warning",
      );
    }
    return;
  }
  if (data.type === "property_wait_owner") {
    renderPropertyStatus(
      window.appState.activePropertyStatusContainer,
      "STEP 1 / 1",
      "Tap owner/buyer NFC card to confirm.",
    );
    return;
  }
  if (data.type === "transaction_wait_sender") {
    if (window.appState.activeTransactionKind === "property") {
      renderPropertyStatus(
        window.appState.activePropertyStatusContainer,
        "STEP 1 / 1",
        "Tap owner/buyer NFC card to confirm.",
      );
    } else {
      renderTransactionStatus("STEP 1 / 2", "Tap Sender NFC Card");
    }
    return;
  }
  if (data.type === "transaction_wait_target") {
    if (window.appState.activeTransactionKind !== "property") {
      renderTransactionStatus("STEP 2 / 2", "Waiting Receiver...");
    }
    return;
  }
  if (data.type === "transaction_wait_receiver") {
    if (window.appState.activeTransactionKind === "property") {
      return;
    }
    const target = data.toRole;
    if (target === "BANK") {
      renderTransactionStatus(
        "PROCESSING",
        "Processing transaction...",
      );
    } else {
      renderTransactionStatus(
        "STEP 2 / 2",
        "Tap Receiver NFC Card",
      );
    }
    return;
  }
  if (data.type === "transaction_processing") {
    if (window.appState.activeTransactionKind === "property") {
      renderPropertyStatus(
        window.appState.activePropertyStatusContainer,
        "PROCESSING",
        "Processing property action...",
      );
    } else {
      renderTransactionStatus("PROCESSING", "Processing transaction...");
    }
    return;
  }
  if (data.type === "transaction_success") {
    if (window.appState.activeTransactionKind === "property") {
      return;
    }
    renderTransactionStatus("SUCCESS", "Money transferred successfully.");
    setTimeout(() => {
      resetTransferForm();
      renderTransactionStatus("READY", "Create a new transaction.");
    }, 2000);
    const cancelButton = document.getElementById("cancelTransferButton");
    if (cancelButton) {
      cancelButton.style.display = "none";
    }
    return;
  }
  if (data.type === "transaction_failed") {
    if (window.appState.activeTransactionKind === "property") {
      renderPropertyStatus(
        window.appState.activePropertyStatusContainer,
        "FAILED",
        "Property action failed (cek aturan game / saldo).",
      );
      const container = window.appState.activePropertyStatusContainer;
      clearPropertyActionState();
      setTimeout(() => {
        renderPropertyStatus(container, "READY", "Pilih properti untuk aksi berikutnya.");
      }, 2000);
      return;
    }
    renderTransactionStatus("FAILED", "Transaction failed.");
    setTimeout(() => {
      resetTransferForm();
      renderTransactionStatus("READY", "Create a new transaction.");
    }, 2000);
    const cancelButton = document.getElementById("cancelTransferButton");
    if (cancelButton) {
      cancelButton.style.display = "none";
    }
    return;
  }
  if (data.type === "transaction_timeout") {
    if (window.appState.activeTransactionKind === "property") {
      renderPropertyStatus(
        window.appState.activePropertyStatusContainer,
        "TIMEOUT",
        "Property action cancelled because timeout.",
      );
      const container = window.appState.activePropertyStatusContainer;
      clearPropertyActionState();
      setTimeout(() => {
        renderPropertyStatus(container, "READY", "Pilih properti untuk aksi berikutnya.");
      }, 3000);
      return;
    }
    renderTransactionStatus(
      "TIMEOUT",
      "Transaction cancelled because timeout.",
    );
    setTimeout(() => {
      resetTransferForm();
      renderTransactionStatus("READY", "Create a new transaction.");
    }, 5000);
    const cancelButton = document.getElementById("cancelTransferButton");
    if (cancelButton) {
      cancelButton.style.display = "none";
    }
    return;
  }
  if (data.type === "transaction_cancelled") {
    if (window.appState.activeTransactionKind === "property") {
      clearPropertyActionState();
      return;
    }
    renderTransactionStatus(
      "CANCELLED",
      "Transaction cancelled.",
    );
    setTimeout(() => {
      resetTransferForm();
      renderTransactionStatus(
        "READY",
        "Create a new transaction.",
      );
    }, 2000);
    return;
  }
  if (data.type === "game_state") {
    handleGameState(data);
    return;
  }
  if (data.type === "access_granted") {
    console.log("ACCESS GRANTED");
    window.appState.activeRole = data.role;
    hideGlobalStatus();
    openPrivatePage();
    return;
  }
  if (data.type === "access_denied") {
    showGlobalStatus(
      "ACCESS DENIED",
      "Kartu ini tidak punya akses ke role tersebut.",
      "error",
    );
    return;
  }
  if (data.type === "need_claim") {
    showGlobalStatus(
      "TAP KARTU NFC",
      `Tempelkan kartu ${data.role} untuk konfirmasi klaim role.`,
      "info",
    );
    claimRole(data.role);
    return;
  }
  if (data.type === "claim_wrong_card") {
    showGlobalStatus(
      "KARTU SALAH",
      `Kartu tidak sesuai. Coba tempelkan kartu ${data.role} lagi.`,
      "error",
    );
    return;
  }
  if (data.type === "claim_already_owned") {
    showGlobalStatus(
      "ROLE SUDAH DIMILIKI",
      `Role ${data.role} sudah diklaim device lain. Pilih role lain.`,
      "error",
    );
    return;
  }
  if (data.type === "claim_timeout") {
    showGlobalStatus(
      "WAKTU HABIS",
      "Klaim role dibatalkan karena timeout. Silakan coba lagi.",
      "warning",
    );
    return;
  }
  if (data.type === "property_state") {
    handlePropertyState(data);
    return;
  }
  if (data.type === "property_update") {
    handlePropertyUpdate(data);
    return;
  }
  if (data.type === "community_chest_result") {
    showCardPopup(
      "community_chest",
      data.cardId,
      data.cardText,
      data.drawerRole,
    );
    return;
  }
  if (data.type === "chance_result") {
    showCardPopup("chance", data.cardId, data.cardText, data.drawerRole);
    return;
  }
  console.warn("UNKNOWN MESSAGE :", data);
}
