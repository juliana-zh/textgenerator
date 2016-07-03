#include <boost/assert.hpp>
#include <algorithm>

#include "dictionary.h"

namespace Dict
{

//-----------------------------------------------------------------------------
ID_t Dictionary::getID(const Token_t &token) const
{
    Token_t localToken(token);
    localToken.toLower();
    
    const auto &itToken = tokenToId.find(localToken);
    
    if (itToken == tokenToId.end())
    {
        // если такого токена нет в словаре
        throw std::runtime_error("Dictionary: No such token in dictionary");
    } 
      
    return itToken->second;
}

//-----------------------------------------------------------------------------
Token_t Dictionary::getToken(ID_t id) const
{
    if ( !(id < idToToken.size()) )
    {
        throw std::runtime_error("Dictionary: Word ID out of bounds");
    }
    
    return idToToken[id];
}

//-----------------------------------------------------------------------------
ID_t Dictionary::pushToken(const Token_t &inputToken)
{
    Token_t token(inputToken);
    token.toLower();  
      
    const auto &itToken = tokenToId.find(token);
    
    if (itToken != tokenToId.end())
    {        
        // токен уже есть в словаре, добавлять не надо
        return itToken->second;
    }
    
    ID_t newID = generateNewID();
    
    tokenToId[token] = newID;    
    idToToken.emplace_back(token);
    
    BOOST_ASSERT(tokenToId.size() == idToToken.size());
    BOOST_ASSERT(idToToken[newID] == token);

    return newID;
}

//-----------------------------------------------------------------------------
inline ID_t Dictionary::generateNewID() const
{
    return idToToken.size();  
}

//-----------------------------------------------------------------------------
Dictionary::Dictionary()
{
    reset();
}

//-----------------------------------------------------------------------------
void Dictionary::reset()
{
    clear();
    pushToken("#");
    pushToken('.');
}


}  // namespace Dict