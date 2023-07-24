#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <random>
#include <cctype>

namespace random {
  std::string getValidWord(const std::vector<std::string> &words) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::string word;

    do {
      word = words[gen() % words.size()];
    } while ((word.find('-') != std::string::npos)
    || (word.find(' ') != std::string::npos));

    return word;
  }
}

namespace visuals {
  std::map<int, std::string> visMan = {
    {0, R"(
                ___________
               | /        |
               |/        ( )
               |          |
               |         / \
               |
           )"},
    {1, R"(
                ___________
               | /        |
               |/        ( )
               |          |
               |         /
               |
            )"},
    {2, R"(
                ___________
               | /        |
               |/        ( )
               |          |
               |
               |
            )"},
    {3, R"(
                ___________
               | /        |
               |/        ( )
               |
               |
               |
            )"},
    {4, R"(
                ___________
               | /        |
               |/
               |
               |
               |
            )"},
    {5, R"(
                ___________
               | /
               |/
               |
               |
               |
            )"},
    {6, R"(
                ___________
               |
               |
               |
               |
               |
            )"}
  };
}

inline namespace {
  void displayDifficulty(const std::string_view &wordDisplay) {
    const int hard = 12;
    const int medium = 8;
    if (wordDisplay.length() > hard) {
      std::cout << "Difficulty: Hard" << '\n';
    } else if (wordDisplay.length() > medium) {
      std::cout << "Difficulty: Medium" << '\n';
    } else {
      std::cout << "Difficulty: Easy" << '\n';
    }
  }

  void displayVisual(const int lives) {
    std::cout << visuals::visMan[lives] << '\n';
  }

  void displayWord(const std::string &word,
                   const std::set<char> &usedLetters) {
    std::string wordDisplay;
    for (const char &letter: word) {
      if (usedLetters.count(letter) > 0) {
        wordDisplay += letter;
      } else {
        wordDisplay += '-';
      }
      wordDisplay += " ";
    }

    std::cout << "Current word: " << wordDisplay << '\n';
  }

  char getUserGuess() {
    char userLetter{};
    std::string input;

    while (true) {
      std::cout << "Guess a letter: ";
      std::cin >> input;

      if (1 == input.length()) {
        userLetter = static_cast<char>
          (std::toupper(static_cast<char>(input[0])));
        if (std::isalpha(userLetter)) {
          break;
        }
      }
      std::cout << "\nInvalid input! Please enter a single letter.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return userLetter;
  }

  [[nodiscard]] bool isValidGuess(const std::set<char> &alphabet,
                                  const char guess) {
    return alphabet.count(guess) > 0;
  }

  void checkGuess(const std::string_view &, const char guess,
                  std::set<char> &usedLetters, std::set<char> &wordLetters,
                  int &lives) {
    if (wordLetters.count(guess) > 0) {
      wordLetters.erase(guess);
    } else {
      --lives;
      std::cout << "\nYour letter, " << guess
      << ", is not in the word." << '\n';
    }
    usedLetters.insert(guess);
  }

  void clearconsole() {
    std::cout << "\033[2J\033[1;1H";
  }

  void playHangman() {
    std::vector<std::string> words = {
      "apple", "banana", "orange", "grape", "strawberry", "watermelon",
      "chocolate", "cookie", "pizza", "pasta", "hamburger", "sandwich",
      "computer", "laptop", "keyboard", "mouse", "monitor", "printer",
      "sun", "moon", "star", "planet", "galaxy", "universe",
      "cat", "dog", "bird", "elephant", "tiger", "lion",
      "car", "bicycle", "motorcycle", "airplane", "train", "ship",
      "book", "notebook", "pen", "pencil", "marker", "eraser", "ruler",
      "school", "teacher", "student", "university", "college", "classroom",
      "music", "guitar", "piano", "violin", "trumpet", "flute",
      "beach", "mountain", "forest", "jungle", "river", "ocean",
      "movie", "picture", "camera", "video", "actor", "actress",
      "shirt", "pants", "shoes", "socks", "hat", "jacket",
      "money", "wallet", "credit card", "coin", "dollar", "euro",
      "love", "friend", "family", "kiss", "hug", "heart",
      "life", "death", "time", "clock", "hour", "minute", "second",
      "game", "play", "football", "basketball", "baseball", "tennis",
      "phone", "call", "message", "telephone", "number", "smartphone",
      "tree", "flower", "grass", "leaf", "root", "branch",
      "house", "door", "window", "roof", "wall", "floor",
      "chair", "table", "lamp", "light", "bed", "pillow",
      "letter", "envelope", "postcard", "stamp", "send", "receive",
      "water", "fire", "earth", "air", "wind", "rain", "snow",
      "breakfast", "lunch", "dinner", "food", "eat", "drink",
      "astronaut", "alien", "spaceship", "planet", "star", "galaxy",
      "doctor", "nurse", "hospital", "sick", "medicine", "health",
      "police", "firefighter", "soldier", "army", "navy", "air force",
      "wedding", "bride", "groom", "marry", "married", "marriage",
      "birthday", "cake", "party", "celebrate", "present", "gift",
      "christmas", "santa", "claus", "reindeer", "elf", "present",
      "halloween", "ghost", "witch", "monster", "vampire", "zombie",
      "thanksgiving", "turkey", "pilgrim", "indian", "mayflower", "feast",
      "easter", "egg", "bunny", "rabbit", "chocolate", "candy",
      "valentine", "heart", "cupid", "love", "sweetheart", "chocolate",
      "new year", "party", "celebrate", "january", "midnight", "countdown",
      "asgard", "midgard", "valhalla", "thor", "loki", "odin",
      "zeus", "poseidon", "hades", "athena", "apollo", "ares",
      "aladdin", "jasmine", "genie", "jafar", "abu", "carpet",
    };

    // Transform the words to uppercase for easier comparison
    std::transform(words.begin(), words.end(), words.begin(),
                   [](std::string &word) {
                     for (char &c: word) {
                       c = static_cast<char>(std::toupper(c));
                     }
                     return word;
                   });

    std::set<char> alphabet;
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
      alphabet.insert(ch);
    }

    int guess = 0;

    while (true) {
      std::string word = random::getValidWord(words);
      std::set<char> wordLetters(word.begin(), word.end());
      std::set<char> usedLetters;
      int lives = 7;

      std::cout << "You are starting a new game!\n";

      while ((!wordLetters.empty()) && (lives > 0)) {
        std::cout << "You have " << lives
                  << " lives left and you have used these letters: ";
        for (const char &letter: usedLetters) {
          std::cout << letter << " ";
        }
        std::cout << '\n';

        ::displayDifficulty(word);

        ::displayVisual(lives);

        ::displayWord(word, usedLetters);

        char userGuess = ::getUserGuess();

        while (!::isValidGuess(alphabet, userGuess)) {
          std::cout << "\nThat is not a valid letter. Guess another letter: ";
          userGuess = ::getUserGuess();
        }

        if (usedLetters.count(userGuess) > 0) {
          std::cout << "\nYou have already used that letter. "
                       "Guess another letter." << '\n';
        } else {
          ::checkGuess(word, userGuess, usedLetters, wordLetters, lives);
        }
      }

      if (0 == lives) {
        std::cout << visuals::visMan[lives] << '\n';
        std::cout << "You died, sorry. The word was " << word << '\n';
      } else {
        std::cout << "Nice! You guessed the word " << word << "!!" << '\n';
        ++guess;
      }

      std::cout << "Do you want to play again? (Y/N) ";
      char playAgain{};
      std::cin >> playAgain;
      playAgain = std::toupper(playAgain);

      if (playAgain != 'Y') {
        break;
      }

      ::clearconsole();
    }

    int rounds{};
    rounds++;

    std::cout << "Thanks for playing!" << '\n';
    std::cout << "You guessed " << guess << "/" << rounds << " word(s) in total!" << '\n';
  }
}

  int main() {
    ::playHangman();
    return 0;
  }

