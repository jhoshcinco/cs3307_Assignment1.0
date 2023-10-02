#include "WordleGame.h"



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
            result += "?";
        } else {
            style.setForegroundColor(Wt::WColor("grey"));
            result += ".";
        }
        letterText->setDecorationStyle(style);
        guessInput_->setText("");
    }
//    resultsContainer_->addWidget(std::make_unique<Wt::WText>(result + "<br/>"));

    if (result == secretWord_) {
        endGame(true);
    } else if (attempts_ >= 6) {
        endGame(false);
    }
}





void WordleGame::endGame(bool won) {
    submitBtn_->disable();
    if (won) {
        statusText_->setText("Congratulations! You've guessed the word!");
    } else {
        statusText_->setText("Sorry! The correct word was: " + secretWord_);
    }
    submitBtn_->setText("Restart Game");
    submitBtn_->enable();
    submitBtn_->clicked().connect(this, &WordleGame::restartGame);

}
void WordleGame::restartGame(){
    submitBtn_->setText("Submit Guess");
    secretWord_ = randomSecretWord();
    attempts_ = 0;
    resultsContainer_->clear();
    statusText_->setText(" ");
//    guessInput_->setText(" ");
    submitBtn_->clicked().connect(this, &WordleGame::checkGuess);
}
