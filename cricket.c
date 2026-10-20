#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SQUAD 11
#define POOL 15
#define MAX_TEAMS 20
#define NAME_LEN 30

typedef struct
{
    char name[NAME_LEN];
    char manager[NAME_LEN];
    char squad[POOL][NAME_LEN];    /* file theke asha 15 jon */
    char players[SQUAD][NAME_LEN]; /* user-er bachha 11 jon (batting order) */
} Team;

typedef struct
{
    char team_name[NAME_LEN];
    int runs;
    int wickets;
    int overs;
    int balls;
    int bat_runs[SQUAD];
    int status[SQUAD];
} InningsScore;

/* ---------- input helpers ---------- */

int read_int(void)
{
    char line[64];
    int v;
    while (1)
    {
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("| %-74s |\n", "Input closed. Exiting.");
            printf("+----------------------------------------------------------------------------+\n");
            exit(0);
        }
        if (sscanf(line, "%d", &v) == 1)
            return v;
        printf("+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "Invalid input! Please enter a number.");
        printf("+----------------------------------------------------------------------------+\n");
        printf("Enter a number: ");
    }
}

/* ---------- commentary and umpire signals ---------- */

void print_wicket(int no_ball)
{
    int type = rand() % 3;
    printf("+----------------------------------------------------------------------------+\n");
    if (type == 0)
        printf("| %-74s |\n", "--> COMMENTARY: Clean bowled! What a massive breakthrough!");
    else if (type == 1)
        printf("| %-74s |\n", "--> COMMENTARY: CAUGHT OUT! In the air... and safely taken in the field!");
    else
        printf("| %-74s |\n", "--> COMMENTARY: LBW! That looked plumb in front!");

    if (no_ball)
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: It was a NO-BALL! Finger stays DOWN... NOT OUT!");
    else if (type == 0)
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Stumps shattered... finger goes up!");
    else if (type == 1)
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Clean catch confirmed... finger goes up!");
    else
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: After a moment's thought... finger goes up!");
    printf("+----------------------------------------------------------------------------+\n");
}

void print_commentary(int input)
{
    printf("+----------------------------------------------------------------------------+\n");
    switch (input)
    {
    case 0:
        printf("| %-74s |\n", "--> COMMENTARY: Solid defense, no run.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Dot ball, umpire counts it.");
        break;
    case 1:
        printf("| %-74s |\n", "--> COMMENTARY: Tucked away into the gap for a quick single.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Fair delivery, run stands.");
        break;
    case 2:
        printf("| %-74s |\n", "--> COMMENTARY: Great running between the wickets! Excellent 2 runs.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Fair delivery, runs stand.");
        break;
    case 3:
        printf("| %-74s |\n", "--> COMMENTARY: Superb field saving! They stretch for three.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Fair delivery, runs stand.");
        break;
    case 4:
        printf("| %-74s |\n", "--> COMMENTARY: WHAT A HIT! Cracked away to the fence for FOUR!");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Arm waved across the chest... FOUR!");
        break;
    case 6:
        printf("| %-74s |\n", "--> COMMENTARY: MONSTROUS SHOT! That goes high into the stands for SIX!");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Both arms raised above the head... SIX!");
        break;
    case 7:
        printf("| %-74s |\n", "--> COMMENTARY: Wide ball! Extra run awarded.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Arms stretched out wide... WIDE!");
        break;
    case 8:
        printf("| %-74s |\n", "--> COMMENTARY: No ball! Extra run awarded.");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Right arm extended at shoulder height... NO BALL!");
        break;
    default:
        printf("| %-74s |\n", "--> COMMENTARY: Good placement for runs!");
        printf("| %-74s |\n", "--> UMPIRE'S DECISION: Fair delivery, runs stand.");
    }
    printf("+----------------------------------------------------------------------------+\n");
}

/* ---------- match history ---------- */

void save_match_history(Team *t1, Team *t2, InningsScore inn1, InningsScore inn2, const char *result)
{
    FILE *fp = fopen("match_history.txt", "a");
    if (fp == NULL)
    {
        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "Error opening file!");
        printf("+----------------------------------------------------------------------------+\n");
        return;
    }
    fprintf(fp, "%s (Manager: %s) %d/%d vs %s (Manager: %s) %d/%d | Result: %s\n",
            inn1.team_name, (strcmp(inn1.team_name, t1->name) == 0 ? t1->manager : t2->manager),
            inn1.runs, inn1.wickets,
            inn2.team_name, (strcmp(inn2.team_name, t1->name) == 0 ? t1->manager : t2->manager),
            inn2.runs, inn2.wickets, result);
    fclose(fp);
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "[Match saved to history file]");
    printf("+----------------------------------------------------------------------------+\n");
}

void view_match_history(void)
{
    FILE *fp = fopen("match_history.txt", "r");
    if (fp == NULL)
    {
        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "No match history found.");
        printf("+----------------------------------------------------------------------------+\n");
        return;
    }
    char line[400];
    int count = 0, len, off;
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "MATCH HISTORY");
    printf("+----------------------------------------------------------------------------+\n");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        len = (int)strlen(line);
        count++;
        printf("| Match %-68d |\n", count);

        for (off = 0; off < len; off += 74)
        {
            printf("| %-74.74s |\n", line + off);
        }
        printf("+----------------------------------------------------------------------------+\n");
    }
    if (count == 0)
    {
        printf("| %-74s |\n", "No matches recorded yet.");
        printf("+----------------------------------------------------------------------------+\n");
    }
    fclose(fp);
}

/* ---------- teams from file ---------- */

/* File format (one team per line):
   TeamName|ManagerName|player1,player2,...,player15 */
int load_teams(Team teams[], int max)
{
    FILE *fp = fopen("teams.txt", "r");
    if (fp == NULL)
        return 0;
    char line[1024];
    int n = 0;
    while (n < max && fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0')
            continue;
        char *name = strtok(line, "|");
        char *mgr = strtok(NULL, "|");
        char *list = strtok(NULL, "|");
        if (!name || !mgr || !list)
            continue;
        strncpy(teams[n].name, name, NAME_LEN - 1);
        teams[n].name[NAME_LEN - 1] = '\0';
        strncpy(teams[n].manager, mgr, NAME_LEN - 1);
        teams[n].manager[NAME_LEN - 1] = '\0';
        int cnt = 0;
        char *p = strtok(list, ",");
        while (p && cnt < POOL)
        {
            strncpy(teams[n].squad[cnt], p, NAME_LEN - 1);
            teams[n].squad[cnt][NAME_LEN - 1] = '\0';
            cnt++;
            p = strtok(NULL, ",");
        }
        if (cnt == POOL)
            n++;
    }
    fclose(fp);
    return n;
}

int select_team(Team teams[], int n, int exclude, const char *title)
{
    int c;
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", title);
    printf("+----------------------------------------------------------------------------+\n");
    for (int i = 0; i < n; i++)
    {
        if (i == exclude)
            continue;
        printf("| %2d. %-30s Manager: %-30s |\n", i + 1, teams[i].name, teams[i].manager);
    }
    printf("+----------------------------------------------------------------------------+\n");
    while (1)
    {
        printf("Select team number: ");
        c = read_int();
        if (c >= 1 && c <= n && c - 1 != exclude)
            return c - 1;
        printf("Invalid team! Try again.\n");
    }
}

void select_xi(Team *t)
{
    int picked[POOL] = {0};
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| SELECT PLAYING XI : %-54s |\n", t->name);
    printf("+----------------------------------------------------------------------------+\n");
    for (int i = 0; i < POOL; i++)
        printf("| %2d. %-69s |\n", i + 1, t->squad[i]);
    printf("+----------------------------------------------------------------------------+\n");
    printf("Pick 11 players in BATTING ORDER (1st = striker, 2nd = non-striker).\n");
    for (int i = 0; i < SQUAD; i++)
    {
        int c;
        while (1)
        {
            printf("  Batting position %-2d -> player no (1-%d): ", i + 1, POOL);
            c = read_int();
            if (c < 1 || c > POOL)
                printf("  Invalid number!\n");
            else if (picked[c - 1])
                printf("  Already selected! Choose another.\n");
            else
                break;
        }
        picked[c - 1] = 1;
        strcpy(t->players[i], t->squad[c - 1]);
    }
}

/* ---------- guessing logic ---------- */

/* codes: 0-6 run, 7 wide, 8 no-ball, 9 wicket */
int guess_outcome(int guess, int *matched)
{
    int r = rand() % 10;
    if (guess == r)
    {
        *matched = 1;
        return r;
    }
    *matched = 0;
    return abs(guess - r); /* 1..9 */
}

/* ---------- innings ---------- */

void print_scorecard(Team *bat, InningsScore *s)
{
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| SCORECARD : %-62s |\n", s->team_name);
    printf("+----------------------------------------------------------------------------+\n");
    for (int i = 0; i < SQUAD; i++)
    {
        const char *st = s->status[i] == 0 ? "did not bat" : (s->status[i] == 1 ? "not out" : "out");
        printf("|   %-2d %-29s %3d   (%-11s)%20s |\n", i + 1, bat->players[i], s->bat_runs[i], st, "");
    }
    printf("+----------------------------------------------------------------------------+\n");
}

InningsScore play_innings(Team *bat, Team *bowl, int over, int target)
{
    InningsScore score;
    memset(&score, 0, sizeof(score));
    strcpy(score.team_name, bat->name);
    score.overs = over;

    int event, guess, matched, outcome;
    int max_balls = over * 6;
    int striker = 0, non_striker = 1, next_in = 2;
    score.status[striker] = 1;
    score.status[non_striker] = 1;

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", ">>> INNINGS START <<<");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Batting : %-64s |\n", bat->name);
    printf("| Manager : %-64s |\n", bat->manager);
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Bowling : %-64s |\n", bowl->name);
    printf("| Bowl Manager: %-60s |\n", bowl->manager);
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Opener 1 : %-63s |\n", bat->players[striker]);
    printf("| Opener 2 : %-63s |\n", bat->players[non_striker]);
    printf("+----------------------------------------------------------------------------+\n");
    if (target > 0)
    {
        printf("| Target to win : %-58d |\n", target);
        printf("+----------------------------------------------------------------------------+\n");
    }

    while (score.balls < max_balls && score.wickets < 10)
    {
        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| On strike   : %-60s |\n", bat->players[striker]);
        printf("| Non-striker : %-60s |\n", bat->players[non_striker]);
        printf("+----------------------------------------------------------------------------+\n");
        printf("Guess ball (%d.%d) [0-6 run, 7 wide, 8 no-ball, 9 wicket]: ",
               score.balls / 6, (score.balls % 6) + 1);
        guess = read_int();
        if (guess < 0 || guess > 9)
        {
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("| %-74s |\n", "Invalid guess! Enter 0 to 9.");
            printf("+----------------------------------------------------------------------------+\n");
            continue;
        }

        outcome = guess_outcome(guess, &matched);
        event = (outcome == 9) ? -1 : outcome;

        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", matched ? "*** Your guess MATCHED! ***"
                                      : "Your guess missed. Outcome = difference.");

        if (event == -1)
        {
            score.wickets++;
            score.balls++;
            print_wicket(0);
            score.status[striker] = 2;
            printf("+----------------------------------------------------------------------------+\n");
            printf("| OUT         : %-29s (%-3d runs)%20s |\n", bat->players[striker], score.bat_runs[striker], "");
            if (score.wickets < 10)
            {
                striker = next_in++;
                score.status[striker] = 1;
                printf("| NEW BATSMAN : %-60s |\n", bat->players[striker]);
            }
            printf("+----------------------------------------------------------------------------+\n");
        }
        else if (event >= 0 && event <= 6)
        {
            score.runs += event;
            score.bat_runs[striker] += event;
            score.balls++;
            print_commentary(event);
            if (event % 2 == 1)
            {
                int t = striker;
                striker = non_striker;
                non_striker = t;
            }
        }
        else /* 7 = wide, 8 = no-ball : 1 extra run, ball gona hobe na */
        {
            print_commentary(event);
            score.runs += 1;
        }

        if ((event == -1 || (event >= 0 && event <= 6)) && score.balls % 6 == 0 && score.balls > 0 &&
            score.balls < max_balls && score.wickets < 10)
        {
            int t = striker;
            striker = non_striker;
            non_striker = t;
            printf("+----------------------------------------------------------------------------+\n");
            printf("| --- End of over %-3d ---%51s |\n", score.balls / 6, "");
            printf("+----------------------------------------------------------------------------+\n");
        }

        printf("+----------------------------------------------------------------------------+\n");
        printf("| %-29s Score: %3d/%-2d  Overs: %3d.%-18d |\n",
               score.team_name, score.runs, score.wickets,
               score.balls / 6, score.balls % 6);
        printf("+----------------------------------------------------------------------------+\n");

        if (target > 0 && score.runs >= target)
            break;
    }

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| FINISHED : %-29s %3d/%-2d in %3d.%d overs%12s |\n",
           score.team_name, score.runs, score.wickets, score.balls / 6, score.balls % 6, "");
    printf("+----------------------------------------------------------------------------+\n");
    print_scorecard(bat, &score);

    return score;
}

/* ---------- match setup ---------- */

void arrange_match(void)
{
    Team all[MAX_TEAMS];
    Team *bat_first, *bat_second;
    int choice, over;
    Team *toss_winner;

    int n = load_teams(all, MAX_TEAMS);
    if (n < 2)
    {
        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "teams.txt not found or has less than 2 valid teams!");
        printf("+----------------------------------------------------------------------------+\n");
        return;
    }

    int i1 = select_team(all, n, -1, "SELECT TEAM 1");
    int i2 = select_team(all, n, i1, "SELECT TEAM 2");
    Team *team1 = &all[i1];
    Team *team2 = &all[i2];

    select_xi(team1);
    select_xi(team2);

    toss_winner = (rand() % 2 == 0) ? team1 : team2;
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "TOSS");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Toss won by : %-60s |\n", toss_winner->name);
    printf("| %-74s |\n", "Winner chooses to Bat or Bowl:");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "1. Bat");
    printf("| %-74s |\n", "2. Bowl");
    printf("+----------------------------------------------------------------------------+\n");
    do
    {
        printf("Enter choice (1 or 2): ");
        choice = read_int();
    } while (choice != 1 && choice != 2);

    Team *other = (toss_winner == team1) ? team2 : team1;
    if (choice == 1)
    {
        bat_first = toss_winner;
        bat_second = other;
    }
    else
    {
        bat_first = other;
        bat_second = toss_winner;
    }

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| Batting first : %-58s |\n", bat_first->name);
    printf("+----------------------------------------------------------------------------+\n");

    do
    {
        printf("\nEnter total overs for the match: ");
        over = read_int();
    } while (over <= 0);

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "INPUT GUIDE");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "Guess each ball: 0-6 = runs, 7 = wide, 8 = no-ball, 9 = wicket");
    printf("| %-74s |\n", "Exact match with the hidden ball = that outcome happens.");
    printf("| %-74s |\n", "Otherwise outcome = |your guess - hidden value|.");
    printf("+----------------------------------------------------------------------------+\n");

    InningsScore inn1 = play_innings(bat_first, bat_second, over, 0);
    int target = inn1.runs + 1;

    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "SECOND INNINGS BEGINS");
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Chasing  : %-63s |\n", bat_second->name);
    printf("| Target   : %-63d |\n", target);
    printf("+----------------------------------------------------------------------------+\n");

    InningsScore inn2 = play_innings(bat_second, bat_first, over, target);

    char result[160];
    printf("\n+----------------------------------------------------------------------------+\n");
    printf("| %-74s |\n", "MATCH RESULT");
    printf("+----------------------------------------------------------------------------+\n");

    if (inn2.runs >= target)
    {
        int wickets_left = 10 - inn2.wickets;
        printf("| Winner : %-29s by %-2d wickets%22s |\n", inn2.team_name, wickets_left, "");
        snprintf(result, sizeof(result), "%s won by %d wickets", inn2.team_name, wickets_left);
    }
    else if (inn1.runs > inn2.runs)
    {
        int run_margin = inn1.runs - inn2.runs;
        printf("| Winner : %-29s by %-4d runs%23s |\n", inn1.team_name, run_margin, "");
        snprintf(result, sizeof(result), "%s won by %d runs", inn1.team_name, run_margin);
    }
    else
    {
        printf("| %-74s |\n", "MATCH TIED!");
        strcpy(result, "Match Tied");
    }
    printf("+----------------------------------------------------------------------------+\n");

    save_match_history(team1, team2, inn1, inn2, result);
}

int main(void)
{
    srand((unsigned)time(0));

    int ch;
    do
    {
        printf("\n+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "                     CRICKET MATCH MANAGEMENT SYSTEM");
        printf("+----------------------------------------------------------------------------+\n");
        printf("| %-74s |\n", "1. Play New Match");
        printf("| %-74s |\n", "2. View Match History");
        printf("| %-74s |\n", "3. Exit");
        printf("+----------------------------------------------------------------------------+\n");
        printf("Choice: ");
        ch = read_int();

        if (ch == 1)
        {
            arrange_match();
        }
        else if (ch == 2)
        {
            view_match_history();
        }
        else if (ch == 3)
        {
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("| %-74s |\n", "Goodbye!");
            printf("+----------------------------------------------------------------------------+\n");
        }
        else
        {
            printf("\n+----------------------------------------------------------------------------+\n");
            printf("| %-74s |\n", "Invalid choice! Try again.");
            printf("+----------------------------------------------------------------------------+\n");
        }
    } while (ch != 3);

    return 0;
}
