#pragma once
#include <stdio.h>

namespace try1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		public:
			
			MyForm(void)
			{
				InitializeComponent();
				//
				//TODO: Add the constructor code here
				//
			}
			


		protected:
			/// <summary>
			/// Clean up any resources being used.
			/// </summary>
			~MyForm()
			{
				if (components)
				{
					delete components;
				}
			}
		private: System::Windows::Forms::PictureBox^ pictureBox1;
		public: System::Drawing::Color paintBrush;
		protected:
		private: System::Windows::Forms::Button^ button1;
		private: System::Windows::Forms::Button^ button2;
		private: System::Windows::Forms::Button^ button3;
		private: System::Windows::Forms::Button^ button4;
		private: System::Windows::Forms::Button^ button5;
		private: System::Windows::Forms::Button^ button6;
		private: System::Windows::Forms::TextBox^ textBox1;



		protected:

		private:
			/// <summary>
			/// Required designer variable.
			/// </summary>
			System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
			/// <summary>
			/// Required method for Designer support - do not modify
			/// the contents of this method with the code editor.
			/// </summary>
			void InitializeComponent(void)
			{
				System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
				this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				this->button1 = (gcnew System::Windows::Forms::Button());
				this->button2 = (gcnew System::Windows::Forms::Button());
				this->button3 = (gcnew System::Windows::Forms::Button());
				this->button4 = (gcnew System::Windows::Forms::Button());
				this->button5 = (gcnew System::Windows::Forms::Button());
				this->button6 = (gcnew System::Windows::Forms::Button());
				this->textBox1 = (gcnew System::Windows::Forms::TextBox());
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				this->SuspendLayout();
				// 
				// pictureBox1
				// 
				this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
				this->pictureBox1->Location = System::Drawing::Point(44, 108);
				this->pictureBox1->Name = L"pictureBox1";
				this->pictureBox1->Size = System::Drawing::Size(305, 255);
				this->pictureBox1->TabIndex = 1;
				this->pictureBox1->TabStop = false;
				this->pictureBox1->DoubleClick += gcnew System::EventHandler(this, &MyForm::pictureBox1_DoubleClick);
				// 
				// button1
				// 
				this->button1->BackColor = System::Drawing::Color::OrangeRed;
				this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
				this->button1->FlatAppearance->BorderSize = 5;
				this->button1->Location = System::Drawing::Point(429, 108);
				this->button1->Name = L"button1";
				this->button1->Size = System::Drawing::Size(85, 71);
				this->button1->TabIndex = 2;
				this->button1->Text = L"button1";
				this->button1->UseVisualStyleBackColor = false;
				this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
				// 
				// button2
				// 
				this->button2->BackColor = System::Drawing::Color::Yellow;
				this->button2->Location = System::Drawing::Point(520, 108);
				this->button2->Name = L"button2";
				this->button2->Size = System::Drawing::Size(85, 71);
				this->button2->TabIndex = 3;
				this->button2->Text = L"button2";
				this->button2->UseVisualStyleBackColor = false;
				this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
				// 
				// button3
				// 
				this->button3->BackColor = System::Drawing::Color::Lime;
				this->button3->Location = System::Drawing::Point(429, 185);
				this->button3->Name = L"button3";
				this->button3->Size = System::Drawing::Size(85, 71);
				this->button3->TabIndex = 4;
				this->button3->Text = L"button3";
				this->button3->UseVisualStyleBackColor = false;
				this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
				// 
				// button4
				// 
				this->button4->BackColor = System::Drawing::Color::Cyan;
				this->button4->Location = System::Drawing::Point(520, 185);
				this->button4->Name = L"button4";
				this->button4->Size = System::Drawing::Size(85, 71);
				this->button4->TabIndex = 5;
				this->button4->Text = L"button4";
				this->button4->UseVisualStyleBackColor = false;
				this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
				// 
				// button5
				// 
				this->button5->BackColor = System::Drawing::Color::SaddleBrown;
				this->button5->Location = System::Drawing::Point(429, 262);
				this->button5->Name = L"button5";
				this->button5->Size = System::Drawing::Size(85, 71);
				this->button5->TabIndex = 6;
				this->button5->Text = L"button5";
				this->button5->UseVisualStyleBackColor = false;
				this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
				// 
				// button6
				// 
				this->button6->BackColor = System::Drawing::Color::Magenta;
				this->button6->Location = System::Drawing::Point(520, 262);
				this->button6->Name = L"button6";
				this->button6->Size = System::Drawing::Size(85, 71);
				this->button6->TabIndex = 7;
				this->button6->Text = L"button6";
				this->button6->UseVisualStyleBackColor = false;
				this->button6->Click += gcnew System::EventHandler(this, &MyForm::button6_Click);
				// 
				// textBox1
				// 
				this->textBox1->BackColor = System::Drawing::Color::Silver;
				this->textBox1->Location = System::Drawing::Point(429, 343);
				this->textBox1->Name = L"textBox1";
				this->textBox1->Size = System::Drawing::Size(174, 20);
				this->textBox1->TabIndex = 8;
				// 
				// MyForm
				// 
				this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				this->ClientSize = System::Drawing::Size(665, 439);
				this->Controls->Add(this->textBox1);
				this->Controls->Add(this->button6);
				this->Controls->Add(this->button5);
				this->Controls->Add(this->button4);
				this->Controls->Add(this->button3);
				this->Controls->Add(this->button2);
				this->Controls->Add(this->button1);
				this->Controls->Add(this->pictureBox1);
				this->Name = L"MyForm";
				this->Text = L"MyForm";
				(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				this->ResumeLayout(false);
				this->PerformLayout();

			}
#pragma endregion
		private: void textBox1_ChangeColor() {
			textBox1->BackColor = paintBrush;
		}
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button1->BackColor;
			MyForm::paintButton_Click();
		}
		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button2->BackColor;
			MyForm::paintButton_Click();
		}
		private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button3->BackColor;
			MyForm::paintButton_Click();
		}
		private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button4->BackColor;
			MyForm::paintButton_Click();
		}
		private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button5->BackColor;
			MyForm::paintButton_Click();
		}
		private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
			paintBrush = this->button6->BackColor;
			MyForm::paintButton_Click();
		}
		
		private: void paintButton_Click() {
			MyForm::textBox1_ChangeColor();
		}

		
		private: System::Void pictureBox1_DoubleClick(System::Object^ sender, System::EventArgs^ e) {
			DoubleClick_toOverride();
		}

		//
		// ToDo: virtual destructor
		//
		public: virtual void DoubleClick_toOverride() {

		}

		//
		// TODO: pictureBox image setter
		// this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
		//

	};

	
	


}

//
