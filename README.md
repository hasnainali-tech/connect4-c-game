# Connect 4 Game in C 🎮

This is a console-based **Connect-4 game** written in C language.  
The player competes against the computer, and the board updates after every move.

---

## ✅ Features
✔ Dynamic 2D game board  
✔ Player vs Computer mode  
✔ Pieces drop to the lowest available position  
✔ Computer selects random valid columns  
✔ **Win detection**:
- Row
- Column
- Diagonal (/ direction)
  
✔ Draw detection when the board becomes full  
✔ Input validation & error handling  
✔ Supports **any board size** (minimum 4x4)

---

## 🧠 What I Learned
- Working with 2D arrays
- Logic building for game rules
- Random number generation using `rand()`
- Time delay using `clock()`
- Handling edge cases and invalid inputs

---

## 📂 How to Run
1. Save the `.c` file
2. Compile using GCC:
   ```bash
   gcc connect4.c -o connect4
 
