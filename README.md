# textgenerator
Text generator - Bigram model (Markov chain)

Схема работы:<br>
1) Разбиваем исходный текст на последовательность токенов (слов, знаков препинания);<br>
2) Составляем биграммы. Например, для предложения "Москва - столица России." будут сгенерированы следующие биграммы: <br>
{"#", "Москва" } <br>
{"Москва", "-" } <br>
{"-", "столица"} <br>
{"столица", "России"} <br>
{"России", "."} <br>
{".", "#"}; <br>
3) Берем токен для начала предложения; <br>
4) Генерируем токен-продолжение в зависимости от предыдущего слова, с учетом его вероятности; <br>
5) Повторяем предыдущий шаг до тех пор, пока не встретим символ конца предложения.
