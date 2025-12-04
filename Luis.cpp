#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // still needed for swap
#include <ctime>      // for time()
using namespace std;


void displayOptions(vector<int>& options,vector<string>& answers);

int main() {
    // Declarations
    string subject;
    vector<string> questions;
    vector<string> answers;
    string tempQuestion;
    string tempAnswer;
    char addMore;
    char continueQuiz;
    int qIndex;
    int randIndex;
    int userChoice;
    vector<int> options;
    bool correct;

    //seeding RNG
    srand(time(NULL));

    //gets us a subject for our flashcards
    cout << "Enter the subject of your flashcards: ";
    getline(cin, subject);

    //process to add flashcards to the vector using .push_back
    cout << "Create your flashcards:\n";

    addMore = 'y';
    while (addMore == 'y' || addMore == 'Y') {
        cout << "\nEnter a question: ";
        getline(cin, tempQuestion);
        cout << "Enter the answer: ";
        getline(cin, tempAnswer);

        questions.push_back(tempQuestion);
        answers.push_back(tempAnswer);

        cout << "Add another flashcard? (y/n): ";
        cin >> addMore;
        cin.ignore();
    }

    //actually starts the quiz process 
    cout << "\n" << subject << " Quiz\n";
    continueQuiz = 'y';

    while (continueQuiz == 'y' || continueQuiz == 'Y') {

        //uses a randomzer to pick the flashcard in the vector
        qIndex = rand() % questions.size();

        cout << "\nQuestion: " << questions[qIndex] << endl;

        // clears out the options, then creates a list of options
        options.clear();
        options.push_back(qIndex); //this simply inserts correct answer first

        //randomizes our incorrect answers, so that the user doesn't memorize which specific slot is correct, but rather the answer itself
        while (options.size() < 4 && options.size() < questions.size()) {
            randIndex = rand() % questions.size(); //picks a random flashcard
            if (find(options.begin(), options.end(), randIndex) == options.end()) { //this checks to make sure its not going to put the same incorrect answer in twice, or the same orrect answer in
                options.push_back(randIndex);// if we dont have it in yet, add it
            }
        }

        // shuffles the code using rand again
        for (int i = options.size() - 1; i > 0; --i) {
          int j = rand() % (i + 1);
          swap(options[i], options[j]);//using the default c++ swap
}

        displayOptions(options, answers); // runs display function

        //loops until we get a correct answer
        correct = false;
        while (!correct) {
            cout << "Your choice (1-" << options.size() << "): ";
            cin >> userChoice;

            if (userChoice >= 1 && userChoice <= options.size()) {
                if (answers[options[userChoice - 1]] == answers[qIndex]) {
                    cout << "Correct!! \n";
                    correct = true;
                } else {
                    cout << "Incorrect. Try again." << endl;;
                }
            } else {
                cout << "Invalid choice. Enter 1-" << options.size() << endl;
            }
        }

        cout << "Continue quiz? (y/n): ";
        cin >> continueQuiz;
        cin.ignore();
    }

    cout << "\nThanks for studying!" << endl;
    return 0;
}

void displayOptions(vector<int>& options,vector<string>& answers) {
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << answers[options[i]] << endl;
    }
}