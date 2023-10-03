/*
 * WordleGame :simple wordle made using wt framework
 * @author Jhoshcinco
 * @version 10-02-2023
 */
#include "WordleGame.h"


/**
 * Constructor for the WordleGame class,Initializes the values of the game
 * @param env Wt::WEnvironment object
 */
WordleGame::WordleGame(const Wt::WEnvironment& env):
    Wt::WApplication(env),
    secretWord_(),
    attempts_(0) {
    wordList_={"apple","brain","chair","drink","earth","fruit","glass","heart","index","juice"};
    setTitle("Wordle Game");
    secretWord_ = randomSecretWord();



    resultsContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    guessInput_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    submitBtn_ = root()->addWidget(std::make_unique<Wt::WPushButton>("Submit Guess"));
    statusText_ = root()->addWidget(std::make_unique<Wt::WText>());

    submitBtn_->clicked().connect(this, &WordleGame::checkGuess);
    guessInput_->enterPressed().connect(std::bind(&WordleGame::checkGuess, this));
}

/*
 * @brief selects a random word from the WordList
 * @return the secret word
 */
std::string WordleGame::randomSecretWord() {
    if (wordList_.empty()){
        std::cerr << "Error: word list is empty" << std::endl;
         return "";
    }
    std::srand(std::time(nullptr));
    int index = std::rand() % wordList_.size();
    std::string word = wordList_[index];
    std:: cout << word <<"this is a secret word" << std::endl;
    return word;





}
/*
 * @brief checks if the guess matches the secret word
 *
 * updates the ui to to show results by changing the colors of the letters in the guess.
 * green = correct letter in correct position
 * red = correct letter in wrong position
 * grey = incorrect letter
 */
void WordleGame::checkGuess() {
    statusText_->setText("");
    auto resultContainer = resultsContainer_->addWidget(std::make_unique<Wt::WContainerWidget>());

    std::string guess = guessInput_->text().toUTF8();
    if (guess.length() != secretWord_.length()) {

        statusText_->setText("Please enter a 5-letter word.");
        guessInput_->setText("");
        return;
    }
    attempts_++;
    std::string result;
    for (size_t i = 0; i < secretWord_.length(); ++i) {
        auto letterText = resultContainer->addWidget(std::make_unique<Wt::WText>(std::string(1,guess[i])));
        Wt::WCssDecorationStyle style;
        if (guess[i] == secretWord_[i]) {
            style.setForegroundColor(Wt::WColor("green"));
            result += guess[i];
        } else if (secretWord_.find(guess[i]) != std::string::npos) {
            style.setForegroundColor(Wt::WColor("red"));
        } else {
            style.setForegroundColor(Wt::WColor("grey"));
        }
        letterText->setDecorationStyle(style);
        guessInput_->setText("");
    }
    if (result == secretWord_) {
        endGame(true);
    } else if (attempts_ >= 6) {
        endGame(false);
    }
}




/*
 * @brief ends the game
 * reflects the results of the game in the ui. if won,it updates the status text to won
 * if lost,it updates the status text to lost and shows the secret word
 * changes guess button to restart
 * @param won true or false. if player won or not
 *
 *
 */
void WordleGame::endGame(bool won) {
    submitBtn_->disable();
    if (won) {
        statusText_->setText("Congratulations! You've guessed the word!");
        guessInput_->disable();
    } else {
        statusText_->setText("Sorry! The correct word was: " + secretWord_);
        guessInput_->disable();
    }
    submitBtn_->setText("Restart Game");
    submitBtn_->enable();
    submitBtn_->clicked().connect(this, &WordleGame::restartGame);

}
/*
 * @brief restarts the game
 * resets the ui and the variable to their initial value
 */
void WordleGame::restartGame(){
    submitBtn_->setText("Submit Guess");
    guessInput_->enable();
    secretWord_ = randomSecretWord();
    attempts_ = 0;
    resultsContainer_->clear();
    statusText_->setText(" ");
    submitBtn_->clicked().connect(this, &WordleGame::checkGuess);
}
