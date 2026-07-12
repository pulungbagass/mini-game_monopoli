/* =========================
   HOME PAGE
========================= */

function renderHomePage() {
  console.log("HOME PAGE RENDERED");

  return `
    <!-- BANK -->

    <section
      class="bank-card"
      id="bankButton">
      <div class="bank-left">
        <div class="bank-icon">
          🏦
        </div>
        <div class="bank-info">
          <h2>BANK</h2>
          <p>Total Money : $99999999</p>
        </div>
      </div>
    </section>

    <!-- PLAYER -->

    <section class="section-title">
      <h3>PLAYER</h3>
    </section>

    <section
      class="player-list"
      id="playerCard">
    </section>

    <!-- SYSTEM -->

    <section class="section-title">
      <h3>SYSTEM</h3>
    </section>

    <section class="system-grid">

      <div
        class="system-card"
        data-page="property">
        🏘️
        <span>PROPERTY LIST</span>
      </div>

      <div
        class="system-card"
        data-page="logs">
        📜
        <span>HISTORY</span>
      </div>

      <div
        class="system-card"
        data-page="info">
        ℹ
        <span>GAME INFO</span>
      </div>

      <div
        class="system-card"
        data-page="settings">
        ⚙️
        <span>SETTINGS</span>
      </div>

    </section>
  `;
}

registerPage("home", renderHomePage);

/* =========================
   HOME READY
========================= */

document.addEventListener("pageLoaded", () => {
  /* PLAYER */

  renderPlayerList();

  /* BANK */

  const bankButton = document.getElementById("bankButton");

  if (bankButton) {
    bankButton.addEventListener("click", () => {
      requestAccess("BANK");
    });
  }
});
