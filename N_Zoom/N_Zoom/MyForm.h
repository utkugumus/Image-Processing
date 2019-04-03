#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "Fonk.h"
#include <stdlib.h>
#include <string>
namespace NZoom {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	int width, height;
	
	LPCTSTR input;
	long size;
	BYTE* buffer;
	//int* orgmatris;
	BYTE* raw_intensity;
	BYTE* gecici;
	int ilk_x, ilk_y;
	int son_x, son_y;
	bool ciz = false;
	bool kutuici = false;
	bool zoom = false;
	bool crop = false;
	float fxmask[9] = { 1,2,1,0,0,0,(-1),(-2),(-1) };
	float fymask[9] = { 1,0,(-1),2,0,(-2),1,0,(-1) };

	int matris[9] = { 1,1,1,1,1,1,1,1,1 };
	/// <summary>
	/// MyForm için özet
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		
		int* hist = new int[256];
	
		Bitmap ^ surface;
		Bitmap ^ kesik;
		Bitmap ^ binary;
		Bitmap ^ etikett;
		Graphics^ g;
		Pen^ pen;
		Bitmap ^ zoomer;
		int box_width, box_height;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeansToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  findObjectToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  histogramEqualizedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ddxToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cizToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fxyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;

	public:
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	public:

		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Oluþturucu kodunu buraya ekle
			//
		}

	protected:
		/// <summary>
		///Kullanýlan tüm kaynaklarý temizleyin.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ýntensityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cropToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  zoomToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;

	private:
		/// <summary>
		///Gerekli tasarýmcý deðiþkeni.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Tasarýmcý desteði için gerekli metot - bu metodun 
		///içeriðini kod düzenleyici ile deðiþtirmeyin.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ýntensityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cropToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zoomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kMeansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->findObjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramEqualizedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ddxToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cizToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fxyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->saveToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(820, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->ýntensityToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
			// 
			// ýntensityToolStripMenuItem
			// 
			this->ýntensityToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->cropToolStripMenuItem,
					this->zoomToolStripMenuItem, this->histogramToolStripMenuItem, this->ddxToolStripMenuItem, this->cizToolStripMenuItem, this->fxyToolStripMenuItem
			});
			this->ýntensityToolStripMenuItem->Name = L"ýntensityToolStripMenuItem";
			this->ýntensityToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->ýntensityToolStripMenuItem->Text = L"Intensity";
			this->ýntensityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ýntensityToolStripMenuItem_Click);
			// 
			// cropToolStripMenuItem
			// 
			this->cropToolStripMenuItem->Name = L"cropToolStripMenuItem";
			this->cropToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->cropToolStripMenuItem->Text = L"Crop";
			this->cropToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cropToolStripMenuItem_Click);
			// 
			// zoomToolStripMenuItem
			// 
			this->zoomToolStripMenuItem->Name = L"zoomToolStripMenuItem";
			this->zoomToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->zoomToolStripMenuItem->Text = L"Zoom";
			this->zoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::zoomToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->kMeansToolStripMenuItem,
					this->findObjectToolStripMenuItem, this->histogramEqualizedToolStripMenuItem
			});
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramToolStripMenuItem_Click);
			// 
			// kMeansToolStripMenuItem
			// 
			this->kMeansToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->dilationToolStripMenuItem,
					this->erosionToolStripMenuItem, this->openingToolStripMenuItem, this->closingToolStripMenuItem
			});
			this->kMeansToolStripMenuItem->Name = L"kMeansToolStripMenuItem";
			this->kMeansToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->kMeansToolStripMenuItem->Text = L"KMeans";
			this->kMeansToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansToolStripMenuItem_Click);
			// 
			// dilationToolStripMenuItem
			// 
			this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
			this->dilationToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->dilationToolStripMenuItem->Text = L"Dilation";
			this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
			// 
			// erosionToolStripMenuItem
			// 
			this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
			this->erosionToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->erosionToolStripMenuItem->Text = L"Erosion";
			this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
			// 
			// openingToolStripMenuItem
			// 
			this->openingToolStripMenuItem->Name = L"openingToolStripMenuItem";
			this->openingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->openingToolStripMenuItem->Text = L"Opening";
			this->openingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openingToolStripMenuItem_Click);
			// 
			// closingToolStripMenuItem
			// 
			this->closingToolStripMenuItem->Name = L"closingToolStripMenuItem";
			this->closingToolStripMenuItem->Size = System::Drawing::Size(120, 22);
			this->closingToolStripMenuItem->Text = L"Closing";
			this->closingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closingToolStripMenuItem_Click);
			// 
			// findObjectToolStripMenuItem
			// 
			this->findObjectToolStripMenuItem->Name = L"findObjectToolStripMenuItem";
			this->findObjectToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->findObjectToolStripMenuItem->Text = L"Find_Object";
			this->findObjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::findObjectToolStripMenuItem_Click);
			// 
			// histogramEqualizedToolStripMenuItem
			// 
			this->histogramEqualizedToolStripMenuItem->Name = L"histogramEqualizedToolStripMenuItem";
			this->histogramEqualizedToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->histogramEqualizedToolStripMenuItem->Text = L"Histogram Equalization";
			this->histogramEqualizedToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramEqualizedToolStripMenuItem_Click);
			// 
			// ddxToolStripMenuItem
			// 
			this->ddxToolStripMenuItem->Name = L"ddxToolStripMenuItem";
			this->ddxToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->ddxToolStripMenuItem->Text = L"Edge Image";
			this->ddxToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ddxToolStripMenuItem_Click);
			// 
			// cizToolStripMenuItem
			// 
			this->cizToolStripMenuItem->Name = L"cizToolStripMenuItem";
			this->cizToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->cizToolStripMenuItem->Text = L"Gradient Image";
			this->cizToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cizToolStripMenuItem_Click);
			// 
			// fxyToolStripMenuItem
			// 
			this->fxyToolStripMenuItem->Name = L"fxyToolStripMenuItem";
			this->fxyToolStripMenuItem->Size = System::Drawing::Size(155, 22);
			this->fxyToolStripMenuItem->Text = L"Fxy";
			this->fxyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::fxyToolStripMenuItem_Click_1);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(43, 20);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(22, 53);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(364, 360);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Visible = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(432, 53);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(364, 360);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Visible = false;
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(432, 53);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Histogram";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(364, 360);
			this->chart1->TabIndex = 3;
			this->chart1->Text = L"chart1";
			this->chart1->Visible = false;
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveFileDialog1_FileOk);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(820, 447);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		pictureBox1->Visible = true;
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			pictureBox1->ImageLocation = openFileDialog1->FileName;

		}
		str = pictureBox1->ImageLocation;
		input = (LPCTSTR)str;
		buffer = LoadBMP(&width, &height, &size, input);
	}
	private: System::Void ýntensityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		raw_intensity = ConvertBMPToIntensity(buffer, width, height);
		surface = gcnew Bitmap(width, height);
		pictureBox1->Image = surface;
		Color color;
		int temp;
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				temp = row * width + column;
				
				color = Color::FromArgb(raw_intensity[temp], raw_intensity[temp], raw_intensity[temp]);
				surface->SetPixel(column, row, color);

			}
		}
	}
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		
		pen = gcnew Pen(Color::White, 2);
		ciz = true;
		ilk_x = System::Convert::ToInt32(e->X);
		ilk_y = System::Convert::ToInt32(e->Y);
	}
	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (ciz == true && e->X <= width && e->Y <= height) {
			pictureBox1->Refresh();
			box_width = (System::Convert::ToInt32(e->X)) - ilk_x;
			box_height = (System::Convert::ToInt32(e->Y)) - ilk_y;
			g = pictureBox1->CreateGraphics();
			g->DrawRectangle(pen, ilk_x, ilk_y, box_width, box_height);
		}

		else {
			ciz = false;
		}
		
	}
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	
		ciz = false;
		int* ara_d = new int[box_width*box_height];
		
			son_x = System::Convert::ToInt32(e->X);
			son_y = System::Convert::ToInt32(e->Y);
			
	
		
		if (ciz==false ) {
			pictureBox2->Visible = true;
			if (crop == true) {
				
				kesik = gcnew Bitmap(box_width, box_height);
				pictureBox2->Image = kesik;
			}
				Color color;
			
			int temp, temp_d;
			for (int row = ilk_y; row < son_y; row++) {
				for (int column = ilk_x; column < son_x; column++)
				{
					
					temp = row * width + column;
					temp_d = (row - ilk_y)*box_width + (column - ilk_x);
					
					ara_d[temp_d] = raw_intensity[temp];
					if (crop == true) {
						color = Color::FromArgb(raw_intensity[temp], raw_intensity[temp], raw_intensity[temp]);
						kesik->SetPixel(column - ilk_x, row - ilk_y, color);
					}
				}
			}
			
		
			if (zoom == true ) {
				/**************Maský 0' larla Doldurma********************************/
				float mask[9] = { 0.25,0.5,0.25,0.5,1,0.5,0.25,0.5,0.25 };
				pictureBox2->Visible = true;
				int* zoom_d = new int[(2 * box_width + 1)*(2 * box_height + 1)];
				int degisken;
				for (int k = 0; k < (2*box_height+1); k = k + 2) {
					for (int i = 0; i < (2*box_width+1); i++) {
						degisken = (k*(2*box_width+1)) + i;
						zoom_d[degisken] = 0;

					}
				}
				int temp2;
				int temp3;
				int temp4;
				int k = 0;
				for (int l = 1; l < (2*box_height+1); l = l + 2) {
					k = 0;
					for (int m = 0; m < (2*box_width+1); m++) {
						temp2 = l * (2*box_width+1) + m;

						if (m % 2 == 0) {
							zoom_d[temp2] = 0;
						}
						else if (k < box_width) {

							temp3 = ((l - 1) / 2)*box_width + k;
							zoom_d[temp2] = ara_d[temp3];
							k++;

						}
					} 
				}
		
				/*******************************************************************************/

				/**********  Maský Yerleþtirip Çarpma ********************/
				int* zoom_p = Masking(mask, zoom_d, (2 * box_width + 1),(2*box_height+1));
		
				int temppp;
				zoomer = gcnew Bitmap((2 * box_width - 1),(2 * box_height - 1));
				pictureBox2->Image = zoomer;
				Color color;
				for (int row = 0; row < 2 * box_height - 1; row++) {
					for (int column = 0; column < 2 * box_width - 1; column++) {
						temppp = row * (2*box_width-1) + column;
						color = Color::FromArgb(zoom_p[temppp], zoom_p[temppp], zoom_p[temppp]);
						zoomer->SetPixel(column, row, color);

					}
				}


				
			
				delete [] zoom_d;
				delete[] zoom_p;
			
			}   
		}
		delete [] ara_d;
	  /*******************************************************************************/
	}
	private: System::Void cropToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		zoom = false;
		crop = true;
		chart1->Visible = false;
	}
	private: System::Void histogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		zoom = false;
		crop = false;
		int* intensity=new int[width*height];
		for (int p = 0; p < width*height; p++) {
			intensity[p] = raw_intensity[p];
		}
		chart1->Visible = true;
		pictureBox2->Visible = false;
		/*for (int i = 0; i < 256; i++) {
			hist[i] = 0;
		}  */
		chart1->Series->Clear();
		chart1->Titles->Clear();
		chart1->Series->Add("Histogram");
		chart1->Titles->Add("Histogram");
		/*for (int i = 0; i < width*height; i++) {
			hist[raw_intensity[i]]++;
		

		}  */
		hist = Histogram(width, height,intensity,256);
		for (int i = 0; i < 256; i++) {
			chart1->Series["Histogram"]->Points->AddXY(i + "", hist[i]);
		
		}
	}
private: System::Void zoomToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	crop = false;
	chart1->Visible = false;
	zoom = true;


}
private: System::Void kMeansToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
		
		float t1 = (float)(rand() % 256);
		float t2 = (float)(rand() % 256);
		float g_t1 = -1; 
		float g_t2 = -1;
		float d1, d2;
		float sum1, sum2, sum3, sum4;
		int kume[256];

		do {
			if (g_t1 != (-1) && g_t2 != (-1)) {
				t1 = g_t1;
				t2 = g_t2;
			}
		for (int i = 0; i < 256; i++) {
			d1 = Math::Abs(i - t1);
			d2 = Math::Abs(i - t2);
			if (d1 < d2) {
				kume[i] = 1;
			}
			else {
				kume[i] = 2;
			}
		}

		for (int k = 0; k < 256; k++) {
			if (kume[k] == 1) {
				sum1 += k * hist[k];
				sum3 += hist[k];
			}

			else
			{
				sum2 += k * hist[k];
				sum4 += hist[k];
			}
		}
		g_t1 = (float)sum1 / sum3;
		g_t2 = (float)sum2 / sum4;
		} while (t1 != g_t1 && t2 != g_t2);
		
		for (int i = 1; i < 255; i++) {
			
			if (kume[i] == 1) {
				for (int m = 0; m < width*height; m++) {
					if (raw_intensity[m] == i) {
						raw_intensity[m] = 255;
					}
				}
			}
			else {
				for (int s = 0; s < width*height; s++) {
					if (raw_intensity[s] == i) {
						raw_intensity[s] = 0;
					}
				}
			}
		}
		binary = gcnew Bitmap(width, height);
		pictureBox1->Image = binary;
		Color ccolor;
		int ttemp;
		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				ttemp = row * width + column;
				ccolor = Color::FromArgb(raw_intensity[ttemp], raw_intensity[ttemp], raw_intensity[ttemp]);
				binary->SetPixel(column, row, ccolor);

			}
		} 
	} 

private: System::Void findObjectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int temp,temp2;
	int et = 1;
	int* etiket = new int[width*height];
	for (int m = 0; m < width*height; m++) {
		etiket[m] = 0;
	}
	for (int i = 0; i < height; i++) {
		for (int l = 0; l < width; l++) 
		{
			temp = i * width + l;
		
			if (i > 0) {
				temp2 = (i - 1) * width + l;
			}
			if (raw_intensity[temp] == 0) 
			{
				if (i == 0 && l == 0) {
					etiket[temp] = et;
					et++;
				}
				else if(i==0 && l!=0)
				{
					if (etiket[temp - 1] != 0) {
						etiket[temp] = etiket[temp - 1];
					}
					else
					{
						etiket[temp] = et;
						et++;
					}
				}
				else if(i!=0 && l==0)
				{
					if (etiket[temp2] != 0) {
						etiket[temp] = etiket[temp2];
					}
					else 
					{
						etiket[temp] = et;
						et++;
					}

				}
				else if (etiket[temp - 1] == 0 && etiket[temp2] == 0) 
				{
					etiket[temp] = et;
					et++;
				}

				else if (etiket[temp - 1] != 0 && etiket[temp2] == 0)
				{
					etiket[temp] = etiket[temp - 1];
				}

				else if(etiket[temp-1]==0 && etiket[temp2]!=0) 
				{
					etiket[temp] = etiket[temp2];

				}

				else if(etiket[temp-1]!=0 && etiket[temp2]!=0)
				{
					 if(etiket[temp-1]<etiket[temp2]) 
					 {
						 etiket[temp] = etiket[temp - 1];
						 for (int d = 0; d < temp; d++) 
						 {
							 if (etiket[d] == etiket[temp2]) {
								 etiket[d] = etiket[temp-1];
							}
						 }
						 et--;
					 }

					 else if(etiket[temp2]<etiket[temp-1])
					 {
						 etiket[temp] = etiket[temp2];
						 for (int d = 0; d < temp; d++)
						 {
							 if (etiket[d] == etiket[temp-1]) {
								 etiket[d] = etiket[temp2];
							 }
						 }
						 et--;
					 }
					 else if (etiket[temp-1]==etiket[temp2])
					
					 {
						 etiket[temp] = etiket[temp - 1];
					 }
				}
				
				


			}
		}



	}
	et--;

	
	
	String^ message = "Number of found Objects: "+et;
	
	MessageBox::Show(message);
	

	
	

}
private: System::Void histogramEqualizedToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {


	int sum,sum2;
	int tmp, tmp2;
	float degis;
	int* arahist = new int[256];
	int* araraw = new int[width*height];
	for (int r = 0; r < width*height; r++) {
		araraw[r] = raw_intensity[r];
	}
	for  (int m=0;m<256;m++)
	{
		arahist[m] = 0;
	}  
	for (int i = 0; i < 256; i++) {
		sum = sum + hist[i];
	} 
	for (int k = 0; k < 256; k++) {
		sum2 = sum2 + hist[k];
		degis = ((float)sum2 / sum) * 255;
		tmp =Math::Round(degis);
		for (int s = 0; s < width*height; s++) {
			if (raw_intensity[s] == k) {
				araraw[s] = tmp;
			}
		}
		arahist[tmp] = arahist[tmp] + hist[k];
	} 
	Bitmap ^ yeni = gcnew Bitmap(width, height);
	pictureBox1->Image = yeni;
	Color color;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			tmp2 = row * width + column;

			color = Color::FromArgb(araraw[tmp2], araraw[tmp2], araraw[tmp2]);
			yeni->SetPixel(column, row, color);

		}
	}
	
	chart1->Series->Clear();
	chart1->Series->Add("Histogram");
	for (int i = 0; i < 256; i++) {
		
		chart1->Series["Histogram"]->Points->AddXY(i + "", arahist[i]);

	} 
	
} 
		 
private: System::Void dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int* aramatris = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		aramatris[i] = 0;
	}
	for (int i = 0; i < width*height; i++) {
		if (raw_intensity[i] == 0)
		{
			aramatris[i] = 1;
		}
		else if (raw_intensity[i] == 255) {
			aramatris[i] = 0;
		}
	}
	int ara;
	int* orgmatris = Dilation(aramatris, width, height);
	Bitmap ^ dilation = gcnew Bitmap(width, height);
	pictureBox1->Image = dilation;
	Color color;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			ara= row * width + column;

			color = Color::FromArgb(orgmatris[ara], orgmatris[ara], orgmatris[ara]);
			dilation->SetPixel(column, row, color);

		}
	}


}
private: System::Void erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	int* aramatris = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		aramatris[i] = 0;
	}
	for (int i = 0; i < width*height; i++) {
		if (raw_intensity[i] == 0)
		{
			aramatris[i] = 1;
		}
		else if (raw_intensity[i] == 255) {
			aramatris[i] = 0;
		}
	}
	
	int ara;
	int* orgmatris = Erosion(aramatris, width, height);
	Bitmap ^ erosion = gcnew Bitmap(width, height);
	pictureBox1->Image = erosion;
	Color color;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			ara = row * width + column;

			color = Color::FromArgb(orgmatris[ara], orgmatris[ara], orgmatris[ara]);
			erosion->SetPixel(column, row, color);

		}
	}
}
private: System::Void openingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
	int* aramatris = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		aramatris[i] = 0;
	}
	for (int i = 0; i < width*height; i++) {
		if (raw_intensity[i] == 0)
		{

			aramatris[i] = 1;
		}
		else if (raw_intensity[i] == 255) {
			aramatris[i] = 0;
		}
	}

	int* orgmatris = Erosion(aramatris, width, height);
	for (int i = 0; i < width*height; i++) {
		if (orgmatris[i] == 0)
		{
			orgmatris[i] = 1;
		}
		else if (orgmatris[i] == 255) {
			orgmatris[i] = 0;
		}
	}
	int* newmatris = Dilation(orgmatris, width, height);
	

	int ara;

	Bitmap ^ opening = gcnew Bitmap(width, height);
	pictureBox1->Image = opening;
	Color color;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			ara = row * width + column;

			color = Color::FromArgb(newmatris[ara], newmatris[ara], newmatris[ara]);
			opening->SetPixel(column, row, color);

		}
	}

}
private: System::Void closingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

	int* aramatris = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		aramatris[i] = 0;
	}
	for (int i = 0; i < width*height; i++) {
		if (raw_intensity[i] == 0)
		{
			aramatris[i] = 1;
		}
		else if (raw_intensity[i] == 255) {
			aramatris[i] = 0;
		}
	}

	int* orgmatris = Dilation(aramatris, width, height);
	for (int i = 0; i < width*height; i++) {
		if (orgmatris[i] == 0)
		{
			orgmatris[i] = 1;
		}
		else if (orgmatris[i] == 255) {
			orgmatris[i] = 0;
		}
	}
	int* newmatris = Erosion(orgmatris, width, height);


	int ara;

	Bitmap ^ closing = gcnew Bitmap(width, height);
	pictureBox1->Image = closing;
	Color color;

	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			ara = row * width + column;

			color = Color::FromArgb(newmatris[ara], newmatris[ara], newmatris[ara]);
			closing->SetPixel(column, row, color);

		}
	}
}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Application::Exit();
}
private: System::Void ddxToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	pictureBox2->Visible = true;
	//int dizi[36] = { 2,0,5,4,3,0,0,0,6,2,7,5,1,0,2,0,1,0,6,5,7,7,6,7,7,6,7,6,6,6,6,2,0,4,3,5 };
	
	int mwidth,mheight;
	mwidth = width - 2;
	mheight = height - 2;
	int* raw = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		raw[i] = raw_intensity[i];
	}
	int* dx = Masking(fxmask,raw , width, height);
	int* dy = Masking(fymask, raw, width, height);
	double sayi;
	int* fxy = new int[(mwidth)*(mheight)];
	double* fgra = new double[(mwidth)*(mheight)];
	int* nonmax = new int[(mwidth)*(mheight)];
	/*****       FX+FY           ******/
	for (int k = 0; k < (mwidth)*(mheight); k++) {
		fxy[k] = (dx[k]) +(dy[k]);
	}
	/*************************************/
	
	/*******  Find Vector of Gradient     ********/
	for (int i = 0; i < (mwidth)*(mheight); i++) {
		sayi = dy[i] / (dx[i] + 0.1);
		fgra[i] = (System::Math::Atan(sayi))*(180/System::Math::PI);

	} 
	
	/***********************    Direction of Gradient                    *************************/
	
	int temp, temp2, temp3;
	for (int row= 0; row < (mheight); row++) {
		for (int column = 0; column < (mwidth); column++) {
			if (row != 0) {
				temp2 = (row - 1)*mwidth + column;
			}
			if (row != mheight - 1) {
				temp3 = (row + 1)*mwidth + column;
			}
			temp = row * mwidth + column;
			if ( (fgra[temp] >= 0 && fgra[temp] < 22.5) || (fgra[temp] > 157.5 && fgra[temp] < 202.5 ) || (fgra[temp] > 337.5 && fgra[temp] <= 360)) { //yatay
				if (column == 0) {
					if (fxy[temp] < fxy[temp + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}
				else if (column == mwidth - 1) {
					if (fxy[temp] < fxy[temp - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}
				else {
					if ((fxy[temp] < fxy[temp - 1]) || (fxy[temp] < fxy[temp + 1])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}



			}

			



			if ((fgra[temp] > 62.5 && fgra[temp] < 122.5) || (fgra[temp] > 247.5 && fgra[temp] < 292.5)) { // 90 and 270
				/*if (row == 0) {
					if (fxy[temp] < fxy[temp3]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else if (row == mheight - 1) {
					if (fxy[temp] < fxy[temp2]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}
				else {
					if ((fxy[temp] < fxy[temp2]) || (fxy[temp] < fxy[temp3])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

			}

			*/
			/************/



			




				if (row == 0) {
					if (fxy[temp] < fxy[temp3]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else if (row == mheight - 1) {
					if (fxy[temp] < fxy[temp2]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}
				else {
					if ((fxy[temp] < fxy[temp2]) || (fxy[temp] < fxy[temp3])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
			}

			if ( (fgra[temp] >= 22.5 && fgra[temp] <= 62.5) || (fgra[temp] >= 202.5 && fgra[temp] <= 247.5) ) { // 0<x<90 and 180<x<270
				if (row == 0 && column == 0) {
					nonmax[temp] = fxy[temp];

				}
				else if (row == 0 && column != 0) {
					if (fxy[temp] < fxy[temp3 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if (row != 0 && column == 0) {
					if (fxy[temp] < fxy[temp2 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

				else if (row == mheight - 1 && column == mwidth - 1) {
					nonmax[temp] = fxy[temp];
				}
				else if ((row == mwidth - 1) && (column != mwidth - 1) && (column!=0) ) {

					if (fxy[temp] < fxy[temp2 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if ((row != 0) && (column == mwidth - 1) && (row != mheight - 1)) {
					if (fxy[temp] < fxy[temp3 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else {
					if ((fxy[temp] < fxy[temp2 + 1]) || (fxy[temp] < fxy[temp3 - 1])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

		}

			if ( (fgra[temp] >= 122.5 && fgra[temp] <=157.5) || (fgra[temp] >= 292.5 && fgra[temp] <= 337.5 ) ) { // 90<z<180 and 270<z<360
			/*	if (row == 0 && column == 0) {
					if (fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}*/
				 if ( (row==0)  && (column!=mwidth-1)) {
					if (fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if (row == 0 && column == mwidth - 1) {
					nonmax[temp] = fxy[temp];
				}
				else if (row != 0 && column == 0 && row != mheight - 1) {
					if (fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else  if (row == mheight - 1 && column == 0) {
					nonmax[temp] = fxy[temp];
				}
				
				else if (row == mheight - 1 && column != 0) {
					if (fxy[temp] < fxy[temp2 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else if (row != 0 && column == mwidth - 1 && row != mheight - 1) {
					if (fxy[temp] < fxy[temp2 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}

				else {
					if (fxy[temp] < fxy[temp2 - 1] || fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}


			}




		}


	}
	/*******  Hysterize Threshold            ******/
//	int* hist2 = Histogram(mwidth, mheight, nonmax,256);
	int tlow = 0; int thight = 0; 
	for (int c = 0; c < mwidth*mheight; c++) {
		if (thight < nonmax[c]) {
			thight = nonmax[c];
		}   
									
	}
	/*if (max <= 680) {
		max = max - 280;
	}
	else if (max > 680 && max < 1000) {
		max = max - 500;
	}
	else if (max >= 1000) {
		max = max - 600;
	}
	min = min +40;*/
	int maxcontrol = Math::Round(thight - (thight*0.80));
	int mincontrol = Math::Round(tlow + (tlow*0.20));
	for (int h = 0; h < mwidth*mheight; h++) {
	
		 if (nonmax[h] >= maxcontrol) {
			nonmax[h] = 1;
		}
		 else if (nonmax[h] <= tlow) {
			 nonmax[h] = 0;
		 }
		
	}

	/****  Direction of Edge       ****/

int teemp, teemp2, teemp3;
int t = 0;
while (true) {
	int control = 0;
	for (int f = 0; f < mwidth*mheight; f++) {
		if (nonmax[f] != 0 && nonmax[f] != 1) {
			control = 1;
			break;
		}

	}
	if (control == 0) {
		break;
	}
	
		for (int row = 0; row < (mheight); row++) {
			for (int column = 0; column < (mwidth); column++) {
				if (row != 0) {
					teemp2 = (row - 1)*mwidth + column;
				}
				if (row != mheight - 1) {
					teemp3 = (row + 1)*mwidth + column;
				}

				teemp = row * mwidth + column;
				//if (nonmax[teemp] != 0 && nonmax[teemp] != 1)

				if (nonmax[teemp] != 0 && nonmax[teemp] != 1) {


					if ((fgra[teemp] >= 0 && fgra[teemp] < 22.5) || (fgra[teemp] > 157.5 && fgra[teemp] < 202.5) || (fgra[teemp] > 337.5 && fgra[teemp] <= 360)) {

						if (row == 0) {
							if (nonmax[teemp3] == 1) {
								nonmax[teemp] = 1;
							}
							else if (nonmax[teemp3] == 0) {
								nonmax[teemp] = 0;
							}
						}

						else if (row == (mheight - 1)) {
							if (nonmax[teemp2] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp2] == 1) {
								nonmax[teemp] = 1;
							}


						}
						else {
							if ((nonmax[teemp2] == 1 && nonmax[teemp3] != 0) || (nonmax[teemp2] != 0 && nonmax[teemp3] == 1)) {
								nonmax[teemp] = 1;
							}
							else if ((nonmax[teemp2] == 0 && nonmax[teemp3] != 1) || (nonmax[teemp2] != 1 && nonmax[teemp3] == 0)) {
								nonmax[teemp] = 0;
							}
							else if ((nonmax[teemp2] == 1 && nonmax[teemp3] == 0) || (nonmax[teemp2] == 0 && nonmax[teemp3] == 1)) {

								int d1 = System::Math::Abs(nonmax[teemp] - mincontrol);
								int d2 = System::Math::Abs(nonmax[teemp] - maxcontrol);

								if (d1 < d2) {
									nonmax[teemp] = 0;
								}
								else {
									nonmax[teemp] = 1;
								}


							}



						}


					}


					if ((fgra[teemp] > 62.5 && fgra[teemp] < 122.5) || (fgra[teemp] > 247.5 && fgra[teemp] < 292.5)) {

						if (column == 0) {
							if (nonmax[teemp + 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp + 1] == 1) {
								nonmax[teemp] = 1;
							}

						}
						else if (column == mwidth - 1) {
							if (nonmax[teemp - 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp - 1] == 1) {
								nonmax[teemp] = 1;
							}

						}
						else {
							if ((nonmax[teemp - 1] == 0 && nonmax[teemp + 1] != 1) || (nonmax[teemp - 1] != 1 && nonmax[teemp + 1] == 0)) {
								nonmax[teemp] = 0;
							}
							else if ((nonmax[teemp - 1] == 1 && nonmax[teemp + 1] != 0) || (nonmax[teemp - 1] != 0 && nonmax[teemp + 1] == 1)) {
								nonmax[teemp] = 1;
							}
							else if ((nonmax[teemp - 1] == 1 && nonmax[teemp + 1] == 0) || (nonmax[teemp - 1] == 0 && nonmax[teemp + 1] == 1)) {
								int d1 = System::Math::Abs(nonmax[teemp] - mincontrol);
								int d2 = System::Math::Abs(nonmax[teemp] - maxcontrol);

								if (d1 < d2) {
									nonmax[teemp] = 0;
								}
								else {
									nonmax[teemp] = 1;
								}

							}
						}



					}

					if ((fgra[teemp] >= 22.5 && fgra[teemp] <= 62.5) || (fgra[teemp] >= 202.5 && fgra[teemp] <= 247.5)) {

						/*	if (row == 0 && column == 0) {
						if (nonmax[teemp3 + 1] == 0) {
						nonmax[teemp] = 0;
						}
						else if (nonmax[teemp3 + 1] == 1) {
						nonmax[teemp] = 1;
						}
						}*/
						if (row == 0 && column != mwidth - 1) {
							if (nonmax[teemp3 + 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp3 + 1] == 1) {
								nonmax[teemp] = 1;
							}

						}
						else if (row != 0 && column == 0 && row != mheight - 1) {
							if (nonmax[teemp3 + 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp3 + 1] == 1) {
								nonmax[teemp] = 1;
							}

						}

						else if (row == mheight - 1 && column != 0) {
							if (nonmax[teemp2 - 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp2 - 1] == 1) {
								nonmax[teemp] = 1;
							}
						}

						else if (row != 0 && column == mwidth - 1 && row != mheight - 1) {
							if (nonmax[teemp2 - 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp2 - 1] == 1) {
								nonmax[teemp] = 1;
							}


						}

						else {
							if ((nonmax[teemp2 - 1] == 0 && nonmax[teemp3 + 1] != 1) || (nonmax[teemp2 - 1] != 1 && nonmax[teemp3 + 1] == 0)) {
								nonmax[teemp] = 0;
							}
							else if ((nonmax[teemp2 - 1] == 1 && nonmax[teemp3 + 1] != 0) || (nonmax[teemp2 - 1] != 0 && nonmax[teemp3 + 1] == 1)) {
								nonmax[teemp] = 1;
							}
							else if ((nonmax[teemp2 - 1] == 1 && nonmax[teemp3 + 1] == 0) || (nonmax[teemp2 - 1] == 0 && nonmax[teemp3 + 1] == 1)) {
								int d1 = System::Math::Abs(nonmax[teemp] - mincontrol);
								int d2 = System::Math::Abs(nonmax[teemp] - maxcontrol);

								if (d1 < d2) {
									nonmax[teemp] = 0;
								}
								else {
									nonmax[teemp] = 1;
								}
							

							}

						}


					}

					if ((fgra[teemp] >= 122.5 && fgra[teemp] <= 157.5) || (fgra[teemp] >= 292.5 && fgra[teemp] <= 337.5)) {

						if (row == 0 && column != 0) {
							if (nonmax[teemp3 - 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp3 - 1] == 1) {
								nonmax[teemp] = 1;
							}

						}
						else if (row != 0 && column == 0) {
							if (nonmax[teemp2 + 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp2 + 1] == 1) {
								nonmax[teemp] = 1;
							}

						}

						else if (row == mwidth - 1 && column != mwidth - 1 && column != 0) {

							if (nonmax[teemp2 + 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp2 + 1] == 1) {
								nonmax[teemp] = 1;
							}

						}
						else if (row != 0 && column == mwidth - 1 && row != mheight - 1) {
							if (nonmax[teemp3 - 1] == 0) {
								nonmax[teemp] = 0;
							}
							else if (nonmax[teemp3 - 1] == 1) {
								nonmax[teemp] = 1;
							}
						}

						else {
							if ((nonmax[teemp2 + 1] == 0 && nonmax[teemp3 - 1] != 1) || (nonmax[teemp3 - 1] == 0 && nonmax[teemp2 + 1] != 1)) {
								nonmax[teemp] = 0;
							}
							else if ((nonmax[teemp2 + 1] == 1 && nonmax[teemp3 - 1] != 0) || (nonmax[teemp3 - 1] == 1 && nonmax[teemp2 + 1] != 0)) {
								nonmax[teemp] = 1;
							}
							else if ((nonmax[teemp2 + 1] == 1 && nonmax[teemp3 - 1] == 0) || (nonmax[teemp2 + 1] == 0 && nonmax[teemp3 - 1] == 1)) {
								int d1 = System::Math::Abs(nonmax[teemp] - mincontrol);
								int d2 = System::Math::Abs(nonmax[teemp] - maxcontrol);

								if (d1 < d2) {
									nonmax[teemp] = 0;
								}
								else {
									nonmax[teemp] = 1;
								}


							}
						}





					}

				}



			}


		}
	}

	


	/******************************************************************/
	/*int dsize = Math::Round(Math::Sqrt((mwidth-1)*(mwidth-1)+(mheight-1)*(mheight-1)));
	
		int* dmatris = new int[dsize*4];
		for (int i = 0; i < dsize * 4; i++) {
			dmatris[i] = 0;
		}
		/*for (int row = 0; row < dsize; row++)
		{
			for (int column = 0; column < 361; column++) {
				int ttemp = row * dsize + column;
				if (nonmax[ttemp] == 1) {
					int d = Math::Round((column * (Math::Cos(fgra[ttemp])) )+ (row * (Math::Sin(fgra[ttemp]))));
					



				}
			}

		} */
	/*	double pain; int p_index;
		for (int row = 0; row < mheight; row++) {
			for (int column = 0; column < mwidth; column++) {
				int ttemp = row * mwidth + column;
				if (nonmax[ttemp] == 1) {

					if ((fgra[ttemp] >= 22.5 && fgra[ttemp] <= 62.6) || (fgra[ttemp] >= 202.5 && fgra[ttemp] <= 247.5)) {
						 pain = 45;
						 p_index = 1;
					}
						
					else if ((fgra[ttemp] >= 0 && fgra[ttemp] < 22.5) || (fgra[ttemp] > 157.5 && fgra[ttemp] < 202.5) || (fgra[ttemp] > 337.5 && fgra[ttemp] <= 360)) {
						pain = 0;
						p_index = 0;
					}
					else if ((fgra[ttemp] > 62.5 && fgra[ttemp] < 122.5) || (fgra[ttemp] > 247.5 && fgra[ttemp] < 292.5)) {
						pain = 90;
						p_index = 2;
					}
					else if ((fgra[ttemp] >= 122.5 && fgra[ttemp] <= 157.5) || (fgra[ttemp] >= 292.5 && fgra[ttemp] <= 337.5)) {
						pain = 135;
						p_index = 3;
					}
					
					int d= Math::Round(((column+1) * (Math::Cos(pain*Math::PI/180.0))) + ((row+1) * (Math::Sin(pain*Math::PI / 180.0))));
					int index = d * 4 +p_index;
					//dmatris[i

				


			}


		}

		int max16_d[36];
		int max16_pain[36];
		int* copydmatris=new int [dsize * 4];
		for (int i = 0; i < dsize * 4; i++) {
			copydmatris[i] = dmatris[i];
		}
		int keep = 0;
		int keep_i = 0;  int keep_d = 0; int keep_pain = 0;
		int z = 0;
		while (z < 36) {
			keep = 0;
			for (int row = 0; row < dsize; row++) {
				for (int column = 0; column < 4; column++) {
					int temp = row * 4 + column;
					if (keep < copydmatris[temp] ) {
						keep = copydmatris[temp];
						keep_i = temp;
						keep_d = row;
						keep_pain = column;
					}

				}
				
			}
			max16_d[z] = keep_d;
			max16_pain[z] = keep_pain;
			z++;
			copydmatris[keep_i] = 0;


		}
		


		Bitmap ^ canny = gcnew Bitmap(width, height);
		pictureBox2->Image = canny;
		Color color;

		for (int row = 0; row < height; row++) {
			for (int column = 0; column < width; column++) {
				int ara = row * width + column;

				color = Color::FromArgb(raw[ara], raw[ara], raw[ara]);
				canny->SetPixel(column, row, color);

			}
		} 
		Graphics^ c;
		pictureBox2->Refresh();
		Pen^ kalem = gcnew Pen(Color::Red, 1);
		c = pictureBox2->CreateGraphics();
	/*	for (int i = 0; i < 4; i++) {
			c->DrawLine(kalem, 0, i, width, i);
		} */
	
	/*	for (int u = 0; u < 36; u++) {
			
			if (max16_pain[u] == 2) {
				/*	int value = max16_d[u] * width;
					for (int i = value; i < width - 1; i++) {
						raw[i] = 255;
				    } */

		/*		c->DrawLine(kalem, 0, max16_d[u], width - 1, max16_d[u]);
				

			}
			else if (max16_pain[u] == 0) {
				/*for (int row = 0; row < height; row++) {
					int temp = row * width + max16_d[u];
					raw[temp] = 255;
				}*/

		/*		c->DrawLine(kalem, max16_d[u],0,max16_d[u],height-1);
				
			}
			else if (max16_pain[u] == 1) {
			
				int i = 1;  int l = 0;
				int x1, y1, x2, y2;
						while ((max16_d[u] - i >= 0) && (((max16_d[u] -1) +l ) <= (width-1))) {
							temp = width * (max16_d[u] - i) + ((max16_d[u]-1) + l);
							x1 = max16_d[u] - i;
							y1 = ((max16_d[u] - 1) + l);
							//raw[temp] = 255;
							i++; l++;
						}
						int s = 0; int m = 1;
						
						while (((max16_d[u] - 1)+s <= height-1) && ((max16_d[u] - m)  >=0 )) {
							temp = width * ((max16_d[u] - 1)+s) + (max16_d[u] - m);
							//raw[temp] = 255;
							x2 = ((max16_d[u] - 1) + s);
							y2 = (max16_d[u] - m);
							s++; m++;
						} 
						
						c->DrawLine(kalem, x1, y1, x2, y2);
						
			}
		
			else if (max16_pain[u] == 3) {
				int i = 1;  int l = 0;
				int x1, y1, x2, y2;
				while ((max16_d[u] - i >= 0) && ((width - (max16_d[u] + l)) >= 0)) {
					temp = width * (max16_d[u] - i) + (width-(max16_d[u]+l));
					x1 = max16_d[u] - i;
					y1 = (width - (max16_d[u] + l));
					//raw[temp] = 255;
					i++; l++;
				}
				int s = 0; int m = 0;

				while (((max16_d[u] - 1) + s <= height - 1) && ((width - max16_d[u]) + m)<=width-1) {
					temp = width * ((max16_d[u] - 1) + s) + ((width-max16_d[u])+m);
					//raw[temp] = 255;
					x2 = ((max16_d[u] - 1) + s);
					y2 = ((width - max16_d[u]) + m);
					s++; m++;
				}

				c->DrawLine(kalem, x1, y1, x2, y2);
				



			}




		}  */
		//c->DrawRectangle(kalem, 30, 30, 100, 100);
		
	//	pictureBox1->Refresh();
		
		
	//	c->DrawLine(kalem, 0, max16_d[2], (width - 1), max16_d[2]);

		//pictureBox2->Refresh();*/
/*int* endnon = new int[width*height];
int b = 0;
for (int i = 0; i < width*height;i ++) {
	endnon[i] = 0;
}
for (int row = 1; row < height - 1; row++) {
	for (int column = 1; column < width - 1; column++) {
		int aratemp = row * width + column;
		endnon[aratemp] = nonmax[b];
		b++;
	}

} */
for (int i = 0; i < mwidth*mheight; i++) {
	if (nonmax[i] == 1) {
		nonmax[i] = 255;
	}
	else if(nonmax[i]==0) {
		nonmax[i] = 0;
	}

} 

Bitmap ^ canny = gcnew Bitmap(mwidth, mheight);
pictureBox2->Image = canny;
Color color;

for (int row = 0; row < mheight; row++) {
	for (int column = 0; column < mwidth; column++) {
		int ara = row * mwidth + column;

		color = Color::FromArgb(nonmax[ara], nonmax[ara], nonmax[ara]);
		canny->SetPixel(column, row, color);

	}
}


} 
private: System::Void cizToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	
	pictureBox2->Visible = true;
	//int dizi[36] = { 2,0,5,4,3,0,0,0,6,2,7,5,1,0,2,0,1,0,6,5,7,7,6,7,7,6,7,6,6,6,6,2,0,4,3,5 };

	int mwidth, mheight;
	mwidth = width - 2;
	mheight = height - 2;
	int* raw = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		raw[i] = raw_intensity[i];
	}
	int* dx = Masking(fxmask, raw, width, height);
	int* dy = Masking(fymask, raw, width, height);
	double sayi;
	int* fxy = new int[(mwidth)*(mheight)];
	double* fgra = new double[(mwidth)*(mheight)];
	int* nonmax = new int[(mwidth)*(mheight)];
	/*****       FX+FY           ******/
	for (int k = 0; k < (mwidth)*(mheight); k++) {
		fxy[k] = (dx[k]) + (dy[k]);
	}
	/*************************************/

	/*******  Find Vector of Gradient     ********/
	for (int i = 0; i < (mwidth)*(mheight); i++) {
		sayi = dy[i] / (dx[i] + 0.1);
		fgra[i] = (System::Math::Atan(sayi))*(180 / System::Math::PI);

	}

	/***********************    Direction of Gradient                    *************************/

	int temp, temp2, temp3;
	for (int row = 0; row < (mheight); row++) {
		for (int column = 0; column < (mwidth); column++) {
			if (row != 0) {
				temp2 = (row - 1)*mwidth + column;
			}
			if (row != mheight - 1) {
				temp3 = (row + 1)*mwidth + column;
			}
			temp = row * mwidth + column;
			if ((fgra[temp] >= 0 && fgra[temp] < 22.5) || (fgra[temp] > 157.5 && fgra[temp] < 202.5) || (fgra[temp] > 337.5 && fgra[temp] <= 360)) { //yatay
				if (column == 0) {
					if (fxy[temp] < fxy[temp + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}
				else if (column == mwidth - 1) {
					if (fxy[temp] < fxy[temp - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}
				else {
					if ((fxy[temp] < fxy[temp - 1]) || (fxy[temp] < fxy[temp + 1])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

			}



			if ((fgra[temp] > 62.5 && fgra[temp] < 122.5) || (fgra[temp] > 247.5 && fgra[temp] < 292.5)) { // 90 and 270
				if (row == 0) {
					if (fxy[temp] < fxy[temp3]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else if (row == mheight - 1) {
					if (fxy[temp] < fxy[temp2]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}
				else {
					if ((fxy[temp] < fxy[temp2]) || (fxy[temp] < fxy[temp3])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

			}


			if ((fgra[temp] >= 22.5 && fgra[temp] <= 62.5) || (fgra[temp] >= 202.5 && fgra[temp] <= 247.5)) { // 0<x<90 and 180<x<270
				if (row == 0 && column == 0) {
					nonmax[temp] = fxy[temp];

				}
				else if (row == 0 && column != 0) {
					if (fxy[temp] < fxy[temp3 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if (row != 0 && column == 0) {
					if (fxy[temp] < fxy[temp2 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

				else if (row == mheight - 1 && column == mwidth - 1) {
					nonmax[temp] = fxy[temp];
				}
				else if ((row == mwidth - 1) && (column != mwidth - 1) && (column != 0)) {

					if (fxy[temp] < fxy[temp2 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if ((row != 0) && (column == mwidth - 1) && (row != mheight - 1)) {
					if (fxy[temp] < fxy[temp3 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else {
					if ((fxy[temp] < fxy[temp2 + 1]) || (fxy[temp] < fxy[temp3 - 1])) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}

			}

			if ((fgra[temp] >= 122.5 && fgra[temp] <= 157.5) || (fgra[temp] >= 292.5 && fgra[temp] <= 337.5)) { 
				if ((row == 0) && (column != mwidth - 1)) {
					if (fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else if (row == 0 && column == mwidth - 1) {
					nonmax[temp] = fxy[temp];
				}
				else if (row != 0 && column == 0 && row != mheight - 1) {
					if (fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}

				}
				else  if (row == mheight - 1 && column == 0) {
					nonmax[temp] = fxy[temp];
				}

				else if (row == mheight - 1 && column != 0) {
					if (fxy[temp] < fxy[temp2 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}
				}

				else if (row != 0 && column == mwidth - 1 && row != mheight - 1) {
					if (fxy[temp] < fxy[temp2 - 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}

				else {
					if (fxy[temp] < fxy[temp2 - 1] || fxy[temp] < fxy[temp3 + 1]) {
						nonmax[temp] = 0;
					}
					else {
						nonmax[temp] = fxy[temp];
					}


				}


			}




		}


	}
	/*******  Hysterize Threshold            ******/
	//	int* hist2 = Histogram(mwidth, mheight, nonmax,256);
	int tlow = 0; int thight = 0;
	int *gradientýmage = new int[mwidth*mheight];
	for (int c = 0; c < mwidth*mheight; c++) {
		if (thight < nonmax[c]) {
			thight = nonmax[c];
		}

	}
/*	if (max >= 1000)
		min = min + 200;
	else
		min = min + 100;
		max = max - 300; */
	for (int i = 0; i < mwidth*mheight; i++) {
		gradientýmage[i] = (255 * nonmax[i]) / thight;
	}
	/*thight = thight - (thight*(0.25));
	tlow = tlow + (thight*0.10);
	for (int h = 0; h < mwidth*mheight; h++) {

		if ( gradientýmage[h]>= thight) {
			gradientýmage[h] = 255;
		}
		else if (gradientýmage[h] <= tlow) {
			gradientýmage[h] = 0;
		}

	} */


	/*for (int m = 0; m < mwidth*mheight; m++) {
		if (nonmax[m] != 0 && nonmax[m] != 1) {
			int d1 = System::Math::Abs(nonmax[m] - min);
			int d2 = System::Math::Abs(nonmax[m] - max);
			if (d1 < d2) {
				nonmax[m] = 0;
			}
			else {
				nonmax[m] = 1;
			}
		}
	} */



	/*int* endnon = new int[width*height];
	int b = 0;
	for (int i = 0; i < width*height; i++) {
		endnon[i] = 0;
	} 
	for (int row = 1; row < height - 1; row++) {
		for (int column = 1; column < width - 1; column++) {
			int aratemp = row * width + column;
			endnon[aratemp] = nonmax[b];
			b++;
		} 

	}
	for (int i = 0; i < width*height; i++) {
		if (endnon[i] == 1) {
			endnon[i] = 255;
		}
	} */

	Bitmap ^ canny = gcnew Bitmap(mwidth, mheight);
	pictureBox2->Image = canny;
	Color color;

	for (int row = 0; row < mheight; row++) {
		for (int column = 0; column < mwidth; column++) {
			int ara = row * mwidth + column;

			color = Color::FromArgb(gradientýmage[ara], gradientýmage[ara], gradientýmage[ara]);
			canny->SetPixel(column, row, color);

		}
	}



}
private: System::Void fxyToolStripMenuItem_Click_1(System::Object^  sender, System::EventArgs^  e) {
	pictureBox2->Visible = true;
	//int dizi[36] = { 2,0,5,4,3,0,0,0,6,2,7,5,1,0,2,0,1,0,6,5,7,7,6,7,7,6,7,6,6,6,6,2,0,4,3,5 };

	int mwidth, mheight;
	mwidth = width - 2;
	mheight = height - 2;
	int* raw = new int[width*height];
	for (int i = 0; i < width*height; i++) {
		raw[i] = raw_intensity[i];
	}
	int* dx = Masking(fxmask, raw, width, height);
	int* dy = Masking(fymask, raw, width, height);
	double sayi;
	int* fxy = new int[(mwidth)*(mheight)];
	double* fgra = new double[(mwidth)*(mheight)];
	int* nonmax = new int[(mwidth)*(mheight)];
	/*****       FX+FY           ******/
	for (int k = 0; k < (mwidth)*(mheight); k++) {
		fxy[k] = (dx[k]) + (dy[k]);
	}



	int* ffxy = new int[mwidth*mheight];
	int thight = 0;
	for (int c = 0; c < mwidth*mheight; c++) {
		if (thight <fxy[c]) {
			thight = fxy[c];
		}

	}

	for (int m = 0; m < mwidth*mheight; m++) {
		ffxy[m] = (255 * fxy[m]) / thight;

	}

	Bitmap ^ fsum = gcnew Bitmap(mwidth, mheight);
	pictureBox2->Image = fsum;
	Color color;

	for (int row = 0; row < mheight; row++) {
		for (int column = 0; column < mwidth; column++) {
			int ara = row * mwidth + column;

			color = Color::FromArgb(ffxy[ara], ffxy[ara], ffxy[ara]);
			fsum->SetPixel(column, row, color);

		}
	}

}
private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	saveFileDialog1->ShowDialog();
}
private: System::Void menustrip_save_ok_Click(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
	// Main Operations
	
	
}
private: System::Void saveFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
	Bitmap^ bmp = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	pictureBox2->DrawToBitmap(bmp, pictureBox2->ClientRectangle);
	bmp->Save(saveFileDialog1->FileName, System::Drawing::Imaging::ImageFormat::Bmp);
}
};
	
}