#ifndef UTILS_H
#define UTILS_H
#include <unicode/unistr.h>
#include <boost/filesystem/path.hpp>

#include "dictionary.h"

namespace utils
{

/**
 * Биграмма представлена парой id двух подряд идущих токенов
 * Примеры (текстовых) биграмм для предложения "Жаркое лето."
 * {#, Жаркое}, {Жаркое, лето}, {лето, .}, {., #}
 */
struct Bigram
{
    Dict::ID_t prevId;
    Dict::ID_t curId;    
    Bigram (Dict::ID_t idPrev, Dict::ID_t idCur)
        : prevId(idPrev)
        , curId(idCur)        
    {}
    bool operator==(const Bigram &other) const
    {
        return prevId == other.prevId && curId == other.curId;
    }
};

/**
 * Получить набор биграмм 
 * @param vecIdTokens - входной вектор из id токенов
 * @param vecBigrams  - результатирующий вектор биграмм 
 */
void getBigrams ( const std::vector<Dict::ID_t>&vecIdTokens
                , std::vector<Bigram>&vecBigrams ); 
    
/**
 * Разбивка строки на токены (слова, частицы, предлоги, 
 * знаки препинания и т.п.) 
 * @param wstr        - входная строка для разбивки
 * @param vecIdTokens - результатирующий вектор из id токенов
 */
void tokenizeLine ( const std::string &line
                  , std::vector<Dict::ID_t>&vecIdTokens );    
    
/**
 * Разбивка содержимого файла на токены (слова, частицы, предлоги, 
 * знаки препинания и т.п.) 
 * @param is          - имя входного потока для чтения
 * @param vecIdTokens - результатирующий вектор из id токенов
 */
void tokenizeFile ( std::istream &is
                  , std::vector<Dict::ID_t> &vecIdTokens );
  
/**
 * Проверка, является ли данная строка знаком пунктуации
 * @param  - заданная строка
 */
bool isSpecialPunctMark( const Dict::Token_t &token);

/**
 * Сделать заглавной первую букву строки
 */
void capitalizeFirstLetter(icu::UnicodeString &str);

}; // namespace utils

#endif // UTILS_H
