#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <random>
#include <cctype>
#include <algorithm>

/**
 * Get a valid word from the list of words
 * @param words The list of words
 * @return A valid word
 */
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

/**
 * Display the difficulty of the word based on its length
 * @param wordDisplay The word to display
 */
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
  std::cout << ::visMan[lives] << '\n';
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
      (std::toupper((input[0])));
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

/**
 * Check if the guess is correct
 * @param word The word to guess
 * @param guess The letter to guess
 * @param usedLetters The set of used letters
 * @param wordLetters The set of word letters
 * @param lives The number of lives
 */
void checkGuess(const std::string &, const char guess,
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

/**
* Play the hangman game
*
* The game will randomly select a word from the list of words
* and the player will have to guess the word by guessing the letters
* in the word.
*/
void playHangman() {
  std::vector<std::string> words = {
    "APPLE", "BANANA", "ORANGE", "GRAPE", "STRAWBERRY", "WATERMELON",
    "CHOCOLATE", "COOKIE", "PIZZA", "PASTA", "HAMBURGER", "SANDWICH",
    "COMPUTER", "LAPTOP", "KEYBOARD", "MOUSE", "MONITOR", "PRINTER",
    "SUN", "MOON", "STAR", "PLANET", "GALAXY", "UNIVERSE",
    "CAT", "DOG", "BIRD", "ELEPHANT", "TIGER", "LION",
    "CAR", "BICYCLE", "MOTORCYCLE", "AIRPLANE", "TRAIN", "SHIP",
    "BOOK", "NOTEBOOK", "PEN", "PENCIL", "MARKER", "ERASER", "RULER",
    "SCHOOL", "TEACHER", "STUDENT", "UNIVERSITY", "COLLEGE", "CLASSROOM",
    "MUSIC", "GUITAR", "PIANO", "VIOLIN", "TRUMPET", "FLUTE",
    "BEACH", "MOUNTAIN", "FOREST", "JUNGLE", "RIVER", "OCEAN",
    "MOVIE", "PICTURE", "CAMERA", "VIDEO", "ACTOR", "ACTRESS",
    "SHIRT", "PANTS", "SHOES", "SOCKS", "HAT", "JACKET",
    "MONEY", "WALLET", "CREDIT CARD", "COIN", "DOLLAR", "EURO",
    "LOVE", "FRIEND", "FAMILY", "KISS", "HUG", "HEART",
    "LIFE", "DEATH", "TIME", "CLOCK", "HOUR", "MINUTE", "SECOND",
    "GAME", "PLAY", "FOOTBALL", "BASKETBALL", "BASEBALL", "TENNIS",
    "PHONE", "CALL", "MESSAGE", "TELEPHONE", "NUMBER", "SMARTPHONE",
    "TREE", "FLOWER", "GRASS", "LEAF", "ROOT", "BRANCH",
    "HOUSE", "DOOR", "WINDOW", "ROOF", "WALL", "FLOOR",
    "CHAIR", "TABLE", "LAMP", "LIGHT", "BED", "PILLOW",
    "LETTER", "ENVELOPE", "POSTCARD", "STAMP", "SEND", "RECEIVE",
    "WATER", "FIRE", "EARTH", "AIR", "WIND", "RAIN", "SNOW",
    "BREAKFAST", "LUNCH", "DINNER", "FOOD", "EAT", "DRINK",
    "ASTRONAUT", "ALIEN", "SPACESHIP", "PLANET", "STAR", "GALAXY",
    "DOCTOR", "NURSE", "HOSPITAL", "SICK", "MEDICINE", "HEALTH",
    "POLICE", "FIREFIGHTER", "SOLDIER", "ARMY", "NAVY", "AIR FORCE",
    "WEDDING", "BRIDE", "GROOM", "MARRY", "MARRIED", "MARRIAGE",
    "BIRTHDAY", "CAKE", "PARTY", "CELEBRATE", "PRESENT", "GIFT",
    "CHRISTMAS", "SANTA", "CLAUS", "REINDEER", "ELF", "PRESENT",
    "HALLOWEEN", "GHOST", "WITCH", "MONSTER", "VAMPIRE", "ZOMBIE",
    "THANKSGIVING", "TURKEY", "PILGRIM", "INDIAN", "MAYFLOWER", "FEAST",
    "EASTER", "EGG", "BUNNY", "RABBIT", "CHOCOLATE", "CANDY",
    "VALENTINE", "HEART", "CUPID", "LOVE", "SWEETHEART", "CHOCOLATE",
    "NEW YEAR", "PARTY", "CELEBRATE", "JANUARY", "MIDNIGHT", "COUNTDOWN",
    "ZEUS", "POSEIDON", "HADES", "ATHENA", "APOLLO", "ARES",
    "HERA", "APHRODITE", "HERMES", "ARTEMIS", "HEPHAESTUS", "HESTIA",
    "DEMETER", "DIONYSUS", "HERCULES", "PERSEUS", "ACHILLES", "PANDORA",
    "SPHINX", "MEDUSA", "PEGASUS", "CENTAUR", "MINOTAUR", "CERBERUS",
    "ATLAS", "PROMETHEUS", "ICARUS", "ODYSSEUS", "PENELOPE", "CIRCE",
    "THOR", "ODIN", "LOKI", "FREYJA", "FREYR", "TYR",
    "ACHILLES", "AGAMEMNON", "HELEN", "HECTOR", "PARIS", "PATROCLUS",
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
    std::string word = ::getValidWord(words);
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
      std::cout << ::visMan[lives] << '\n';
      std::cout << "You died, sorry. The word was " << word << '\n';
    } else {
      std::cout << "Nice! You guessed the word " << word << "!!" << '\n';
      ++guess;
    }

    std::cout << "Do you want to play again? (Y/N) ";
    char playAgain{};
    std::cin >> playAgain;
    playAgain = static_cast<char>(std::toupper(playAgain));

    if (playAgain != 'Y') {
      break;
    }

    ::clearconsole();
  }

  std::cout << "Thanks for playing!" << '\n';
  std::cout << "You guessed " << guess
            << " word(s) in total!" << '\n';
}

int main() {
  ::playHangman();
  return 0;
}