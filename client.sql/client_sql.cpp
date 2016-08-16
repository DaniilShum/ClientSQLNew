/////---------------------------------------------------------------------------
#include "client_sql.h"
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TService1 *Service1;
//---------------------------------------------------------------------------
__fastcall TService1::TService1(TComponent* Owner)
	: TService(Owner)
{
  int k=-1;
  while(k<0)
  {
     _di_IXMLDocument XMLDocument = NewXMLDocument();

  XMLDocument->Active = True;
  XMLDocument->Encoding = "UTF-8";

  //    C:\\SyncOpora\\opora.synk\\sync_file.xml
  XMLDocument->LoadFromFile("C:\\SyncOpora\\opora.synk\\sync_file.xml");

  _di_IXMLNode rootNode = XMLDocument->ChildNodes->Nodes[WideString("root")];
  _di_IXMLNode infoNode = rootNode->ChildNodes->GetNode(WideString("ross"));
  AnsiString dataDate = infoNode->ChildNodes->GetNode(WideString("makeData"))->GetNodeValue();
  AnsiString dataTime = infoNode->ChildNodes->GetNode(WideString("makeTime"))->GetNodeValue();
  unsigned int lastID = infoNode->ChildNodes->GetNode(WideString("lastID"))->GetNodeValue();

  //Запись в xml файл
  _di_IXMLDocument XML = NewXML("Ross");

  //  AnsiString queryString = "SELECT * FROM ZAKAZ WHERE DATA_END >= '" + dataDate + "'";
  AnsiString queryString = "SELECT * FROM dbo.ZAKAZ WHERE NN > " + (AnsiString)lastID;


  // "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=RBU;Data Source=ADMIN-ПК\SQLEXPRESS"
  DataSource1->DataSet = ADOQuery1;
  ADOQuery1->Close();
  ADOQuery1->SQL->Clear();
  ADOQuery1->SQL->Add(queryString);
  ADOQuery1->Open();

  RbuDataType DataRBU;
  int k = DataSource1->DataSet->RecordCount;
  int i = 0;
  while(i<k)
  {
    DataRBU.day =           DataSource1->DataSet->FieldList->Fields[51]->Text;
    DataRBU.time =          DataSource1->DataSet->FieldList->Fields[52]->Text;
    DataRBU.sand =          DataSource1->DataSet->FieldList->Fields[10]->AsFloat;
    DataRBU.macadam =       DataSource1->DataSet->FieldList->Fields[14]->AsFloat;
    DataRBU.cement =        DataSource1->DataSet->FieldList->Fields[38]->AsFloat;
    DataRBU.water =         DataSource1->DataSet->FieldList->Fields[42]->AsFloat;
    DataRBU.chemical =      DataSource1->DataSet->FieldList->Fields[26]->AsFloat ;
    DataRBU.productDev =    DataSource1->DataSet->FieldList->Fields[6]->AsFloat;
    DataRBU.product =       DataSource1->DataSet->FieldList->Fields[4]->Text;
    DataRBU.recordID =      DataSource1->DataSet->FieldList->Fields[0]->AsInteger;

    setValueRbu(DataRBU);

    i++;

    DataSource1->DataSet->Next();
  }

  ADOQuery1->SQL->Clear();

  // D:\\SyncOpora\\YandexDisk\\opora.synk\\factory\\ross.xml
  // C:\\SyncOpora\\opora.synk
  XML->SaveToFile("C:\\SyncOpora\\opora.synk\\factory\\ross.xml");
  sleep(1800);

  }
}

TServiceController __fastcall TService1::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}

void __stdcall ServiceController(unsigned CtrlCode)
{
	Service1->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
 