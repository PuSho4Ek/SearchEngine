#ifndef SEARCHENGINE_CONVERTERJSON_H
#define SEARCHENGINE_CONVERTERJSON_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "nlohmann/json.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace nlohmann;

class ConverterJson {
public:
    ConverterJson() = default;

    /**
    * Метод получения содержимого файлов
    * @return Возвращает список с содержимым файлов перечисленных
    * в config.json
    */
    vector<string> GetTextDocuments();

    /**
    * Метод считывает поле max_responses для определения предельного
    * количества ответов на один запрос
    * @return Возвращает кол-во максимальных ответов на один запрос
    */
    int GetResponsesLimit();

    /**
    * Метод получения запросов из файла requests.json
    * @return возвращает список запросов из файла requests.json
    */
    vector<string> GetRequests();

    /**
    * Положить в файл answers.json результаты поисковых запросов
    */
    void putAnswers(vector<vector<pair<int, float>>> answers);
};


#endif //SEARCHENGINE_CONVERTERJSON_H
