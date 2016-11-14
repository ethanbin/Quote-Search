#pragma once
#include "Quotes.h"
#include <fstream>
#include <msclr\marshal_cppstd.h>
#include <string>
#include "Quote.h"
#include "Author.h"

namespace CppWinForm1 {
	Quotes MyAuthorQuotes;

	int searchType = 0; //0 for unselected, 1 for letter search, 2 for binary search
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
			
			MyAuthorQuotes.resize(NumQuotes);

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
				MyAuthorQuotes.entry(tempQuote, i);
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
					MyAuthorQuotes.entry(tempQuote, i);
					//_Quotes[i].copy(tempQuote, tempAuthor);	//copy it over to _Quotes[i] and now it has the proper values
				}
			}
			userAddedQuotes.close();
			quoteList.close();

			MyAuthorQuotes.authorSelectionSort();

			//Quotes MyThemeQuotes = MyQuotes; //NOTE: this is a shallow copy. we need a copy function/constructor before we can sort by author
			//MyQuotes.themeSelectionSort();
			//note, themeSearchEvent has binary part commented out. after this is done we need to bring it back.
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  searchAllEvent;
	protected:

	protected:

	private: System::Windows::Forms::TextBox^  inputBar;

	protected:



	private: System::Windows::Forms::RichTextBox^  displayWindow;
	private: System::Windows::Forms::Button^  searchQuoteEvent;




	private: System::Windows::Forms::Button^  themeSearchEvent;
	private: System::Windows::Forms::Button^  authorSearchEvent;
	private: System::Windows::Forms::Button^  yearSearchEvent;
	private: System::Windows::Forms::Button^  displayAllEvent;
	private: System::Windows::Forms::RadioButton^  binaryOption;
	private: System::Windows::Forms::RadioButton^  letterOption;
	private: System::Windows::Forms::TextBox^  quoteAddBar;
	private: System::Windows::Forms::TextBox^  authorAddBar;
	private: System::Windows::Forms::TextBox^  themeAddBar;
	private: System::Windows::Forms::RichTextBox^  quotePreview;
	private: System::Windows::Forms::Button^  previewEvent;


	private: System::Windows::Forms::Button^  addQuoteEvent;


	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  deathAddBar;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::FlowLayoutPanel^  flowLayoutPanel1;
	private: System::Windows::Forms::TextBox^  birthAddBar;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	private: System::Windows::Forms::Label^  label1;


























	private: System::ComponentModel::IContainer^  components;







	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->searchAllEvent = (gcnew System::Windows::Forms::Button());
			this->inputBar = (gcnew System::Windows::Forms::TextBox());
			this->displayWindow = (gcnew System::Windows::Forms::RichTextBox());
			this->searchQuoteEvent = (gcnew System::Windows::Forms::Button());
			this->themeSearchEvent = (gcnew System::Windows::Forms::Button());
			this->authorSearchEvent = (gcnew System::Windows::Forms::Button());
			this->yearSearchEvent = (gcnew System::Windows::Forms::Button());
			this->displayAllEvent = (gcnew System::Windows::Forms::Button());
			this->binaryOption = (gcnew System::Windows::Forms::RadioButton());
			this->letterOption = (gcnew System::Windows::Forms::RadioButton());
			this->quoteAddBar = (gcnew System::Windows::Forms::TextBox());
			this->authorAddBar = (gcnew System::Windows::Forms::TextBox());
			this->themeAddBar = (gcnew System::Windows::Forms::TextBox());
			this->quotePreview = (gcnew System::Windows::Forms::RichTextBox());
			this->previewEvent = (gcnew System::Windows::Forms::Button());
			this->addQuoteEvent = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->deathAddBar = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->birthAddBar = (gcnew System::Windows::Forms::TextBox());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->flowLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// searchAllEvent
			// 
			this->searchAllEvent->Location = System::Drawing::Point(12, 38);
			this->searchAllEvent->Name = L"searchAllEvent";
			this->searchAllEvent->Size = System::Drawing::Size(102, 23);
			this->searchAllEvent->TabIndex = 0;
			this->searchAllEvent->Text = L"Search All";
			this->searchAllEvent->UseVisualStyleBackColor = true;
			this->searchAllEvent->Click += gcnew System::EventHandler(this, &MyForm::searchAllEvent_Click);
			// 
			// inputBar
			// 
			this->inputBar->Location = System::Drawing::Point(12, 12);
			this->inputBar->Name = L"inputBar";
			this->inputBar->Size = System::Drawing::Size(642, 20);
			this->inputBar->TabIndex = 2;
			this->inputBar->Text = L"Enter your search here";
			// 
			// displayWindow
			// 
			this->displayWindow->Location = System::Drawing::Point(12, 67);
			this->displayWindow->Name = L"displayWindow";
			this->displayWindow->Size = System::Drawing::Size(642, 579);
			this->displayWindow->TabIndex = 5;
			this->displayWindow->Text = L"";
			// 
			// searchQuoteEvent
			// 
			this->searchQuoteEvent->Location = System::Drawing::Point(120, 38);
			this->searchQuoteEvent->Name = L"searchQuoteEvent";
			this->searchQuoteEvent->Size = System::Drawing::Size(102, 23);
			this->searchQuoteEvent->TabIndex = 11;
			this->searchQuoteEvent->Text = L"Search Quotes";
			this->searchQuoteEvent->UseVisualStyleBackColor = true;
			this->searchQuoteEvent->Click += gcnew System::EventHandler(this, &MyForm::searchQuoteEvent_Click);
			// 
			// themeSearchEvent
			// 
			this->themeSearchEvent->Location = System::Drawing::Point(336, 38);
			this->themeSearchEvent->Name = L"themeSearchEvent";
			this->themeSearchEvent->Size = System::Drawing::Size(102, 23);
			this->themeSearchEvent->TabIndex = 14;
			this->themeSearchEvent->Text = L"Search Themes";
			this->themeSearchEvent->UseVisualStyleBackColor = true;
			this->themeSearchEvent->Click += gcnew System::EventHandler(this, &MyForm::themeSearchEvent_Click);
			// 
			// authorSearchEvent
			// 
			this->authorSearchEvent->Location = System::Drawing::Point(228, 38);
			this->authorSearchEvent->Name = L"authorSearchEvent";
			this->authorSearchEvent->Size = System::Drawing::Size(102, 23);
			this->authorSearchEvent->TabIndex = 15;
			this->authorSearchEvent->Text = L"Search Authors";
			this->authorSearchEvent->UseVisualStyleBackColor = true;
			this->authorSearchEvent->Click += gcnew System::EventHandler(this, &MyForm::authorSearchEvent_Click);
			// 
			// yearSearchEvent
			// 
			this->yearSearchEvent->Location = System::Drawing::Point(444, 38);
			this->yearSearchEvent->Name = L"yearSearchEvent";
			this->yearSearchEvent->Size = System::Drawing::Size(102, 23);
			this->yearSearchEvent->TabIndex = 16;
			this->yearSearchEvent->Text = L"Search Years";
			this->yearSearchEvent->UseVisualStyleBackColor = true;
			this->yearSearchEvent->Click += gcnew System::EventHandler(this, &MyForm::yearSearchEvent_Click);
			// 
			// displayAllEvent
			// 
			this->displayAllEvent->Location = System::Drawing::Point(552, 38);
			this->displayAllEvent->Name = L"displayAllEvent";
			this->displayAllEvent->Size = System::Drawing::Size(102, 23);
			this->displayAllEvent->TabIndex = 17;
			this->displayAllEvent->Text = L"Display All";
			this->displayAllEvent->UseVisualStyleBackColor = true;
			this->displayAllEvent->Click += gcnew System::EventHandler(this, &MyForm::displayAllEvent_Click);
			// 
			// binaryOption
			// 
			this->binaryOption->AutoSize = true;
			this->binaryOption->Location = System::Drawing::Point(660, 12);
			this->binaryOption->Name = L"binaryOption";
			this->binaryOption->Size = System::Drawing::Size(178, 17);
			this->binaryOption->TabIndex = 18;
			this->binaryOption->TabStop = true;
			this->binaryOption->Text = L"Search by Keywords and Letters";
			this->binaryOption->UseVisualStyleBackColor = true;
			this->binaryOption->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// letterOption
			// 
			this->letterOption->AutoSize = true;
			this->letterOption->Location = System::Drawing::Point(660, 41);
			this->letterOption->Name = L"letterOption";
			this->letterOption->Size = System::Drawing::Size(222, 17);
			this->letterOption->TabIndex = 19;
			this->letterOption->TabStop = true;
			this->letterOption->Text = L"Binary Search (Authors and Themes Only)";
			this->letterOption->UseVisualStyleBackColor = true;
			this->letterOption->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// quoteAddBar
			// 
			this->quoteAddBar->Location = System::Drawing::Point(3, 3);
			this->quoteAddBar->Name = L"quoteAddBar";
			this->quoteAddBar->Size = System::Drawing::Size(212, 20);
			this->quoteAddBar->TabIndex = 20;
			this->quoteAddBar->Text = L"Enter Quote Here";
			// 
			// authorAddBar
			// 
			this->authorAddBar->Location = System::Drawing::Point(3, 81);
			this->authorAddBar->Name = L"authorAddBar";
			this->authorAddBar->Size = System::Drawing::Size(212, 20);
			this->authorAddBar->TabIndex = 21;
			this->authorAddBar->Text = L"Enter Author Here";
			// 
			// themeAddBar
			// 
			this->themeAddBar->Location = System::Drawing::Point(3, 29);
			this->themeAddBar->Name = L"themeAddBar";
			this->themeAddBar->Size = System::Drawing::Size(212, 20);
			this->themeAddBar->TabIndex = 22;
			this->themeAddBar->Text = L"Enter Theme Here";
			// 
			// quotePreview
			// 
			this->quotePreview->Location = System::Drawing::Point(3, 214);
			this->quotePreview->Name = L"quotePreview";
			this->quotePreview->Size = System::Drawing::Size(212, 312);
			this->quotePreview->TabIndex = 23;
			this->quotePreview->Text = L"\n\n\n\n\n\n               Preview is shown here";
			// 
			// previewEvent
			// 
			this->previewEvent->Location = System::Drawing::Point(3, 185);
			this->previewEvent->Name = L"previewEvent";
			this->previewEvent->Size = System::Drawing::Size(212, 23);
			this->previewEvent->TabIndex = 24;
			this->previewEvent->Text = L"Preview Quote to Enter";
			this->previewEvent->UseVisualStyleBackColor = true;
			this->previewEvent->Click += gcnew System::EventHandler(this, &MyForm::previewEvent_Click);
			// 
			// addQuoteEvent
			// 
			this->addQuoteEvent->Location = System::Drawing::Point(3, 532);
			this->addQuoteEvent->Name = L"addQuoteEvent";
			this->addQuoteEvent->Size = System::Drawing::Size(212, 23);
			this->addQuoteEvent->TabIndex = 25;
			this->addQuoteEvent->Text = L"Add Quote";
			this->addQuoteEvent->UseVisualStyleBackColor = true;
			this->addQuoteEvent->Click += gcnew System::EventHandler(this, &MyForm::addQuoteEvent_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 169);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(212, 13);
			this->label2->TabIndex = 27;
			this->label2->Text = L"Click to Preview and ensure Input is correct";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 65);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(146, 13);
			this->label3->TabIndex = 28;
			this->label3->Text = L"If no Author available, enter 0";
			// 
			// deathAddBar
			// 
			this->deathAddBar->Location = System::Drawing::Point(3, 146);
			this->deathAddBar->Name = L"deathAddBar";
			this->deathAddBar->Size = System::Drawing::Size(212, 20);
			this->deathAddBar->TabIndex = 29;
			this->deathAddBar->Text = L"Enter Death-Year Here";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 104);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(137, 13);
			this->label4->TabIndex = 31;
			this->label4->Text = L"If no Year available, enter 0";
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->quoteAddBar);
			this->flowLayoutPanel1->Controls->Add(this->themeAddBar);
			this->flowLayoutPanel1->Controls->Add(this->label1);
			this->flowLayoutPanel1->Controls->Add(this->label3);
			this->flowLayoutPanel1->Controls->Add(this->authorAddBar);
			this->flowLayoutPanel1->Controls->Add(this->label4);
			this->flowLayoutPanel1->Controls->Add(this->birthAddBar);
			this->flowLayoutPanel1->Controls->Add(this->deathAddBar);
			this->flowLayoutPanel1->Controls->Add(this->label2);
			this->flowLayoutPanel1->Controls->Add(this->previewEvent);
			this->flowLayoutPanel1->Controls->Add(this->quotePreview);
			this->flowLayoutPanel1->Controls->Add(this->addQuoteEvent);
			this->flowLayoutPanel1->Location = System::Drawing::Point(660, 84);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(220, 562);
			this->flowLayoutPanel1->TabIndex = 32;
			this->flowLayoutPanel1->Visible = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(177, 13);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Ensure Author is properly capitalized";
			// 
			// birthAddBar
			// 
			this->birthAddBar->Location = System::Drawing::Point(3, 120);
			this->birthAddBar->Name = L"birthAddBar";
			this->birthAddBar->Size = System::Drawing::Size(212, 20);
			this->birthAddBar->TabIndex = 32;
			this->birthAddBar->Text = L"Enter Birth-Year Here";
			// 
			// linkLabel1
			// 
			this->linkLabel1->ActiveLinkColor = System::Drawing::SystemColors::ActiveCaption;
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->linkLabel1->LinkColor = System::Drawing::SystemColors::HotTrack;
			this->linkLabel1->Location = System::Drawing::Point(714, 61);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(124, 19);
			this->linkLabel1->TabIndex = 33;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"QUOTE ADDER";
			this->linkLabel1->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linkLabel1_LinkClicked);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(892, 658);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->flowLayoutPanel1);
			this->Controls->Add(this->letterOption);
			this->Controls->Add(this->binaryOption);
			this->Controls->Add(this->displayAllEvent);
			this->Controls->Add(this->yearSearchEvent);
			this->Controls->Add(this->authorSearchEvent);
			this->Controls->Add(this->themeSearchEvent);
			this->Controls->Add(this->searchQuoteEvent);
			this->Controls->Add(this->displayWindow);
			this->Controls->Add(this->inputBar);
			this->Controls->Add(this->searchAllEvent);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->flowLayoutPanel1->ResumeLayout(false);
			this->flowLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void searchAllEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ userInputSystemString;
	userInputSystemString = inputBar->Text;
	msclr::interop::marshal_context context;
	std::string userInput = context.marshal_as<std::string>(userInputSystemString); //convert System String to std string to use with existing code
	
	if (searchType == 0)
		displayWindow->Text = "Please select your desired method of search with the readio buttons to begin your search.";
	else if (searchType == 1)
	{
		std::string squiggle = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		std::string quoteIntro = "\tSearch Results Relating to Quotes\n";
		std::string authorIntro = "\tSearch Results Relating to Authors\n";
		std::string themeIntro = "\tSearch Results Relating to Themes\n";
		std::string yearIntro = "\tSearch Results Relating to Years\n";
		std::string currentSearchResult, endResult = "\n";

		//searching Quote
		currentSearchResult = MyAuthorQuotes.searchQuote(userInput);
		if (currentSearchResult != "0")
			endResult = endResult + squiggle + quoteIntro + squiggle + currentSearchResult;
		
		//searching Author
		currentSearchResult = MyAuthorQuotes.searchAuthor(userInput);
		if (currentSearchResult != "0")
			endResult = endResult + squiggle + quoteIntro + squiggle + currentSearchResult;

		//searching Theme
		currentSearchResult = MyAuthorQuotes.searchTheme(userInput);
		if (currentSearchResult != "0")
			endResult = endResult + squiggle + quoteIntro + squiggle + currentSearchResult;

		//searching Year
		currentSearchResult = MyAuthorQuotes.searchYear(userInput);
		if (currentSearchResult != "0")
			endResult = endResult + squiggle + quoteIntro + squiggle + currentSearchResult;

		if (endResult == "\n")
			endResult = "No Quote matches the given Input according to Letters, Authors, Themes, or Years.";

		String^ MyString = gcnew String(endResult.c_str()); //convert std string to System String to output in displayWindow
		displayWindow->Text = MyString;
	}
	else if (searchType == 2)
	{
		displayWindow->Text = "Binary Display can only be used for Themes and Authors. Please change Search-Type to Search All.";
	}
}

private: System::Void searchQuoteEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ userInputSystemString;
	userInputSystemString = inputBar->Text;

	msclr::interop::marshal_context context;
	std::string userInput = context.marshal_as<std::string>(userInputSystemString);
	
	if (searchType == 0)
		displayWindow->Text = "Please select your desired method of search with the readio buttons to begin your search.";
	else if (searchType == 1)
	{
		std::string searched = MyAuthorQuotes.searchQuote(userInput);

		String^ MyString = gcnew String(searched.c_str());

		displayWindow->Text = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\tSearch Results Relating to Quotes\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + MyString;
	}
	else if (searchType == 2)
		displayWindow->Text = "Binary Display can only be used for Themes and Authors. Please change Search-Type to Search All.";
}

private: System::Void authorSearchEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ userInputSystemString;
	userInputSystemString = inputBar->Text;
	msclr::interop::marshal_context context;
	std::string userInput = context.marshal_as<std::string>(userInputSystemString);

	if (searchType == 0)
		displayWindow->Text = "Please select your desired method of search with the readio buttons to begin your search.";

	else if (searchType == 1)
	{
		std::string searched = MyAuthorQuotes.searchAuthor(userInput);

		String^ MyString = gcnew String(searched.c_str());

		displayWindow->Text = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\tSearch Results Relating to Authors\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + MyString;
	}
	else if (searchType == 2)
	{
		int matchingIndex = MyAuthorQuotes.authorBinarySearch(userInput);
		if (matchingIndex == -1)
			displayWindow->Text = "No Results.\nAuthor does not exist.";
		else
		{
			std::string searched = MyAuthorQuotes.returnFullQuote(matchingIndex);
			String^ MyString = gcnew String(searched.c_str());
			displayWindow->Text = MyString;
		}
	}
}

private: System::Void themeSearchEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	
	String^ userInputSystemString;
	userInputSystemString = inputBar->Text;
	msclr::interop::marshal_context context;
	std::string userInput = context.marshal_as<std::string>(userInputSystemString);

	if (searchType == 0)
		displayWindow->Text = "Please select your desired method of search with the readio buttons to begin your search.";
	else if (searchType == 1)
	{
		std::string searched = MyAuthorQuotes.searchTheme(userInput);

		String^ MyString = gcnew String(searched.c_str());

		displayWindow->Text = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\tSearch Results Relating to Themes\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + MyString;
	}
	else if (searchType == 2)
	{
		/*
		int matchingIndex = MyThemeQuotes.themeBinarySearch(userInput);
		if (matchingIndex == -1)
			displayWindow->Text = "No Results.\nTheme does not exist.";
		else
		{
			std::string searched = MyQuotes.returnFullQuote(matchingIndex);
			String^ MyString = gcnew String(searched.c_str());

			displayWindow->Text = MyString;
		}
		*/
		displayWindow->Text = "No Quote object in theme-sorted-format exists yet. This feature will be completed and added soon.";
	}
}

private: System::Void yearSearchEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ userInputSystemString;
	userInputSystemString = inputBar->Text;
	msclr::interop::marshal_context context;
	std::string userInput = context.marshal_as<std::string>(userInputSystemString);
	
	if (searchType == 0)
		displayWindow->Text = "Please select your desired method of search with the readio buttons to begin your search.";
	else if (searchType == 1)
	{
		std::string searched = MyAuthorQuotes.searchTheme(userInput);

		String^ MyString = gcnew String(searched.c_str());

		displayWindow->Text = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\tSearch Results Relating to Years\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + MyString;
	}
	else if (searchType == 2)
	{
		displayWindow->Text = "Due to multiple Quotes sharing like years, a Binary Search is ineffective. Please use a Keyword/Letter Search instead.";
	}
}

private: System::Void displayAllEvent_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string searched = MyAuthorQuotes.displayAll();
		String^ MyString = gcnew String(searched.c_str());
		displayWindow->Text = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\t All Quotes\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" + MyString;
}
private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	searchType = 1;
}
private: System::Void radioButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	searchType = 2;
}

		 //QUOTE ADDER FUNCTIONS
private: System::Void previewEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ preview = quoteAddBar->Text + "\n" + themeAddBar->Text + "\n" + authorAddBar->Text 
		+ " ("  + birthAddBar->Text + " - " + deathAddBar->Text + ")";
	quotePreview->Text = preview;
}
private: System::Void addQuoteEvent_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ systemQuote = quoteAddBar->Text;
	String^ systemTheme = themeAddBar->Text;
	String^ systemAuthor = authorAddBar->Text;
	String^ systemBirth = birthAddBar->Text;
	String^ systemDeath = deathAddBar->Text;

	msclr::interop::marshal_context context;
	std::string quote = context.marshal_as<std::string>(systemQuote);
	std::string theme = context.marshal_as<std::string>(systemTheme);
	std::string author = context.marshal_as<std::string>(systemAuthor);
	std::string birth = context.marshal_as<std::string>(systemBirth);
	std::string death = context.marshal_as<std::string>(systemDeath);

	// checks for a number

	if (birth > "2020" || death > "2020")
		quotePreview->Text = "Quote-Add Failed! Make sure Birth-Year and Death-Year do not exceed 2020.";

	else if (birth >= "0" && birth <= "9" || birth >= "00" && birth <= "99" || birth >= "000" && birth <= "999" || birth >= "0000" && birth < "2020")
	{
		if (death >= "0" && death <= "9" || death >= "00" && death <= "99" || death >= "000" && death <= "999" || death >= "0000" && death < "2020")
		{
			MyAuthorQuotes.addQuote(quote, theme, author, birth, death);
			quotePreview->Text = "Quote successfully added!";
		}
		else
			quotePreview->Text = "Quote-Add Failed! Make sure Birth-Year and Death-Year are correct.";
	}
	else
		quotePreview->Text = "Quote-Add Failed! Make sure Birth-Year and Death-Year are correct.";
}
		 //shows and hides the Quote-Adder

private: System::Void linkLabel1_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	if(flowLayoutPanel1->Visible == false)
	flowLayoutPanel1->Visible = true;
	else if (flowLayoutPanel1->Visible == true)
		flowLayoutPanel1->Visible = false;
}
};
}