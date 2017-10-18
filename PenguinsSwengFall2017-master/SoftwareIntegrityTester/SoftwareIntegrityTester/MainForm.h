#pragma once

#include <msclr\marshal_cppstd.h>

#define VERSION "0.1.0"
#define VERSIONTEXT "Put Version Text Here"
#define HELPTEXT "Put Help Text Here"
#define DEBUG true
#define SEPERATOR "---------------------------------\n"

namespace SoftwareIntegrityTester {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;

	public enum class Priority { Low, Normal, Critical };
	public enum class Risk { Low, Med, High };

	 ref struct Weakness {
		String^ name;
		Priority priority;
		Risk risk;
		String^ solution;
		Weakness(String^ n, Priority p, Risk r, String^ s) :
			name(n), priority(p), risk(r), solution(s) {
		}
		String^ toString() {
			return name +"\nPriority:"+ priority.ToString() + "\nRisk: " + risk.ToString() + "\nSolution:\n" + solution +"\n";
		}
	};
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
		//display version pop-up when app loads
		bool versionOnStart = true;

		//stores file content for all files that are opened
		List<String^>^fileContentList = gcnew List<String^>();
		//stores full file path of all the files that are opened
		List<String^>^ filepathList = gcnew List<String^>();

		List<Weakness^>^ weaknessList = gcnew List<Weakness^>();
		
	public:
		MainForm(void)
		{
			InitializeComponent();

			versionLabel->Text = "Version " + VERSION;
			if (DEBUG)
				AllocConsole();
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
			fileList->Items->Add(openFileDialog1->SafeFileName);
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
	private: System::Void helpToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		MessageBox::Show(HELPTEXT);
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
				 this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openButton = (gcnew System::Windows::Forms::Button());
				 this->runButton = (gcnew System::Windows::Forms::Button());
				 this->versionLabel = (gcnew System::Windows::Forms::Label());
				 this->fileList = (gcnew System::Windows::Forms::ListBox());
				 this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
				 this->removeSelectedFilesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
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
				 this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
				 this->menuStrip1->Size = System::Drawing::Size(363, 24);
				 this->menuStrip1->TabIndex = 0;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // filterToolStripMenuItem
				 // 
				 this->filterToolStripMenuItem->Name = L"filterToolStripMenuItem";
				 this->filterToolStripMenuItem->Size = System::Drawing::Size(45, 20);
				 this->filterToolStripMenuItem->Text = L"Filter";
				 // 
				 // helpToolStripMenuItem
				 // 
				 this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
				 this->helpToolStripMenuItem->Size = System::Drawing::Size(44, 20);
				 this->helpToolStripMenuItem->Text = L"Help";
				 this->helpToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::helpToolStripMenuItem_Click);
				 // 
				 // openButton
				 // 
				 this->openButton->Location = System::Drawing::Point(9, 287);
				 this->openButton->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
				 this->openButton->Name = L"openButton";
				 this->openButton->Size = System::Drawing::Size(90, 49);
				 this->openButton->TabIndex = 1;
				 this->openButton->Text = L"Open";
				 this->openButton->UseVisualStyleBackColor = true;
				 this->openButton->Click += gcnew System::EventHandler(this, &MainForm::openButton_Click);
				 // 
				 // runButton
				 // 
				 this->runButton->Location = System::Drawing::Point(103, 287);
				 this->runButton->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
				 this->runButton->Name = L"runButton";
				 this->runButton->Size = System::Drawing::Size(90, 49);
				 this->runButton->TabIndex = 2;
				 this->runButton->Text = L"Run";
				 this->runButton->UseVisualStyleBackColor = true;
				 // 
				 // versionLabel
				 // 
				 this->versionLabel->AutoSize = true;
				 this->versionLabel->Location = System::Drawing::Point(297, 344);
				 this->versionLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
				 this->versionLabel->Name = L"versionLabel";
				 this->versionLabel->Size = System::Drawing::Size(42, 13);
				 this->versionLabel->TabIndex = 4;
				 this->versionLabel->Text = L"Version";
				 // 
				 // fileList
				 // 
				 this->fileList->ContextMenuStrip = this->contextMenuStrip1;
				 this->fileList->Font = (gcnew System::Drawing::Font(L"Calibri", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->fileList->FormattingEnabled = true;
				 this->fileList->ItemHeight = 29;
				 this->fileList->Location = System::Drawing::Point(9, 34);
				 this->fileList->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
				 this->fileList->Name = L"fileList";
				 this->fileList->SelectionMode = System::Windows::Forms::SelectionMode::MultiExtended;
				 this->fileList->Size = System::Drawing::Size(344, 236);
				 this->fileList->TabIndex = 5;
				 // 
				 // contextMenuStrip1
				 // 
				 this->contextMenuStrip1->ImageScalingSize = System::Drawing::Size(32, 32);
				 this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->removeSelectedFilesToolStripMenuItem });
				 this->contextMenuStrip1->Name = L"contextMenuStrip1";
				 this->contextMenuStrip1->Size = System::Drawing::Size(191, 26);
				 // 
				 // removeSelectedFilesToolStripMenuItem
				 // 
				 this->removeSelectedFilesToolStripMenuItem->Name = L"removeSelectedFilesToolStripMenuItem";
				 this->removeSelectedFilesToolStripMenuItem->Size = System::Drawing::Size(190, 22);
				 this->removeSelectedFilesToolStripMenuItem->Text = L"Remove Selected Files";
				 this->removeSelectedFilesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::removeSelectedFilesToolStripMenuItem_Click);
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 // 
				 // MainForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(363, 357);
				 this->Controls->Add(this->fileList);
				 this->Controls->Add(this->versionLabel);
				 this->Controls->Add(this->runButton);
				 this->Controls->Add(this->openButton);
				 this->Controls->Add(this->menuStrip1);
				 this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
				 this->MainMenuStrip = this->menuStrip1;
				 this->Margin = System::Windows::Forms::Padding(2, 2, 2, 2);
				 this->MaximizeBox = false;
				 this->MaximumSize = System::Drawing::Size(379, 396);
				 this->MinimumSize = System::Drawing::Size(379, 396);
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
