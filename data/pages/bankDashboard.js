function renderBankDashboard() {
    return `
        <button class="back-button">
            ← BACK
        </button>
        <div class="page-card">
            <h2>
                BANK DASHBOARD
            </h2>
            <div class="bank-card">
                <div class="bank-left">
                    <div class="bank-icon">
                        🏦
                    </div>
                    <div class="bank-info">
                        <h2>
                            BANK
                        </h2>
                        <p>
                            Game Administrator
                        </p>
                    </div>
                </div>
            </div>

            <div class="section-title">
                <h3>
                    BANK MENU
                </h3>
            </div>
            <div class="system-grid">
                <div
                    class="system-card"
                    data-page="transferPage">
                    💸
                    <span>
                        TRANSFER
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="auction">
                    🔨
                    <span>
                        AUCTION
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="propertyManager">
                    🏘️
                    <span>
                        PROPERTY GM
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="playerManager">
                    👥
                    <span>
                        PLAYER GM
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="transactionLog">
                    📜
                    <span>
                        LOG
                    </span>
                </div>
                <div
                    class="system-card"
                    data-page="settings">
                    ⚙️
                    <span>
                        SETTINGS
                    </span>
                </div>
            </div>
        </div>
    `;
}
registerPage(
    "bankDashboard",
    renderBankDashboard
);
