#pragma once
#include "RoundButton.h"
#include <string>
#define TIME_LIMIT 10
#define PLAYER_BASE_TIME 10

namespace Project2ChineseBoardGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Resources;
	using namespace cli;

	/// <summary>
	/// gameBoard 的摘要
	/// </summary>

	
	public ref class gameBoard : public System::Windows::Forms::Form
	{
	public: 
		array<RoundButton^, 2>^ btnGrid = gcnew array<RoundButton^, 2>(9, 10);
		int timeleft;
		int minutes, second;
		int blackTIME;
		int redTIME;
		bool exceed2MIN = false;
		bool buttonClicked = false;
	private: System::Windows::Forms::GroupBox^ TotalTIME;
	public:
	private: System::Windows::Forms::Label^ RedTotalTime;
	private: System::Windows::Forms::Label^ BlackTotalTime;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ TurnChangeTest;
	private: System::Windows::Forms::Label^ label2;
	public:
		String^ playerNow = "black";
		gameBoard(void)
		{
			
			InitializeComponent();
			generateButton();

			//
			//TODO:  在此加入建構函式程式碼
			//
		}

		void generateButton() {
			ResXResourceSet^ resources = gcnew ResXResourceSet("\chessImage.resx");
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

		void turnChange() {
			timer1->Stop();
			timeleft = TIME_LIMIT;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "分" + second + "秒";
			exceed2MIN = false;
			if (playerNow == "black") {
				PlayerNow->Text = L"紅方玩家";
				PlayerNow->ForeColor = System::Drawing::Color::Red;
				playerNow = "red";
			}
			else {
				PlayerNow->Text = L"黑方玩家";
				PlayerNow->ForeColor = System::Drawing::Color::Black;
				playerNow = "black";
			}
			timer1->Start();
		}

		void timerReset() {
			timeleft = TIME_LIMIT;
			blackTIME = PLAYER_BASE_TIME;
			redTIME = PLAYER_BASE_TIME;
			exceed2MIN = false;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "分" + second + "秒";
			minutes = blackTIME / 60;
			second = blackTIME % 60;
			BlackTotalTime->Text = minutes + "分" + second + "秒";
			minutes = redTIME / 60;
			second = redTIME % 60;
			RedTotalTime->Text = minutes + "分" + second + "秒";
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
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ PlayerNow;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ TimeText;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::Button^ surrender;
	private: System::Windows::Forms::Button^ exit;

	protected:

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(gameBoard::typeid));
			this->chessBoard = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->PlayerNow = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->TimeText = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->surrender = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->TotalTIME = (gcnew System::Windows::Forms::GroupBox());
			this->RedTotalTime = (gcnew System::Windows::Forms::Label());
			this->BlackTotalTime = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TurnChangeTest = (gcnew System::Windows::Forms::Button());
			this->TotalTIME->SuspendLayout();
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
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(795, 165);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(202, 40);
			this->label1->TabIndex = 1;
			this->label1->Text = L"現在回合:";
			// 
			// PlayerNow
			// 
			this->PlayerNow->AutoSize = true;
			this->PlayerNow->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->PlayerNow->Location = System::Drawing::Point(1003, 165);
			this->PlayerNow->Name = L"PlayerNow";
			this->PlayerNow->Size = System::Drawing::Size(181, 40);
			this->PlayerNow->TabIndex = 2;
			this->PlayerNow->Text = L"黑方玩家";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(795, 80);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(202, 40);
			this->label3->TabIndex = 3;
			this->label3->Text = L"剩餘時間:";
			// 
			// TimeText
			// 
			this->TimeText->AutoSize = true;
			this->TimeText->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TimeText->Location = System::Drawing::Point(1003, 80);
			this->TimeText->Name = L"TimeText";
			this->TimeText->Size = System::Drawing::Size(38, 40);
			this->TimeText->TabIndex = 4;
			this->TimeText->Text = L"0";
			// 
			// timer1
			// 
			this->timer1->Interval = 1000;
			this->timer1->Tick += gcnew System::EventHandler(this, &gameBoard::timer1_Tick);
			// 
			// surrender
			// 
			this->surrender->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->surrender->Location = System::Drawing::Point(984, 627);
			this->surrender->Name = L"surrender";
			this->surrender->Size = System::Drawing::Size(248, 68);
			this->surrender->TabIndex = 5;
			this->surrender->Text = L"投降";
			this->surrender->UseVisualStyleBackColor = true;
			this->surrender->Click += gcnew System::EventHandler(this, &gameBoard::button1_Click);
			// 
			// exit
			// 
			this->exit->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->exit->Location = System::Drawing::Point(984, 701);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(248, 68);
			this->exit->TabIndex = 6;
			this->exit->Text = L"退出遊戲";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &gameBoard::button2_Click);
			// 
			// TotalTIME
			// 
			this->TotalTIME->Controls->Add(this->RedTotalTime);
			this->TotalTIME->Controls->Add(this->BlackTotalTime);
			this->TotalTIME->Controls->Add(this->label4);
			this->TotalTIME->Controls->Add(this->label2);
			this->TotalTIME->Font = (gcnew System::Drawing::Font(L"標楷體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TotalTIME->Location = System::Drawing::Point(985, 396);
			this->TotalTIME->Name = L"TotalTIME";
			this->TotalTIME->Size = System::Drawing::Size(247, 151);
			this->TotalTIME->TabIndex = 8;
			this->TotalTIME->TabStop = false;
			this->TotalTIME->Text = L"總剩餘時間:";
			// 
			// RedTotalTime
			// 
			this->RedTotalTime->AutoSize = true;
			this->RedTotalTime->Font = (gcnew System::Drawing::Font(L"標楷體", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->RedTotalTime->Location = System::Drawing::Point(94, 93);
			this->RedTotalTime->Name = L"RedTotalTime";
			this->RedTotalTime->Size = System::Drawing::Size(26, 28);
			this->RedTotalTime->TabIndex = 3;
			this->RedTotalTime->Text = L"0";
			// 
			// BlackTotalTime
			// 
			this->BlackTotalTime->AutoSize = true;
			this->BlackTotalTime->Font = (gcnew System::Drawing::Font(L"標楷體", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->BlackTotalTime->Location = System::Drawing::Point(94, 42);
			this->BlackTotalTime->Name = L"BlackTotalTime";
			this->BlackTotalTime->Size = System::Drawing::Size(26, 28);
			this->BlackTotalTime->TabIndex = 2;
			this->BlackTotalTime->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"標楷體", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->ForeColor = System::Drawing::Color::Red;
			this->label4->Location = System::Drawing::Point(6, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(96, 28);
			this->label4->TabIndex = 1;
			this->label4->Text = L"紅方: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"標楷體", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(6, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(96, 28);
			this->label2->TabIndex = 0;
			this->label2->Text = L"黑方: ";
			// 
			// TurnChangeTest
			// 
			this->TurnChangeTest->Font = (gcnew System::Drawing::Font(L"標楷體", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TurnChangeTest->Location = System::Drawing::Point(984, 553);
			this->TurnChangeTest->Name = L"TurnChangeTest";
			this->TurnChangeTest->Size = System::Drawing::Size(248, 68);
			this->TurnChangeTest->TabIndex = 9;
			this->TurnChangeTest->Text = L"回合結束";
			this->TurnChangeTest->UseVisualStyleBackColor = true;
			this->TurnChangeTest->Click += gcnew System::EventHandler(this, &gameBoard::TurnChangeTest_Click);
			// 
			// gameBoard
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1244, 827);
			this->Controls->Add(this->TurnChangeTest);
			this->Controls->Add(this->TotalTIME);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->surrender);
			this->Controls->Add(this->TimeText);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->PlayerNow);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chessBoard);
			this->Name = L"gameBoard";
			this->Text = L"中國象棋";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &gameBoard::gameBoard_FormClosed);
			this->Load += gcnew System::EventHandler(this, &gameBoard::gameBoard_Load);
			this->TotalTIME->ResumeLayout(false);
			this->TotalTIME->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Grid_btn_click(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (!exceed2MIN) {
			timeleft--;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "分" + second + "秒";
		}
		else {
			if (playerNow == "black") {
				blackTIME--;
				minutes = blackTIME / 60;
				second = blackTIME % 60;
				BlackTotalTime->Text = minutes + "分" + second + "秒";
			}
			else {
				redTIME--;
				minutes = redTIME / 60;
				second = redTIME % 60;
				RedTotalTime->Text = minutes + "分" + second + "秒";
			}
		}
		if (timeleft == 0) {
			timeleft = TIME_LIMIT;
			exceed2MIN = true;
			//minutes = timeleft / 60;
			//second = timeleft % 60;
			return;
		}
		if (redTIME == 0) {
			timer1->Stop();
			MessageBox::Show("黑方玩家獲勝!");
			this->Close();
		}
		if (blackTIME == 0) {
			timer1->Stop();
			MessageBox::Show("紅方玩家獲勝!");
			this->Close();
		}
	}
	private: System::Void gameBoard_Load(System::Object^ sender, System::EventArgs^ e) {
		timerReset();
		timer1->Start();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ now = PlayerNow->Text;
		MessageBox::Show(now + "投降!");
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void gameBoard_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		timer1->Enabled = false;
	}
	private: System::Void TurnChangeTest_Click(System::Object^ sender, System::EventArgs^ e) {
		turnChange();
	}
};
}
