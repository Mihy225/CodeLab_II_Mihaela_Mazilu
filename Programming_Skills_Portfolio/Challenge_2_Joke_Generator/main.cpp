#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

// AI-assisted example developed with OpenAI ChatGPT.
// Demonstrates file handling, random selection and user interaction.

struct Joke {
    std::string question;
    std::string answer;
};
// Read jokes from the supplied text file
bool readJokes(const std::string& filename, std::vector<Joke>& jokes) {
    std::ifstream input(filename);

    if (!input) {
        std::cerr << "Unable to open: " << filename << "\n";
        return false;
    }
    std::string line;

    while (std::getline(input, line)) {
        std::size_t position = line.find('?');

        if (position == std::string::npos) {
            continue;
        }

        std::string question = line.substr(0, position + 1);
        std::string answer = line.substr(position + 1);

        if (!question.empty() && !answer.empty()) {
            jokes.push_back({question, answer});
        }
    }

    return !jokes.empty();
}
// Choose and present a randomly selected joke
void presentJoke(const std::vector<Joke>& jokes,
                 std::mt19937& engine) {
    std::uniform_int_distribution<std::size_t> pick(
        0, jokes.size() - 1
    );

    const Joke& selected = jokes[pick(engine)];

    std::cout << "\nAlexa: " << selected.question << "\n";
    std::cout << "Press Enter for the punchline...";

    std::string response;
    std::getline(std::cin, response);

    std::cout << "Alexa: " << selected.answer << "\n\n";
}

// Main programme
int main() {
    std::vector<Joke> jokes;

    if (!readJokes("randomJokes.txt", jokes)) {
        std::cerr << "No valid jokes found in the dataset.\n";
        return 1;
    }

    std::random_device seed;
    std::mt19937 engine(seed());

    std::cout << "================================\n";
    std::cout << "       ALEXA JOKE ASSISTANT\n";
    std::cout << "================================\n";
    std::cout << "Say: Alexa, tell me a joke\n";
    std::cout << "Type: quit to close\n\n";

    std::string command;
    bool running = true;

    while (running) {
        std::cout << "You: ";

        if (!std::getline(std::cin, command)) {
            break;
        }

        if (command == "Alexa, tell me a joke") {
            presentJoke(jokes, engine);
        }
        else if (command == "quit") {
            std::cout << "Alexa: Goodbye!\n";
            running = false;
        }
        else {
            std::cout << "Alexa: I did not understand that.\n";
            std::cout << "Please try the suggested command.\n\n";
        }
    }
    return 0;
}