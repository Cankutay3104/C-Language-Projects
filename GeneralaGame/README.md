# Generala Dice Game

## Description
A command-line implementation of the Generala dice game developed for CNG140. The game pits a human player against a computer in a race to achieve high-scoring dice combinations across $N$ rounds.

## Features
* **Core Logic**: Implements a 5-dice game with sequence, selection, and repetition control constructs.
* **Scoring System**: Automatically calculates scores for categories including Generala (50 pts), Four of a Kind (40 pts), Full House (30 pts), and Straights (20 pts).
* **Computer AI**: Features a decision-making algorithm where the computer only rerolls if it is one die away from a Generala.
* **Turn Management**: Supports up to three rolls per turn with the ability to "keep" specific dice.

## Technical Constraints & Implementation
* **Memory Management**: Developed strictly without the use of arrays or global variables.
* **Functional Decomposition**: Organized into highly cohesive functions: `roll-a-dice()`, `play_computer()`, `play_user()`, and `scoresheet()`.
* **Input Validation**: Includes robust handling for turn decisions and dice selection.
