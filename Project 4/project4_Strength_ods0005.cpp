/* project4_Strength_ods0005.cpp
 * Owen Strength
 * 10/27/2023
 *
 * complied using g++
 * This program is a trivia game that asks the user questions and keeps track of their score.
 * The program uses a linked list to store the triviaNodes
 * The program uses a triviaNode class to store the question, answer, points, and next node
 * The program also uses conditional compilation to run unit tests. (Look in the main function to see how to run the game)
 * The program also allows the user to add questions to the linked list at the beginning of the game.
 *
 * References:
 * Hints provided by Dr. Li on Canvas in the Project Description
 */

#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// triviaNode class
class triviaNode
{
public:
    string question;
    string answer;
    int points;
    triviaNode *next;
};

static int questionsAsked = 0;

// add node to linked list
void addNode(triviaNode *head, string question, string answer, int points)
{
    triviaNode *newNode = new triviaNode;
    newNode->question = question;
    newNode->answer = answer;
    newNode->points = points;
    newNode->next = NULL;

    triviaNode *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

// initialize head node of linked list and add 3 questions
void initialize(triviaNode *head)
{
    head->question = "How long was the shortest war on record? (Hint: how many minutes)";
    head->answer = "38";
    head->points = 100;
    head->next = NULL;

    addNode(head, "What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)", "Bank of Italy", 50);
    addNode(head, "What is the best-selling video game of all time? (Hint: Call of Duty or Wii Sports)", "Wii Sports", 20);
}

// add question to linked list
void addQuestion(triviaNode *head)
{
    string question;
    cout << "Enter a question: ";
    getline(cin, question);
    string answer;
    cout << "Enter an answer: ";
    getline(cin, answer);
    int points;
    cout << "Enter award points: ";
    cin >> points;
    addNode(head, question, answer, points);
}

// count number of nodes in linked list
int countNodes(triviaNode *head)
{
    triviaNode *current = head;
    int count = 0;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

// ask question and return score -1 if numQuestions is 0, -2 if numQuestions is greater than number of questions in linked list
int askQuestions(triviaNode *head, int numQuestions)
{
    triviaNode *current = head;
    int score = 0;
    questionsAsked = 0;
    if (numQuestions == 0)
    {
        cout << "Warning - The number of trivia to be asked must equal to or be larger than 1." << endl;
        return -1;
    }
    if (numQuestions > countNodes(head))
    {
        cout << "Warning - There are only " << countNodes(head) << " trivia in the list." << endl;
        return -2;
    }
    for (int i = 0; i < numQuestions; i++)
    {
        cout << "Question: " << current->question << endl;
        string answer;
        cout << "Answer: ";
        cin.clear();
        // answer needs to be the whole string not the first word
        getline(cin, answer);
        if (answer == current->answer)
        {
            cout << "Your answer is correct. You receive " << current->points << " points." << endl;
            score += current->points;
        }
        else
        {
            cout << "Your answer is wrong. The correct answer is: " << current->answer << endl;
        }
        cout << "Your total points: " << score << endl;
        cout << endl;
        current = current->next;
        questionsAsked++;
    }
    return score;
}

// UNIT TESTS
void unitTest1()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "Unit Test Case 1: Ask no questions. The program should give a warning message." << endl;
    assert(askQuestions(head, 0) == -1);
    cout << "Case 1 Passed" << endl;
    cout << endl;
}

void unitTest2()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
    assert(askQuestions(head, 1) == 0);
    cout << "Case 2.1 Passed" << endl;
    cout << endl;

    cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
    assert(askQuestions(head, 1) == 100);
    cout << "Case 2.2 Passed" << endl;
    cout << endl;
}

void unitTest3()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "Unit Test Case 3: Ask all the questions of the last trivia in the linked list" << endl;
    askQuestions(head, countNodes(head));
    assert(questionsAsked == 3);
    cout << "Case 3 Passed" << endl;
    cout << endl;
}

void unitTest4()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "Unit Test Case 4: Ask 5 questions in the linked list." << endl;
    assert(askQuestions(head, 5) == -2);
    cout << "Case 4 Passed" << endl;
    cout << endl;
}

// DRIVER
void testDriver()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "*** This is a debug version ***" << endl;
    unitTest1();
    unitTest2();
    unitTest3();
    unitTest4();
    cout << "*** End of the Debug Version ***" << endl;
}

// asks user to add questions to linked list at the beginning of the game
void gameStartup(triviaNode *head)
{
    bool createQuestion = true;
    while (createQuestion)
    {
        addQuestion(head);
        cout << "Continue? (Yes/No): ";
        string response;
        cin >> response;
        if (response == "No" || response == "no")
        {
            createQuestion = false;
        }
        cin.ignore();
    }
}

// Main Game
void TriviaGame()
{
    triviaNode *head = new triviaNode;
    initialize(head);

    cout << "*** Welcome to Owen's trivia quiz game ***" << endl;
    gameStartup(head);
    cout << endl;
    askQuestions(head, countNodes(head));

    cout << "Thank you for playing the trivia quiz game. Goodbye!" << endl;
}

// main function using conditional compilation
int main()
{
#define UNIT_TESTING // Comment out this line to run the game else run testing
#ifdef UNIT_TESTING
    testDriver();
#else
    TriviaGame();
#endif
}
