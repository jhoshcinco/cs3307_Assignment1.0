#include <Wt/WApplication.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WContainerWidget.h>
#include <vector>
#include <Wt/WBreak.h>
#include <string>
#include <cstdlib>
#include <ctime>


class WordleGame : public Wt::WApplication {
public:
    WordleGame(const Wt::WEnvironment& env);

private:
    std::string secretWord_;
    int attempts_;
    std::vector<std::string> wordList_;
    Wt::WContainerWidget *resultsContainer_;
    Wt::WLineEdit *guessInput_;
    Wt::WPushButton *submitBtn_;
    Wt::WText *statusText_;

    void loadWordList(const std::string& filename);
    std::string randomSecretWord();
    void restartGame();
    void checkGuess();
    void endGame(bool won);
};
