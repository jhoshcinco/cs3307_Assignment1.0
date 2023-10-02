#include "WordleGame.h"



WordleGame::WordleGame(const Wt::WEnvironment& env):
    Wt::WApplication(env),
    secretWord_("apple"),
    attempts_(0) {
    loadWordList("C:\\Users\\Jhosh\\CLionProjects\\cs3307_Assignment1.0\\words.txt");
//    secretWord_= randomSecretWord();
    setTitle("Wordle Game");



    resultsContainer_ = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    guessInput_ = root()->addWidget(std::make_unique<Wt::WLineEdit>());
    submitBtn_ = root()->addWidget(std::make_unique<Wt::WPushButton>("Submit Guess"));
    statusText_ = root()->addWidget(std::make_unique<Wt::WText>());

    submitBtn_->clicked().connect(this, &WordleGame::checkGuess);
}

void WordleGame::loadWordList(const std::string &filename) {
    std::ifstream file(filename);
    if(!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }
    std::string word;
    while(std::getline(file, word)) {
        wordList_.push_back(word);
    }
    std :: cout << wordList_.size() << std::endl;
    file.close();
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
    auto resultContainer = resultsContainer_->addWidget(std::make_unique<Wt::WContainerWidget>());

    std::string guess = guessInput_->text().toUTF8();
    if (guess.length() != secretWord_.length()) {

        statusText_->setText("Please enter a 5-letter word.");
        return;
    }
    attempts_++;
//    guessResults(guess);
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


}
