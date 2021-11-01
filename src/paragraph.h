#pragma once

#include <string>

#include "article.h"

class Paragraph : public Article {
    public:
        Paragraph(int level, std::string text) {
            if (level <= 0) {
                throw std::string("Level is negative or zero\n");
            }
            if (level > 6) {
                throw std::string("Level is larger then six\n");
            }
            _level = level;
            while (level--) {
                _text += "#";
            }
            _text += " " + text;
        }

        ~Paragraph() {}

        std::string getText() const override {
            if (_count == 0) {
                return _text + "\n";
            }
            return _text;
        }

        int getLevel() const override {
            return _level;
        }

        void add(Article* content) override {
            if (content->getLevel() != 0 && content->getLevel() < _level) {
                throw "error on add" + std::to_string(content->getLevel()) +
                      "greater then" + std::to_string(_level);
            }
            _text += "\n" + content->getText();
            _count++;
        }

    private:
        int _level;
        int _count = 0;
        std::string _text;
};
