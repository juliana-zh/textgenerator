#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>

#include "model.h"

namespace Gen
{

/**
 * Структура для опций командной строки
 */    
struct Options
{
    boost::filesystem::path fname;  // входной файл для обработки
    size_t nTokens;                 // количество требуемых токенов
};

/**
 * Главный обработчик текста
 * @param opt   - cтруктура для опций командной строки
 */
void mainBuilder(const Options &opt);

/**
 * Сгенерировать предложение по данной модели
 * @param model   - биграммная модель
 * @param result  - созданное предложение
 * @param nTokens - число токенов в созданном предложении
 */
void createSentence ( BGR::BigramModel &model
                    , std::string &result
                    , size_t &nTokens);
        
/**
 * Сгенерировать текст из N токенов по данной модели
 * @param model       - биграммная модель 
 * @param nTokensText - число необходимых токенов (как минимум)
 * @param os          - выходной поток
 */
void createText ( BGR::BigramModel &model                
                , size_t nTokensText
                , std::ostream &os);
       
/**
 * Добавить токен точки в конец текста
 * @param vecIdTokens - вектор из id токенов
 */
void addDot(std::vector<Dict::ID_t> &vecIdTokens);

} // namespace Gen

#endif // GENERATOR_H
