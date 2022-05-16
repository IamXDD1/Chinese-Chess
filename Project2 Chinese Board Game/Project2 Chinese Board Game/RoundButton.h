#pragma once

namespace Project2ChineseBoardGame {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace cli;

	public ref class RoundButton : Button { // circle button method
	public:
		bool isChessB = false;
		bool isChessR = false;
		bool movable = false;
	protected:
		void OnPaint(PaintEventArgs^ e) override {
			GraphicsPath^ grPath = gcnew GraphicsPath();
			grPath->AddEllipse(0, 0, ClientSize.Width, ClientSize.Height);
			this->Region = gcnew System::Drawing::Region(grPath);
			Button::OnPaint(e);
		}
	
	};
}