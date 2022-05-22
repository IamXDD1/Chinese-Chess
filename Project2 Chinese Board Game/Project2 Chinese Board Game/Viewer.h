#pragma once
#include "gameBoard.h"
#include "Program.h"

namespace Project2ChineseBoardGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Viewer ���K�n
	/// </summary>
	public ref class Viewer : public System::Windows::Forms::Form
	{
	public:
		Viewer(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}
		

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~Viewer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ Title;
	protected:
	private: System::Windows::Forms::Button^ GameStart;
	private: System::Windows::Forms::Button^ LoadGame;
	private: System::Windows::Forms::Button^ EndGame;
	private: System::Windows::Forms::Label^ author;
	private: System::Windows::Forms::LinkLabel^ Github;
	private: System::Windows::Forms::OpenFileDialog^ FileLoading;




	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Viewer::typeid));
			this->Title = (gcnew System::Windows::Forms::Label());
			this->GameStart = (gcnew System::Windows::Forms::Button());
			this->LoadGame = (gcnew System::Windows::Forms::Button());
			this->EndGame = (gcnew System::Windows::Forms::Button());
			this->author = (gcnew System::Windows::Forms::Label());
			this->Github = (gcnew System::Windows::Forms::LinkLabel());
			this->FileLoading = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SuspendLayout();
			// 
			// Title
			// 
			this->Title->AutoSize = true;
			this->Title->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Title->Location = System::Drawing::Point(248, 90);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(358, 80);
			this->Title->TabIndex = 0;
			this->Title->Text = L"����H��";
			this->Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GameStart
			// 
			this->GameStart->BackColor = System::Drawing::Color::Transparent;
			this->GameStart->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->GameStart->Location = System::Drawing::Point(74, 277);
			this->GameStart->Name = L"GameStart";
			this->GameStart->Size = System::Drawing::Size(204, 86);
			this->GameStart->TabIndex = 1;
			this->GameStart->Text = L"�}�l�C��";
			this->GameStart->UseVisualStyleBackColor = false;
			this->GameStart->Click += gcnew System::EventHandler(this, &Viewer::GameStart_Click);
			// 
			// LoadGame
			// 
			this->LoadGame->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LoadGame->ForeColor = System::Drawing::SystemColors::ControlText;
			this->LoadGame->Location = System::Drawing::Point(74, 385);
			this->LoadGame->Name = L"LoadGame";
			this->LoadGame->Size = System::Drawing::Size(204, 86);
			this->LoadGame->TabIndex = 2;
			this->LoadGame->Text = L"Ū���C��";
			this->LoadGame->UseVisualStyleBackColor = true;
			this->LoadGame->Click += gcnew System::EventHandler(this, &Viewer::LoadGame_Click);
			// 
			// EndGame
			// 
			this->EndGame->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->EndGame->Location = System::Drawing::Point(74, 493);
			this->EndGame->Name = L"EndGame";
			this->EndGame->Size = System::Drawing::Size(204, 86);
			this->EndGame->TabIndex = 3;
			this->EndGame->Text = L"�C������";
			this->EndGame->UseVisualStyleBackColor = true;
			this->EndGame->Click += gcnew System::EventHandler(this, &Viewer::EndGame_Click);
			// 
			// author
			// 
			this->author->AutoSize = true;
			this->author->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->author->Location = System::Drawing::Point(582, 277);
			this->author->Name = L"author";
			this->author->Size = System::Drawing::Size(209, 168);
			this->author->TabIndex = 4;
			this->author->Text = L"Author:\r\n\r\nB11030037�d�ÿ�\r\n\r\nB11030021�嵾�M\r\n\r\nB11030001���l�Y";
			this->author->Click += gcnew System::EventHandler(this, &Viewer::author_Click);
			// 
			// Github
			// 
			this->Github->AutoSize = true;
			this->Github->Font = (gcnew System::Drawing::Font(L"Consolas", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Github->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->Github->LinkColor = System::Drawing::Color::Black;
			this->Github->Location = System::Drawing::Point(609, 546);
			this->Github->Name = L"Github";
			this->Github->Size = System::Drawing::Size(180, 33);
			this->Github->TabIndex = 5;
			this->Github->TabStop = true;
			this->Github->Text = L"Github Repo";
			this->Github->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Viewer::Github_LinkClicked);
			// 
			// Viewer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(838, 643);
			this->Controls->Add(this->Github);
			this->Controls->Add(this->author);
			this->Controls->Add(this->EndGame);
			this->Controls->Add(this->LoadGame);
			this->Controls->Add(this->GameStart);
			this->Controls->Add(this->Title);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Viewer";
			this->Text = L"����H��";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void GameStart_Click(System::Object^ sender, System::EventArgs^ e) {
		do {
			gameBoard^ board = gcnew gameBoard{};
			this->Hide();
			board->ShowDialog();
			delete board;
		} while (MessageBox::Show("Do you want a new game?","", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes);
		this->Show();
	}

	private: System::Void LoadGame_Click(System::Object^ sender, System::EventArgs^ e) {
		File* file = new File();
		if (FileLoading->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ fname = FileLoading->FileName;
			vector<string> data;
			file->setFilename(msclr::interop::marshal_as<string>(fname));
			if(file->Load(data)){
				gameBoard^ board = gcnew gameBoard(data, file);
				this->Hide();
				board->ShowDialog();
				delete board;
				this->Show();
			}
		}
	}
	
	private: System::Void Github_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		this->Github->LinkVisited = true;
		System::Diagnostics::Process::Start("https://github.com/IamXDD1/Chinese-Chess");
	}
	private: System::Void EndGame_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void author_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
