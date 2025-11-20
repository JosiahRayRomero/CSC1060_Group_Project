#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

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

    // Declarations for randomization
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist;
   
    // Obtains quiz name
    cout << "Enter the subject of your flashcards: ";
    getline(cin, subject);

    // Creates an indefnite amount of flashcards
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

    // Quiz start
    cout << "\n" << subject << " Quiz\n";
    continueQuiz = 'y';

    while (continueQuiz == 'y' || continueQuiz == 'Y') {
        dist = uniform_int_distribution<int>(0, questions.size() - 1);
        qIndex = dist(rng);
        cout << "\nQuestion: " << questions[qIndex] << endl;

        options.clear();
        options.push_back(qIndex);

        while (options.size() < 4 && options.size() < questions.size()) {
            randIndex = dist(rng);
            if (find(options.begin(), options.end(), randIndex) == options.end()) {
                options.push_back(randIndex);
            }
        }

        shuffle(options.begin(), options.end(), rng);

        for (size_t i = 0; i < options.size(); ++i) {
            cout << i + 1 << ". " << answers[options[i]] << endl;
        }

        correct = false;
        while (!correct) {
            cout << "Your choice (1-" << options.size() << "): ";
            cin >> userChoice;

            if (userChoice >= 1 && userChoice <= options.size()) {
                if (answers[options[userChoice - 1]] == answers[qIndex]) {
                    cout << "Correct!! \n";
                    correct = true;
                }
                else {
                    cout << "Incorrect. Try again. \n";
                }
            }
            else {
                cout << "Invalid choice. Enter 1-" << options.size() << ".\n";
            }
        }

        cout << "Continue quiz? (y/n): ";
        cin >> continueQuiz;
        cin.ignore();
    }

    cout << "\nThanks for studying!" << endl; //Adjust
    return 0;
}