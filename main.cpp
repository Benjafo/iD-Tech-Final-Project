// Final project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
string create();
void clear_screen(char);
int droprewardscheck(int);
int main()
{
	bool logout = false;
	do
	{
		string name;
		int enemy = 1, startingenemy;
		int maxhp, hp, atk, coins;
		int critchance, evasion, combo, counter;
		int wizard;
		bool validname = false;
		char fill = ' ';
		do
		{
			cout << "Enter your name (/create to create a new profile): ";
			cin >> name;
			if (name == "/create")
			{
				name = create();
				validname = true;
				continue;
			}
			transform(name.begin(), name.end(), name.begin(), ::tolower);

			ifstream input;
			size_t pos;
			string line;

			input.open(".Players.txt");
			while (getline(input, line))
			{
				pos = line.find(name);
				if (pos != string::npos)
				{
					validname = true;
				}
			}
		} while (validname == false);

		fstream file;
		file.open(name + ".txt", ios::in);

		file >> maxhp;
		file >> atk;
		file >> startingenemy;
		file >> coins;
		file >> wizard;
		file >> critchance;
		file >> evasion;
		file >> combo;
		file >> counter;

		cout << "Starting enemy: " << startingenemy << endl;

		int enemyhp = 2 * (enemy - 1) + 10;
		int enemyatk = 1 + (enemy / 3);
		string choice;
		int starterlevel;

		while (true)
		{
			bool canusewizard = false;
			string mode;
			//print home base screen here
			clear_screen(fill);
			int wait = 2000;
			cout << "\nWelcome, " << name << "!\n\n\nBen's final project\nA game by Ben Foley\n\n\nCopyright 2018 BadAtCoding Game Studios\n\n\nCredits:\nWritten by: Ben Foley";
			cout << "\nIdeas: Ben Foley\nError - checking: Ben Foley\n";
			cout << "All coding by: Ben Foley\nStealing my tickets while I was frustrated over errors in my code: John Kiely\n\n\n";
			cout << "What would you like to do?\nOptions are:\nBattle\nUpgrades\nLogOut\n";
			enemy = 1;
			if (wizard == 1)
			{
				cout << "Wizard\n\n\n";
				canusewizard = true;
			}
			else
				cout << "\n\n";
			cin >> mode;

			if (mode == "wizard" || mode == "Wizard" || mode == "WIZARD")
			{
				clear_screen(fill);
				cout << "What level would you like to go to (max is " << startingenemy << ")? ";
				cin >> starterlevel;
				cout << "\n\n\n";
				if (cin.fail())
				{
					cout << "Fatal Error: request too large\nClosing program\n\n\n";
					return 0;
				}
				enemy = starterlevel;
				mode = "battle";
			}
			if (mode == "battle" || mode == "Battle")
			{
				//battle
				clear_screen(fill);
				
				bool autorun = false;
				string garbage;
				hp = maxhp;
				do
				{
					if (autorun == false)
					{
						cout << "Fighting enemy " << enemy << endl;
						cout << "Type 'a' to attack, 'c' to view coins, 'auto' to auto-attack. ";
						cin >> garbage;
					}
					if (garbage == "c")
						cout << "You have " << coins << " coins\n.";
					if (garbage == "auto")
					{
						autorun = true;
						wait = 300;
						garbage = "a";
					}
					if (garbage == "a")
					{
						
						//critical hit
						random_device rdcritical;
						int critdamage = 0;
						int critical = rdcritical() % 100 + 1;
						if (critical <= critchance)
						{
							cout << "\nCritical!";
							critdamage = 1.2 * atk;
						}
						//evasion chance
						bool evaded = false;
						random_device rdevasion;
						int evasionchance = rdevasion() % 100 + 1;
						if (evasionchance <= evasion)
						{
							cout << "\nEnemy attack evaded!";
							evaded = true;
						}
						//an attack
						if (autorun == true)
							cout << "\nFighting enemy " << enemy << endl;
						enemyhp = enemyhp - atk - critdamage;
						cout << "\nYou dealt " << atk + critdamage << " damage to enemy " << enemy << ".\n";
						if (enemyhp <= 0)
						{
							enemyhp = 2 * (enemy - 1) + 10;
							enemyatk = 1 + (enemy / 3);
							droprewardscheck(enemy);
							cout << "Enemy " << enemy << " killed. (+" << enemy << " coins)\n\n";
							cout << "You have " << hp << " hp.\n\n";
							coins = coins + 1 + (enemy / 10);
							if (enemy % 10 == 0)
								coins = coins + (5 * (enemy / 10));
							if (enemy > startingenemy)
								startingenemy = enemy;
							enemy++;
							this_thread::sleep_for(chrono::milliseconds(wait));
							clear_screen(fill);
						}
						else
						{
							hp = hp - enemyatk;
							if (hp < 0)
								hp = 0;
							if (evaded == false)
							{
								cout << "Enemy " << enemy << " dealt " << enemyatk << " damage to you.\nYou have " << hp << " hp.\n\n";
							}
							else
								cout << endl;
						}
						if (hp <= 0)
						{
							cout << "You died. Returning to home.";
							
							this_thread::sleep_for(chrono::milliseconds(1000));
							clear_screen(fill);
							break;
						}
					}
					//write to file save data
					file.open(name + ".txt", ios::out);
					file << maxhp << endl;
					file << atk << endl;
					file << startingenemy << endl;
					file << coins << endl;
					file << wizard << endl;
					file << critchance << endl;
					file << evasion << endl;
					file << combo << endl;
					file << counter << endl;
					file.close();
				} while (true);
			}
			else if (mode == "LogOut" || mode == "logout" || mode == "Logout" || mode == "Log out" || mode == "log out")
			{
				//write to file save data
				file.open(name + ".txt", ios::out);
				file << maxhp << endl;
				file << atk << endl;
				file << startingenemy << endl;
				file << coins << endl;
				file << wizard << endl;
				file << critchance << endl;
				file << evasion << endl;
				file << combo << endl;
				file << counter << endl;
				file.close();
				logout = true;
				clear_screen(fill);
			}
			else if (mode == "Upgrades" || mode == "upgrades")
			{
				do
				{
					string upgrade;
					clear_screen(fill);
					cout << "\nWelcome to the upgrade shop!\n\n\nIn the upgrade shop, you can power up your hp and attack.\nYou can also buy special upgrades";
					cout << ".\nType 'exit' to exit.\n\n\nYou have:\n";
					cout << maxhp << " max hp,\n" << atk << " atk,\n" << coins << " coins.\n\n\n";
					cout << "Select item to upgrade:\nhp\natk\ncritical\nevasion\ncombo attack\ncounter attack\n";
					if (wizard == 0)
						cout << "wizard\n";
					cin >> upgrade;
					if (upgrade == "exit" || upgrade == "Exit")
					{
						clear_screen(fill);
						break;
					}
					if (upgrade == "hp" || upgrade == "HP" || upgrade == "Hp")
					{
						string confirm;
						clear_screen(fill);
						do
						{
							cout << "Type 'exit' to exit.\n";
							cout << "You will upgrade your max hp by 1 for a price of " << (maxhp * 3) + 1 << " coins. Proceed? ";
							cin >> confirm;
							if (confirm == "yes" || confirm == "Yes")
							{
								if (coins > (maxhp * 3) + 1)
								{
									coins = coins - ((maxhp * 3) + 1);
									maxhp = maxhp + 1;
								}
								else
								{
									cout << "You don't have enough coins for that.\n";
									this_thread::sleep_for(chrono::milliseconds(1000));
									confirm = "exit";
								}
							}
							if (confirm == "Exit" || confirm == "exit" || confirm == "no" || confirm == "No")
								break;
						} while (true);
					}
					if (upgrade == "atk" || upgrade == "ATK" || upgrade == "Atk")
					{
						string confirm;
						clear_screen(fill);
						do
						{
							cout << "Type 'exit' to exit.\n";
							cout << "You will upgrade your atk by 1 for a price of " << (atk * 5) + 3 << " coins. Proceed? ";
							cin >> confirm;
							if (confirm == "yes" || confirm == "Yes")
							{
								if (coins > (atk * 5) + 3)
								{
									coins = coins - ((atk * 5) + 3);
									atk = atk + 1;
								}
								else
								{
									cout << "You don't have enough coins for that.\n";
									this_thread::sleep_for(chrono::milliseconds(1000));
									confirm = "exit";
								}
							}
							if (confirm == "Exit" || confirm == "exit" || confirm == "no" || confirm == "No")
								break;
						} while (true);
					}
					if (upgrade == "wizard" || upgrade == "WIZARD" || upgrade == "Wizard")
					{
						string confirm;
						clear_screen(fill);
						cout << "You will buy the wizard for a price of 1,500 coins. Proceed? ";
						cin >> confirm;
						if (confirm == "yes" || confirm == "Yes")
						{
							if (coins > 1500)
							{
								coins = coins - 1500;
								wizard = 1;
							}
							else
							{
								cout << "You don't have enough coins for that.\n";
								this_thread::sleep_for(chrono::milliseconds(1000));
							}
						}
					}
					if (upgrade == "critical" || upgrade == "Critical")
					{
						string confirm;
						clear_screen(fill);
						cout << "You will upgrade the chance of a critical hit by 1% for a price of " << (1 + (50 * critchance)) << " coins, making it " << critchance + 1 << ". Proceed? ";
						cin >> confirm;
						if (confirm == "yes" || confirm == "Yes")
						{
							if (coins > (1 + (50 * critchance)))
							{
								coins = coins - (1 + (50 * critchance));
								critchance++;
							}
							else
							{
								cout << "You don't have enough coins for that.\n";
								this_thread::sleep_for(chrono::milliseconds(1000));
							}
						}
					}
					if (upgrade == "evasion" || upgrade == "Evasion")
					{
						string confirm;
						clear_screen(fill);
						cout << "You will upgrade the chance of evasion by 1% for a price of " << (1 + (50 * evasion)) << " coins, making it " << evasion + 1 << ". Proceed? ";
						cin >> confirm;
						if (confirm == "yes" || confirm == "Yes")
						{
							if (coins > (1 + (50 * evasion)))
							{
								coins = coins - (1 + (50 * evasion));
								evasion++;
							}
							else
							{
								cout << "You don't have enough coins for that.\n";
								this_thread::sleep_for(chrono::milliseconds(1000));
							}
						}
					}

					//write to file save data
					file.open(name + ".txt", ios::out);
					file << maxhp << endl;
					file << atk << endl;
					file << startingenemy << endl;
					file << coins << endl;
					file << wizard << endl;
					file << critchance << endl;
					file << evasion << endl;
					file << combo << endl;
					file << counter << endl;
					file.close();
				} while (true);
			}
			if (logout == true)
				break;
		}
	}
	while (true);
}

void clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

string create()
{
	char fill = ' ';
	string newname;
	cout << "Enter the name of the profile you would like to create: ";
	cin >> newname;
	ofstream outfile;
	outfile.open(".Players.txt", ios_base::app);
	outfile << newname << endl;
	fstream file;
	string filename;
	filename = newname + ".txt";
	file.open(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Player profile created.\n";
		this_thread::sleep_for(chrono::milliseconds(1000));
		clear_screen(fill);
		file.open(filename, ios::out);
		file << 50 << endl;
		file << 5 << endl;
		file << 1 << endl;
		file << 5 << endl;
		file << 0 << endl;
		file << 0 << endl;
		file << 0 << endl;
		file << 0 << endl;
		file << 0 << endl;
	}
	return newname;
}

int droprewardscheck(int enemy)
{
	int reward = 0;
	if (enemy % 10 == 0)
	{
		int enemylevel = enemy & 10;
		reward = enemylevel * 5;
	}
	return reward;
}
