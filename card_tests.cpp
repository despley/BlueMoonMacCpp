#include <boost/test/unit_test.hpp>
#include "Cards.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(Accepts_Command_Chain) {

    std::vector<people> peoples;

    peoples.push_back(people("graham"));
    peoples.back().deck.push_back(card());

    BOOST_CHECK_EQUAL(peoples.back().deck.back().icons, 0);

    unsigned int j = peoples.back().deck.back().icons;
    j |= 1 << 2;
    peoples.back().deck.back().icons |= j;

    BOOST_CHECK_EQUAL(peoples.back().deck.back().icons, j);

    BOOST_CHECK_EQUAL(peoples.back().deck.back().icons, j);
}
