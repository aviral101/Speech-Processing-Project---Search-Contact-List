#pragma once
#include <msclr\marshal_cppstd.h>

namespace Group9_SearchContactList {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for updateForm
	/// </summary>
	public ref class updateForm : public System::Windows::Forms::Form
	{
	public:
		updateForm(void)
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
		~updateForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;


	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  textBox5;


	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		String ^ext;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(updateForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(136, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(65, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Name";
			this->label1->Click += gcnew System::EventHandler(this, &updateForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(91, 95);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(110, 24);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Phone No.";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(139, 158);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(62, 24);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Email";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(114, 218);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(87, 24);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Address";
			// 
			// button1
			// 
			this->button1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.BackgroundImage")));
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->button1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button1.Image")));
			this->button1->Location = System::Drawing::Point(573, 440);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(112, 44);
			this->button1->TabIndex = 4;
			this->button1->Text = L"Save";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &updateForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(246, 34);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(253, 28);
			this->textBox1->TabIndex = 5;
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(246, 95);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(253, 28);
			this->textBox2->TabIndex = 6;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(246, 158);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(253, 28);
			this->textBox3->TabIndex = 7;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(246, 218);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(253, 28);
			this->textBox4->TabIndex = 8;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(134, 278);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 24);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Image";
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(505, 278);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(38, 30);
			this->button2->TabIndex = 10;
			this->button2->Text = L"...";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &updateForm::button2_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"button3.Image")));
			this->button3->Location = System::Drawing::Point(297, 375);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(131, 44);
			this->button3->TabIndex = 13;
			this->button3->Text = L"Record";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &updateForm::button3_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::Transparent;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(217, 343);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(292, 20);
			this->label6->TabIndex = 14;
			this->label6->Text = L"Record 20 instances of the name.";
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(246, 278);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(253, 28);
			this->textBox5->TabIndex = 15;
			// 
			// updateForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(721, 496);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"updateForm";
			this->Text = L"updateForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				//try
				{
					//std::string path = "//UserInfo/"+textBox1->Text+ext;
					//CopyFile(textBox5->Text,path,0);
				}
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			  Stream^ myStream;
			  OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

			  openFileDialog1->InitialDirectory = "c:\\";
			  openFileDialog1->Filter = "Files|*.jpg;*.jpeg;*.png;";
			  openFileDialog1->FilterIndex = 2;
			  openFileDialog1->RestoreDirectory = true;

			  if ( openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK )
			  {
				 if ( (myStream = openFileDialog1->OpenFile()) != nullptr )
				 {
					textBox5->Text = openFileDialog1->FileName->ToString();
					ext = System::IO::Path::GetExtension(openFileDialog1->FileName);
					myStream->Close();
				 }
			  }
		 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 StreamWriter^ outFile = gcnew StreamWriter("new_contact_added.txt");
			 outFile->Write(textBox1->Text);
			 outFile->Close();
			 record_newContact();
			 
		 }
};
}
