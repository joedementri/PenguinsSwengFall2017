#pragma once
#include "Weakness.h"
namespace SoftwareIntegrityTester {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for FilterSettings
	/// </summary>
	public ref class FilterSettings : public System::Windows::Forms::Form
	{
		List<Weakness^>^ weaknessList = gcnew List<Weakness^>();
	public:
		FilterSettings(List<Weakness^>^ weakList)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			weaknessList = weakList;
			for each (Weakness^ w in weaknessList)
			{
				wList->Items->Add(w);
			}
			//all checkboxes are checked by default
			for (int i = 0; i < wList->Items->Count; i++)
			{
				wList->SetItemChecked(i, true);
			}


			propLabel->Visible = false;
			linkLabel1->Visible = false;
			linkLabel1->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(this, &FilterSettings::linkLabel1Clicked);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FilterSettings()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckedListBox^  wList;
	protected:

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  propLabel;
	private: System::Windows::Forms::LinkLabel^  linkLabel1;
	protected:

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
			this->wList = (gcnew System::Windows::Forms::CheckedListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->propLabel = (gcnew System::Windows::Forms::Label());
			this->linkLabel1 = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// wList
			// 
			this->wList->FormattingEnabled = true;
			this->wList->Location = System::Drawing::Point(9, 10);
			this->wList->Margin = System::Windows::Forms::Padding(2);
			this->wList->Name = L"wList";
			this->wList->Size = System::Drawing::Size(266, 304);
			this->wList->TabIndex = 0;
			this->wList->SelectedIndexChanged += gcnew System::EventHandler(this, &FilterSettings::wList_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(294, 10);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(85, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Properties:";
			// 
			// propLabel
			// 
			this->propLabel->AutoSize = true;
			this->propLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->propLabel->Location = System::Drawing::Point(294, 46);
			this->propLabel->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->propLabel->Name = L"propLabel";
			this->propLabel->Size = System::Drawing::Size(0, 17);
			this->propLabel->TabIndex = 2;
			// 
			// linkLabel1
			// 
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->Location = System::Drawing::Point(295, 180);
			this->linkLabel1->Name = L"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(55, 13);
			this->linkLabel1->TabIndex = 3;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = L"linkLabel1";
			// 
			// FilterSettings
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(659, 372);
			this->Controls->Add(this->linkLabel1);
			this->Controls->Add(this->propLabel);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->wList);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"FilterSettings";
			this->Text = L"FilterSettings";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		private: System::Void linkLabel1Clicked(System::Object^  sender, LinkLabelLinkClickedEventArgs^ e)
		{
			linkLabel1->LinkVisited = true;
			System::Diagnostics::Process::Start(weaknessList[wList->SelectedIndex]->getCweLink());
		}
	private: System::Void wList_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		Weakness^ w = weaknessList[wList->SelectedIndex];
		propLabel->Visible = true;
		propLabel->Text = w->toString();
		if (!w->getCweLink()->IsNullOrEmpty(w->getCweLink())) {
			linkLabel1->Visible = true;
			linkLabel1->LinkVisited = false;
			linkLabel1->Text = w->getCweLink();
		}
		else {
			linkLabel1->Visible = false;
		}
	}
	};
}