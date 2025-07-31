#include <iostream>
#include <string>
#include <vector>

#ifndef MENU_HPP
#define MENU_HPP

class Menu
{
    private:
        std::string title;
        std::vector<std::string> optionsText;
        std::string optionZero;

        char titleDecoration;
        int titleDecoRepeatCount;

        char optionLeftDecoration;
        char optionRightDecoration;

    public:
        Menu(): optionZero("Exit"), titleDecoration('='), titleDecoRepeatCount(4), optionLeftDecoration('['), optionRightDecoration(']') {};
        Menu(const std::string& title): title(title), optionZero("Exit"), titleDecoration('='), titleDecoRepeatCount(4), optionLeftDecoration('['), optionRightDecoration(']') {};

        ~Menu() = default;

        void setTitle(const std::string& title);
        void setOptionZero(const std::string& optionZero);
        void disableOptionZero();

        void setTitleDecoration(const char& deco);
        void setTitleDecoRepeatCount(int num);
        
        void setOptionLeftDecoration(const char& leftDeco);
        void setOptionRightDecoration(const char& rightDeco);

        void addOption(const std::string& optionText);
        void dropOption(int numOption);
        void clearOptions();
        void changeOptions(std::vector<std::string> optionsText);

        void printMenu();
        int chooseOption();
};

#endif