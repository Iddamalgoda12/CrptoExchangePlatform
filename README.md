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

##Order Matching Engine

The order matching engine is the core of the exchange. It matches buyers and sellers when their orders are compatible.

Sorts orders:
Buy orders → highest price first
Sell orders → lowest price first
This ensures the best available prices are matched first.
Checks for a match:
A trade can happen when bid >= ask.
Executes trades:
The engine matches the orders and uses the smaller order amount, allowing partial fills (part of an order can be completed).
Updates orders:
The remaining amount is updated, and fully completed orders are removed.
Records trades:
Completed trades are stored with their price, amount, product, and timestamp.

This simulates the basic behavior of a real cryptocurrency exchange order book while demonstrating sorting, queues, matching algorithms, and state management.

## Overview

CryptoExchangePlatform is a text-based crypto exchange simulation that uses historical order data from CSV files to emulate basic trading behavior.

The application starts with a default wallet and allows the user to:
- view available trading pairs,
- place ask orders to sell currency,
- place bid orders to buy currency,
- update wallet balances,
- and advance through market time frames to match orders.

The codebase is structured around few key domain objects:
- `OrderBook`
- `OrderBookEntry`
- `Wallet`
- `CsvReader`
- `MerkelMain`

## Features

- Console-based trading simulation
- Historical CSV market data loading
- Buy and sell order placement
- Wallet balance tracking
- Automatic order matching
- Time-frame based market progression
- Trade execution logging to `sales.csv`
- Clean separation between headers and source files
