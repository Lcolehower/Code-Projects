// Rupee_Project_ColehowerLuke.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <algorithm>
using namespace std;

// Card structure
struct Card {
    string value;
    char suit;
    Card* next;
};
// Deck class
class Deck {
public:
    Card* top;

    Deck() {
        top = nullptr;
        initializeDeck();
    }
    void initializeDeck() {
        string values[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
        char suits[] = { 'S', 'C', 'H', 'D' };

        for (char suit : suits) {
            for (string value : values) {
                addCard(value, suit);
            }
        }
        shuffleDeck();
    }

    void addCard(string value, char suit) {
        Card* newCard = new Card{ value, suit, top };
        top = newCard;
    }

    void shuffleDeck() {
        srand(static_cast<unsigned int>(time(0)));
        vector<Card*> cards;
        Card* current = top;

        while (current) {
            cards.push_back(current);
            current = current->next;
        }

        // Randomly shuffle cards
        for (size_t i = 0; i < cards.size(); i++) {
            size_t j = rand() % cards.size();
            swap(cards[i], cards[j]);
        }

        // Rebuild deck
        top = nullptr;
        for (Card* card : cards) {
            card->next = top;
            top = card;
        }
    }

    Card* drawCard() {
        if (!top) return nullptr;
        Card* drawnCard = top;
        top = top->next;
        return drawnCard;
    }
};
// Discard River class
class DiscardRiver {
public:
    vector<Card*> river;

    void addCard(Card* card) {
        river.push_back(card);
    }

    void showRiver() {
        cout << "Discard River: ";
        for (Card* card : river) {
            cout << "[" << card->value << card->suit << "] ";
        }
        cout << endl;
    }
};
// Player class
class Player {
public:
    vector<Card*> hand;
    int score;

    Player() : score(0) {}

    void addCard(Card* card) {
        hand.push_back(card);
    }

    void showHand() {
        cout << "Hand: ";
        for (Card* card : hand) {
            cout << "[" << card->value << card->suit << "] ";
        }
        cout << endl;
    }

    int calculateCardValue(Card* card) {
        if (card->value == "A") return 15;
        else if (card->value == "10" || card->value == "J" || card->value == "Q" || card->value == "K") return 10;
        else return 5; // For cards 2-9
    }

    void layDownMatches() {
        unordered_map<string, vector<Card*>> valueMap;

        // Group cards by value
        for (Card* card : hand) {
            valueMap[card->value].push_back(card);
        }

        // Lay down matches of 3 or more
        for (auto& pair : valueMap) {
            if (pair.second.size() >= 3) {
                cout << "Laying down: ";
                for (Card* card : pair.second) {
                    cout << "[" << card->value << card->suit << "] ";
                    score += calculateCardValue(card); // Increment score based on matches
                }
                cout << endl;

                // Remove laid down cards from hand
                for (Card* card : pair.second) {
                    hand.erase(remove(hand.begin(), hand.end(), card), hand.end());
                }
            }
        }
    }

    bool isEmpty() {
        return hand.empty();
    }

    void checkForMatches() {
        unordered_map<string, vector<Card*>> valueMap;

        // Group cards by value
        for (Card* card : hand) {
            valueMap[card->value].push_back(card);
        }

        bool hasMatches = false;

        // Check for matches
        for (auto& pair : valueMap) {
            if (pair.second.size() >= 3) {
                hasMatches = true;
                cout << "Possible match: ";
                for (Card* card : pair.second) {
                    cout << "[" << card->value << card->suit << "] ";
                }
                cout << endl;
            }
        }

        if (!hasMatches) {
            cout << "No possible matches can be made.\n";
        }
    }

    int totalHandValue() {
        int total = 0;
        for (Card* card : hand) {
            total += calculateCardValue(card);
        }
        return total;
    }
};

// Game class
class Game {
private:
    Deck deck;
    DiscardRiver discardRiver;
    Player players[2];
    int currentPlayer;

public:
    Game() : currentPlayer(0) {
        dealCards();
    }

    void dealCards() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 7; j++) {
                players[i].addCard(deck.drawCard());
            }
        }
        // Add the top card of the deck to the discard river
        Card* topCard = deck.drawCard();
        discardRiver.addCard(topCard);
        cout << "Top card added to discard river: [" << topCard->value << topCard->suit << "]\n";
    }

    void play() {
        while (true) {
            Player& player = players[currentPlayer];
            player.showHand();
            discardRiver.showRiver();

            cout << "Player " << (currentPlayer + 1) << ", choose an action: \n1) Draw from Deck\n2) Draw from River\n> ";
            int action;
            cin >> action;

            Card* drawnCard = nullptr;
            if (action == 1) {
                drawnCard = deck.drawCard();
                if (drawnCard) {
                    cout << "Drawing from deck: [" << drawnCard->value << drawnCard->suit << "]\n";
                }
                else {
                    cout << "No more cards in the deck!\n";
                }
            }
            else if (action == 2) {
                if (!discardRiver.river.empty()) {
                    cout << "Choose a card from the river (0 to " << discardRiver.river.size() - 1 << "): ";
                    int riverIndex;
                    cin >> riverIndex;
                    if (riverIndex >= 0 && riverIndex < discardRiver.river.size()) {
                        drawnCard = discardRiver.river[riverIndex];
                        discardRiver.river.erase(discardRiver.river.begin() + riverIndex);
                        cout << "Drawing from river: [" << drawnCard->value << drawnCard->suit << "]\n";
                    }
                    else {
                        cout << "Invalid index. Drawing from deck instead.\n";
                        drawnCard = deck.drawCard();
                    }
                }
                else {
                    cout << "River is empty! Drawing from deck instead.\n";
                    drawnCard = deck.drawCard();
                }
            }

            if (drawnCard) {
                player.addCard(drawnCard);
                player.checkForMatches();  // Check for possible matches

                cout << "Do you want to lay down any matches? (Y/N): ";
                char layDownChoice;
                cin >> layDownChoice;

                if (layDownChoice == 'Y' || layDownChoice == 'y') {
                    player.layDownMatches();  // Attempt to lay down matches
                }
            }

            cout << "Do you want to discard a card? (Y/N): ";
            char discardChoice;
            cin >> discardChoice;

            if (discardChoice == 'Y' || discardChoice == 'y') {
                cout << "Enter the position of the card to discard (0 to " << player.hand.size() - 1 << "): ";
                int discardIndex;
                cin >> discardIndex;
                if (discardIndex >= 0 && discardIndex < player.hand.size()) {
                    Card* discardedCard = player.hand[discardIndex];
                    cout << "Discarding [" << discardedCard->value << discardedCard->suit << "]\n";
                    discardRiver.addCard(discardedCard);
                    player.hand.erase(player.hand.begin() + discardIndex);
                }
                else {
                    cout << "Invalid index. No card discarded.\n";
                }
            }

            // Check if player hand is empty
            if (player.isEmpty()) {
                cout << "Player " << (currentPlayer + 1) << " has discarded all their cards!\n";
                break; // End the game
            }

            // Switch to next player
            currentPlayer = (currentPlayer + 1) % 2;
        }
        // Final scoring and winner announcement
        cout << "Game over!\n";
        for (int i = 0; i < 2; i++) {
            cout << "Player " << (i + 1) << " score: " << players[i].score << endl;
            if (!players[i].isEmpty()) {
                cout << "Player " << (i + 1) << " loses points for remaining cards: " << players[i].totalHandValue() << endl;
                players[i].score -= players[i].totalHandValue(); 
            }
        }
    }
}; 
int main() {
    cout << "Welcome to Rupee! Ready to start? Y/N: ";
    char choice;
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        Game game;
        game.play();
    }
    else {
        cout << "Goodbye!\n";
    }

    return 0;
}

