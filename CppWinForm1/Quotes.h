#pragma once
#include<vector>
#include"Quote.h"

class Quotes
{
public:
	Quotes();
	void copy(const Quotes &); //this is a member function rather than a traditional copy constructor because
	//a copy constructor can only be called when first declaring the object, but we need to declare the object outside
	//a function to make sure the object can be used by any function (such as buttons) and copy it later
	//on inside a function because that is when the Quotes that will be copied from will be initialized

	void resize(int);
	
	void authorSelectionSort();
	void themeSelectionSort();
	void entry(Quote, int);
	int authorBinarySearch(std::string);
	int themeBinarySearch(std::string);
	std::string returnFullQuote(int);
	std::string displayAll();
	std::string searchAuthor(std::string);
	std::string searchQuote(std::string);
	std::string searchTheme(std::string);
	std::string searchYear(std::string);
	void addQuote(std::string, std::string, std::string, std::string, std::string);

private:
	int _NumQuotes;
	//std::vector<Quote> _Quotes;
	Quote *_Quotes;
	int _NumPasses = 0;
};