/* project2_Strength_ods0005.cpp
 * Owen Strength
 * 9/14/2023
 *
 * compiled using g++
 * This program simulates a duel between three people: Aaron, Bob, and Charlie.
 * The program uses two strategies to determine the best strategy for Aaron.
 * Strategy 1: Aaron shoots at the most accurate shooter still alive.
 * Strategy 2: Aaron intentionally misses his first shot.
 * The program also includes unit tests for each function.
 * The program will output the probability of each person winning using each strategy.
 * The program will also output which strategy is better.
 *
 * References:
 * Hints provided by Dr. Li on Canvas
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
#include <cstdlib>
using namespace std;

// consts
const int run_times = 10000;
const int inverse_probability_Aaron = 3;
const int inverse_probability_Bob = 2;

// statics
static bool Aarron_alive = true;
static bool Bob_alive = true;
static bool Charlie_alive = true;

static int Aaron1_wins = 0;
static int Aaron2_wins = 0;

/* Strategy 1: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 *        C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.
 *         Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots1(bool B_alive, bool C_alive)
{
    if (C_alive)
    {
        Charlie_alive = false;
    }
    else
    {
        Bob_alive = false;
    }
}

/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 *        C_alive indicates whether Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 *         Change C_alive into false if Charlie is killed.
 */
void Bob_shoots(bool A_alive, bool C_alive)
{
    if (C_alive)
    {
        Charlie_alive = false;
    }
    else
    {
        Aarron_alive = false;
    }
}

/* Call by reference
 * Input: A_alive indicates if Aaron is alive or dead
 *        B_alive indicates whether Bob is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 *         Change B_alive into false if Bob is killed.
 */
void Charlie_shoots(bool A_alive, bool B_alive)
{
    if (B_alive)
    {
        Bob_alive = false;
    }
    else
    {
        Aarron_alive = false;
    }
}

/* Strategy 2: Use call by reference
 * Input: B_alive indicates whether Bob alive or dead
 *        C_alive indicates whether Charlie is alive or dead
 * Return: Change B_alive into false if Bob is killed.
 *         Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots2(bool B_alive, bool C_alive)
{
    if (B_alive && C_alive)
    {
        return;
    }
    else if (B_alive)
    {
        Bob_alive = false;
    }
    else if (C_alive)
    {
        Charlie_alive = false;
    }
}

/* Implementation of at_least_two_alive() */
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)
{
    std::vector<bool> b;
    b.push_back(A_alive);
    b.push_back(B_alive);
    b.push_back(C_alive);
    int count = std::count(b.begin(), b.end(), true);
    return count >= 2;
}

/* Implementation of the test driver for at_least_two_alive() */
void test_at_least_two_alive(void)
{
    cout << "Unit Testing 1: Function - at_least_two_alive()" << std::endl;
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ...\n";
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";
}

/* Implementation of the test driver for Aaron_shoots1() */
void test_Aaron_shoots1(void)
{
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    Bob_alive = true;
    Charlie_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(false == Charlie_alive);
    cout << "\t\tAaron is shooting at Charlie\n";
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    Bob_alive = false;
    Charlie_alive = true;
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(false == Charlie_alive);
    cout << "\t\tAaron is shooting at Charlie\n";
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    Bob_alive = true;
    Charlie_alive = false;
    Aaron_shoots1(Bob_alive, Charlie_alive);
    assert(false == Bob_alive);
    cout << "\t\tAaron is shooting at Bob\n";
}

/* Implementation of the test driver for Bob_shoots() */
void test_Bob_shoots(void)
{
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    Aarron_alive = true;
    Charlie_alive = true;
    cout << "\tCase 1: Aaron alive, Charlie alive\n";

    Bob_shoots(Aarron_alive, Charlie_alive);
    assert(false == Charlie_alive);
    cout << "\t\tBob is shooting at Charlie\n";
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    Aarron_alive = false;
    Charlie_alive = true;
    Bob_shoots(Aarron_alive, Charlie_alive);
    assert(false == Charlie_alive);
    cout << "\t\tBob is shooting at Charlie\n";
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    Aarron_alive = true;
    Charlie_alive = false;
    Bob_shoots(Aarron_alive, Charlie_alive);
    assert(false == Aarron_alive);
    cout << "\t\tBob is shooting at Aaron\n";
}

/* Implementation of the test driver for Charlie_shoots() */
void test_Charlie_shoots(void)
{
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    Aarron_alive = true;
    Bob_alive = true;
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    Charlie_shoots(Aarron_alive, Bob_alive);
    assert(false == Bob_alive);
    cout << "\t\tCharlie is shooting at Bob\n";
    cout << "\tCase 2: Aaron dead, Bob alive\n";
    Aarron_alive = false;
    Bob_alive = true;
    Charlie_shoots(Aarron_alive, Bob_alive);
    assert(false == Bob_alive);
    cout << "\t\tCharlie is shooting at Bob\n";
    cout << "\tCase 3: Aaron alive, Bob dead\n";
    Aarron_alive = true;
    Bob_alive = false;
    Charlie_shoots(Aarron_alive, Bob_alive);
    assert(false == Aarron_alive);
    cout << "\t\tCharlie is shooting at Aaron\n";
}

/* Implementation of the test driver for Aaron_shoots2() */
void test_Aaron_shoots2(void)
{
    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    Bob_alive = true;
    Charlie_alive = true;
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(true == Bob_alive && true == Charlie_alive);
    cout << "\t\tAaron intentionally misses his first shot\n";
    cout << "\t\tBoth Bob and Charlie are alive\n";
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    Bob_alive = false;
    Charlie_alive = true;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(false == Charlie_alive);
    cout << "\t\tAaron is shooting at Charlie\n";
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    Bob_alive = true;
    Charlie_alive = false;
    Aaron_shoots2(Bob_alive, Charlie_alive);
    assert(false == Bob_alive);
    cout << "\t\tAaron is shooting at Bob\n";
}

/* Strategy 1: Aaron shoots at the most accurate shooter still alive. So does Charlie and Bob */
void strategy1()
{
    int aaron_wins = 0;
    int bob_wins = 0;
    int charlie_wins = 0;
    for (int i = 0; i < run_times; i++)
    {
        Aarron_alive = true;
        Bob_alive = true;
        Charlie_alive = true;
        while (at_least_two_alive(Aarron_alive, Bob_alive, Charlie_alive))
        {
            if (Aarron_alive && rand() % inverse_probability_Aaron == 0)
            {
                Aaron_shoots1(Bob_alive, Charlie_alive);
            }
            if (Bob_alive && rand() % inverse_probability_Bob == 0)
            {
                Bob_shoots(Aarron_alive, Charlie_alive);
            }
            if (Charlie_alive)
            {
                Charlie_shoots(Aarron_alive, Bob_alive);
            }
        }
        if (Aarron_alive)
        {
            aaron_wins++;
        }
        else if (Bob_alive)
        {
            bob_wins++;
        }
        else
        {
            charlie_wins++;
        }
    }
    Aaron1_wins = aaron_wins;
    cout << "Aaron won " << aaron_wins << "/" << run_times << " duels or " << (double)aaron_wins / run_times * 100 << "%\n";
    cout << "Bob won " << bob_wins << "/" << run_times << " duels or " << (double)bob_wins / run_times * 100 << "%\n";
    cout << "Charlie won " << charlie_wins << "/" << run_times << " duels or " << (double)charlie_wins / run_times * 100 << "%\n";
}

/* An alternative strategy for Aaron is to intentionally miss on his first shot,
while the rest of duel is as same as that in Strategy 1.*/
void strategy2()
{
    int aaron_wins = 0;
    int bob_wins = 0;
    int charlie_wins = 0;
    for (int i = 0; i < run_times; i++)
    {
        Aarron_alive = true;
        Bob_alive = true;
        Charlie_alive = true;
        while (at_least_two_alive(Aarron_alive, Bob_alive, Charlie_alive))
        {
            if (Aarron_alive && rand() % inverse_probability_Aaron == 0)
            {
                Aaron_shoots2(Bob_alive, Charlie_alive);
            }
            if (Bob_alive && rand() % inverse_probability_Bob == 0)
            {
                Bob_shoots(Aarron_alive, Charlie_alive);
            }
            if (Charlie_alive)
            {
                Charlie_shoots(Aarron_alive, Bob_alive);
            }
        }
        if (Aarron_alive)
        {
            aaron_wins++;
        }
        else if (Bob_alive)
        {
            bob_wins++;
        }
        else
        {
            charlie_wins++;
        }
    }
    Aaron2_wins = aaron_wins;
    cout << "Aaron won " << aaron_wins << "/" << run_times << " duels or " << (double)aaron_wins / run_times * 100 << "%\n";
    cout << "Bob won " << bob_wins << "/" << run_times << " duels or " << (double)bob_wins / run_times * 100 << "%\n";
    cout << "Charlie won " << charlie_wins << "/" << run_times << " duels or " << (double)charlie_wins / run_times * 100 << "%\n";
}

/* pause between each segment of the program. pressing any key then enter will unpause the program*/
void press_enter_to_continue(void)
{
    cout << "Press any key then enter to continue...";
    cin.ignore().get(); // Pause Command for Linux Terminal
}

int main()
{
    // random seed
    srand(time(0));
    cout << "*** Welcome to Owen's Duel Simulator ***\n";
    test_at_least_two_alive();
    press_enter_to_continue();

    test_Aaron_shoots1();
    press_enter_to_continue();

    test_Bob_shoots();
    press_enter_to_continue();

    test_Charlie_shoots();
    press_enter_to_continue();

    test_Aaron_shoots2();
    press_enter_to_continue();

    cout << "Ready to test strategy 1 (run 10000 times):\n";
    press_enter_to_continue();
    cout << "\n";
    strategy1();
    cout << "\n";

    cout << "Ready to test strategy 2 (run 10000 times):\n";
    press_enter_to_continue();
    cout << "\n";
    strategy2();
    cout << "\n";

    if (Aaron1_wins > Aaron2_wins)
    {
        cout << "Strategy 1 is better than strategy 2.\n";
    }
    else
    {
        cout << "Strategy 2 is better than strategy 1.\n";
    }
}
