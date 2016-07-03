#ifndef MODEL_H
#define MODEL_H

#include <chrono>
#include <random>
#include <stdexcept>

#include <boost/noncopyable.hpp>
#include <boost/functional/hash.hpp>

#include "utils.h"

namespace std
{
    template<>
    struct hash<utils::Bigram> {
    public:
        size_t operator()(const utils::Bigram &bi) const 
        {
            std::size_t seed = 0;
            boost::hash_combine(seed, bi.prevId);
            boost::hash_combine(seed, bi.curId);
    
            return seed;            
        }
    };
}

namespace BGR
{
   
/**
 * Класс для реализации биграмной модели и получения следующего токена
 * после данного, исходя из вероятности его встретить в исходном тексте 
 * после этого токена.
 */    
class BigramModel : boost::noncopyable
{
public:
    
    /**
     * Конструктор биграммной модели.
     * @param bgr       - набор биграмм
     * @param sizeModel - размер модели
     */
    BigramModel(const std::vector<utils::Bigram>&bgr, uint64_t sizeModel);       
     
    /**
     * Получить токен, который будет идти после данного токена,
     * исходя из вероятности встретить его в исходном тексте после него. 
     * @param id - идентификатор входящего токена
     * @return идентификатор полученного токена
     */
    Dict::ID_t getNextRandToken(Dict::ID_t id);

private:
    
    /**
     * Структура для хранения id токена и вероятности встретить это токен     
     */
    struct Statistic
    {
        Dict::ID_t id;
        double probability;
    };
        
    void buildModel();
    
    /**
     * Заполение вектора stat - статистики по биграммам
     */
    void buildStatistic();
    
    /**
     * Сосчитать, сколько токенов каждого вида встретилось в исходном тексте
     * и сколько биграмм каждого вида есть
     */
    void countElements();
    
    /**
     * Проверка id на невыход за границы внутренних структур 
     */
    void checkId(Dict::ID_t id) const;
    
    // сколько раз данный токен встретился в исходном тексте
    std::vector<Dict::ID_t> countToken;  
    
    // сколько раз данная биграмма встретилась в исходном тексте
    std::unordered_map<utils::Bigram, size_t> countBigram;
    
    // отображение из id токена в список токенов, которые идут за ним 
    // c соответствующей вероятностью
    std::vector<std::vector<Statistic>> stat;
    
    // ссылка на последовательность биграмм
    const std::vector<utils::Bigram>&vecBigrams;
    
    uint64_t sizeModel; 
    
    std::default_random_engine generator {
                    (unsigned) std::chrono::system_clock::now().time_since_epoch().count() };
                    
    std::uniform_real_distribution<double> distribution {0.0, 1.0};
};

} // namespace BGR

#endif // MODEL_H

