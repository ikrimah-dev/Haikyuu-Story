#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Utility: safe integer input with a FOR loop (avoids while-loop gotchas on Codecademy)
// Shows a prompt, lists options 1..N, gives the user up to maxTries chances.
// If still invalid, auto-selects option 1 to continue the story gracefully.
int askChoice(const string& prompt, const vector<string>& options, int maxTries = 5) {
    cout << "\n" << prompt << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        cout << "  " << (i + 1) << ") " << options[i] << "\n";
    }

    int choice = -1;
    for (int tries = 0; tries < maxTries; ++tries) {
        cout << "Enter a number (1-" << options.size() << "): ";
        if (cin >> choice && choice >= 1 && choice <= (int)options.size()) {
            return choice;
        }
        // Clear error + flush bad input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Try again.\n";
    }

    cout << "Too many invalid attempts — choosing option 1 to keep the match going.\n";
    return 1;
}

int main() {
    // Simple “character sheet”
    int skill = 0;     // ball control, hitting, serving
    int teamwork = 0;  // communication, synergy
    int grit = 0;      // clutch factor
    int fatigue = 0;   // overtraining risk

    cout << "==============================\n";
    cout << "  HAIKYUU!! : Road to Nationals\n";
    cout << "==============================\n\n";
    cout << "You're a first-year jumping into the world of volleyball.\n";
    cout << "Your goal this season: earn a starting spot and help your team win big.\n";

    // BRANCH POINT #1 — Choose a team (uses switch)
    int teamChoice = askChoice(
        "Tryout time! Which team do you join?",
        {
            "Karasuno High — the crows aiming to fly again.",
            "Nekoma High — cool-headed, defense-first 'connect' volleyball.",
            "Fukurodani Academy — power with brains; the Owls soar."
        }
    );

    string teamName;
    switch (teamChoice) {
        case 1:
            teamName = "Karasuno";
            skill += 1;        // faster, high-tempo reps
            teamwork += 1;
            cout << "\nYou join Karasuno! Speed training and quicks await.\n";
            break;
        case 2:
            teamName = "Nekoma";
            teamwork += 2;     // receive drills, long rallies
            cout << "\nYou join Nekoma! Endless rallies sharpen your read of the game.\n";
            break;
        case 3:
            teamName = "Fukurodani";
            skill += 2;        // strong hitters, serve-targeting practice
            cout << "\nYou join Fukurodani! Smart offense and heavy serves set the tone.\n";
            break;
        default:
            teamName = "Karasuno";
            cout << "\nDefaulting to Karasuno.\n";
            break;
    }

    // BRANCH POINT #2 — Where do you practice today?
    int practiceChoice = askChoice(
        "Practice time. Where do you train?",
        {
            "School gym — structured drills with the full squad.",
            "Beach court — sand training for footwork and stamina.",
            "Neighborhood park — pick-up games, anything goes."
        }
    );

    if (practiceChoice == 1) {
        skill += 2;
        teamwork += 1;
        fatigue += 1;
        cout << "\nGym reps sharpen fundamentals. Coach pushes you hard.\n";
    } else if (practiceChoice == 2) {
        skill += 1;
        grit += 2;     // sand builds resilience
        fatigue += 2;
        cout << "\nSand burns the legs, but your balance and grit skyrocket.\n";
    } else {
        skill += 1;
        teamwork += 1;
        cout << "\nStreet-ball chaos improves your adaptability and comms.\n";
    }

    // Mid-season checkpoint flavor
    cout << "\nMid-season scrimmage vs. a tough rival. Coach is watching.\n";

    // BRANCH POINT #3 — Offense: where do you swing?
    int attackChoice = askChoice(
        "A perfect set comes your way. You choose to:",
        {
            "Swing down the line — risky, but decisive.",
            "Rip cross-court — safer power angle.",
            "Soft tip over the block — read the defense."
        }
    );

    if (attackChoice == 1) {
        skill += 2;
        grit += 1;
        fatigue += 1;
        cout << "\nYou paint the line! The bench erupts. High-risk, high-reward.\n";
    } else if (attackChoice == 2) {
        skill += 1;
        cout << "\nYou hammer cross-court. Solid, reliable point.\n";
    } else {
        teamwork += 2; // reading blockers + coordinating with setter
        cout << "\nFeathery tip into open court — brains over brawn.\n";
    }

    // BRANCH POINT #4 — Serve philosophy
    int serveChoice = askChoice(
        "End of set. It’s your serve. What’s the plan?",
        {
            "Jump serve at the libero — test their best.",
            "Float serve to the seams — disrupt formations.",
            "Short serve to front row — make the setter scramble."
        }
    );

    if (serveChoice == 1) {
        skill += 2;
        grit += 1;
        fatigue += 1;
        cout << "\nCannon of a jump serve — even good passers shank under pressure.\n";
    } else if (serveChoice == 2) {
        skill += 1;
        teamwork += 1;
        cout << "\nFloat knuckles through the seam. Their rhythm cracks.\n";
    } else {
        teamwork += 2;
        cout << "\nCheeky short serve — setter sprints and offense collapses.\n";
    }

    // Simple post-choices “training” loop example:
    // FOR loop gives 3 optional focus reps without using while-input.
    cout << "\nCoach gives you 3 extra focus reps. Choose what to grind each rep:\n";
    for (int rep = 1; rep <= 3; ++rep) {
        int repChoice = askChoice(
            "Focus rep " + to_string(rep) + ":",
            { "First-touch (receive)", "Serving", "Approach & jump timing" }
        );
        if (repChoice == 1) { teamwork += 1; }
        else if (repChoice == 2) { skill += 1; }
        else { skill += 1; grit += 1; fatigue += 1; }
    }

    // Season outcome logic (multiple endings)
    cout << "\n=== Season Review (" << teamName << ") ===\n";
    // Tweak thresholds to taste
    bool overtrained = fatigue >= 5;
    bool ace = (skill >= 6 && teamwork >= 3 && !overtrained);
    bool starter = (skill >= 4 && teamwork >= 3 && !overtrained);
    bool clutchHero = (grit >= 4 && skill >= 3 && !overtrained);
    bool connector = (teamwork >= 5 && skill >= 3 && !overtrained);

    if (overtrained) {
        cout << "Ending: Burnout Alarm\n";
        cout << "You pushed too hard. Fatigue caught up and minor injuries nagged you.\n";
        cout << "Coach benches you to recover before playoffs. Lesson learned: train smart.\n";
        return 0;
    }

    if (ace) {
        cout << "Ending: Ace in the Spotlight\n";
        cout << "Your serve-pressure and hitting clinic turn heads. You crack the starting six,\n"
                "swing clutch points, and scouts start asking Coach about you. Nationals dream alive!\n";
        return 0;
    }

    if (starter) {
        cout << "Ending: Starting Lineup Earned\n";
        cout << "Consistency and team chemistry win the day. You’re named a starter and help\n"
                "the squad upset a seeded team. The gym goes wild. Keep building!\n";
        return 0;
    }

    if (clutchHero) {
        cout << "Ending: Guts Over Glory\n";
        cout << "Even when plays break, you refuse to. Diving saves and fearless swings turn sets.\n"
                "You become the team’s heartbeat in tight moments. The jersey fits.\n";
        return 0;
    }

    if (connector) {
        cout << "Ending: The Connector\n";
        cout << "You read the court like Nekoma itself. Perfect covers, clever tips, smart targets.\n"
                "Teammates play taller with you on court. Coach trusts you in any rotation.\n";
        return 0;
    }

    // Default ending (still positive, encourages replay)
    cout << "Ending: Promise on the Bench\n";
    cout << "You showed flashes, but need more reps. Coach highlights first-touch and serve\n"
            "consistency as the next steps. The climb continues — see you next practice.\n";
    return 0;
}
