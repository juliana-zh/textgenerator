#include <fstream>

#include "generator.h"

namespace Gen
{
  
//-----------------------------------------------------------------------------
void createSentence ( BGR::BigramModel &model
                    , std::string &result
                    , size_t &nTokens)
{
    result.clear();
    nTokens = 0;
    
    icu::UnicodeString uniresult;
    
    Dict::ID_t idSharp = Dict::DictSingleton::getDict().getID("#");
    
    Dict::ID_t b0 = idSharp;
    Dict::ID_t b1 = idSharp;
      
    while (true)    
    {
        b0 = b1;
        b1 = model.getNextRandToken(b0);
        
        Dict::Token_t tok = Dict::DictSingleton::getDict().getToken(b1);
        
        if (tok == "#")
        {
            break;
        } 
        
        if (utils::isSpecialPunctMark(tok) || b0 == idSharp)
        {
            uniresult += tok;            
        }
        else
        {
            uniresult += " " + tok;
        }
        
        ++nTokens;
    }          
    
    utils::capitalizeFirstLetter(uniresult); 
    uniresult += " ";
    uniresult.toUTF8String(result);
}

//-----------------------------------------------------------------------------
void createText ( BGR::BigramModel &model                
                , size_t nTokensText
                , std::ostream &os)
{   
    size_t counterTokens = 0;
    
    // добавляем по предложению, пока не наберем достаточное количество токенов
    while (counterTokens < nTokensText)
    {
        std::string localSentence;
        size_t localCounterTokens = 0;
        createSentence(model, localSentence, localCounterTokens);
        
        os << localSentence;
        
        counterTokens += localCounterTokens;
    }    
}
        
//-----------------------------------------------------------------------------
void mainBuilder(const Options &opt) 
{
    std::ifstream ifs(opt.fname.string());
    
    if (!ifs.is_open())
    {    
        throw std::runtime_error("Error opening file: " + opt.fname.string());        
    }
                
    // разбиваем файл на подряд идущие токены, сохраняем в вектор их id    
    std::vector<Dict::ID_t>vecIdTokens;
    utils::tokenizeFile ( ifs, vecIdTokens );
        
    if (vecIdTokens.empty())
    {
        return;
    }
    
    addDot(vecIdTokens);
    
    // формируем биграммы
    std::vector<utils::Bigram> vecBigrams;    
    utils::getBigrams ( vecIdTokens, vecBigrams );
    
    BGR::BigramModel model(vecBigrams, Dict::DictSingleton::getDict().maxId() + 1);
    
    // генерируем текст, вывод в поток
    Gen::createText(model, opt.nTokens, std::cout); 
}    

//-----------------------------------------------------------------------------
void addDot(std::vector<Dict::ID_t> &vecIdTokens)
{
    Dict::ID_t idDot = Dict::DictSingleton::getDict().getID(".");
    
    if (vecIdTokens.back() != idDot)
    {
        vecIdTokens.push_back(idDot);
    }
}
    
} // namespace Gen