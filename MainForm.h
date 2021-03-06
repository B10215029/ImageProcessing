#pragma once
#include <Windows.h>
#include <gl\GL.h>
#include "Image.h"
#define SCALE_FACTOR 1.5

namespace ImageProcessing {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MainForm 的摘要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			this->progressTimer = gcnew System::Windows::Forms::Timer();
			this->progressTimer->Tick += gcnew System::EventHandler(this, &MainForm::progressTimer_Tick);
			this->panel1->MouseDown += (gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseDown));
			this->panel1->MouseUp += (gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseUp));
			this->panel1->MouseMove += (gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseMove));
			this->panel1->MouseWheel += (gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::panel1_MouseWheel));
			this->panel1->DragEnter += (gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragEnter));
			this->panel1->DragDrop += (gcnew System::Windows::Forms::DragEventHandler(this, &MainForm::panel1_DragDrop));
			this->panel1->AllowDrop = true;
			hDC = GetDC((HWND)(panel1->Handle.ToInt32()));
			hGLRC = initializeOpenGLContext(hDC);
			image = NULL;
			texture = 0;
			mouseX = -1;
			mouseY = -1;
			mouseDown = false;
			imageFileName = nullptr;
		}
		HGLRC initializeOpenGLContext(HDC hDC);
		void updateTexture();
		void draw();

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		HDC hDC;
		HGLRC hGLRC;
		Image* image;
		unsigned int texture;
		int mouseX;
		int mouseY;
		bool mouseDown;
		System::String^ imageFileName;
		System::Threading::Thread^ progressingThread;
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveImageToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  filterModeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  gLNEARESTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gLLINEARToolStripMenuItem;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  colorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  grayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  uniformQuantizationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  populosityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ditheringToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  naiveThresholdToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  brightnessPreservingThresholdToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  randomToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clusteredToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  floydSteinbergToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  colorFloydSteinbergToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  filteringToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  boxToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bartlettToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussianToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  arbitrarySizeGaussianToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  edgeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  enhanceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sizeRotateToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  halfToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  doubleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  arbitraryUniformScaleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rotationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  composingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  overToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  inToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  outToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  atopToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  xorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bonusToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  nPRToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::Timer^  progressTimer;
	private: System::Windows::Forms::ToolStripMenuItem^  reopenImageToolStripMenuItem;

	private: System::Windows::Forms::Panel^  panel1;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->reopenImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveImageToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->filterModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gLNEARESTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gLLINEARToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->grayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->uniformQuantizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->populosityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ditheringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->naiveThresholdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->brightnessPreservingThresholdToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->randomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clusteredToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->floydSteinbergToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorFloydSteinbergToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->filteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->boxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bartlettToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gaussianToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->arbitrarySizeGaussianToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->edgeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->enhanceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sizeRotateToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->halfToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->doubleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->arbitraryUniformScaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rotationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->composingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->overToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->inToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->outToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->atopToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->xorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bonusToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->nPRToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Location = System::Drawing::Point(0, 27);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(584, 509);
			this->panel1->TabIndex = 0;
			this->panel1->Resize += gcnew System::EventHandler(this, &MainForm::panel1_Resize);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {
				this->fileToolStripMenuItem,
					this->colorToolStripMenuItem, this->ditheringToolStripMenuItem, this->filteringToolStripMenuItem, this->sizeRotateToolStripMenuItem,
					this->composingToolStripMenuItem, this->bonusToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(584, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->reopenImageToolStripMenuItem,
					this->openImageToolStripMenuItem, this->saveImageToolStripMenuItem, this->toolStripSeparator1, this->filterModeToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(38, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// reopenImageToolStripMenuItem
			// 
			this->reopenImageToolStripMenuItem->Name = L"reopenImageToolStripMenuItem";
			this->reopenImageToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->reopenImageToolStripMenuItem->Text = L"Reopen Image";
			this->reopenImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::reopenImageToolStripMenuItem_Click);
			// 
			// openImageToolStripMenuItem
			// 
			this->openImageToolStripMenuItem->Name = L"openImageToolStripMenuItem";
			this->openImageToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->openImageToolStripMenuItem->Text = L"Open Image";
			this->openImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openImageToolStripMenuItem_Click);
			// 
			// saveImageToolStripMenuItem
			// 
			this->saveImageToolStripMenuItem->Name = L"saveImageToolStripMenuItem";
			this->saveImageToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->saveImageToolStripMenuItem->Text = L"Save Image";
			this->saveImageToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::saveImageToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(177, 6);
			// 
			// filterModeToolStripMenuItem
			// 
			this->filterModeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->gLNEARESTToolStripMenuItem,
					this->gLLINEARToolStripMenuItem
			});
			this->filterModeToolStripMenuItem->Name = L"filterModeToolStripMenuItem";
			this->filterModeToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->filterModeToolStripMenuItem->Text = L"Filter Mode";
			// 
			// gLNEARESTToolStripMenuItem
			// 
			this->gLNEARESTToolStripMenuItem->Checked = true;
			this->gLNEARESTToolStripMenuItem->CheckOnClick = true;
			this->gLNEARESTToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->gLNEARESTToolStripMenuItem->Name = L"gLNEARESTToolStripMenuItem";
			this->gLNEARESTToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->gLNEARESTToolStripMenuItem->Text = L"GL_NEAREST";
			this->gLNEARESTToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::gLNEARESTToolStripMenuItem_CheckedChanged);
			// 
			// gLLINEARToolStripMenuItem
			// 
			this->gLLINEARToolStripMenuItem->CheckOnClick = true;
			this->gLLINEARToolStripMenuItem->Name = L"gLLINEARToolStripMenuItem";
			this->gLLINEARToolStripMenuItem->Size = System::Drawing::Size(148, 22);
			this->gLLINEARToolStripMenuItem->Text = L"GL_LINEAR";
			this->gLLINEARToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::gLLINEARToolStripMenuItem_CheckedChanged);
			// 
			// colorToolStripMenuItem
			// 
			this->colorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->grayToolStripMenuItem,
					this->uniformQuantizationToolStripMenuItem, this->populosityToolStripMenuItem
			});
			this->colorToolStripMenuItem->Name = L"colorToolStripMenuItem";
			this->colorToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->colorToolStripMenuItem->Text = L"Color";
			// 
			// grayToolStripMenuItem
			// 
			this->grayToolStripMenuItem->Name = L"grayToolStripMenuItem";
			this->grayToolStripMenuItem->Size = System::Drawing::Size(196, 22);
			this->grayToolStripMenuItem->Text = L"Gray";
			this->grayToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::grayToolStripMenuItem_Click);
			// 
			// uniformQuantizationToolStripMenuItem
			// 
			this->uniformQuantizationToolStripMenuItem->Name = L"uniformQuantizationToolStripMenuItem";
			this->uniformQuantizationToolStripMenuItem->Size = System::Drawing::Size(196, 22);
			this->uniformQuantizationToolStripMenuItem->Text = L"Uniform Quantization";
			// 
			// populosityToolStripMenuItem
			// 
			this->populosityToolStripMenuItem->Name = L"populosityToolStripMenuItem";
			this->populosityToolStripMenuItem->Size = System::Drawing::Size(196, 22);
			this->populosityToolStripMenuItem->Text = L"Populosity";
			// 
			// ditheringToolStripMenuItem
			// 
			this->ditheringToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->naiveThresholdToolStripMenuItem,
					this->brightnessPreservingThresholdToolStripMenuItem, this->randomToolStripMenuItem, this->clusteredToolStripMenuItem, this->floydSteinbergToolStripMenuItem,
					this->colorFloydSteinbergToolStripMenuItem
			});
			this->ditheringToolStripMenuItem->Name = L"ditheringToolStripMenuItem";
			this->ditheringToolStripMenuItem->Size = System::Drawing::Size(71, 20);
			this->ditheringToolStripMenuItem->Text = L"Dithering";
			// 
			// naiveThresholdToolStripMenuItem
			// 
			this->naiveThresholdToolStripMenuItem->Name = L"naiveThresholdToolStripMenuItem";
			this->naiveThresholdToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->naiveThresholdToolStripMenuItem->Text = L"Naive Threshold";
			// 
			// brightnessPreservingThresholdToolStripMenuItem
			// 
			this->brightnessPreservingThresholdToolStripMenuItem->Name = L"brightnessPreservingThresholdToolStripMenuItem";
			this->brightnessPreservingThresholdToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->brightnessPreservingThresholdToolStripMenuItem->Text = L"Brightness Preserving Threshold ";
			// 
			// randomToolStripMenuItem
			// 
			this->randomToolStripMenuItem->Name = L"randomToolStripMenuItem";
			this->randomToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->randomToolStripMenuItem->Text = L"Random";
			// 
			// clusteredToolStripMenuItem
			// 
			this->clusteredToolStripMenuItem->Name = L"clusteredToolStripMenuItem";
			this->clusteredToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->clusteredToolStripMenuItem->Text = L"Clustered";
			// 
			// floydSteinbergToolStripMenuItem
			// 
			this->floydSteinbergToolStripMenuItem->Name = L"floydSteinbergToolStripMenuItem";
			this->floydSteinbergToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->floydSteinbergToolStripMenuItem->Text = L"Floyd-Steinberg";
			// 
			// colorFloydSteinbergToolStripMenuItem
			// 
			this->colorFloydSteinbergToolStripMenuItem->Name = L"colorFloydSteinbergToolStripMenuItem";
			this->colorFloydSteinbergToolStripMenuItem->Size = System::Drawing::Size(254, 22);
			this->colorFloydSteinbergToolStripMenuItem->Text = L"Color Floyd-Steinberg";
			// 
			// filteringToolStripMenuItem
			// 
			this->filteringToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->boxToolStripMenuItem,
					this->bartlettToolStripMenuItem, this->gaussianToolStripMenuItem, this->arbitrarySizeGaussianToolStripMenuItem, this->edgeToolStripMenuItem,
					this->enhanceToolStripMenuItem
			});
			this->filteringToolStripMenuItem->Name = L"filteringToolStripMenuItem";
			this->filteringToolStripMenuItem->Size = System::Drawing::Size(64, 20);
			this->filteringToolStripMenuItem->Text = L"Filtering";
			// 
			// boxToolStripMenuItem
			// 
			this->boxToolStripMenuItem->Name = L"boxToolStripMenuItem";
			this->boxToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->boxToolStripMenuItem->Text = L"Box";
			// 
			// bartlettToolStripMenuItem
			// 
			this->bartlettToolStripMenuItem->Name = L"bartlettToolStripMenuItem";
			this->bartlettToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->bartlettToolStripMenuItem->Text = L"Bartlett";
			// 
			// gaussianToolStripMenuItem
			// 
			this->gaussianToolStripMenuItem->Name = L"gaussianToolStripMenuItem";
			this->gaussianToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->gaussianToolStripMenuItem->Text = L"Gaussian";
			// 
			// arbitrarySizeGaussianToolStripMenuItem
			// 
			this->arbitrarySizeGaussianToolStripMenuItem->Name = L"arbitrarySizeGaussianToolStripMenuItem";
			this->arbitrarySizeGaussianToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->arbitrarySizeGaussianToolStripMenuItem->Text = L"Arbitrary-Size Gaussian";
			// 
			// edgeToolStripMenuItem
			// 
			this->edgeToolStripMenuItem->Name = L"edgeToolStripMenuItem";
			this->edgeToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->edgeToolStripMenuItem->Text = L"Edge";
			// 
			// enhanceToolStripMenuItem
			// 
			this->enhanceToolStripMenuItem->Name = L"enhanceToolStripMenuItem";
			this->enhanceToolStripMenuItem->Size = System::Drawing::Size(203, 22);
			this->enhanceToolStripMenuItem->Text = L"Enhance";
			// 
			// sizeRotateToolStripMenuItem
			// 
			this->sizeRotateToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->halfToolStripMenuItem,
					this->doubleToolStripMenuItem, this->arbitraryUniformScaleToolStripMenuItem, this->rotationToolStripMenuItem
			});
			this->sizeRotateToolStripMenuItem->Name = L"sizeRotateToolStripMenuItem";
			this->sizeRotateToolStripMenuItem->Size = System::Drawing::Size(90, 20);
			this->sizeRotateToolStripMenuItem->Text = L"Size&&Rotate";
			// 
			// halfToolStripMenuItem
			// 
			this->halfToolStripMenuItem->Name = L"halfToolStripMenuItem";
			this->halfToolStripMenuItem->Size = System::Drawing::Size(204, 22);
			this->halfToolStripMenuItem->Text = L"Half";
			// 
			// doubleToolStripMenuItem
			// 
			this->doubleToolStripMenuItem->Name = L"doubleToolStripMenuItem";
			this->doubleToolStripMenuItem->Size = System::Drawing::Size(204, 22);
			this->doubleToolStripMenuItem->Text = L"Double";
			// 
			// arbitraryUniformScaleToolStripMenuItem
			// 
			this->arbitraryUniformScaleToolStripMenuItem->Name = L"arbitraryUniformScaleToolStripMenuItem";
			this->arbitraryUniformScaleToolStripMenuItem->Size = System::Drawing::Size(204, 22);
			this->arbitraryUniformScaleToolStripMenuItem->Text = L"Arbitrary Uniform Scale";
			// 
			// rotationToolStripMenuItem
			// 
			this->rotationToolStripMenuItem->Name = L"rotationToolStripMenuItem";
			this->rotationToolStripMenuItem->Size = System::Drawing::Size(204, 22);
			this->rotationToolStripMenuItem->Text = L"Rotate";
			// 
			// composingToolStripMenuItem
			// 
			this->composingToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->overToolStripMenuItem,
					this->inToolStripMenuItem, this->outToolStripMenuItem, this->atopToolStripMenuItem, this->xorToolStripMenuItem
			});
			this->composingToolStripMenuItem->Name = L"composingToolStripMenuItem";
			this->composingToolStripMenuItem->Size = System::Drawing::Size(85, 20);
			this->composingToolStripMenuItem->Text = L"Composing";
			// 
			// overToolStripMenuItem
			// 
			this->overToolStripMenuItem->Name = L"overToolStripMenuItem";
			this->overToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->overToolStripMenuItem->Text = L"Over";
			this->overToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::overToolStripMenuItem_Click);
			// 
			// inToolStripMenuItem
			// 
			this->inToolStripMenuItem->Name = L"inToolStripMenuItem";
			this->inToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->inToolStripMenuItem->Text = L"In";
			// 
			// outToolStripMenuItem
			// 
			this->outToolStripMenuItem->Name = L"outToolStripMenuItem";
			this->outToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->outToolStripMenuItem->Text = L"Out";
			// 
			// atopToolStripMenuItem
			// 
			this->atopToolStripMenuItem->Name = L"atopToolStripMenuItem";
			this->atopToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->atopToolStripMenuItem->Text = L"Atop";
			// 
			// xorToolStripMenuItem
			// 
			this->xorToolStripMenuItem->Name = L"xorToolStripMenuItem";
			this->xorToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->xorToolStripMenuItem->Text = L"Xor";
			// 
			// bonusToolStripMenuItem
			// 
			this->bonusToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->nPRToolStripMenuItem });
			this->bonusToolStripMenuItem->Name = L"bonusToolStripMenuItem";
			this->bonusToolStripMenuItem->Size = System::Drawing::Size(53, 20);
			this->bonusToolStripMenuItem->Text = L"Bonus";
			// 
			// nPRToolStripMenuItem
			// 
			this->nPRToolStripMenuItem->Name = L"nPRToolStripMenuItem";
			this->nPRToolStripMenuItem->Size = System::Drawing::Size(99, 22);
			this->nPRToolStripMenuItem->Text = L"NPR";
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripStatusLabel1,
					this->toolStripProgressBar1
			});
			this->statusStrip1->Location = System::Drawing::Point(0, 539);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(584, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(467, 17);
			this->toolStripStatusLabel1->Spring = true;
			this->toolStripStatusLabel1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(100, 16);
			this->toolStripProgressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 561);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Controls->Add(this->panel1);
			this->Name = L"MainForm";
			this->Text = L"Image Processing";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Shown += gcnew System::EventHandler(this, &MainForm::MainForm_Shown);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void MainForm_Shown(System::Object^  sender, System::EventArgs^  e) {
	draw();
}
private: System::Void MainForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	if (progressingThread && progressingThread->IsAlive) {
		progressingThread->Abort();
	}
	if (image) {
		delete image;
	}
}
private: System::Void panel1_Resize(System::Object^  sender, System::EventArgs^  e) {
	draw();
}
private: System::Void gLNEARESTToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (this->gLNEARESTToolStripMenuItem->Checked) {
		this->gLLINEARToolStripMenuItem->Checked = false;
		updateTexture();
	}
}
private: System::Void gLLINEARToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (this->gLLINEARToolStripMenuItem->Checked) {
		this->gLNEARESTToolStripMenuItem->Checked = false;
		updateTexture();
	}
}
public: static Image* openImage(System::String^ imageFileName) {
	try {
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(imageFileName);
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height);
		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadOnly, bitmap->PixelFormat);
		unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
		Image *image;
		if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format24bppRgb) {
			image = new Image(bitmap->Width, bitmap->Height, data, false);
		}
		else if (bitmap->PixelFormat == System::Drawing::Imaging::PixelFormat::Format32bppArgb) {
			image = new Image(bitmap->Width, bitmap->Height, data);
		}
		bitmap->UnlockBits(bitmapData);
		return image;
	}
	catch (...) {
		return NULL;
	}
}
public: void setImage(Image* image) {
	if (this->image) {
		delete this->image;
	}
	this->image = image;
	updateTexture();
}
public: void setImage(System::String^ imageFileName) {
	this->imageFileName = imageFileName;
	setImage(openImage(imageFileName));
	this->toolStripStatusLabel1->Text = (this->image ? "Open image: " : "Can't open image: ") + imageFileName;
}
private: System::Void openImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		setImage(openFileDialog1->FileName);
	}
}
public: static bool saveImage(Image* image, System::String^ imageFileName) {
	try {
		System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(image->width, image->height, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bitmap->Width, bitmap->Height);
		System::Drawing::Imaging::BitmapData^ bitmapData = bitmap->LockBits(rect, System::Drawing::Imaging::ImageLockMode::WriteOnly, bitmap->PixelFormat);
		unsigned char* data = (unsigned char*)bitmapData->Scan0.ToPointer();
		for (int i = 0, n = image->width * image->height; i < n; i++) {
			data[i * 4 + 2] = image->data[i * 4 + 0];
			data[i * 4 + 1] = image->data[i * 4 + 1];
			data[i * 4 + 0] = image->data[i * 4 + 2];
			data[i * 4 + 3] = image->data[i * 4 + 3];
		}
		bitmap->UnlockBits(bitmapData);
		bitmap->Save(imageFileName, System::Drawing::Imaging::ImageFormat::Png);
		return true;
	}
	catch (...) {
		return false;
	}
}
public: void saveImage(System::String^ imageFileName) {
	this->toolStripStatusLabel1->Text = (saveImage(image, imageFileName) ? "Save image: " : "Can't save image: ") + imageFileName;
}
private: System::Void saveImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		saveImage(saveFileDialog1->FileName);
	}
}
private: System::Void panel1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mouseDown = true;
	mouseX = e->X;
	mouseY = e->Y;
}
private: System::Void panel1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	mouseDown = false;
}
private: System::Void panel1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (mouseDown && image) {
		image->offsetX += e->X - mouseX;
		image->offsetY += e->Y - mouseY;
		draw();
	}
	mouseX = e->X;
	mouseY = e->Y;
}
private: System::Void panel1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (image) {
		image->scale += e->Delta > 0 ? 1 : -1;
		image->offsetX += (image->offsetX - (e->X - panel1->Width / 2.0)) * ((e->Delta > 0 ? SCALE_FACTOR : (1.0 / SCALE_FACTOR)) - 1);
		image->offsetY += (image->offsetY - (e->Y - panel1->Height / 2.0)) * ((e->Delta > 0 ? SCALE_FACTOR : (1.0 / SCALE_FACTOR)) - 1);
		draw();
	}
}
private: System::Void panel1_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	System::String^ imageFileName = ((array<String^>^)(e->Data->GetData(DataFormats::FileDrop)))[0];
	setImage(imageFileName);
}
private: System::Void panel1_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	if (e->Data->GetDataPresent(DataFormats::FileDrop))
		e->Effect = DragDropEffects::Copy;
	else
		e->Effect = DragDropEffects::None;
}
private: System::Void progressTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
	if (image) {
		SetProgress(image->progress);
	}
}
private: System::Void reopenImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	if (imageFileName) {
		setImage(imageFileName);
	}
}
delegate void BoolArgReturningVoidDelegate(bool enable);
private: System::Void SetProgressTimerEnable(bool enable) {
	if (this->InvokeRequired) {
		this->Invoke(gcnew BoolArgReturningVoidDelegate(this, &MainForm::SetProgressTimerEnable), enable);
	}
	else {
		this->progressTimer->Enabled = enable;
	}
}
delegate void IntegerArgReturningVoidDelegate(int value);
private: System::Void SetProgress(int value) {
	if (this->toolStripProgressBar1->GetCurrentParent()->InvokeRequired) {
		this->toolStripProgressBar1->GetCurrentParent()->Invoke(gcnew IntegerArgReturningVoidDelegate(this, &MainForm::SetProgress), value);
	}
	else {
		this->toolStripProgressBar1->Value = min(max(value, 0), 100);
	}
}
delegate void StringArgReturningVoidDelegate(System::String^ str);
private: System::Void SetStatus(System::String^ str) {
	if (this->toolStripStatusLabel1->GetCurrentParent()->InvokeRequired) {
		this->toolStripStatusLabel1->GetCurrentParent()->Invoke(gcnew StringArgReturningVoidDelegate(this, &MainForm::SetStatus), str);
	}
	else {
		this->toolStripStatusLabel1->Text = str;
	}
}
private: System::Void runProcessing(Object^ args) {
	if (image && !this->progressTimer->Enabled) {
		SetProgressTimerEnable(true);
		//(image->*(*reinterpret_cast<ImageMethod*>(static_cast<System::IntPtr>(obj).ToPointer())))();
		if (dynamic_cast<ImageVoidArgFunctionObject^>(args)) {
			ImageVoidArgFunctionObject^ data = dynamic_cast<ImageVoidArgFunctionObject^>(args);
			(image->*data->func)();
		}
		else if (dynamic_cast<ImageImageArgFunctionObject^>(args)) {
			ImageImageArgFunctionObject^ data = dynamic_cast<ImageImageArgFunctionObject^>(args);
			(image->*data->func)(data->image);
			delete data->image;
		}
		SetProgressTimerEnable(false);
		SetProgress(0);
		updateTexture();
	}
}
private: System::Void startProcessing(ImageVoidArgFunctionObject::FunctionType func) {
	if (image && !this->progressTimer->Enabled) {
		progressingThread = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(this, &MainForm::runProcessing));
		progressingThread->Start(gcnew ImageVoidArgFunctionObject(func));
	}
}
private: System::Void startProcessing(ImageImageArgFunctionObject::FunctionType func) {
	if (image && !this->progressTimer->Enabled && openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		progressingThread = gcnew System::Threading::Thread(gcnew System::Threading::ParameterizedThreadStart(this, &MainForm::runProcessing));
		progressingThread->Start(gcnew ImageImageArgFunctionObject(func, openImage(openFileDialog1->FileName)));
	}
}
private: System::Void grayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	startProcessing(&Image::gray);
}
private: System::Void overToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	startProcessing(&Image::over);
}
};
}
