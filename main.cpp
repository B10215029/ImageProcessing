#include "MainForm.h"

[System::STAThreadAttribute]
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ImageProcessing::MainForm form;
	if (lpCmdLine[0]) {
		form.openImage(gcnew System::String(lpCmdLine));
	}
	System::Windows::Forms::Application::Run(%form);
}

[System::STAThreadAttribute]
int main(int argc, char* argv[]) {
	ImageProcessing::MainForm form;
	if (argc >= 2) {
		form.openImage(gcnew System::String(argv[1]));
	}
	System::Windows::Forms::Application::Run(%form);
}
