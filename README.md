# 🏏 Cricket Match Management System

A console-based cricket match simulator written in **C**. Pick two teams from a file, choose your Playing XI in batting order, take the toss, and play a limited-overs match ball by ball by guessing each delivery's outcome. Results are saved to a match history file.

---

## ✨ Features

- **Team loading from file** – teams, managers and 15-player squads are read from `teams.txt` (up to 20 teams)
- **Playing XI selection** – choose 11 of 15 players in your own batting order
- **Random toss** – the winner chooses to bat or bowl
- **Custom match length** – enter any number of overs
- **Ball-by-ball guessing gameplay** with live commentary and umpire decisions
- **Wide and no-ball handling** – extra run added, ball does not count
- **Strike rotation** – on odd runs and at the end of each over
- **Live scoreboard** and final **batting scorecards** for both innings
- **Chase logic** – the second innings ends as soon as the target is reached
- **Match result** – win by runs, win by wickets, or tie
- **Match history** – every match is appended to `match_history.txt` and can be viewed from the menu
- **Input validation** – bad input never crashes the program

---

## 📁 Project Structure

```
cricket-management-system/
├── cricket.c         # Complete source code
├── teams.txt         # Team data (editable)
├── Makefile          # Build shortcuts
├── .gitignore        # Ignores binaries and generated history
├── LICENSE           # MIT License
└── README.md         # This file
```

`match_history.txt` is created automatically after your first match.

---

## ⚙️ Requirements

- A C compiler (GCC or Clang)
- `make` (optional, for the shortcut commands)

---

## 🚀 Build and Run

**Using make (Linux / macOS / MinGW):**

```bash
make        # compile
make run    # compile and run
make clean  # remove the compiled binary
```

**Using GCC directly:**

```bash
gcc -Wall -Wextra -std=c99 -o cricket cricket.c
./cricket          # Linux / macOS
cricket.exe        # Windows
```

> ⚠️ Run the program from the folder that contains `teams.txt`, because it is read from the current working directory.

---

## 🎮 How to Play

1. Choose **1. Play New Match** from the main menu.
2. Select **Team 1** and **Team 2**.
3. For each team, pick **11 players from the 15-man squad in batting order**. The first two picks are the openers (striker and non-striker).
4. A random **toss** decides who chooses to bat or bowl.
5. Enter the **number of overs**.
6. For each ball, **guess a number from 0 to 9**:

| Code | Meaning |
|------|---------|
| 0–6  | Dot ball / runs scored |
| 7    | Wide (+1 run, ball not counted) |
| 8    | No-ball (+1 run, ball not counted) |
| 9    | Wicket |

### Outcome rule

The game generates a hidden random number from 0 to 9.

- If your guess **matches** the hidden number, that outcome happens.
- Otherwise the outcome is the **absolute difference** between your guess and the hidden number (`|guess − hidden|`).

For example, if you guess `4` and the hidden number is `1`, the outcome is `3` runs.

### Innings rules

- An innings ends when all overs are bowled or 10 wickets fall.
- In the second innings, the chasing team wins as soon as it passes the target (`first innings runs + 1`).

---

## 📝 `teams.txt` Format

One team per line, fields separated by `|`, players separated by `,`:

```
TeamName|ManagerName|player1,player2,...,player15
```

Rules:

- Each team **must have exactly 15 players**, otherwise the line is skipped
- Team, manager and player names must be under **30 characters**
- Avoid using `|` or `,` inside names
- At least **2 valid teams** are required to start a match

Example:

```
Bangladesh Tigers|Rahim Uddin|Tamim,Liton,Shanto,Mushfiq,Shakib,Mahmudullah,Afif,Mehidy,Taskin,Mustafizur,Shoriful,Nasum,Hasan,Soumya,Towhid
```

---

## 📜 Match History Format

Each match is saved as one line in `match_history.txt`:

```
Team A (Manager: X) 120/5 vs Team B (Manager: Y) 118/9 | Result: Team A won by 2 runs
```

---

## 🧱 Code Overview

| Function | Purpose |
|----------|---------|
| `read_int()` | Safe integer input with validation |
| `load_teams()` | Parses `teams.txt` into `Team` structs |
| `select_team()` / `select_xi()` | Team and Playing XI selection |
| `guess_outcome()` | Core guessing logic |
| `play_innings()` | Runs one full innings with scoring, strike changes and wickets |
| `print_commentary()` / `print_wicket()` | Commentary and umpire signals |
| `print_scorecard()` | Batting scorecard |
| `arrange_match()` | Full match flow: setup, toss, two innings, result |
| `save_match_history()` / `view_match_history()` | History file handling |

---

## 🔮 Possible Improvements

- Bowler selection and bowling figures
- Run-out and extras breakdown in the scorecard
- Super over for tied matches
- Tournament / points table mode
- Add or edit teams from inside the program

---

## 🤝 Contributing

Contributions are welcome. Fork the repo, create a branch, and open a pull request.

## 📄 License

Released under the [MIT License](LICENSE).

## 👤 Author

**Your Name** – [GitHub](https://github.com/your-username)
