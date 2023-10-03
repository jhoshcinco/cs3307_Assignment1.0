/*
 * WordleGame :simple wordle made using wt framework
 * @author Jhoshcinco
 * @version 10-02-2023
 */
#include "WordleGame.h"
#include <Wt/WServer.h>

int main(int argc, char **argv) {
    try {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
        server.addEntryPoint(Wt::EntryPointType::Application, [](const Wt::WEnvironment& env) {
            return std::make_unique<WordleGame>(env);
        });
        server.run();
    } catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}
