#include "../include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(const vector<string>& input_docs) {
    docs = input_docs;
    // перебираем все документы
    for (int i = 0; i < docs.size(); i++) {
        thread t;
        for (int j = 0; j < docs[i].length(); j++) {
            // записываем в переменную слово и
            // проверяем самые популярные разделители слов
            string current_word;
            for (; docs[i][j]!=' ' && docs[i][j]!=',' && docs[i][j]!='.' && docs[i][j]!='!'
                    && docs[i][j]!='?' && j < docs[i].length(); j++) {
                current_word += tolower(docs[i][j]);
            }
            // добавляем в словарь наше слово
            if (!current_word.empty()) {
                // если не находим нужного слова в словаре то добавляем его
                if (freq_dictionary.find(current_word) == freq_dictionary.end()) {
                    freq_dictionary.insert(pair<string, vector<Entry>>(current_word, {{(size_t)i, 1}}));
                }
                else {
                    // производим поиск нужного элемента перебором
                    bool find_current_word = false;
                    for (auto& entry : freq_dictionary[current_word]) {
                        if (entry.doc_id == i) {
                            entry.count += 1;
                            find_current_word = true;
                        }
                    }
                    // при отсутствии нужного элемента создаём его
                    if (!find_current_word) {
                        freq_dictionary[current_word].push_back({(size_t) i, 1});
                    }
                }
            }
        }
    }
}

vector<Entry> InvertedIndex::GetWordCount(const string &word) {
    if (freq_dictionary.find(word) == freq_dictionary.end()) {
        vector<Entry> vec = {{}};
        return vec;
    }
    return freq_dictionary[word];
}