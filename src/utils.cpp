#include <unicode/regex.h>
#include <unicode/unistr.h>

#include "utils.h"

namespace utils
{
       
//-----------------------------------------------------------------------------
void tokenizeLine(const std::string &line, std::vector<Dict::ID_t>&vecIdTokens )
{            
    icu::UnicodeString str(line.c_str());
    
    UErrorCode status = U_ZERO_ERROR;
    static RegexMatcher matcher("[а-яА-ЯЁёa-zA-Z0-9-]+|[,:;?!]+|[.{1}]", 0, status);
    matcher.reset(str);
    
    int64_t startIndex = 0;
    while (matcher.find(startIndex, status) && (status == U_ZERO_ERROR) )
    {
        Dict::Token_t token = matcher.group(status);
        
        Dict::ID_t id = Dict::DictSingleton::getDict().pushToken(token);
        vecIdTokens.push_back(id); 
                 
        startIndex = matcher.end(status);
    }  
}
  
//-----------------------------------------------------------------------------
void tokenizeFile ( std::istream &is
                  , std::vector<Dict::ID_t>&vecIdTokens )
{    
    std::string str;
    while (std::getline(is, str))
    {                          
        tokenizeLine(str, vecIdTokens); 
    } 
}  
  
//-----------------------------------------------------------------------------
void getBigrams ( const std::vector<Dict::ID_t>&vecIdTokens
                , std::vector<Bigram>&vecBigrams )
{
    Dict::ID_t idSharp = Dict::DictSingleton::getDict().getID("#");  
    Dict::ID_t idDot   = Dict::DictSingleton::getDict().getID(".");    
        
    Dict::ID_t b0 = idSharp; 
    for (auto b1 : vecIdTokens)    
    {
        vecBigrams.push_back({b0, b1});
        
        if (b1 == idDot)
        {
            vecBigrams.push_back({b1, idSharp});
            b0 = idSharp;
        }
        else
        {
            b0 = b1;    
        }        
    }    
}

//-----------------------------------------------------------------------------
bool isSpecialPunctMark( const Dict::Token_t &token)
{
    static const std::vector<Dict::Token_t>punktMarks = {".", "!", "?", ",", ";", ":"};
    
    return std::find(punktMarks.begin(), punktMarks.end(), token) != punktMarks.end();
}

//-----------------------------------------------------------------------------
void capitalizeFirstLetter(icu::UnicodeString &str)
{
    if (str.isEmpty())
    {
        return;
    }
        
    icu::UnicodeString repl(str[0]);
    repl.toUpper();        
    str.replace(0, 1, repl);
}
  
}; // namespace utils