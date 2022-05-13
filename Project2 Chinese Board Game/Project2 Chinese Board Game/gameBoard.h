#pragma once
#include "RoundButton.h"

namespace Project2ChineseBoardGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace cli;

	/// <summary>
	/// gameBoard 的摘要
	/// </summary>

	
	public ref class gameBoard : public System::Windows::Forms::Form
	{
	public: 
		array<RoundButton^, 2>^ btnGrid = gcnew array<RoundButton^, 2>(9, 10);
		gameBoard(void)
		{
			
			InitializeComponent();
			generateButton();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

		void generateButton() {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(gameBoard::typeid));
			int buttonSize = chessBoard->Width / 9;
			// make board match size
			chessBoard->Width = chessBoard->Height * 0.9;

			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					btnGrid[i, j] = gcnew RoundButton();
					btnGrid[i, j]->Height = 70;
					btnGrid[i, j]->Width = 70;
					// add click event
					btnGrid[i, j]->Click += gcnew System::EventHandler(this, &gameBoard::Grid_btn_click);
					// add button to chess board
					chessBoard->Controls->Add(btnGrid[i, j]);
					btnGrid[i, j]->Location = Point(i * buttonSize + 5, j * buttonSize + 5);
					// set button's view to transparent
					btnGrid[i, j]->BackColor = Color::FromArgb(0, 255, 255, 255);
					btnGrid[i, j]->BringToFront();
					btnGrid[i, j]->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
					btnGrid[i, j]->FlatStyle = FlatStyle::Flat;
					btnGrid[i, j]->FlatAppearance->BorderSize = 0;
					// set button highlight when mouse hovering
					btnGrid[i, j]->FlatAppearance->MouseOverBackColor = Color::FromArgb(50, 32, 80, 191);
					btnGrid[i, j]->FlatAppearance->MouseDownBackColor = Color::Transparent;
					
				}
			}

			// initialize chess position
			btnGrid[0, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotB")));
			btnGrid[8, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotB")));
			btnGrid[0, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotR")));
			btnGrid[8, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotR")));
			btnGrid[1, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseB")));
			btnGrid[7, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseB")));
			btnGrid[1, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseR")));
			btnGrid[7, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseR")));
			btnGrid[2, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantB")));
			btnGrid[6, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantB")));
			btnGrid[2, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantR")));
			btnGrid[6, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantR")));
			btnGrid[3, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorB")));
			btnGrid[5, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorB")));
			btnGrid[3, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorR"))); 
			btnGrid[5, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorR")));
			btnGrid[4, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"generalB")));
			btnGrid[4, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"generalR")));
			btnGrid[1, 2]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonB")));
			btnGrid[7, 2]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonB")));
			btnGrid[1, 7]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonR")));
			btnGrid[7, 7]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonR")));
			btnGrid[0, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB")));
			btnGrid[2, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB")));
			btnGrid[4, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB")));
			btnGrid[6, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB")));
			btnGrid[8, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB")));
			btnGrid[0, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR")));
			btnGrid[2, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR")));
			btnGrid[4, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR")));
			btnGrid[6, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR")));
			btnGrid[8, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR")));

		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~gameBoard()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ chessBoard;





	protected:

	protected:

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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(gameBoard::typeid));
			this->chessBoard = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// chessBoard
			// 
			this->chessBoard->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chessBoard.BackgroundImage")));
			this->chessBoard->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->chessBoard->ImeMode = System::Windows::Forms::ImeMode::Off;
			this->chessBoard->Location = System::Drawing::Point(12, 12);
			this->chessBoard->Name = L"chessBoard";
			this->chessBoard->Size = System::Drawing::Size(720, 800);
			this->chessBoard->TabIndex = 0;
			// 
			// gameBoard
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1234, 827);
			this->Controls->Add(this->chessBoard);
			this->Name = L"gameBoard";
			this->Text = L"gameBoard";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Grid_btn_click(System::Object^ sender, System::EventArgs^ e) {

	}
	};
}
