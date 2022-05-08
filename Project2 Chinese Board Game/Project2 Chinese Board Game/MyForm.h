#pragma once
#include "gameBoard.h"

namespace Project2ChineseBoardGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}
		

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
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



	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->Title = (gcnew System::Windows::Forms::Label());
			this->GameStart = (gcnew System::Windows::Forms::Button());
			this->LoadGame = (gcnew System::Windows::Forms::Button());
			this->EndGame = (gcnew System::Windows::Forms::Button());
			this->author = (gcnew System::Windows::Forms::Label());
			this->Github = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// Title
			// 
			this->Title->AutoSize = true;
			this->Title->Font = (gcnew System::Drawing::Font(L"華康竹風體W4", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Title->Location = System::Drawing::Point(222, 106);
			this->Title->Name = L"Title";
			this->Title->Size = System::Drawing::Size(358, 80);
			this->Title->TabIndex = 0;
			this->Title->Text = L"中國象棋";
			this->Title->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GameStart
			// 
			this->GameStart->Font = (gcnew System::Drawing::Font(L"華康竹風體W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->GameStart->Location = System::Drawing::Point(74, 277);
			this->GameStart->Name = L"GameStart";
			this->GameStart->Size = System::Drawing::Size(204, 86);
			this->GameStart->TabIndex = 1;
			this->GameStart->Text = L"開始遊戲";
			this->GameStart->UseVisualStyleBackColor = true;
			this->GameStart->Click += gcnew System::EventHandler(this, &MyForm::GameStart_Click);
			// 
			// LoadGame
			// 
			this->LoadGame->Font = (gcnew System::Drawing::Font(L"華康竹風體W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LoadGame->Location = System::Drawing::Point(74, 385);
			this->LoadGame->Name = L"LoadGame";
			this->LoadGame->Size = System::Drawing::Size(204, 86);
			this->LoadGame->TabIndex = 2;
			this->LoadGame->Text = L"讀取遊戲";
			this->LoadGame->UseVisualStyleBackColor = true;
			this->LoadGame->Click += gcnew System::EventHandler(this, &MyForm::LoadGame_Click);
			// 
			// EndGame
			// 
			this->EndGame->Font = (gcnew System::Drawing::Font(L"華康竹風體W4", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->EndGame->Location = System::Drawing::Point(74, 493);
			this->EndGame->Name = L"EndGame";
			this->EndGame->Size = System::Drawing::Size(204, 86);
			this->EndGame->TabIndex = 3;
			this->EndGame->Text = L"遊戲結束";
			this->EndGame->UseVisualStyleBackColor = true;
			this->EndGame->Click += gcnew System::EventHandler(this, &MyForm::EndGame_Click);
			// 
			// author
			// 
			this->author->AutoSize = true;
			this->author->Font = (gcnew System::Drawing::Font(L"Consolas", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->author->Location = System::Drawing::Point(554, 277);
			this->author->Name = L"author";
			this->author->Size = System::Drawing::Size(207, 56);
			this->author->TabIndex = 4;
			this->author->Text = L"Author:\r\nB11030037吳秉諺";
			// 
			// Github
			// 
			this->Github->AutoSize = true;
			this->Github->Font = (gcnew System::Drawing::Font(L"Consolas", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Github->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->Github->LinkColor = System::Drawing::Color::Black;
			this->Github->Location = System::Drawing::Point(581, 546);
			this->Github->Name = L"Github";
			this->Github->Size = System::Drawing::Size(180, 33);
			this->Github->TabIndex = 5;
			this->Github->TabStop = true;
			this->Github->Text = L"Github Repo";
			this->Github->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::Github_LinkClicked);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(800, 688);
			this->Controls->Add(this->Github);
			this->Controls->Add(this->author);
			this->Controls->Add(this->EndGame);
			this->Controls->Add(this->LoadGame);
			this->Controls->Add(this->GameStart);
			this->Controls->Add(this->Title);
			this->Name = L"MyForm";
			this->Text = L"Chinese Chess";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void GameStart_Click(System::Object^ sender, System::EventArgs^ e) {
		gameBoard^ board = gcnew gameBoard{};
		this->Hide();
		board->ShowDialog();
		this->Show();

	}

	private: System::Void LoadGame_Click(System::Object^ sender, System::EventArgs^ e) {

	}
	
	private: System::Void Github_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		this->Github->LinkVisited = true;
		System::Diagnostics::Process::Start("https://github.com/IamXDD1/Chinese-Chess");
	}
	private: System::Void EndGame_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
