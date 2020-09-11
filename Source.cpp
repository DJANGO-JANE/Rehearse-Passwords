/***************************************************
*													
*		Description: Password Memorising Application
*		Written by: DJANGO JANE						
*		Date: 2/09/2020								
*			                                        
***************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <string>
#include <direct.h>
#include <corecrt_io.h>
#include "djcrypt.h"
#include "Operations.h"


#pragma region Prototypes and Globals
/// <summary>
/// Main menu for the application.
/// </summary>
int MainMenu();

djane::DjaneCryption djCry(47, 53);
djane::Operations Oprtor(&djCry);


const std::string TOP_BORDER = "\n\t\t========================================================================\n";
const std::string BOTTOM_BORDER = TOP_BORDER;
const std::string MARGIN = "\t\t\t";
const std::string BANNER = MARGIN + "\t\t";
int listSize=0;
#define PROGRAM_DIR "PassMApp"
#pragma endregion


int main()
{
	int choice;
	
	char yesOrNo;

	while (true)
	{
		choice = MainMenu();
		switch (choice)
		{
			/*
			//		ADD NEW RECORD TO FILE
			*/
			case 1:
				system("cls");
					do {
						std::cin.ignore();
						std::string acc, passText,passText2;

						std::cout << TOP_BORDER;
						std::cout << MARGIN << "\t\t N E W \t R E C O R D \n\n";
						std::cout << MARGIN << "Enter the name of the account: "; getline(std::cin, acc); std::cout << std::endl;
						std::cout << MARGIN << "Enter the password of " << acc << ": "; getline(std::cin, passText); std::cout << std::endl;
						std::cout << MARGIN << "Enter password again : "; getline(std::cin, passText);
						std::cout << BOTTOM_BORDER;

						if ((passText.length()))
						{
								for (size_t i = 0; i < acc.size(); i++)
								{
									if (isspace(acc[i])) acc[i] = '_';
								}
							if (Oprtor.addRecordToFile(acc,passText))
							{
								std::cout << "\n"<<MARGIN<<">> " << acc << " added successfully.\n";
							}
							else
							{
								std::cout << "\n" << MARGIN << ">> " << acc << " was unable save.\n";
							}
						}
						else 
						{
							std::cout << "\n" << MARGIN << ">> No password has been entered for " << acc << ": "; getline(std::cin, passText);
							continue;
						}
						std::cout << "\n" << MARGIN << "\t PRESS [ESC] to go back to main menu.\n";
					} while(_getch() != VK_ESCAPE );
				break;
			/*
			//		REHEARSE PASSWORDS
			*/
			case 2:
				system("cls");
					do
					{
						int count = 0,attempt=0;
						std::cin.ignore();
						std::string acc = Oprtor.getPasswordHint(), passText;
						if (acc.empty())
						{
							break;
						}
						std::cout << TOP_BORDER;
						std::cout << MARGIN << "\tP A S S W O R D \t R E H E A R S A L \n\n";
						std::cout << MARGIN << MARGIN << acc << ":" << std::endl<<std::endl;
						std::cout << BOTTOM_BORDER;
						std::cout << MARGIN << MARGIN; getline(std::cin, passText);

						//***
						//***	TODO: Make entered text appear as symbols and implement Backspace operation
						//***
						//while (pass=_getch()!=13 && _getch()!=VK_RETURN)
						//{
						//	if (pass==VK_BACK)
						//	{
						//		if (passTxt.length() != 0)
						//		{
						//			std::cout << "\b \b";
						//			passTxt.resize(passTxt.length() - 1);
						//		}
						//	}
						//	else if (pass == 0 || pass == 224)
						//	{
						//		_getch();
						//		continue;
						//	}
						//	else
						//	{
						//		passTxt += _getch();
						//		_putch('*');
						//	}
						//}

						if (passText.length())
						{
							int referee = 0,attempt=1;
							if (Oprtor.checkPassword(acc, (passText)))
							{
								std::cout << std::endl;
								std::cout<< BANNER << "==== A P P R O V E D ====" << std::endl;
								referee = 1;
							}
							else 
							{
								std::cout << std::endl;
								std::cout<< BANNER << "==== D E N I E D ====" << std::endl;
							}
							Oprtor.WriteToRecord(acc, referee, attempt);
							//continue;
						}
						else
						{
							std::cout << "\n\t\t\t==== T R Y  A G A I N ====" << std::endl;
						}
						std::cout << "\n" << MARGIN << "\t PRESS [ESC] to go back to main menu.\n";
					} while (_getch()!=VK_ESCAPE );
				break;
			case 3:
			
				system("cls");
				do
				{

					int input = 0;
					std::cin.ignore();

						std::cout << TOP_BORDER;
						std::cout << MARGIN << "\t D E L E T E \t F I L E \t R E C O R D S \n\n";
						std::cout << MARGIN << MARGIN << "[ y/n ] \n";
						std::cout << BOTTOM_BORDER;
						std::cout << MARGIN << MARGIN <<"   "; std::cin.get(yesOrNo);

						if ((yesOrNo == 'y') || (yesOrNo == 'Y'))
						{
							Oprtor.RemoveAppFile();
							system("pause");
							break;
						}

				} while ((yesOrNo != 'n') && (yesOrNo != 'N'));
				break;

			default:
				MainMenu();
		}
	}	
}

int MainMenu()
{
	//////////////////////////////////////////////////////////
	const char* ENV_DIR =  "C:\\Users\\Public\\" ;
	char path[100] = { "" };
	strcat(path, ENV_DIR);
	strcat(path, PROGRAM_DIR);
	//////////////////////////////////////////////////////////

	system("cls");
	int columnSize = 0;

	//Check and resolve working directory issues
	Oprtor.WorkingDirectoryCheck(path);

	

	/*				Driver Operations						*/
	int input;

	std::cout << TOP_BORDER << std::endl;
	std::ifstream list("data.dat");
	
	while (list.is_open() && !list.eof())
	{
		if (columnSize >= 3)
		{
			std::cout << std::endl;
			columnSize = 0;
			continue;
		}
		else
		{
			std::string data;
			getline(list, data);
			std::cout << "\t\t"<<std::setw(10) << data.substr(0, data.find(' '));
			columnSize++;
			listSize++;
			continue;
		}
	}
	std::cout <<TOP_BORDER<< std::endl;
	std::cout << MARGIN<<" [1] Record Information.\n";
	std::cout << MARGIN<<" [2] Rehearse Passwords.\n";
	std::cout << MARGIN<<" [3] Empty Files.\n";
	std::cout << BOTTOM_BORDER;
	std::cout << "\t\t\t\t>> "; std::cin >> input;

	if (isalpha((input)))
	{
		std::cout << "\n\t\t\t >> CHOOSE A NUMBER BETWEEN THE SQUARE BRACKETS ABOVE.\n";
		return -1;
	}
	else
	{
		return input;
	}
}
