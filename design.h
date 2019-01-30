//
// Created by David Espley on 2019-01-27.
//

#ifndef BLUEMOON3_CARDS_H
#define BLUEMOON3_CARDS_H

#define MAX_PEOPLE      9
#define DECK_SIZE       30

using namespace std;
struct card
{
    /* Card values */
    int fire = -1;
    int earth = -1;

    /* Card type (character, support, etc) */
    int type;

    /* Card icons */
    unsigned int icons;

    /* Name of card */
    string name;

    /* Special text */
    string text;

    /* Special text priority */
    int special_prio;

    /* Special text category */
    int special_cat;

    /* Special text timing */
    int special_time;

    /* Special text effect */
    int special_effect;

    /* Special text value (usually amount of some sort) */
    int special_value;

    /* People card belongs to (different from deck they are found in) */
    int people;

    /* Index of card card in people */
    int index;

    /* Number of moons on card */
    int moons;

    /* Capacity of a ship */
    int capacity;

};
struct people
{
    /* Name of people */
    string name;

    /* Deck of card designs */
    vector<card> deck;

};

#endif //BLUEMOON3_CARDS_H
