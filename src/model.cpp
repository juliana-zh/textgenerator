
#include "model.h"

namespace BGR 
{
    
//-----------------------------------------------------------------------------
BigramModel::BigramModel(const std::vector<utils::Bigram>&bgr, uint64_t sizeModel)
    : countToken(sizeModel)
    , stat(sizeModel, std::vector<Statistic>())
    , vecBigrams(bgr)
    , sizeModel(sizeModel)
{    
    buildModel();
}   
    
//-----------------------------------------------------------------------------
void BigramModel::buildModel()
{
    countElements(); 
    buildStatistic();
}

//-----------------------------------------------------------------------------
void BigramModel::countElements()
{
    for (const auto &bigr : vecBigrams)
    {
        checkId(bigr.prevId);
        checkId(bigr.curId);
        
        ++countToken[bigr.prevId];
        ++countToken[bigr.curId];
        
        ++countBigram[bigr];
    }    
}

//-----------------------------------------------------------------------------
void BigramModel::checkId(Dict::ID_t id) const
{
    if (!(id < sizeModel))
    {
        std::string err;
        err += "BigramModel error statement (id >= sizeModel): ";
        err += "id = " + std::to_string(id);        
        err += "; sizeModel = ", std::to_string(sizeModel);            
        
        throw std::runtime_error(err);
    }
}

//-----------------------------------------------------------------------------
void BigramModel::buildStatistic()
{
    for (const auto &bigr : vecBigrams)
    {  
        checkId(bigr.prevId);
        checkId(bigr.curId);
        
        stat[bigr.prevId].push_back({ bigr.curId
                      , (double) countBigram[bigr] / countToken[bigr.prevId] });
    }
}

//-----------------------------------------------------------------------------
Dict::ID_t BigramModel::getNextRandToken(Dict::ID_t id)
{    
    checkId(id);
    
    double randD = distribution(generator);
    
    double prob = 0.0;
    for (const auto &statElem : stat[id])
    {
        prob += statElem.probability;
        
        if (randD < prob)
        {
            return statElem.id;
        }
    } 
    
    if (stat[id].empty())
    {
        throw std::runtime_error("Внутренняя ошибка BigramModel: stat[id] is empty");
    }
    return stat[id].back().id;
}

} // namespace BGR
