# Mayka's Waffles — Console Ordering System

A C++ command-line point-of-sale (POS) and order management system built with full CRUD functionality (Create, Read, Update, Delete).

## Features
- **Menu & Pricing:** 10 waffle flavors with formatted currency totals (`₱`).
- **Order Management:** Place new orders, automatically merge duplicate flavors, update existing items, or cancel orders.
- **Receipt Generation:** Prints an itemized receipt upon order completion.
- **Input Validation:** Handles non-numeric and out-of-range inputs safely.

## How to Run Locally
```bash
g++ Maykas_Waffles.cpp -o Maykas_Waffles
./Maykas_Waffles