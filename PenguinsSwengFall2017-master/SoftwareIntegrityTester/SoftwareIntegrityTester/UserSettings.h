#pragma once

namespace SoftwareIntegrityTester {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for UserSettings
	/// </summary>
	public ref class UserSettings : public System::Windows::Forms::Form
	{
	
		String^ tempPath = "";
	public:
		UserSettings(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UserSettings()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		UserSettings::Visible = false;
	}
	private: System::Void outputDesinationBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		FolderBrowserDialog^ folderBrowserDialog1 = gcnew FolderBrowserDialog();
		folderBrowserDialog1->RootFolder = Environment::SpecialFolder::Desktop;
		folderBrowserDialog1->Description = "Select Output Destination";
		folderBrowserDialog1->ShowNewFolderButton = true;
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			tempPath = folderBrowserDialog1->SelectedPath;
		}

		displayPath->Text = tempPath;
	}
	
	//When Save button is clicked, path is saved. Sets boolean to true or false if checkbox is checked.
	private: System::Void saveBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		path = tempPath;
		if (checkBox1->Checked == true)
		{
			
		}
	}


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  saveBtn;
	private: System::Windows::Forms::Button^  outputDesinationBtn;
	public: static String^ path = Environment::GetFolderPath(Environment::SpecialFolder::Desktop);
	private: System::Windows::Forms::TextBox^  displayPath;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::CheckBox^  checkBox1;

	public:

	public:

	public:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->saveBtn = (gcnew System::Windows::Forms::Button());
			this->outputDesinationBtn = (gcnew System::Windows::Forms::Button());
			this->displayPath = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(391, 391);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(159, 65);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Close";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &UserSettings::button1_Click);
			// 
			// saveBtn
			// 
			this->saveBtn->AccessibleDescription = L"";
			this->saveBtn->Location = System::Drawing::Point(225, 391);
			this->saveBtn->Margin = System::Windows::Forms::Padding(4);
			this->saveBtn->Name = L"saveBtn";
			this->saveBtn->Size = System::Drawing::Size(159, 65);
			this->saveBtn->TabIndex = 1;
			this->saveBtn->Text = L"Save";
			this->saveBtn->UseVisualStyleBackColor = true;
			this->saveBtn->Click += gcnew System::EventHandler(this, &UserSettings::saveBtn_Click);
			// 
			// outputDesinationBtn
			// 
			this->outputDesinationBtn->Location = System::Drawing::Point(269, 31);
			this->outputDesinationBtn->Margin = System::Windows::Forms::Padding(4);
			this->outputDesinationBtn->Name = L"outputDesinationBtn";
			this->outputDesinationBtn->Size = System::Drawing::Size(236, 27);
			this->outputDesinationBtn->TabIndex = 3;
			this->outputDesinationBtn->Text = L"Select Output Directory";
			this->outputDesinationBtn->UseVisualStyleBackColor = true;
			this->outputDesinationBtn->Click += gcnew System::EventHandler(this, &UserSettings::outputDesinationBtn_Click);
			// 
			// displayPath
			// 
			this->displayPath->Location = System::Drawing::Point(167, 66);
			this->displayPath->Margin = System::Windows::Forms::Padding(4);
			this->displayPath->Name = L"displayPath";
			this->displayPath->ReadOnly = true;
			this->displayPath->Size = System::Drawing::Size(443, 22);
			this->displayPath->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(31, 66);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(116, 17);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Output Directory:";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(167, 124);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(219, 21);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = L"Display Full File Path(s) in List";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// UserSettings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(773, 470);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->displayPath);
			this->Controls->Add(this->outputDesinationBtn);
			this->Controls->Add(this->saveBtn);
			this->Controls->Add(this->button1);
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"UserSettings";
			this->Text = L"User Settings";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
};
}
