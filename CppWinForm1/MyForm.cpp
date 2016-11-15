#pragma once
#include "Quotes.h"
#include "MyForm.h"
#include<fstream>
#include"Quotes.h"

using namespace System;
using namespace System::Windows::Forms;

void readinQuotes(Quotes * MyAuthorQuotes)
{
	int NumQuotes = 0;
	std::string line, theme, author, birth, death, input;
	std::string lineCollector;

	std::ifstream userAddedQuotes;
	userAddedQuotes.open("user_added_quotes.txt");
	if (userAddedQuotes.is_open())
	{
		for (; getline(userAddedQuotes, lineCollector); NumQuotes++)
		{//counts how many lines there are
		}
	}
	userAddedQuotes.clear();					//resets eof
	userAddedQuotes.seekg(0, std::ios::beg);	//goes back to first line


	std::ifstream quoteList;
	quoteList.open("quotes.txt");
	if (!quoteList.is_open())
		exit(EXIT_SUCCESS);

	for (; getline(quoteList, lineCollector); NumQuotes++)
	{//counts how many lines there are
	}

	NumQuotes = NumQuotes / 3;	//because every 3 lines make 1 Quote
								//_Quotes.resize(_NumQuotes);	//changes vector size to have _numQuotes many addresses while keeping values
	MyAuthorQuotes->resize(NumQuotes);

	quoteList.clear();					//resets eof
	quoteList.seekg(0, std::ios::beg);	//goes back to first line

	int i = 0;
	for (; !quoteList.eof(); i++)
	{
		getline(quoteList, line);			//read in the quote
		getline(quoteList, theme);			//read in the theme
		getline(quoteList, author, '(');	//read in the author up to the opening parantheses for the year
		author[author.length() - 1] = ',';	//replaces space after author's name with a comma
		author[0] = toupper(author[0]);		//will always make first letter uppercase - this is to make unknown into Unknown for sorting
		getline(quoteList, birth, ' ');		//read in the birth year up to the immediately following space
		quoteList.ignore();					//to skip the '-'
		quoteList.ignore();					//to skip the space after '-'
		getline(quoteList, death, ')');		//read in death year up to the closing parantheses
		quoteList.ignore();					// to skip the \n character
		Author tempAuthor(author, birth, death);	//creates a variable author with appropriate information to be used for copying
		Quote tempQuote(line, theme, tempAuthor);	//initialize a new instance of Quote with the info we need, then....
		MyAuthorQuotes->entry(tempQuote, i);
		//_Quotes[i].copy(tempQuote, tempAuthor);	//copy it over to _Quotes[i] and now it has the proper values
	}

	if (userAddedQuotes.is_open())
	{
		userAddedQuotes.ignore(); // firstline is \n, this stops that from being an issue
		for (; !userAddedQuotes.eof(); i++) //reads in user-added quotes
		{
			getline(userAddedQuotes, line);			//read in the quote
			getline(userAddedQuotes, theme);			//read in the theme
			getline(userAddedQuotes, author, '(');	//read in the author up to the opening parantheses for the year
			author[author.length() - 1] = ',';	//replaces space after author's name with a comma
			author[0] = toupper(author[0]);		//will always make first letter uppercase - this is to make unknown into Unknown for sorting
			getline(userAddedQuotes, birth, ' ');		//read in the birth year up to the immediately following space
			userAddedQuotes.ignore();					//to skip the '-'
			userAddedQuotes.ignore();					//to skip the space after '-'
			getline(userAddedQuotes, death, ')');		//read in death year up to the closing parantheses
			userAddedQuotes.ignore();					// to skip the \n character
			Author tempAuthor(author, birth, death);	//creates a variable author with appropriate information to be used for copying
			Quote tempQuote(line, theme, tempAuthor);	//initialize a new instance of Quote with the info we need, then....
			MyAuthorQuotes->entry(tempQuote, i);
		}
	}
	userAddedQuotes.close();
	quoteList.close();
	MyAuthorQuotes->authorSelectionSort();
}

[STAThread]
void Main(array<String^>^ args)
{
	Quotes MyAuthorQuotes;
	Quotes * MyAuthorPointer = &MyAuthorQuotes;
	
	readinQuotes(MyAuthorPointer);

	Quotes MyThemeQuotes(MyAuthorQuotes);
	MyThemeQuotes.themeSelectionSort();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm1::MyForm form(MyAuthorQuotes, MyThemeQuotes);
	Application::Run(%form);
}
