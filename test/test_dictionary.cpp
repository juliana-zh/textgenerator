#define BOOST_TEST_MODULE UnitTest
#include <boost/test/unit_test.hpp>

#include "../src/dictionary.h"

BOOST_AUTO_TEST_SUITE(DictTests)

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( dictNoWords )
{             
    Dict::Dictionary dict;
  
    BOOST_CHECK_THROW( dict.getID("Dixit"), std::runtime_error );   
    BOOST_CHECK_THROW( dict.getToken(2),    std::runtime_error );   
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( twoEqualObj )
{  
    Dict::Dictionary dict;
    
    static const Dict::ID_t id = 2;
  
    BOOST_CHECK_EQUAL( dict.pushToken("СЛОВО"), id );
    BOOST_CHECK_EQUAL( dict.pushToken("слово"), id );
             
    BOOST_CHECK_EQUAL( dict.getID("Слово"), id );   
    BOOST_CHECK( dict.getToken(id) == "слово" );   
}

//-----------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE( threeDiffObj )
{     
    Dict::Dictionary dict;
  
    static const Dict::ID_t startId = 2;
    
    BOOST_CHECK_EQUAL( dict.pushToken("Dixit" ),      startId     ); 
    BOOST_CHECK_EQUAL( dict.pushToken("Cluedo"),      startId + 1 );
    BOOST_CHECK_EQUAL( dict.pushToken("Hearthstone"), startId + 2 );   
    
    BOOST_CHECK( dict.getToken(startId    ) == "dixit"  ); 
    BOOST_CHECK( dict.getToken(startId + 1) == "cluedo" );
    BOOST_CHECK( dict.getToken(startId + 2) == "hearthstone" );
    
    BOOST_CHECK_THROW( dict.getID("UnknownObj"),       std::runtime_error );   
    BOOST_CHECK_THROW( dict.getToken(startId + 100),   std::runtime_error ); 
}


BOOST_AUTO_TEST_SUITE_END()