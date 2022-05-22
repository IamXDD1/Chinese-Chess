#pragma once
#include "RoundButton.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <msclr\marshal_cppstd.h>
#include "Program.h"
#define TIME_LIMIT 120
#define PLAYER_BASE_TIME 1800


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
	/// gameBoard ���K�n
	/// </summary>


	public ref class gameBoard : public System::Windows::Forms::Form
	{
	public:
		GameManager* GM = new GameManager();
		File* file = new File();
		vector<string>* datas = new vector<string>;
		int datas_index;
		cli::array<RoundButton^, 2>^ btnGrid = gcnew cli::array<RoundButton^, 2>(9, 10);
		int totaltime;
		int timeleft;
		int minutes, second;
		int blackTIME;
		int redTIME;
		bool exceed2MIN = false;
		bool buttonClicked = false;
		// button for chess board click event
		RoundButton^ current;
		RoundButton^ target;
		double disx;
		double disy;
		int stepcount = 0;
		Point temp;
		//
		String^ playerNow = "red";
		bool loading = false;
		//bool* general_death = new bool;

		gameBoard(void)
		{
			srand(time(NULL));
			time_t now = time(0);
			string dt = to_string(rand());  //ctime(&now);
			string filename = "./game data/log_" + dt + ".txt";
			file->setFilename(filename);
			loading = false;
			InitializeComponent();
			nextStep->Visible = false;
			nextStep->Enabled = false;
			previousStep->Visible = false;
			previousStep->Enabled = false;
			generateButton();
			lockNonPlayerNowBtn();
			//*general_death = false;
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

		gameBoard(vector<string> data, File* inputfile)
		{
			delete file;
			file = inputfile;
			loading = true;
			InitializeComponent();
			label3->Visible = false;
			TimeText->Visible = false;
			timer1->Enabled = false;
			surrender->Enabled = false;
			surrender->Visible = false;
			TurnChangeTest->Visible = false;
			TurnChangeTest->Enabled = false;
			TotalTIME->Enabled = false;
			TotalTIME->Visible = false;
			TotalTimeCount->Visible = false;
			TotalTimeLabel->Visible = false;
			generateButton();
			lockAllBtn();
			delete datas;
			datas = new vector<string>(data);
			datas_index = 0;
			//*general_death = false;
			//
			//TODO:  �b���[�J�غc�禡�{���X
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
					btnGrid[i, j]->x = i;
					btnGrid[i, j]->y = j;
					btnGrid[i, j]->Location = Point(i * buttonSize + 5, j * buttonSize + 5);
					// set button's view to transparent
					btnGrid[i, j]->BackColor = Color::FromArgb(0, 255, 255, 255);
					btnGrid[i, j]->BringToFront();
					btnGrid[i, j]->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
					btnGrid[i, j]->FlatStyle = FlatStyle::Flat;
					btnGrid[i, j]->FlatAppearance->BorderSize = 0;
					// set button highlight when mouse hovering
					btnGrid[i, j]->FlatAppearance->MouseOverBackColor = Color::FromArgb(90, 32, 80, 191);
					btnGrid[i, j]->FlatAppearance->MouseDownBackColor = Color::Transparent;
					btnGrid[i, j]->MouseEnter += gcnew System::EventHandler(this, &gameBoard::Btn_Enter);
					btnGrid[i, j]->MouseLeave += gcnew System::EventHandler(this, &gameBoard::Btn_Leave);
				}
			}

			// initialize chess position
			btnGrid[0, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotB"))); btnGrid[0, 0]->isChessB = true;
			btnGrid[8, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotB"))); btnGrid[8, 0]->isChessB = true;
			btnGrid[0, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotR"))); btnGrid[0, 9]->isChessR = true;
			btnGrid[8, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"chariotR"))); btnGrid[8, 9]->isChessR = true;
			btnGrid[1, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseB"))); btnGrid[1, 0]->isChessB = true;
			btnGrid[7, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseB"))); btnGrid[7, 0]->isChessB = true;
			btnGrid[1, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseR"))); btnGrid[1, 9]->isChessR = true;
			btnGrid[7, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"horseR"))); btnGrid[7, 9]->isChessR = true;
			btnGrid[2, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantB"))); btnGrid[2, 0]->isChessB = true;
			btnGrid[6, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantB"))); btnGrid[6, 0]->isChessB = true;
			btnGrid[2, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantR"))); btnGrid[2, 9]->isChessR = true;
			btnGrid[6, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"elephantR"))); btnGrid[6, 9]->isChessR = true;
			btnGrid[3, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorB"))); btnGrid[3, 0]->isChessB = true;
			btnGrid[5, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorB"))); btnGrid[5, 0]->isChessB = true;
			btnGrid[3, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorR"))); btnGrid[3, 9]->isChessR = true;
			btnGrid[5, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"advisorR"))); btnGrid[5, 9]->isChessR = true;
			btnGrid[4, 0]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"generalB"))); btnGrid[4, 0]->isChessB = true;
			btnGrid[4, 9]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"generalR"))); btnGrid[4, 9]->isChessR = true;
			btnGrid[1, 2]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonB"))); btnGrid[1, 2]->isChessB = true;
			btnGrid[7, 2]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonB"))); btnGrid[7, 2]->isChessB = true;
			btnGrid[1, 7]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonR"))); btnGrid[1, 7]->isChessR = true;
			btnGrid[7, 7]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cannonR"))); btnGrid[7, 7]->isChessR = true;
			btnGrid[0, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB"))); btnGrid[0, 3]->isChessB = true;
			btnGrid[2, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB"))); btnGrid[2, 3]->isChessB = true;
			btnGrid[4, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB"))); btnGrid[4, 3]->isChessB = true;
			btnGrid[6, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB"))); btnGrid[6, 3]->isChessB = true;
			btnGrid[8, 3]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierB"))); btnGrid[8, 3]->isChessB = true;
			btnGrid[0, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR"))); btnGrid[0, 6]->isChessR = true;
			btnGrid[2, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR"))); btnGrid[2, 6]->isChessR = true;
			btnGrid[4, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR"))); btnGrid[4, 6]->isChessR = true;
			btnGrid[6, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR"))); btnGrid[6, 6]->isChessR = true;
			btnGrid[8, 6]->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"soldierR"))); btnGrid[8, 6]->isChessR = true;

		}

		void turnChange() {
			timer1->Stop();
			//if (general_death) 
			stalemate_and_checkmate();
			checkIfGameEnds();
			timeleft = TIME_LIMIT;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "��" + second + "��";
			exceed2MIN = false;
			if (playerNow == "black") {
				PlayerNow->Text = L"���誱�a";
				PlayerNow->ForeColor = System::Drawing::Color::Red;
				playerNow = "red";
			}
			else {
				PlayerNow->Text = L"�¤誱�a";
				PlayerNow->ForeColor = System::Drawing::Color::Black;
				playerNow = "black";
			}
			lockNonPlayerNowBtn();
			timer1->Start();
		}

		void timerReset() {
			timeleft = TIME_LIMIT;
			blackTIME = PLAYER_BASE_TIME;
			redTIME = PLAYER_BASE_TIME;
			totaltime = 0;
			TotalTimeLabel->Text = "0��0��";
			exceed2MIN = false;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "��" + second + "��";
			minutes = blackTIME / 60;
			second = blackTIME % 60;
			BlackTotalTime->Text = minutes + "��" + second + "��";
			minutes = redTIME / 60;
			second = redTIME % 60;
			RedTotalTime->Text = minutes + "��" + second + "��";
		}

		void buttonMove(RoundButton^ current, RoundButton^ target, vector<Pos>& cango) {
			if (!current->movable || (!loading && !GM->gameBoard.checkcango(target->x, target->y, cango))) {
				return;
			}
			int tempx = current->x;
			int tempy = current->y;
			current->x = target->x;
			current->y = target->y;
			target->x = tempx;
			target->y = tempy;
			temp = current->Location;
			disx = target->Location.X - current->Location.X;
			disy = target->Location.Y - current->Location.Y;
			RoundButton^ SwapT = btnGrid[tempx, tempy];
			btnGrid[tempx, tempy] = btnGrid[current->x, current->y];
			btnGrid[current->x, current->y] = SwapT;
			nextStep->Enabled = false;
			previousStep->Enabled = false;
			current->MouseEnter -= gcnew System::EventHandler(this, &gameBoard::Btn_Enter);
			current->MouseLeave -= gcnew System::EventHandler(this, &gameBoard::Btn_Leave);
			animation->Start();
		}

		void lockNonPlayerNowBtn() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					if (playerNow == "black") {
						if (btnGrid[i, j]->isChessB) {
							btnGrid[i, j]->movable = true;
						}
						else {
							btnGrid[i, j]->movable = false;
						}
					}
					else {
						if (btnGrid[i, j]->isChessR) {
							btnGrid[i, j]->movable = true;
						}
						else {
							btnGrid[i, j]->movable = false;
						}
					}
				}
			}
		}

		void lockAllBtn() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					btnGrid[i, j]->movable = false;
				}
			}
		}

		void unlockAllBtn() {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 10; j++) {
					btnGrid[i, j]->movable = true;
				}
			}
		}

		void ShowLegalPath(vector<Pos>& cango) {
			for (Pos it : cango) {
				btnGrid[it.x, it.y]->BackColor = Color::FromArgb(70, 255, 0, 0);
				if (btnGrid[it.x, it.y]->isChessB || btnGrid[it.x, it.y]->isChessR) {
					btnGrid[it.x, it.y]->Width = 80;
					btnGrid[it.x, it.y]->Height = 80;
					btnGrid[it.x, it.y]->FlatAppearance->MouseOverBackColor = Color::FromArgb(70, 255, 0, 0);
					btnGrid[it.x, it.y]->canBeChosen = true;
				}
			}
		}

		void HideLegalPath(vector<Pos>& cango) {
			for (Pos it : cango) {
				btnGrid[it.x, it.y]->BackColor = Color::FromArgb(0, 255, 255, 255);
				if (btnGrid[it.x, it.y]->isChessB || btnGrid[it.x, it.y]->isChessR) {
					btnGrid[it.x, it.y]->Width = 70;
					btnGrid[it.x, it.y]->Height = 70;
					btnGrid[it.x, it.y]->FlatAppearance->MouseOverBackColor = Color::FromArgb(90, 32, 80, 191);
					btnGrid[it.x, it.y]->canBeChosen = false;
				}
			}
		}

		void ChessKilled(RoundButton^ target) {
			target->isChessB = false;
			target->isChessR = false;
			target->movable = false;
			target->BackgroundImage = nullptr;
		}

		void checkIfGameEnds() {
			if (file->gameRecord.size() == 0) return;
			else if (file->gameRecord[file->gameRecord.size() - 1] == "Black Win") {
				timer1->Stop();
				TotalTimer->Stop();
				MessageBox::Show("�¤誱�a�ӧQ!");
				this->Close();
			}
			else if (file->gameRecord[file->gameRecord.size() - 1] == "Red Win") {
				timer1->Stop();
				TotalTimer->Stop();
				MessageBox::Show("���誱�a�ӧQ!");
				this->Close();
			}
			else {
				return;
			}
		}

		void fileOutput() {
			String^ filename = msclr::interop::marshal_as<String^>(file->filename);
			String^ str = "";

			for (int i = 0; i < file->gameRecord.size(); i++) {
				str += msclr::interop::marshal_as<String^>(file->gameRecord[i] + '\n');
			}
			System::IO::File::WriteAllText(filename, str);
		}

		void ContinueInTheMiddle() {
			label3->Visible = true;
			TimeText->Visible = true;
			timer1->Enabled = true;
			surrender->Enabled = true;
			surrender->Visible = true;
			TurnChangeTest->Visible = true;
			TurnChangeTest->Enabled = true;
			TotalTIME->Enabled = true;
			TotalTIME->Visible = true;
			nextStep->Visible = false;
			nextStep->Enabled = false;
			previousStep->Visible = false;
			previousStep->Enabled = false;
			TotalTimeCount->Visible = true;
			TotalTimeLabel->Visible = true;
			lockNonPlayerNowBtn();
			timer1->Stop();
			TotalTimer->Stop();
			timerReset();
			loading = false;
			timer1->Start();
			TotalTimer->Start();
			srand(time(NULL));
			time_t now = time(0);
			string dt = to_string(rand());  //ctime(&now);
			string filename = "./game data/log_" + dt + ".txt";
			file->setFilename(filename);
		}

		void stalemate_and_checkmate() {
			bool isCheckmate = false;
			Board::load_all_chess_cango();
			int color = (playerNow == "red") ? BLACK : RED;
			if (Board::ifMoveThenLose(isCheckmate, color))
			{
				if (color == BLACK) file->gameRecord.push_back("Red Win");
				else file->gameRecord.push_back("Black Win");
			}

			if (isCheckmate) {
				if (color == BLACK) MessageBox::Show("����N�x!");
				else MessageBox::Show("�¤�N�x!");
			}
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~gameBoard()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Panel^ chessBoard;
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::Label^ PlayerNow;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::Label^ TimeText;
		System::Windows::Forms::Timer^ timer1;
		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ surrender;
		System::Windows::Forms::Button^ exit;
		System::Windows::Forms::GroupBox^ TotalTIME;
		System::Windows::Forms::Label^ RedTotalTime;
		System::Windows::Forms::Label^ BlackTotalTime;
		System::Windows::Forms::Label^ label4;
		System::Windows::Forms::Button^ TurnChangeTest;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::Timer^ animation;
		System::Windows::Forms::Button^ nextStep;
		System::Windows::Forms::Button^ previousStep;
		System::Windows::Forms::Label^ TotalTimeLabel;
		System::Windows::Forms::Label^ TotalTimeCount;
		System::Windows::Forms::Timer^ TotalTimer;
	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
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
			this->animation = (gcnew System::Windows::Forms::Timer(this->components));
			this->nextStep = (gcnew System::Windows::Forms::Button());
			this->previousStep = (gcnew System::Windows::Forms::Button());
			this->TotalTimeLabel = (gcnew System::Windows::Forms::Label());
			this->TotalTimeCount = (gcnew System::Windows::Forms::Label());
			this->TotalTimer = (gcnew System::Windows::Forms::Timer(this->components));
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
			this->label1->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(795, 171);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(189, 40);
			this->label1->TabIndex = 1;
			this->label1->Text = L"�{�b�^�X:";
			// 
			// PlayerNow
			// 
			this->PlayerNow->AutoSize = true;
			this->PlayerNow->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->PlayerNow->ForeColor = System::Drawing::Color::Red;
			this->PlayerNow->Location = System::Drawing::Point(1003, 171);
			this->PlayerNow->Name = L"PlayerNow";
			this->PlayerNow->Size = System::Drawing::Size(181, 40);
			this->PlayerNow->TabIndex = 2;
			this->PlayerNow->Text = L"���誱�a";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(795, 107);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(189, 40);
			this->label3->TabIndex = 3;
			this->label3->Text = L"�Ѿl�ɶ�:";
			// 
			// TimeText
			// 
			this->TimeText->AutoSize = true;
			this->TimeText->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TimeText->Location = System::Drawing::Point(1003, 107);
			this->TimeText->Name = L"TimeText";
			this->TimeText->Size = System::Drawing::Size(42, 40);
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
			this->surrender->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->surrender->Location = System::Drawing::Point(984, 627);
			this->surrender->Name = L"surrender";
			this->surrender->Size = System::Drawing::Size(248, 68);
			this->surrender->TabIndex = 5;
			this->surrender->Text = L"�뭰";
			this->surrender->UseVisualStyleBackColor = true;
			this->surrender->Click += gcnew System::EventHandler(this, &gameBoard::button1_Click);
			// 
			// exit
			// 
			this->exit->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->exit->Location = System::Drawing::Point(984, 701);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(248, 68);
			this->exit->TabIndex = 6;
			this->exit->Text = L"�h�X�C��";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &gameBoard::button2_Click);
			// 
			// TotalTIME
			// 
			this->TotalTIME->Controls->Add(this->RedTotalTime);
			this->TotalTIME->Controls->Add(this->BlackTotalTime);
			this->TotalTIME->Controls->Add(this->label4);
			this->TotalTIME->Controls->Add(this->label2);
			this->TotalTIME->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TotalTIME->Location = System::Drawing::Point(985, 396);
			this->TotalTIME->Name = L"TotalTIME";
			this->TotalTIME->Size = System::Drawing::Size(247, 151);
			this->TotalTIME->TabIndex = 8;
			this->TotalTIME->TabStop = false;
			this->TotalTIME->Text = L"�`�Ѿl�ɶ�:";
			// 
			// RedTotalTime
			// 
			this->RedTotalTime->AutoSize = true;

			this->RedTotalTime->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->RedTotalTime->Location = System::Drawing::Point(94, 93);
			this->RedTotalTime->Name = L"RedTotalTime";
			this->RedTotalTime->Size = System::Drawing::Size(29, 28);
			this->RedTotalTime->TabIndex = 3;
			this->RedTotalTime->Text = L"0";
			// 
			// BlackTotalTime
			// 
			this->BlackTotalTime->AutoSize = true;
			this->BlackTotalTime->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->BlackTotalTime->Location = System::Drawing::Point(94, 42);
			this->BlackTotalTime->Name = L"BlackTotalTime";
			this->BlackTotalTime->Size = System::Drawing::Size(29, 28);
			this->BlackTotalTime->TabIndex = 2;
			this->BlackTotalTime->Text = L"0";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label4->ForeColor = System::Drawing::Color::Red;
			this->label4->Location = System::Drawing::Point(6, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(82, 28);
			this->label4->TabIndex = 1;
			this->label4->Text = L"����: ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(6, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(82, 28);
			this->label2->TabIndex = 0;
			this->label2->Text = L"�¤�: ";
			// 
			// TurnChangeTest
			// 
			this->TurnChangeTest->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TurnChangeTest->Location = System::Drawing::Point(984, 553);
			this->TurnChangeTest->Name = L"TurnChangeTest";
			this->TurnChangeTest->Size = System::Drawing::Size(248, 68);
			this->TurnChangeTest->TabIndex = 9;
			this->TurnChangeTest->Text = L"�^�X����";
			this->TurnChangeTest->UseVisualStyleBackColor = true;
			this->TurnChangeTest->Click += gcnew System::EventHandler(this, &gameBoard::TurnChangeTest_Click);
			// 
			// animation
			// 
			this->animation->Interval = 20;
			this->animation->Tick += gcnew System::EventHandler(this, &gameBoard::animation_Tick);
			// 
			// nextStep
			// 
			this->nextStep->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->nextStep->Location = System::Drawing::Point(1010, 257);
			this->nextStep->Name = L"nextStep";
			this->nextStep->Size = System::Drawing::Size(188, 63);
			this->nextStep->TabIndex = 10;
			this->nextStep->Text = L"�U�@�B";
			this->nextStep->UseVisualStyleBackColor = true;
			this->nextStep->Click += gcnew System::EventHandler(this, &gameBoard::nextStep_Click);
			// 
			// previousStep
			// 
			this->previousStep->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->previousStep->Location = System::Drawing::Point(802, 257);
			this->previousStep->Name = L"previousStep";
			this->previousStep->Size = System::Drawing::Size(188, 63);
			this->previousStep->TabIndex = 11;
			this->previousStep->Text = L"�q�o�̶}�l";
			this->previousStep->UseVisualStyleBackColor = true;
			this->previousStep->Click += gcnew System::EventHandler(this, &gameBoard::previousStep_Click);
			// 
			// TotalTimeLabel
			// 
			this->TotalTimeLabel->AccessibleDescription = L"";
			this->TotalTimeLabel->AutoSize = true;
			this->TotalTimeLabel->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TotalTimeLabel->Location = System::Drawing::Point(1003, 43);
			this->TotalTimeLabel->Name = L"TotalTimeLabel";
			this->TotalTimeLabel->Size = System::Drawing::Size(149, 40);
			this->TotalTimeLabel->TabIndex = 13;
			this->TotalTimeLabel->Text = L"0��0��";
			// 
			// TotalTimeCount
			// 
			this->TotalTimeCount->AutoSize = true;
			this->TotalTimeCount->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->TotalTimeCount->Location = System::Drawing::Point(795, 43);
			this->TotalTimeCount->Name = L"TotalTimeCount";
			this->TotalTimeCount->Size = System::Drawing::Size(202, 40);
			this->TotalTimeCount->TabIndex = 12;
			this->TotalTimeCount->Text = L"�C���p��:";
			// 
			// TotalTimer
			// 
			this->TotalTimer->Interval = 1000;
			this->TotalTimer->Tick += gcnew System::EventHandler(this, &gameBoard::TotalTimer_Tick);
			// 
			// gameBoard
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1244, 827);
			this->Controls->Add(this->TotalTimeLabel);
			this->Controls->Add(this->TotalTimeCount);
			this->Controls->Add(this->previousStep);
			this->Controls->Add(this->nextStep);
			this->Controls->Add(this->TurnChangeTest);
			this->Controls->Add(this->TotalTIME);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->surrender);
			this->Controls->Add(this->TimeText);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->PlayerNow);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->chessBoard);
			this->Font = (gcnew System::Drawing::Font(L"�رd�˭���W4(P)", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"gameBoard";
			this->Text = L"����H��";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &gameBoard::gameBoard_FormClosed);
			this->Load += gcnew System::EventHandler(this, &gameBoard::gameBoard_Load);
			this->TotalTIME->ResumeLayout(false);
			this->TotalTIME->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void Grid_btn_click(System::Object^ sender, System::EventArgs^ e) {
		RoundButton^ btn = (RoundButton^)sender;
		int x = btn->x;
		int y = btn->y;
		static vector<Pos> cango;
		if (buttonClicked) {
			target = btn;
			HideLegalPath(cango);
			GM->gameBoard.moveChess(file, current->x, current->y, target->x, target->y); //����洫
			buttonMove(current, target, cango);
			cango.clear();
			buttonClicked = false;
		}
		else {
			if (!btn->movable) {
				return;
			}
			Chess currChess = GM->gameBoard.getChess(x, y);
			GM->gameBoard.useChess(currChess, cango);
			ShowLegalPath(cango);
			current = btn;
			buttonClicked = true;
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		if (!exceed2MIN) {
			timeleft--;
			minutes = timeleft / 60;
			second = timeleft % 60;
			TimeText->Text = minutes + "��" + second + "��";
		}
		else {
			if (playerNow == "black") { // count black
				blackTIME--;
				minutes = blackTIME / 60;
				second = blackTIME % 60;
				BlackTotalTime->Text = minutes + "��" + second + "��";
			}
			else { // count red
				redTIME--;
				minutes = redTIME / 60;
				second = redTIME % 60;
				RedTotalTime->Text = minutes + "��" + second + "��";
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
			MessageBox::Show("����ɶ��ӺɡA�¤誱�a���!");
			this->Close();
		}
		if (blackTIME == 0) {
			timer1->Stop();
			MessageBox::Show("�¤�ɶ��ӺɡA���誱�a���!");
			this->Close();
		}
	}
	private: System::Void gameBoard_Load(System::Object^ sender, System::EventArgs^ e) {
		timerReset();
		timer1->Start();
		TotalTimer->Start();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ now = PlayerNow->Text;
		MessageBox::Show(now + "�뭰!");
		if (playerNow == "red") {
			file->gameRecord.push_back("Red surrender!");
			file->gameRecord.push_back("Black Win");
		}
		else {
			file->gameRecord.push_back("Black surrender!");
			file->gameRecord.push_back("Red Win");
		}
		checkIfGameEnds();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void gameBoard_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		timer1->Enabled = false;
		TotalTimer->Enabled = false;
		animation->Enabled = false;
		fileOutput();
		//delete general_death;
		delete datas;
		delete GM;
		delete file;

	}
	private: System::Void TurnChangeTest_Click(System::Object^ sender, System::EventArgs^ e) {
		turnChange();
	}
	private: System::Void animation_Tick(System::Object^ sender, System::EventArgs^ e) {
		stepcount++;
		double stepDISx = round(disx / 24.0);
		double stepDISy = round(disy / 24.0);
		current->Location = Point(current->Location.X + stepDISx, current->Location.Y + stepDISy);
		current->BringToFront();
		if (current->Location == target->Location) {
			stepcount = 0;
			target->Location = temp;
			ChessKilled(target);
			animation->Stop();
			current->MouseEnter += gcnew System::EventHandler(this, &gameBoard::Btn_Enter);
			current->MouseLeave += gcnew System::EventHandler(this, &gameBoard::Btn_Leave);
			//checkIfGameEnds();
			turnChange();
			nextStep->Enabled = true;
			previousStep->Enabled = true;
			return;
		}
		if (stepcount == 24) {
			current->Location = target->Location;
			stepcount = 0;
			target->Location = temp;
			ChessKilled(target);
			animation->Stop();
			current->MouseEnter += gcnew System::EventHandler(this, &gameBoard::Btn_Enter);
			current->MouseLeave += gcnew System::EventHandler(this, &gameBoard::Btn_Leave);
			//checkIfGameEnds();
			turnChange();
			nextStep->Enabled = true;
			previousStep->Enabled = true;
			return;
		}
	}
	private: System::Void Btn_Enter(System::Object^ sender, System::EventArgs^ e) {
		RoundButton^ btn = (RoundButton^)sender;
		if (btn->canBeChosen == true) return;
		if (btn->isChessB || btn->isChessR) {
			btn->Width = 80;
			btn->Height = 80;
		}
	}
	private: System::Void Btn_Leave(System::Object^ sender, System::EventArgs^ e) {
		RoundButton^ btn = (RoundButton^)sender;
		if (btn->canBeChosen == true) return;
		if (btn->isChessB || btn->isChessR) {
			btn->Width = 70;
			btn->Height = 70;
		}
	}
	private: System::Void nextStep_Click(System::Object^ sender, System::EventArgs^ e) {

		std::string inputData = datas->at(datas_index);
		if (inputData == "Red Win" || inputData == "Black Win") {
			file->gameRecord.push_back(inputData);
			checkIfGameEnds();
		}
		else if (inputData == "Red surrender!") {
			file->gameRecord.push_back(inputData);
			file->gameRecord.push_back("Black Win");
			MessageBox::Show("���誱�a�뭰!");
			checkIfGameEnds();
		}
		else if (inputData == "Black surrender!") {
			file->gameRecord.push_back(inputData);
			file->gameRecord.push_back("Red Win");
			MessageBox::Show("�¤誱�a�뭰!");
			checkIfGameEnds();
		}
		else {
			int x1 = -1, x2 = -1, y1 = -1, y2 = -1, color = -1;
			string charactor;
			file->Input(inputData, color, charactor, x1, y1, x2, y2);
			GM->gameBoard.moveChess(file, x1, y1, x2, y2, true);
			current = btnGrid[x1, y1];
			target = btnGrid[x2, y2];
			unlockAllBtn();
			vector<Pos> garbage;
			buttonMove(current, target, garbage);
			lockAllBtn();
		}

		datas_index++;
		if (datas_index >= datas->size()) ContinueInTheMiddle();
	}
	private: System::Void previousStep_Click(System::Object^ sender, System::EventArgs^ e) {
		ContinueInTheMiddle();
	}
	private: System::Void TotalTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
		totaltime++;
		int totalMin = totaltime / 60;
		int totalSec = totaltime % 60;
		TotalTimeLabel->Text = totalMin + "��" + totalSec + "��";
	}
	};
}