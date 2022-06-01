#include "../include/ConverterJSON.h"

/**
 * вспомогательня функция ConverterJson::GetTextDocuments()
 * @param fileName - название файла для чтения
 * @return содержимое файла с названием (fileName)
 */
string readFile(const string& fileName) {
    ifstream file(fileName);
    stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

vector<string> ConverterJson::GetTextDocuments()
{
    ifstream file_config("config.json");
    vector<string> files_content;
    json configJson;
    file_config >> configJson;
    file_config.close();
    for (auto &i : configJson["files"]) {
        files_content.push_back(readFile(i));
    }
    return files_content;

}

int ConverterJson::GetResponsesLimit()
{
    ifstream config_file("config.json");
    json config_json;
    config_file >> config_json;
    config_file.close();
    return config_json["config"]["max_responses"];
}

vector<string> ConverterJson::GetRequests()
{
    ifstream requests_file("requests.json");
    json requests_json;
    requests_file >> requests_json;
    requests_file.close();
    return requests_json["requests"];
}

/**
 * вспомогательная функция ConverterJson::putAnswers()
 * @param num - число дла изменения кол-ва цифр
 * @param count - общее кол-во цифр для числа
 * @return возвращает число с определённым кол-ом цифр
 */
string getStrNum(const int& num, int count = 3)
{
    string str_num = to_string(num);
    string ret_num;
    for (int i = 0; i < count-str_num.length(); i++)
    {
        ret_num += "0";
    }
    return ret_num + str_num;
}

void ConverterJson::putAnswers(vector<vector<pair<int, float>>> answers)
{
    json answers_json;
    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i].size() == 0)
        {
            answers_json["answers"]["request" + getStrNum(i+1)]["result"] = false;
        }
        else if (answers[i].size() == 1)
        {
            answers_json["answers"]["request" + getStrNum(i+1)]["result"] = true;
            answers_json["answers"]["request" + getStrNum(i+1)]["docid"] = answers[i][0].first;
            answers_json["answers"]["request" + getStrNum(i+1)]["rank"] = answers[i][0].second;
        }
        else
        {
            answers_json["answers"]["request" + getStrNum(i+1)]["result"] = true;
            vector<json> relevance;
            for (auto &j : answers[i]) relevance.push_back({{"docid", j.first}, {"rank", j.second}});
            answers_json["answers"]["request" + getStrNum(i+1)]["relevance"] = relevance;
        }
    }
    ofstream answers_file("answers.json");
    answers_file << answers_json;
    answers_file.close();
}