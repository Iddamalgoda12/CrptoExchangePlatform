# CryptoExchangePlatform

A console-based cryptocurrency exchange simulator built in C++ to explore and practice core Object-Oriented Programming concepts.

This project models a simplified trading engine where users can:
- inspect market data,
- place buy/sell orders,
- manage a wallet,
- and process historical orders over time.

It is designed as a learning project, but the code is organized in a way that reflects real-world software structure:
- clear class separation,
- header/implementation split,
- reusable utility classes,
- and a main application controller.

## Overview

CryptoExchangePlatform is a text-based crypto exchange simulation that uses historical order data from CSV files to emulate basic trading behavior.

The application starts with a default wallet and allows the user to:
- view available trading pairs,
- place ask orders to sell currency,
- place bid orders to buy currency,
- update wallet balances,
- and advance through market time frames to match orders.

The codebase is built primarily with C++ and structured around a few key domain objects:
- `OrderBook`
- `OrderBookEntry`
- `Wallet`
- `CsvReader`
- `MerkelMain`

---

## Features

- Console-based trading simulation
- Historical CSV market data loading
- Buy and sell order placement
- Wallet balance tracking
- Automatic order matching
- Time-frame based market progression
- Trade execution logging to `sales.csv`
- Clean separation between headers and source files

---
├── data.csv
├── sales.csv
└── test.cpp
