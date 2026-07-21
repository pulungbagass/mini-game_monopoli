/* ======================================================
   GAME LOG (public) - terminal style, newest on top
====================================================== */

function renderLogsPage() {
  setTimeout(renderGameLogList, 0);
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>📜 GAME LOG</h2>
      <p>Semua event global di dalam permainan.</p>

      <div id="gameLogTerminal" class="log-terminal">
        <p class="property-loading">Loading log...</p>
      </div>
    </div>
  `;
}
registerPage("logs", renderLogsPage);

function renderGameLogListIfVisible() {
  if (document.getElementById("gameLogTerminal")) {
    renderGameLogList();
  }
}

function renderGameLogList() {
  const container = document.getElementById("gameLogTerminal");
  if (!container) return;

  const entries = window.appState.gameLog || [];

  if (entries.length === 0) {
    container.innerHTML = `<p class="property-loading">Belum ada event.</p>`;
    return;
  }

  container.innerHTML = entries
    .slice()
    .reverse()
    .map((entry) => {
      const meta = gameLogCategoryMeta(entry.category);
      return `
        <div class="log-line ${meta.cls}">
          <span class="log-time">${formatLogTime(entry.timestamp)}</span>
          <span class="log-tag">${meta.label}</span>
          <span class="log-message">${entry.message}</span>
        </div>
      `;
    })
    .join("");
}

/* ======================================================
   GAME INFO (static classic monopoly rules)
====================================================== */

function renderGameInfoPage() {
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>ℹ GAME INFO</h2>
      <p>Ringkasan aturan dasar Monopoli klasik.</p>

      <div class="info-rules">
        <h4>Memulai Permainan</h4>
        <p>Setiap player mulai dengan saldo awal yang sama. Lewati petak START untuk menerima $200.</p>

        <h4>Membeli Properti</h4>
        <p>Berhenti di petak kosong? Kamu boleh membelinya sesuai harga di kartu, atau membiarkannya untuk dilelang Bank.</p>

        <h4>🔨 Lelang (Auction)</h4>
        <p>Kalau properti tidak dibeli, Bank bisa memulai lelang. Semua player bisa menawar naik memakai tombol +$5/+$10/+$50/+$100 selama 30 detik. Penawar tertinggi otomatis membayar saat lelang berakhir, lalu tap kartu NFC ke device Bank untuk menerima properti.</p>

        <h4>Sewa (Rent)</h4>
        <p>Berhenti di properti milik player lain? Bayar sewa sesuai kartu properti (lebih tinggi kalau ada rumah/hotel atau dikuasai satu grup warna penuh).</p>

        <h4>Gadai (Mortgage)</h4>
        <p>Butuh uang cepat? Gadai properti ke Bank. Properti yang digadai tidak bisa memungut sewa sampai ditebus kembali.</p>

        <h4>Rumah &amp; Hotel</h4>
        <p>Kalau kamu menguasai satu grup warna penuh, kamu bisa membangun rumah, lalu upgrade jadi hotel untuk sewa lebih besar.</p>

        <h4>Kartu Chance &amp; Community Chest</h4>
        <p>Ambil kartu acak yang bisa memberi bonus, denda, atau efek spesial seperti "Get Out of Jail Free".</p>

        <h4>Bangkrut (Bankrupt)</h4>
        <p>Kalau tidak bisa membayar kewajiban meski sudah menjual/menggadaikan aset, player dinyatakan bangkrut dan keluar dari permainan.</p>
      </div>
    </div>
  `;
}
registerPage("info", renderGameInfoPage);

/* ======================================================
   SETTINGS (placeholder ringan)
====================================================== */

function renderSettingsPage() {
  return `
    <button class="back-button">
      ← BACK
    </button>

    <div class="page-card">
      <h2>⚙ SETTINGS</h2>
      <p>Pengaturan perangkat.</p>

      <div style="margin-top:16px;">
        <p><b>Role aktif:</b> ${window.appState.activeRole || "-"}</p>
        <p style="margin-top:8px; font-size:12px; color:#666;">
          Untuk keluar dari role ini, tap ulang kartu NFC kamu ke device,
          atau hubungi Bank untuk melakukan reset sesi.
        </p>
      </div>
    </div>
  `;
}
registerPage("settings", renderSettingsPage);
