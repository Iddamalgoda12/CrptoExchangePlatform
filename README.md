# CryptoExchangePlatform

A console-based cryptocurrency exchange simulator built in C++ to explore and practice core Object-Oriented Programming concepts.

This project models a simplified trading engine where users can:

* inspect market data,
* place buy/sell orders,
* manage a wallet,
* and process historical orders over time.

It is designed as a learning project, but the code is organized in a way that reflects real-world software structure:

* clear class separation,
* header/implementation split,
* reusable utility classes,
* and a main application controller.

---

## Order Matching Engine

The order matching engine is the core of the exchange. It matches buyers and sellers when their orders are compatible.

### Sorts orders

* **Buy orders** → highest price first
* **Sell orders** → lowest price first

This ensures the best available prices are matched first.

### Checks for a match

A trade can happen when:

```text
bid >= ask
```

### Executes trades

The engine matches the orders and uses the smaller order amount, allowing **partial fills** (part of an order can be completed).

### Updates orders

The remaining amount is updated, and fully completed orders are removed.

### Records trades

Completed trades are stored with their price, amount, product, and timestamp.

This simulates the basic behavior of a real cryptocurrency exchange order book while demonstrating sorting, queues, matching algorithms, and state management.

---

## User Functionalities

Users can interact with the exchange through a simple console menu to:

* **View Help** – Learn how the exchange works and how to use each feature.
* **View Exchange Stats** – Check trading pairs, active bids/asks, and price statistics.
* **Place Buy Orders (Bids)** – Specify a product, price, and amount to buy.
* **Place Sell Orders (Asks)** – Specify a product, price, and amount to sell.
* **Manage Wallet** – Deposit, withdraw, and view cryptocurrency balances.
* **Process Orders** – Run the matching engine, execute trades, and move to the next market timeframe.

---

## Key Features

* 📊 Historical cryptocurrency market data from CSV files
* ⚡ Automated order matching engine
* 💰 Best-price order matching
* 🔄 Partial order fills
* 🛡️ Wallet and order validation
* 📝 Trade logging to `sales.csv`
* ⏱️ Historical timeframe progression
* 🎨 Color-coded console interface for easier navigation
