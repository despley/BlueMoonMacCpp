//
// Created by David Espley on 2019-01-26.
//
#include <string>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include "CardHandler.h"
#include "Cards.h"


#ifndef DATADIR
#define DATADIR "."
#endif

using namespace std;

static char const *icon_name[15] =
        {
                "SHIELD_FIRE",
                "SHIELD_EARTH",
                "STOP",
                "RETRIEVE",
                "PAIR",
                "FREE",
                "PROTECTED",
                "GANG_COOL",
                "GANG_TOP",
                "GANG_FUN",
                "GANG_NO",
                "BLUFF_FIRE",
                "BLUFF_EARTH",
                "BLUFF_NONE",
                nullptr
        };
static char const *effect_name[9][32] =
        {
                /* Category zero doesn't exist */
                {
                        nullptr,
                },

                /* Category one */
                {
                        "IGNORE",
                        "INCREASE",
                        "ONE_CHAR",
                        "ALL_CHAR",
                        "ONE_SUPPORT",
                        "ALL_SUPPORT",
                        "ONE_BOOSTER",
                        "ALL_BOOSTER",
                        "CATERPILLAR",
                        "WITH_ICONS",
                        "LEADERSHIP",
                        "BLUFF",
                        "ALL_CARDS",
                        "TOTAL_POWER",
                        "TOTAL_FIRE",
                        "TOTAL_EARTH",
                        "FIRE_VAL",
                        "EARTH_VAL",
                        "ODD_VAL",
                        "EVEN_VAL",
                        "SPECIAL",
                        "ICONS_ALL",
                        "ICONS_BUT_SP",
                        "ICONS_BUT_S",
                        "BY_FACTOR",
                        "TO_VALUE",
                        "BY_VALUE",
                        "TO_SUM",
                        "TO_HIGHER",
                        "EXCEPT_FLIT",
                        nullptr,
                },

                /* Category two */
                {
                        "I_RETREAT",
                        "YOU_RETREAT",
                        "ADDITIONAL",
                        "FEWER",
                        "EXACTLY",
                        "NO_MORE_THAN",
                        nullptr,
                },

                /* Category three */
                {
                        "YOU_MAY_NOT",
                        "I_MAY_PLAY",
                        "ADDITIONAL",
                        "MORE_THAN",
                        "DRAW",
                        "TAKE",
                        "CALL_BLUFF",
                        "CHARACTER",
                        "SUPPORT",
                        "BOOSTER",
                        "LEADERSHIP",
                        "COMBAT",
                        "HAVE_SPECIAL",
                        "NO_SPECIAL",
                        "WITH_VALUE",
                        "AS_FREE",
                        "SHIP_HAND",
                        nullptr,
                },

                /* Category four */
                {
                        "DRAW",
                        "DISCARD",
                        "RETRIEVE",
                        "REVEAL",
                        "SEARCH",
                        "UNDRAW_2",
                        "SHUFFLE",
                        "LOAD",
                        "YOUR_HAND",
                        "YOUR_CHAR",
                        "YOUR_BOOSTER",
                        "YOUR_SUPPORT",
                        "YOUR_DECK",
                        "MY_CHAR",
                        "MY_BOOSTER",
                        "MY_SUPPORT",
                        "MY_HAND",
                        "MY_DISCARD",
                        "NOT_LAST_CHAR",
                        "WITH_ICON",
                        "ACTIVE",
                        "DISCARD_ONE",
                        "RANDOM_DISCARD",
                        "TO",
                        "ATTACK_AGAIN",
                        "ON_BOTTOM",
                        "OPTIONAL",
                        "IF_FROM_SHIP",
                        "ALL",
                        "EITHER",
                        nullptr,
                },

                /* Category five */
                {
                        "PLAY_ONLY_IF",
                        "PLAY_FREE_IF",
                        "FIRE_POWER",
                        "EARTH_POWER",
                        "EITHER_POWER",
                        "YOU_ACTIVE",
                        "YOU_PLAYED",
                        "MY_PLAYED",
                        "MY_INFLUENCE",
                        "YOU_CHARACTER",
                        "YOU_BOOSTER",
                        "YOU_SUPPORT",
                        "YOU_ICONS",
                        "YOU_DRAGONS",
                        "YOU_HANDSIZE",
                        "ELEMENT_SWAP",
                        nullptr,
                },

                /* Category six */
                {
                        "DISCARD",
                        "STORM",
                        "FIRE_VALUE",
                        "EARTH_VALUE",
                        "CHAR",
                        nullptr,
                },

                /* Category seven */
                {
                        "PLAY_SUPPORT",
                        "PLAY_BOOSTER",
                        "DISCARD_FIRE",
                        "DISCARD_EARTH",
                        "DISCARD_BOTH",
                        "DISCARD_EITHER",
                        "DISCARD_CHAR",
                        "CATERPILLAR",
                        "FLOOD",
                        "OR_RETREAT",
                        "OR_DRAGON",
                        nullptr,
                },

                /* Category eight */
                {
                        "YOU_DISCARD",
                        "YOU_DISCLOSE",
                        "TO",
                        "OPTIONAL",
                        nullptr,
                },
        };

string trim(string& str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

static int lookup_effect(char *ptr, int cat)
{
    int i = 0;

    /* Loop over effects */
    while (effect_name[cat][i])
    {
        /* Check this effect */
        if (!strcmp(effect_name[cat][i], ptr)) return 1 << i;

        /* Next effect */
        i++;
    }

    /* No effect found */
    printf(("No effect matching '%s'!\n"), ptr);
    exit(1);
}



vector<people> read_cards()
{

    vector<people> peoples;

    ifstream configFile;
    string configLine;
    string configValue;

    configFile.open("cards.txt");


    /* Loop over entire file */
    while (!configFile.eof())
    {

        getline(configFile, configLine);
        if (configLine.empty() || configLine.front() == '#') {
            continue;
        }


        /* Switch of type of line */
        if (configLine.front() == 'P') {
            /* New people */
            people peopleInstance;
            peopleInstance.name = configLine.substr(2, configLine.length());
            peoples.push_back(peopleInstance);
            continue;
        }
                /* New card */
        if(configLine.front() == 'N') {
            card cc;
            cc.name = configLine.substr(2, configLine.length());
            peoples.back().deck.push_back(cc);
            continue;
        }
        if(configLine.front() == 'V') {
            istringstream stringStream(configLine.substr(2, configLine.length()));
            getline(stringStream, configValue, ':');
            peoples.back().deck.back().fire = stoi(configValue);
            getline(stringStream, configValue, ':');
            peoples.back().deck.back().earth = stoi(configValue);
            continue;
         }
        if(configLine.front() == 'T') {
            peoples.back().deck.back().type = stoi(configLine.substr(2, configLine.length()));
            continue;
        }
        if(configLine.front() == 'F') {
            istringstream stringStream(configLine.substr(2, configLine.length()));
            unsigned int i;
            while(getline(stringStream, configValue, '|'))
            {
                configValue = trim(configValue);
                for(i = 0; icon_name[i]; i++)
                {
                    if((string) icon_name[i] == configValue)
                    {
                        unsigned int j = peoples.back().deck.back().icons;
                        j |= 1 << i;
                        peoples.back().deck.back().icons |= j;
                        cout << peoples.back().deck.back().icons << endl;
                    }
                }
            }
            continue;
        }
        if(configLine.front() == 'C') {
            peoples.back().deck.back().capacity = stoi(configLine.substr(2, configLine.length()));
            continue;
        }
    }

    /* Close card card file */
    configFile.close();
    return peoples;
}

