#include "MainForm.h"

[System::STAThreadAttribute]
int main(array<System::String^>^ args) {
	ImageProcessing::MainForm form;
	System::Windows::Forms::Application::Run(%form);
}
