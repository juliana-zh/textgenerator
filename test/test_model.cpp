#include <iostream>

#include <boost/test/unit_test.hpp>

#include "../src/model.h"

BOOST_AUTO_TEST_SUITE(ModelTests)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkThrow )
{       
    std::vector<utils::Bigram>bg = {{0, 1}};
        
    BOOST_CHECK_THROW( BGR::BigramModel(bg, 0), std::runtime_error );  
    BOOST_CHECK_THROW( BGR::BigramModel(bg, 1), std::runtime_error );
    
    BOOST_CHECK_NO_THROW( BGR::BigramModel(bg, 2) );
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkNextTokenOneBigram )
{       
    std::vector<utils::Bigram>bg = {{0, 1}};
    
    BGR::BigramModel model(bg, 2);
    
    BOOST_CHECK_EQUAL(model.getNextRandToken(0), 1);     
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkNextTokenSomeBigrams )
{       
    std::vector<utils::Bigram>bg = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {1, 5}};
    
    BGR::BigramModel model(bg, 6);
    
    Dict::ID_t res = model.getNextRandToken(1);    
    BOOST_CHECK(res == 2 || res == 5);     
    BOOST_CHECK(res != 4);
}

BOOST_AUTO_TEST_SUITE_END() 