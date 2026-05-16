# 🅿️ Système de Gestion de Parking

A desktop parking management system built with **C** and **GTK2**.

##  Why This Project?

This project was intentionally built with **old, poorly documented technology** (GTK2 + libglade + Autotools) as part of our university curriculum. The goal wasn't just to build a parking system — it was to:

- Learn to work with **zero modern documentation**
- Read and understand **legacy C codebases**
- Debug **without Stack Overflow answers** (almost none exist for GTK2 + libglade)
- Build resilience as developers

> Most GTK2 + libglade resources online are from 2003-2008 and incomplete.
> We had to rely on source code, man pages, and pure trial and error.
> This is closer to real-world legacy code maintenance than most university projects.

##  Features

-  Main launcher with 3 modules
-  Agent Management — add, edit, delete, search agents
-  Parking Management — manage spots, floors, availability
- Reservation Management — add, modify, search reservations

##  Built With

- **Language:** C
- **GUI:** GTK2 (libgtk2.0)
- **Build System:** GNU Autotools
- **UI Design:** Glade 2.x

##  Installation

### Prerequisites
```bash
sudo apt update
sudo apt install build-essential libgtk2.0-dev
```

### Build & Run
```bash
git clone https://github.com/nourchaibi1/Parking-management.git
cd Parking-management
./configure
make
cd src && ./park
```

## 📁 Project Structure
final/
├── src/

│   ├── main.c          # Main entry point

│   ├── interface.c     # GTK UI definitions

│   ├── callbacks.c     # Button handlers

│   ├── p1/src/         # Parking management

│   ├── p2/src/         # Agent management

│   └── p3/src/         # Reservations

├── interface.glade     # UI layout
└── README.md

— University Integrated Project 2024


