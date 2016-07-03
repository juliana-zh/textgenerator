#include <boost/test/unit_test.hpp>
#include <sstream>

#include "../src/generator.h"

BOOST_AUTO_TEST_SUITE(GeneratorTests)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( genSentenceTwoWords )
{       
    Dict::DictSingleton::getDict().reset();
    
    Dict::DictSingleton::getDict().pushToken("Шотландская");   // id = 2
    Dict::DictSingleton::getDict().pushToken("кошка"); // id = 3
    
    std::vector<utils::Bigram>bgr = {{0, 2}, {2, 3}, {3, 1}, {1, 0}};
    BGR::BigramModel model(bgr, 4);  
    
    std::string result;
    size_t nTokens;
    
    Gen::createSentence(model, result, nTokens);
    
    BOOST_CHECK_EQUAL(result, "Шотландская кошка. "); 
    BOOST_CHECK_EQUAL(nTokens, 3);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( genSentenceOneWord )
{       
    Dict::DictSingleton::getDict().reset(); 
    
    Dict::DictSingleton::getDict().pushToken("Кошка");   // id = 2
    
    std::vector<utils::Bigram>bgr = {{0, 2}, {2, 1}, {1, 0}};
    BGR::BigramModel model(bgr, 3);  
    
    std::string result;
    size_t nTokens;
    
    Gen::createSentence(model, result, nTokens);
    
    BOOST_CHECK_EQUAL(result, "Кошка. "); 
    BOOST_CHECK_EQUAL(nTokens, 2);
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( genText )
{
    Dict::DictSingleton::getDict().reset();
    
    Dict::DictSingleton::getDict().pushToken("Шотландская");   // id = 2
    Dict::DictSingleton::getDict().pushToken("кошка");         // id = 3
    
    std::vector<utils::Bigram>bgr = {{0, 2}, {2, 3}, {3, 1}, {1, 0}};
    BGR::BigramModel model(bgr, 4);  
    
    const size_t nTok = 4;
    std::ostringstream ost;
    Gen::createText(model, nTok, ost);
    
    BOOST_CHECK_EQUAL( ost.str(), "Шотландская кошка. Шотландская кошка. "); 
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( genTextTwoDots )
{
    Dict::DictSingleton::getDict().reset();
    std::istringstream iss("..");
        
    std::vector<Dict::ID_t>ids;
    utils::tokenizeFile ( iss, ids );
    
    std::vector<Dict::ID_t>goodresult = {1, 1};
    
    BOOST_CHECK_EQUAL_COLLECTIONS(ids.begin(), ids.end(), goodresult.begin(), goodresult.end());
}

BOOST_AUTO_TEST_SUITE_END()