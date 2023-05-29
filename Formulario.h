#pragma once

//#include"MyForm.h"
#include"Game.h"
//#include"MejoresPuntajes.h"
#include <string>
#include <msclr/marshal_cppstd.h>

namespace ProyectoB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for Formulario
	/// </summary>
	public ref class Formulario : public System::Windows::Forms::Form
	{
	private:
		Bitmap^ fondoTotal = gcnew Bitmap("jueguito.jpg");
	public:
		Formulario(void)
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
		~Formulario()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button3;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button4;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button3
			// 
			this->button3->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(163, 160);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(198, 44);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Continuar";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(88, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(375, 22);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Introduce tu nombre!";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(152, 63);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(222, 26);
			this->textBox1->TabIndex = 7;
			// 
			// button2
			// 
			this->button2->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(163, 309);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(198, 44);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Salir";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(163, 95);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(198, 44);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Jugar";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Formulario::button1_Click);
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Formulario::timer1_Tick);
			// 
			// button4
			// 
			this->button4->Font = (gcnew System::Drawing::Font(L"Goudy Stout", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(163, 225);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(198, 58);
			this->button4->TabIndex = 10;
			this->button4->Text = L"Mejores puntajes";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Formulario::button4_Click);
			// 
			// Formulario
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 425);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"Formulario";
			this->Text = L"Formulario";
			this->Load += gcnew System::EventHandler(this, &Formulario::Formulario_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Formulario_Load(System::Object^ sender, System::EventArgs^ e) {
		timer1->Enabled = true;
	}
private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	Graphics^ graficos = this->CreateGraphics();
	BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
	BufferedGraphics^ buffer = espacio->Allocate(graficos, this->ClientRectangle);
	buffer->Graphics->DrawImage(fondoTotal, 0, 0, (int)buffer->Graphics->VisibleClipBounds.Width, (int)buffer->Graphics->VisibleClipBounds.Height);
	buffer->Render(graficos);
	delete buffer;
	delete espacio;
	delete graficos;
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	
	//MyForm obj;
	//obj.ShowDialog();
	string str = marshal_as<string>(textBox1->Text);
	if (str != "") {
		Game* game = new Game(str);
		game->main();
	}
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	mainli* kj = new mainli();
	kj->main();
}
};
}
