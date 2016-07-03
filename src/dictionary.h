#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <vector>
#include <unordered_map>


#include <boost/noncopyable.hpp>
#include <unicode/unistr.h>

namespace std
{
    template<>
    struct hash<icu::UnicodeString> {
    public:
        size_t operator()(const icu::UnicodeString &s) const
        {
            return (size_t) s.hashCode();
        }
    };
};

namespace Dict
{

using ID_t = uint64_t;
using Token_t = icu::UnicodeString;

/**
 * Словарь, в котором хранятся токены (слова, частицы, предлоги,
 * знаки препинания и т.п.) и соответствующие им идентификаторы
 */
class Dictionary : boost::noncopyable
{
public:

    /**
     * Получить id токена
     * @param token - входной токен
     */
    ID_t getID(const Token_t &token) const;

    /**
     * Получить токен по его id
     * @param id - входной идентификатор
     */
    Token_t getToken(ID_t id) const;

    /**
     * Вставка токена в словарь
     * @param token - входной токен
     * @return id токена
     */
    ID_t pushToken(const Token_t &token);

    /**
     * Перезагрузить словарь
     */
    void reset();

    /**
     * Максимальное id (по всем хранимым токенам)
     */
    inline ID_t maxId() const;

    Dictionary ();

private:

    /**
     * Очисить словарь
     */
    void clear();

    /**
     * Получить еще незанятый каким-либо токеном id
     */
    ID_t generateNewID() const;

    // хранение отображения из id токена в его строковое представление
    std::vector<Token_t>idToToken;

    // хранение отображения из строкового представления токена в его id
    std::unordered_map<Token_t, ID_t>tokenToId;
};

//-----------------------------------------------------------------------------
/**
 * Паттерн синглтон для словаря - с целью предоставить контролируемый доступ
 * к единственному экземпляру.
 */
class DictSingleton
{
    DictSingleton() {}

    DictSingleton( const DictSingleton&);

    DictSingleton& operator=( DictSingleton& );

public:
    static Dictionary& getDict()
    {
        static Dictionary instance;
        return instance;
    }
};

//-----------------------------------------------------------------------------
inline void Dictionary::clear()
{
     tokenToId.clear();
     idToToken.clear();
}

//-----------------------------------------------------------------------------
inline ID_t Dictionary::maxId() const
{
     ID_t sz = idToToken.size();

     if (sz == 0)
     {
         throw std::runtime_error("Error: cловарь не инициализирован");
     }

     return sz - 1;
}

} // namespace Dict

#endif // DICTIONARY_H
