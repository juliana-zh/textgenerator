#include <unicode/unistr.h>
#include <boost/test/unit_test.hpp>

#include "../src/dictionary.h"
#include "../src/utils.h"


BOOST_AUTO_TEST_SUITE(UtilsTests)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkTokenizeLine )
{       
    Dict::DictSingleton::getDict().reset();
    
    std::vector<Dict::ID_t>tokenID;     
    std::string str("Строка для разделения на токены.");
    
    utils::tokenizeLine(str, tokenID);
       
    BOOST_CHECK_EQUAL( tokenID.size(), 6 );
    BOOST_CHECK_EQUAL( tokenID[0], 2 );
    BOOST_CHECK_EQUAL( tokenID.back(), 1 );  
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkTokenizeLineDoubleWord )
{     
    Dict::DictSingleton::getDict().reset();
    
    std::vector<Dict::ID_t>tokenID;
    utils::tokenizeLine("Слово слово.", tokenID);
                  
    BOOST_CHECK_EQUAL(tokenID.size(), 3);
    BOOST_CHECK_EQUAL(Dict::DictSingleton::getDict().getID("слово"), 2);
    BOOST_CHECK_EQUAL(Dict::DictSingleton::getDict().getID("."), 1);
    BOOST_CHECK_EQUAL(tokenID[0], tokenID[1]); 
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkGetBigrams )
{ 
    using namespace utils;
    
    Dict::DictSingleton::getDict().reset();    
        
    Dict::ID_t idSharp = Dict::DictSingleton::getDict().getID("#");
    Dict::ID_t idDot   = Dict::DictSingleton::getDict().getID(".");

    std::vector<Dict::ID_t>ids = {10, 20, idDot};
    std::vector<utils::Bigram>bg;       
        
    getBigrams(ids, bg);    
    
    BOOST_REQUIRE_EQUAL(bg.size(), ids.size() - 1 + 2); 
    BOOST_CHECK( bg[0] == utils::Bigram(idSharp, ids[0])  );
    BOOST_CHECK( bg[1] == utils::Bigram(ids[0],  ids[1])  );
    BOOST_CHECK( bg[2] == utils::Bigram(ids[1],  ids[2])  );
    BOOST_CHECK( bg[3] == utils::Bigram(ids[2],  idSharp) );    
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkDot )
{ 
    using namespace utils;
    
    Dict::DictSingleton::getDict().reset();    
    
    Dict::ID_t idSharp = Dict::DictSingleton::getDict().getID("#");
    Dict::ID_t idDot   = Dict::DictSingleton::getDict().getID(".");
    
    std::vector<Dict::ID_t>ids = {idDot};
    std::vector<utils::Bigram>bg;    
    
    getBigrams(ids, bg);    
    
    BOOST_REQUIRE_EQUAL(bg.size(), ids.size() - 1 + 2); 
    BOOST_CHECK( bg[0] == utils::Bigram(idSharp, ids[0]) );
    BOOST_CHECK( bg[1] == utils::Bigram(ids[0], idSharp) );
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( checkTwoDots )
{ 
    using namespace utils;
    
    Dict::DictSingleton::getDict().reset();    
    
    Dict::ID_t idSharp = Dict::DictSingleton::getDict().getID("#");
    Dict::ID_t idDot   = Dict::DictSingleton::getDict().getID(".");
    
    std::vector<Dict::ID_t>ids = {idDot, idDot};
    std::vector<utils::Bigram>bg;    
    
    getBigrams(ids, bg);    
    
    BOOST_REQUIRE_EQUAL(bg.size(), 4); 
    BOOST_CHECK( bg[0] == utils::Bigram(idSharp, idDot) );
    BOOST_CHECK( bg[1] == utils::Bigram(idDot, idSharp) );
    BOOST_CHECK( bg[2] == utils::Bigram(idSharp, idDot) );
    BOOST_CHECK( bg[3] == utils::Bigram(idDot, idSharp) );
}
BOOST_AUTO_TEST_SUITE_END() 

