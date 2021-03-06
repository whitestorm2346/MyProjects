#pragma once

namespace Calculator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ txtDisplay;
	private: System::Windows::Forms::Button^ btnSpace;
	private: System::Windows::Forms::Button^ btnClear;
	private: System::Windows::Forms::Button^ btnCEntry;
	private: System::Windows::Forms::Button^ btnPMinus;



	protected:



	private: System::Windows::Forms::Button^ btnDigit7;
	private: System::Windows::Forms::Button^ btnDigit8;
	private: System::Windows::Forms::Button^ btnDigit9;



	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ btnDigit4;
	private: System::Windows::Forms::Button^ btnDigit5;
	private: System::Windows::Forms::Button^ btnDigit6;



	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ btnDigit1;
	private: System::Windows::Forms::Button^ btnDigit2;
	private: System::Windows::Forms::Button^ btnDigit3;



	private: System::Windows::Forms::Button^ button16;
	private: System::Windows::Forms::Button^ btnDigit0;
	private: System::Windows::Forms::Button^ btnDecimal;
	private: System::Windows::Forms::Button^ btnEquals;



	private: System::Windows::Forms::Button^ button20;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtDisplay = (gcnew System::Windows::Forms::TextBox());
			this->btnSpace = (gcnew System::Windows::Forms::Button());
			this->btnClear = (gcnew System::Windows::Forms::Button());
			this->btnCEntry = (gcnew System::Windows::Forms::Button());
			this->btnPMinus = (gcnew System::Windows::Forms::Button());
			this->btnDigit7 = (gcnew System::Windows::Forms::Button());
			this->btnDigit8 = (gcnew System::Windows::Forms::Button());
			this->btnDigit9 = (gcnew System::Windows::Forms::Button());
			this->button8 =	(gcnew System::Windows::Forms::Button());
			this->btnDigit4 = (gcnew System::Windows::Forms::Button());
			this->btnDigit5 = (gcnew System::Windows::Forms::Button());
			this->btnDigit6 = (gcnew System::Windows::Forms::Button());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->btnDigit1 = (gcnew System::Windows::Forms::Button());
			this->btnDigit2 = (gcnew System::Windows::Forms::Button());
			this->btnDigit3 = (gcnew System::Windows::Forms::Button());
			this->button16 = (gcnew System::Windows::Forms::Button());
			this->btnDigit0 = (gcnew System::Windows::Forms::Button());
			this->btnDecimal = (gcnew System::Windows::Forms::Button());
			this->btnEquals = (gcnew System::Windows::Forms::Button());
			this->button20 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// txtDisplay
			// 
			this->txtDisplay->Font = (gcnew System::Drawing::Font(L"Consolas", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtDisplay->Location = System::Drawing::Point(12, 12);
			this->txtDisplay->Multiline = true;
			this->txtDisplay->Name = L"txtDisplay";
			this->txtDisplay->Size = System::Drawing::Size(526, 83);
			this->txtDisplay->TabIndex = 0;
			this->txtDisplay->Text = L"0";
			this->txtDisplay->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// btnSpace
			// 
			this->btnSpace->Font = (gcnew System::Drawing::Font(L"Wingdings", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(2)));
			this->btnSpace->Location = System::Drawing::Point(12, 101);
			this->btnSpace->Name = L"btnSpace";
			this->btnSpace->Size = System::Drawing::Size(120, 120);
			this->btnSpace->TabIndex = 1;
			this->btnSpace->Text = L"Õ";
			this->btnSpace->UseVisualStyleBackColor = true;
			this->btnSpace->Click += gcnew System::EventHandler(this, &MyForm::btnSpace_Click);
			// 
			// btnClear
			// 
			this->btnClear->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnClear->Location = System::Drawing::Point(147, 101);
			this->btnClear->Name = L"btnClear";
			this->btnClear->Size = System::Drawing::Size(120, 120);
			this->btnClear->TabIndex = 2;
			this->btnClear->Text = L"C";
			this->btnClear->UseVisualStyleBackColor = true;
			this->btnClear->Click += gcnew System::EventHandler(this, &MyForm::btnClear_Click);
			// 
			// btnCEntry
			// 
			this->btnCEntry->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCEntry->Location = System::Drawing::Point(282, 101);
			this->btnCEntry->Name = L"btnCEntry";
			this->btnCEntry->Size = System::Drawing::Size(120, 120);
			this->btnCEntry->TabIndex = 3;
			this->btnCEntry->Text = L"CE";
			this->btnCEntry->UseVisualStyleBackColor = true;
			this->btnCEntry->Click += gcnew System::EventHandler(this, &MyForm::btnClearEntry_Click);
			// 
			// btnPMinus
			// 
			this->btnPMinus->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnPMinus->Location = System::Drawing::Point(418, 101);
			this->btnPMinus->Name = L"btnPMinus";
			this->btnPMinus->Size = System::Drawing::Size(120, 120);
			this->btnPMinus->TabIndex = 4;
			this->btnPMinus->Text = L"±";
			this->btnPMinus->UseVisualStyleBackColor = true;
			this->btnPMinus->Click += gcnew System::EventHandler(this, &MyForm::btnPlusMinus_Click);
			// 
			// btnDigit7
			// 
			this->btnDigit7->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit7->Location = System::Drawing::Point(12, 227);
			this->btnDigit7->Name = L"btnDigit7";
			this->btnDigit7->Size = System::Drawing::Size(120, 120);
			this->btnDigit7->TabIndex = 1;
			this->btnDigit7->Text = L"7";
			this->btnDigit7->UseVisualStyleBackColor = true;
			this->btnDigit7->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit8
			// 
			this->btnDigit8->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit8->Location = System::Drawing::Point(147, 227);
			this->btnDigit8->Name = L"btnDigit8";
			this->btnDigit8->Size = System::Drawing::Size(120, 120);
			this->btnDigit8->TabIndex = 2;
			this->btnDigit8->Text = L"8";
			this->btnDigit8->UseVisualStyleBackColor = true;
			this->btnDigit8->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit9
			// 
			this->btnDigit9->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit9->Location = System::Drawing::Point(282, 227);
			this->btnDigit9->Name = L"btnDigit9";
			this->btnDigit9->Size = System::Drawing::Size(120, 120);
			this->btnDigit9->TabIndex = 3;
			this->btnDigit9->Text = L"9";
			this->btnDigit9->UseVisualStyleBackColor = true;
			this->btnDigit9->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// button8
			// 
			this->button8->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->Location = System::Drawing::Point(418, 227);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(120, 120);
			this->button8->TabIndex = 4;
			this->button8->Text = L"+";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &MyForm::EnterOperator);
			// 
			// btnDigit4
			// 
			this->btnDigit4->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit4->Location = System::Drawing::Point(12, 353);
			this->btnDigit4->Name = L"btnDigit4";
			this->btnDigit4->Size = System::Drawing::Size(120, 120);
			this->btnDigit4->TabIndex = 1;
			this->btnDigit4->Text = L"4";
			this->btnDigit4->UseVisualStyleBackColor = true;
			this->btnDigit4->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit5
			// 
			this->btnDigit5->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit5->Location = System::Drawing::Point(147, 353);
			this->btnDigit5->Name = L"btnDigit5";
			this->btnDigit5->Size = System::Drawing::Size(120, 120);
			this->btnDigit5->TabIndex = 2;
			this->btnDigit5->Text = L"5";
			this->btnDigit5->UseVisualStyleBackColor = true;
			this->btnDigit5->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit6
			// 
			this->btnDigit6->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit6->Location = System::Drawing::Point(282, 353);
			this->btnDigit6->Name = L"btnDigit6";
			this->btnDigit6->Size = System::Drawing::Size(120, 120);
			this->btnDigit6->TabIndex = 3;
			this->btnDigit6->Text = L"6";
			this->btnDigit6->UseVisualStyleBackColor = true;
			this->btnDigit6->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// button12
			// 
			this->button12->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button12->Location = System::Drawing::Point(418, 353);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(120, 120);
			this->button12->TabIndex = 4;
			this->button12->Text = L"-";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &MyForm::EnterOperator);
			// 
			// btnDigit1
			// 
			this->btnDigit1->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit1->Location = System::Drawing::Point(12, 479);
			this->btnDigit1->Name = L"btnDigit1";
			this->btnDigit1->Size = System::Drawing::Size(120, 120);
			this->btnDigit1->TabIndex = 1;
			this->btnDigit1->Text = L"1";
			this->btnDigit1->UseVisualStyleBackColor = true;
			this->btnDigit1->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit2
			// 
			this->btnDigit2->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit2->Location = System::Drawing::Point(147, 479);
			this->btnDigit2->Name = L"btnDigit2";
			this->btnDigit2->Size = System::Drawing::Size(120, 120);
			this->btnDigit2->TabIndex = 2;
			this->btnDigit2->Text = L"2";
			this->btnDigit2->UseVisualStyleBackColor = true;
			this->btnDigit2->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDigit3
			// 
			this->btnDigit3->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit3->Location = System::Drawing::Point(282, 479);
			this->btnDigit3->Name = L"btnDigit3";
			this->btnDigit3->Size = System::Drawing::Size(120, 120);
			this->btnDigit3->TabIndex = 3;
			this->btnDigit3->Text = L"3";
			this->btnDigit3->UseVisualStyleBackColor = true;
			this->btnDigit3->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// button16
			// 
			this->button16->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button16->Location = System::Drawing::Point(418, 479);
			this->button16->Name = L"button16";
			this->button16->Size = System::Drawing::Size(120, 120);
			this->button16->TabIndex = 4;
			this->button16->Text = L"*";
			this->button16->UseVisualStyleBackColor = true;
			this->button16->Click += gcnew System::EventHandler(this, &MyForm::EnterOperator);
			// 
			// btnDigit0
			// 
			this->btnDigit0->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDigit0->Location = System::Drawing::Point(12, 605);
			this->btnDigit0->Name = L"btnDigit0";
			this->btnDigit0->Size = System::Drawing::Size(120, 120);
			this->btnDigit0->TabIndex = 1;
			this->btnDigit0->Text = L"0";
			this->btnDigit0->UseVisualStyleBackColor = true;
			this->btnDigit0->Click += gcnew System::EventHandler(this, &MyForm::EnterNumber);
			// 
			// btnDecimal
			// 
			this->btnDecimal->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDecimal->Location = System::Drawing::Point(147, 605);
			this->btnDecimal->Name = L"btnDecimal";
			this->btnDecimal->Size = System::Drawing::Size(120, 120);
			this->btnDecimal->TabIndex = 2;
			this->btnDecimal->Text = L".";
			this->btnDecimal->UseVisualStyleBackColor = true;
			this->btnDecimal->Click += gcnew System::EventHandler(this, &MyForm::btnDecimal_Click);
			// 
			// btnEquals
			// 
			this->btnEquals->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnEquals->Location = System::Drawing::Point(282, 605);
			this->btnEquals->Name = L"btnEquals";
			this->btnEquals->Size = System::Drawing::Size(120, 120);
			this->btnEquals->TabIndex = 3;
			this->btnEquals->Text = L"=";
			this->btnEquals->UseVisualStyleBackColor = true;
			this->btnEquals->Click += gcnew System::EventHandler(this, &MyForm::btnEquals_Click);
			// 
			// button20
			// 
			this->button20->Font = (gcnew System::Drawing::Font(L"Consolas", 20, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button20->Location = System::Drawing::Point(418, 605);
			this->button20->Name = L"button20";
			this->button20->Size = System::Drawing::Size(120, 120);
			this->button20->TabIndex = 4;
			this->button20->Text = L"/";
			this->button20->UseVisualStyleBackColor = true;
			this->button20->Click += gcnew System::EventHandler(this, &MyForm::EnterOperator);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(550, 736);
			this->Controls->Add(this->button20);
			this->Controls->Add(this->button16);
			this->Controls->Add(this->button12);
			this->Controls->Add(this->button8);
			this->Controls->Add(this->btnPMinus);
			this->Controls->Add(this->btnEquals);
			this->Controls->Add(this->btnDecimal);
			this->Controls->Add(this->btnDigit3);
			this->Controls->Add(this->btnDigit2);
			this->Controls->Add(this->btnDigit6);
			this->Controls->Add(this->btnDigit5);
			this->Controls->Add(this->btnDigit0);
			this->Controls->Add(this->btnDigit9);
			this->Controls->Add(this->btnDigit1);
			this->Controls->Add(this->btnDigit8);
			this->Controls->Add(this->btnDigit4);
			this->Controls->Add(this->btnCEntry);
			this->Controls->Add(this->btnDigit7);
			this->Controls->Add(this->btnClear);
			this->Controls->Add(this->btnSpace);
			this->Controls->Add(this->txtDisplay);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		double db_1stDigit, db_2ndDigit, db_Result;
		String^ str_Operators;

private: System::Void EnterNumber(System::Object^ sender, System::EventArgs^ e) {
	
	Button^ Numbers = safe_cast<Button^>(sender);

	if (txtDisplay->Text == "0")
	{
		txtDisplay->Text = Numbers->Text;
	}
	else
	{
		txtDisplay->Text = txtDisplay->Text + Numbers->Text;
	}
}

private: System::Void EnterOperator(System::Object^ sender, System::EventArgs^ e) {

	Button^ NumbersOp = safe_cast<Button^>(sender);
	db_1stDigit = Double::Parse(txtDisplay->Text);

	txtDisplay->Text = "";
	str_Operators = NumbersOp->Text;
}

private: System::Void btnDecimal_Click(System::Object^ sender, System::EventArgs^ e) {

	if (!txtDisplay->Text->Contains("."))
	{
		txtDisplay->Text = txtDisplay->Text + ".";
	}
}

private: System::Void btnEquals_Click(System::Object^ sender, System::EventArgs^ e) {

	db_2ndDigit = Double::Parse(txtDisplay->Text);

	if (str_Operators == "+")
	{
		db_Result = db_1stDigit + db_2ndDigit;
		txtDisplay->Text = System::Convert::ToString(db_Result);
	}	
	else if (str_Operators == "-")
	{
		db_Result = db_1stDigit - db_2ndDigit;
		txtDisplay->Text = System::Convert::ToString(db_Result);
	}
	else if (str_Operators == "*")
	{
		db_Result = db_1stDigit * db_2ndDigit;
		txtDisplay->Text = System::Convert::ToString(db_Result);
	}
	else if (str_Operators == "/")
	{
		db_Result = db_1stDigit / db_2ndDigit;
		txtDisplay->Text = System::Convert::ToString(db_Result);
	}
}

private: System::Void btnClear_Click(System::Object^ sender, System::EventArgs^ e) {

	txtDisplay->Text = "0";
}

private: System::Void btnClearEntry_Click(System::Object^ sender, System::EventArgs^ e) {

	txtDisplay->Text = "0";
}

private: System::Void btnPlusMinus_Click(System::Object^ sender, System::EventArgs^ e) {

	if (txtDisplay->Text->Contains("-"))
	{
		txtDisplay->Text = txtDisplay->Text->Remove(0, 1);
	}
	else
	{
		txtDisplay->Text = "-" + txtDisplay->Text;
	}
}

private: System::Void btnSpace_Click(System::Object^ sender, System::EventArgs^ e) {

	if (txtDisplay->Text->Length > 0)
	{
		txtDisplay->Text = txtDisplay->Text->Remove(txtDisplay->Text->Length - 1, 1);
	}

	if (txtDisplay->Text == "")
	{
		txtDisplay->Text = "0";
	}
}
};
}
