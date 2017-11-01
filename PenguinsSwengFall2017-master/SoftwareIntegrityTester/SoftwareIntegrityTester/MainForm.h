#pragma once

#include <msclr\marshal_cppstd.h>
#include "Weakness.h"
#include "UserSettings.h"
#include "FilterSettings.h"

#define VERSION "0.1.0"
#define VERSIONTEXT "Put Version Text Here"
#define HELPTEXT "To run the integrity checker:\n\n1) Click Open, then browse and select the file(s) to be checked.\n\n2) If applicable, click Filter by Weakness in the Filter menu and choose which weaknesses to filter.\n\n3) Click Run."
#define DEBUG true
#define SEPERATOR "---------------------------------\n"

namespace SoftwareIntegrityTester {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		//display version pop-up when app loads
		bool versionOnStart = false;

		//stores file content for all files that are opened
		List<String^>^fileContentList = gcnew List<String^>();
		//stores full file path of all the files that are opened
		List<String^>^ filepathList = gcnew List<String^>();
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  filterByWeaknessToolStripMenuItem;
	private: System::Windows::Forms::Button^  button1;

		List<Weakness^>^ weaknessList = gcnew List<Weakness^>();
		UserSettings^ userSettingsUI = gcnew UserSettings();
	public:
		MainForm(void)
		{
			InitializeComponent();

			versionLabel->Text = "Version " + VERSION;

			if (DEBUG)
				AllocConsole();

			weaknessList->Add(gcnew Weakness(gcnew System::String("Improper Handling of Undefined Values"), Weakness::Risk::High, 232));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Use of uninitialized variable"), Weakness::Risk::High, 457));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Null pointer dereference"), Weakness::Risk::High, 476));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Dead code"), Weakness::Risk::High, 561));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Infinite loop"), Weakness::Risk::High, 835));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Incorrect synchronization"), Weakness::Risk::High, 821));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Missing synchronization"), Weakness::Risk::High, 820));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Incorrect Calculation"), Weakness::Risk::High, 682));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Expression is always true"), Weakness::Risk::High, 571));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Expression is always false"), Weakness::Risk::High, 570));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Unused or redundant assignement"), Weakness::Risk::High, 563));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Division by zero"), Weakness::Risk::High, 369));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Race condition"), Weakness::Risk::High, 457));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Integer Overflow"), Weakness::Risk::High, 190));
			weaknessList->Add(gcnew Weakness(gcnew System::String("Integer Underflow"), Weakness::Risk::High, 191));		

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Void openButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if (userSettingsUI->useFullFilePath) {
				fileList->Items->Add(openFileDialog1->FileName);
				
			}
			else {
				fileList->Items->Add(openFileDialog1->SafeFileName);
				
			}
			
			filepathList->Add(openFileDialog1->FileName);

			String^ temp = "";
			System::IO::StreamReader^ sr = gcnew
				System::IO::StreamReader(openFileDialog1->FileName);
			temp = sr->ReadToEnd();
			fileContentList->Add(temp);
			sr->Close();
			if (DEBUG) {
				Console::WriteLine(
					"ADDED:\n" +
					temp + "\n" +
					openFileDialog1->FileName + "\n" +
					openFileDialog1->SafeFileName + "\n" +
					SEPERATOR);
			}
		}
	}
	private: System::Void runButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (fileList->Items->Count == 0)
			 {
			MessageBox::Show("Select Files to Run Test!");
			}
		else {
				String^ outputPath = "";
				String^ outputName = System::String::Format("{0:yyyy - MM - dd_hh - mm - ss - tt}", System::DateTime::Now) + ".txt";
				outputPath = UserSettings::path + "/" + outputName;
				if (!System::IO::File::Exists(outputPath)) {
				System::IO::File::CreateText(outputPath);				
				}		
			}		
	}
	public: bool isDisplayPathChecked = false; //Boolean to check if check box in settings is checked!

	private: System::Void removeSelectedFilesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		for (int i = fileList->SelectedIndices->Count - 1; i >= 0; i--) {
			int index = fileList->SelectedIndices[i];
			if (DEBUG) {
				Console::WriteLine(
					"REMOVING: index " + fileList->SelectedIndices[i] + "\n" +
					fileContentList[index] + "\n" +
					filepathList[index] + "\n" +
					fileList->Items[index]->ToString() + "\n");
				if (i == 0)
					Console::WriteLine(SEPERATOR);
			}

			fileContentList->RemoveAt(index);
			filepathList->RemoveAt(index);
			fileList->Items->RemoveAt(index);
		}
	}

	private: System::Void filterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void MainForm_Shown(System::Object^  sender, System::EventArgs^  e) {
		if (versionOnStart)
			MessageBox::Show(VERSION + "\n" + VERSIONTEXT);
	}

	//When Help -> Instructions is clicked:
	private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show(HELPTEXT, "Software Integrity Tester Instructions");
	}

	//When Filter -> Filter by weakness... is clicked:
	private: System::Void filterByWeaknessToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		FilterSettings^ fs = gcnew FilterSettings(weaknessList);
		fs->Show();
	}

	//When Settings button is clicked:
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		UserSettings^ us = gcnew UserSettings();
		us->Show();
	}


	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  removeSelectedFilesToolStripMenuItem;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  filterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::Button^  openButton;
	private: System::Windows::Forms::Button^  runButton;
	private: System::Windows::Forms::Label^  versionLabel;
	private: System::Windows::Forms::ListBox^  fileList;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->filterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->filterByWeaknessToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openButton = (gcnew System::Windows::Forms::Button());
				 this->runButton = (gcnew System::Windows::Forms::Button());
				 this->versionLabel = (gcnew System::Windows::Forms::Label());
				 this->fileList = (gcnew System::Windows::Forms::ListBox());
				 this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->removeSelectedFilesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->button1 = (gcnew System::Windows::Forms::Button());
				 this->menuStrip1->SuspendLayout();
				 this->contextMenuStrip1->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->filterToolStripMenuItem,
						 this->helpToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Padding = System::Windows::Forms::Padding(5, 2, 0, 2);
				 this->menuStrip1->Size = System::Drawing::Size(481, 28);
				 this->menuStrip1->TabIndex = 0;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // filterToolStripMenuItem
				 // 
				 this->filterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->filterByWeaknessToolStripMenuItem });
				 this->filterToolStripMenuItem->Name = L"filterToolStripMenuItem";
				 this->filterToolStripMenuItem->Size = System::Drawing::Size(54, 24);
				 this->filterToolStripMenuItem->Text = L"Filter";
				 // 
				 // filterByWeaknessToolStripMenuItem
				 // 
				 this->filterByWeaknessToolStripMenuItem->Name = L"filterByWeaknessToolStripMenuItem";
				 this->filterByWeaknessToolStripMenuItem->Size = System::Drawing::Size(212, 26);
				 this->filterByWeaknessToolStripMenuItem->Text = L"Filter by weakness...";
				 this->filterByWeaknessToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::filterByWeaknessToolStripMenuItem_Click);
				 // 
				 // helpToolStripMenuItem
				 // 
				 this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
				 this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
				 this->helpToolStripMenuItem->Size = System::Drawing::Size(53, 24);
				 this->helpToolStripMenuItem->Text = L"Help";
				 // 
				 // aboutToolStripMenuItem
				 // 
				 this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
				 this->aboutToolStripMenuItem->Size = System::Drawing::Size(168, 26);
				 this->aboutToolStripMenuItem->Text = L"How to use...";
				 this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
				 // 
				 // openButton
				 // 
				 this->openButton->Location = System::Drawing::Point(12, 353);
				 this->openButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->openButton->Name = L"openButton";
				 this->openButton->Size = System::Drawing::Size(120, 60);
				 this->openButton->TabIndex = 1;
				 this->openButton->Text = L"Open";
				 this->openButton->UseVisualStyleBackColor = true;
				 this->openButton->Click += gcnew System::EventHandler(this, &MainForm::openButton_Click);
				 // 
				 // runButton
				 // 
				 this->runButton->Location = System::Drawing::Point(137, 353);
				 this->runButton->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->runButton->Name = L"runButton";
				 this->runButton->Size = System::Drawing::Size(120, 60);
				 this->runButton->TabIndex = 2;
				 this->runButton->Text = L"Run";
				 this->runButton->UseVisualStyleBackColor = true;
				 // 
				 // versionLabel
				 // 
				 this->versionLabel->AutoSize = true;
				 this->versionLabel->Location = System::Drawing::Point(396, 423);
				 this->versionLabel->Name = L"versionLabel";
				 this->versionLabel->Size = System::Drawing::Size(56, 17);
				 this->versionLabel->TabIndex = 4;
				 this->versionLabel->Text = L"Version";
				 // 
				 // fileList
				 // 
				 this->fileList->ContextMenuStrip = this->contextMenuStrip1;
				 this->fileList->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->fileList->FormattingEnabled = true;
				 this->fileList->ItemHeight = 37;
				 this->fileList->Location = System::Drawing::Point(12, 42);
				 this->fileList->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->fileList->Name = L"fileList";
				 this->fileList->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
				 this->fileList->Size = System::Drawing::Size(457, 263);
				 this->fileList->TabIndex = 5;
				 // 
				 // contextMenuStrip1
				 // 
				 this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
				 this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->removeSelectedFilesToolStripMenuItem });
				 this->contextMenuStrip1->Name = L"contextMenuStrip1";
				 this->contextMenuStrip1->Size = System::Drawing::Size(227, 28);
				 // 
				 // removeSelectedFilesToolStripMenuItem
				 // 
				 this->removeSelectedFilesToolStripMenuItem->Name = L"removeSelectedFilesToolStripMenuItem";
				 this->removeSelectedFilesToolStripMenuItem->Size = System::Drawing::Size(226, 24);
				 this->removeSelectedFilesToolStripMenuItem->Text = L"Remove Selected Files";
				 this->removeSelectedFilesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::removeSelectedFilesToolStripMenuItem_Click);
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 // 
				 // button1
				 // 
				 this->button1->Location = System::Drawing::Point(542, 552);
				 this->button1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
				 this->button1->Name = L"button1";
				 this->button1->Size = System::Drawing::Size(108, 60);
				 this->button1->TabIndex = 6;
				 this->button1->Text = L"Settings";
				 this->button1->UseVisualStyleBackColor = true;
				 this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(481, 430);
				 this->Controls->Add(this->button1);
				 this->Controls->Add(this->fileList);
				 this->Controls->Add(this->versionLabel);
				 this->Controls->Add(this->runButton);
				 this->Controls->Add(this->openButton);
				 this->Controls->Add(this->menuStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->MainMenuStrip = this->menuStrip1;
				 this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
				 this->MaximizeBox = false;
				 this->MaximumSize = System::Drawing::Size(499, 477);
				 this->MinimumSize = System::Drawing::Size(499, 477);
				 this->Name = L"MainForm";
				 this->Text = L"Software Integrity Tester";
				 this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 this->contextMenuStrip1->ResumeLayout(false);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion


};
}
