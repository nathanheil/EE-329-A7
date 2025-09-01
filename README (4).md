# EE 329 – UART Terminal Game (STM32L4)

This project implements a **VT100-style terminal game** using the LPUART1 peripheral on the STM32L4A6ZG Nucleo board.  
It demonstrates UART communication, terminal escape sequences, and interactive input handling in an embedded system.

---

## 🎮 Features
- **Splash screen** with ASCII art and startup prompt  
- **80×24 terminal game box** drawn with borders using escape codes  
- **Player character** (`@`) that can be moved with arrow keys  
- **Wrap-around movement** when reaching screen edges  
- **Color control**:  
  - `R` = red text  
  - `G` = green text  
  - `B` = blue text  
  - `W` = reset color  
- **Microsecond delays** via SysTick for splash timing  

---

## 🧩 Source Files
- `main.c / main.h` – Application entry, splash screen, game loop【131†source】【132†source】  
- `uart.c / uart.h` – LPUART1 initialization, printing, and interrupt-driven input handling【133†source】【134†source】  
- `delay.c / delay.h` – Microsecond delay implementation using SysTick【129†source】【130†source】  

---

## ⚡ Hardware Setup
- **Board:** STM32L4A6ZG Nucleo  
- **UART:** LPUART1 on PG7 (TX) / PG8 (RX) configured as AF8【133†source】  
- **Terminal:** Connect via ST-LINK VCP or external USB-UART adapter at the configured baud rate  

---

## 🚀 How to Run
1. Import the sources into **STM32CubeIDE**.  
2. Build and flash to the **NUCLEO-L4A6ZG** board.  
3. Open a UART terminal (e.g., PuTTY, Tera Term) at the correct baud rate.  
4. On reset, a splash screen is displayed. Press **Enter** to start.  
5. Use **arrow keys** to move the `@` symbol inside the box.  
6. Change text colors by pressing `R`, `G`, `B`, or `W`.  

---

## 📂 Repository Structure
```
.
├── main.c / main.h          # Splash screen, game logic
├── uart.c / uart.h          # UART driver and input handling
├── delay.c / delay.h        # SysTick microsecond delay
├── .gitignore               # Ignore build artifacts
└── README.md                # Project documentation
```

---

## ✅ Learning Outcomes
- Using **UART communication** for interactive terminal applications  
- Handling **VT100 escape sequences** for cursor positioning and color control  
- Building **interrupt-driven input systems** in embedded C  
- Combining UART I/O, timing, and game logic into a professional embedded project  

---

## 📜 License
This project is licensed under the MIT License – see [LICENSE](LICENSE).

---

👤 **Author:** Nathan Heil  
📅 **Course:** EE‑329 (Embedded Systems)  
