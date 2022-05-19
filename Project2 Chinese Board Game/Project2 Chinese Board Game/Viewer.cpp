#include "Viewer.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThread]

void main(cli::array<String^>^ args)

{

    Application::EnableVisualStyles();

    Application::SetCompatibleTextRenderingDefault(false);

    Project2ChineseBoardGame::Viewer form;

    Application::Run(% form);

}