#include <iostream>
#include <vector>
#include "Cards.h"
#include "CardHandler.h"

int main() {
    vector<people> peeps;
    read_cards(&peeps);
    for(int y=0; y<peeps.size(); y++) {
        std::cout << peeps[y].name << std::endl;
        vector<card> deck = peeps[y].deck;
        std::cout << "Deck size: " << deck.size()<< std::endl;
        for(int z=0; z<deck.size();z++)
        {
            std::cout << "\tname: " << deck[z].name << endl;
            std::cout << "\tearth: " << deck[z].earth << endl;
            std::cout << "\tfire: " << deck[z].fire << endl;
            std::cout << "\ttype: " << deck[z].type << endl;
            std::cout << "\ticons: " << deck[z].icons << endl;
            string s = deck[z].text;
            if(!s.empty())
                std::cout << "\tSpecial Text: " << s << endl;
            std::cout << "\tShip Capacity: " << deck[z].capacity << endl;
        }
    }
    return 0;
}