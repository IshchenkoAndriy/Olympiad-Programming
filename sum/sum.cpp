#include <iostream>
#include <limits>

int main(int argc, char const *argv[])
{
	std::cout << "Find 3 numbers to sum" << std::endl;
	std::cout << "=====================" << std::endl;

	std::cout << "Type a number with 3 or 4 digits: ";

	int initialNumber;
	std::cin >> initialNumber;

	while (initialNumber < 100 || initialNumber > 9999)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		std::cout << " ...... Number must have 3 or 4 digits." << std::endl;
		std::cout << "Type your namber again: ";
		std::cin >> initialNumber;
	}

	char choiceCharacter;
	char yesChoiceCharacter = 'j';
	char noChoiceCharacter = 'n';
	do {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

		std::cout << " Show all solutions (" << yesChoiceCharacter << '/' << noChoiceCharacter << ") ? ";
		std::cin >> choiceCharacter;
		choiceCharacter = tolower(choiceCharacter);
	} while (choiceCharacter != yesChoiceCharacter && choiceCharacter != noChoiceCharacter);
	
	if (choiceCharacter == yesChoiceCharacter)
	{
		std::cout << "Printing all solutions" << std::endl;
	} else {
		std::cout << "Printing only one solution" << std::endl;
	}


	return 0;
}