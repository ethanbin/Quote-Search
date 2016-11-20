#pragma once
#include "Quotes.h"
#include "MyForm.h"
#include<fstream>
#include"Quotes.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	msclr::interop::marshal_context context;
	std::string arg0 = context.marshal_as<std::string>(args[0]); //quotes.txt
	std::string arg1 = context.marshal_as<std::string>(args[1]); //user_added_quotes.txt

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CppWinForm1::MyForm form(arg0, arg1);
	Application::Run(%form);
}
