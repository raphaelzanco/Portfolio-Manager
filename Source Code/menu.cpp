#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "menu.hpp"

void Menu::setTitle(const std::string& title)
{
    this->title = title;
}

void Menu::setOptionZero(const std::string& optionZero)
{
    this->optionZero = optionZero;
}

void Menu::disableOptionZero()
{
    this->optionZero = "\0";
}

void Menu::setTitleDecoration(const char& deco)
{
    this->titleDecoration = deco;
}

void Menu::setTitleDecoRepeatCount(int num)
{
    if (num < 0)
    {
        std::cout << "Error: Menu cannot receive a negative number in the title Decoration Repetition" << std::endl;
        return;
    }

    this->titleDecoRepeatCount = num;
}

void Menu::setOptionLeftDecoration(const char& leftDeco)
{
    this->optionLeftDecoration = leftDeco;
}

void Menu::setOptionRightDecoration(const char& rightDeco)
{
    this->optionRightDecoration = rightDeco;
}

void Menu::addOption(const std::string& optionText)
{ 
    if (optionText.empty())
    {
        std::cout << "Error: Menu cannot add an option of an empty string" << std::endl;
        return;
    }

    this->optionsText.push_back(optionText);
}

void Menu::dropOption(int numOption)
{
    if (numOption < 1) 
    {
        std::cout << "Error: Menu cannot delete an option from a less than 1 position" << std::endl;
        return;
    }
    else if (numOption > (this->optionsText.size()))
    {
         std::cout << "Error: Menu doesn't have an option " << numOption << std::endl;
        return;
    }
    else
    {
        numOption -= 1;
        this->optionsText.erase(this->optionsText.begin() + numOption);
    }
}

void Menu::clearOptions()
{
    this->optionsText.clear();
}

void Menu::changeOptions(std::vector<std::string> optionsText)
{
    if (optionsText.size() < 1)
    {
        std::cout << "Error: Menu cannot change options from an empty vector" << std::endl;
        return;
    }

    this->optionsText = optionsText;
}

void Menu::printMenu()
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < (this->titleDecoRepeatCount); j++)
        {
            std::cout << this->titleDecoration;
        }

        if (i == 0)
        {
            std::cout << " " << this->title << " ";
        }
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < (this->optionsText.size()); i++)
    {
        std::cout << this->optionLeftDecoration << (i+1) << this->optionRightDecoration << "  " << this->optionsText[i] << std::endl;
    }

    if (this->optionZero != "\0")
    {
        std::cout << this->optionLeftDecoration << "0" << this->optionRightDecoration << "  " << this->optionZero << std::endl;
    }
}

int Menu::chooseOption()
{
    int choice;
    while (true)
    {
        std::cout << std::endl << "Choose an option: ";
        std::cin >> choice;

        // Check for non-numeric input
        if (std::cin.fail())
        {
            std::cout << std::endl << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            continue; 
        }

        if (((this->optionZero) == "\0" && choice > 0 && choice <= (this->optionsText.size())) 
            || ((this->optionZero) != "\0" && choice >= 0 && choice <= (this->optionsText.size())))
        {
            return choice; 
        }
        else
        {
            std::cout << std::endl << "Invalid option. Please try again." << std::endl;
        }
    }
}