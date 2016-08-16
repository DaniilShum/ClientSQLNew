/**
 *  Created by BSS 23.05.2016
 *  Erdal Kumsarov
 *
 */

 #include "BSSxml.h"

 int dataNum = 0;
 _di_IXMLNode rootNode;

 _di_IXMLDocument __fastcall  NewXML(WideString factoryName){

  dataNum = 0;

  // создаем сам файл xml и его начало
  _di_IXMLDocument XMLDocument = NewXMLDocument();

  XMLDocument->Active = True;
  XMLDocument->Encoding = "UTF-8";

  _di_IXMLNode nodElement = XMLDocument->CreateElement("root", "");
  XMLDocument->ChildNodes->Add(nodElement);

  rootNode = XMLDocument->ChildNodes->Nodes[WideString("root")];

  // добавление двух узлов с информацией и данными
  rootNode->AddChild("data", 0);
  rootNode->AddChild("info", 0);

  // заполн€ем дату создани€ файла
  TDateTime CurrentDate = Date();
  _di_IXMLNode dataNode = rootNode->ChildNodes->Nodes[WideString("info")];
  dataNode->AddChild("makeData");
  dataNode->ChildNodes->GetNode(WideString("makeData"))->SetNodeValue(CurrentDate);


  // заполн€ем врем€ создани€ файла
  TDateTime CurrentTime = Time();
  _di_IXMLNode timeNode = rootNode->ChildNodes->Nodes[WideString("info")];
  timeNode->AddChild("makeTime");
  timeNode->ChildNodes->GetNode(WideString("makeTime"))->SetNodeValue(CurrentTime);


  // добавл€ем поле с номером завода
  _di_IXMLNode fNode = rootNode->ChildNodes->Nodes[WideString("info")];
  fNode->AddChild("factory");
  fNode->ChildNodes->GetNode(WideString("factory"))->SetNodeValue(factoryName);

  // добавл€ем поле с количеством записей
  _di_IXMLNode numNode = rootNode->ChildNodes->Nodes[WideString("info")];
  numNode->AddChild("dataNum");
  numNode->ChildNodes->GetNode(WideString("dataNum"))->SetNodeValue(0);


  //_di_IXMLNode rn = rootNode->ChildNodes->Nodes[WideString("data")];
  //rn->AddChild("dict", 0);
  //rn->AddChild("dict", 0);
  //rn->ChildNodes->GetNode(0)->SetNodeValue(rootNode->ChildNodes->Nodes[WideString("info")]->GetNodeType());

  return XMLDocument;
 }




 /**
 * read data to sql
 */
void __fastcall  readRbuData(WideString xmlName, TComponent *owner) {

  _di_IXMLDocument XMLDocument = NewXMLDocument();

  XMLDocument->Active = True;
  XMLDocument->Encoding = "UTF-8";

  XMLDocument->LoadFromFile("test.xml");

  _di_IXMLNode rootNode = XMLDocument->ChildNodes->Nodes[WideString("root")];
  _di_IXMLNode infoNode = rootNode->ChildNodes->GetNode(WideString("info"));
  _di_IXMLNode iNode = infoNode->ChildNodes->GetNode(WideString("dataNum"));
  _di_IXMLNode dataNode = rootNode->ChildNodes->GetNode(WideString("data"));
  int lenght = iNode->GetNodeValue();



  //ѕроба записи в базу SQL

  //инициализаци€
  /*TADOConnection *ADOConnection = new TADOConnection(owner);
  TADOTable *ADOTable = new TADOTable(owner);
  TDataSource *DataSource = new TDataSource(owner);
  TADOQuery *ADOQuery = new TADOQuery(owner);



  //настройка
  ADOConnection->Connected = false;
  ADOConnection->LoginPrompt = false;
  ADOConnection->ConnectionString = "Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=For_1C_Base;Data Source=DANIIL-UB\\SQLEXPRESS";
  ADOConnection->Connected = true;

  ADOTable->Connection = ADOConnection;
  ADOTable->TableName = "Main";
  ADOTable->Active = true;

  DataSource->DataSet = ADOTable;
  DataSource->DataSet = ADOQuery;

  ADOQuery->Connection = ADOConnection;
  ADOQuery->Close();
  ADOQuery->SQL->Clear();
      // ADOQuery->SQL->Add("SELECT * FROM 'C:\\ArmRbu60\\DB\\Materials.DB' WHERE UnLoadDate BETWEEN '01.01.2016' AND '15.01.2016'");
  ADOQuery->SQL->Add("INSERT INTO Main (Num, Factory, Product, ProductDev, Sand, Macadam, Chemical, Cement, Water, Day, Time)");
  ADOQuery->SQL->Add("VALUES (1, 'Demus', 'Ѕетон', 2.5, 5, 5, 5, 5, 5, '23.12.2013', '12:08')");
  ADOQuery->ExecSQL();

 // for(int i = 0; i < lenght; i++)
  //{

      /* ADOQuery->SQL->Add("VALUES ("
                      +i+
                   ","+(String)"Demus"+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("product"))->GetNodeValue().AsType(17)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("productDev"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("sand"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("macadam"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("chemical"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("cement"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("water"))->GetNodeValue().AsType(6)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("dayR"))->GetNodeValue().AsType(17)+
                   ","+dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("timeR"))->GetNodeValue().AsType(17)+")");
             */
      // ADOQuery->SQL->Add("VALUES ("+i+":Param1, :Param2, :Param3, :Param4, :Param5, :Param6, :Param7, :Param8, :Param9, :Param10, :Param11)");

       /*ADOQuery->Parameters->ParamByName("Param1")->Value = i;
       ADOQuery->Parameters->ParamByName("Param2")->Value = "Demus";
       ADOQuery->Parameters->ParamByName("Param3")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("product"))->GetNodeValue().AsType(17);
       ADOQuery->Parameters->ParamByName("Param4")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("productDev"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param5")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("sand"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param6")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("macadam"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param7")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("chemical"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param8")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("cement"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param9")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("water"))->GetNodeValue().AsType(6);
       ADOQuery->Parameters->ParamByName("Param10")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("dayR"))->GetNodeValue().AsType(17);
       ADOQuery->Parameters->ParamByName("Param11")->Value = dataNode->ChildNodes->Nodes[i]->ChildNodes->GetNode(WideString("timeR"))->GetNodeValue().AsType(17);
        */
      // ADOQuery->ExecSQL();
      // DBGrid1->DataSource = DataSource1;
 // }



}





 /**
  * create data struct
  */
RbuDataType __fastcall  createDataStruct()
{
 RbuDataType data;
 /*data.product = -1;
 data.productDev = -1;
 data.sandF = -1;
 data.sandN = -1;
 data.sandR = -1;
 data.macadamF = -1;
 data.macadamN = -1;
 data.macadamR = -1;
 data.chemicalR = -1;
 data.chemicalF = -1;
 data.chemicalN = -1;
 data.cementR = -1;
 data.cementF = -1;
 data.cementN = -1;
 data.waterR = -1;
 data.waterF = -1;
 data.waterN = -1;
 data.dayR = "0.0.0";
 data.timeR = "00:00"; */

 return data;
}



/**
 * add data to record
 */
void __fastcall  setValueRbu(RbuDataType data)
{
  dataNum+=1;

  _di_IXMLNode rn = rootNode->ChildNodes->Nodes[WideString("data")];
  rn->AddChild("dict", 0);
  _di_IXMLNode dict = rn->ChildNodes->Nodes[0];


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("recordID");
  dict->ChildNodes->GetNode(WideString("recordID"))->SetNodeValue(data.recordID);

  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("product");
  dict->ChildNodes->GetNode(WideString("product"))->SetNodeValue(data.product);

  dict->AddChild("productDev");
  dict->ChildNodes->GetNode(WideString("productDev"))->SetNodeValue(data.productDev);


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("sand");
  dict->ChildNodes->GetNode(WideString("sand"))->SetNodeValue(data.sand);


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("macadam");
  dict->ChildNodes->GetNode(WideString("macadam"))->SetNodeValue(data.macadam);


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("chemical");
  dict->ChildNodes->GetNode(WideString("chemical"))->SetNodeValue(data.chemical);



  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("cement");
  dict->ChildNodes->GetNode(WideString("cement"))->SetNodeValue(data.cement);


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("water");
  dict->ChildNodes->GetNode(WideString("water"))->SetNodeValue(data.water);


  /////////////////////////////////////////////////////////////////////////
  dict->AddChild("dayR");
  dict->ChildNodes->GetNode(WideString("dayR"))->SetNodeValue(data.day);

  dict->AddChild("timeR");
  dict->ChildNodes->GetNode(WideString("timeR"))->SetNodeValue(data.time);


  // добавл€ем поле с количеством записей
  _di_IXMLNode numNode = rootNode->ChildNodes->Nodes[WideString("info")];
  numNode->ChildNodes->GetNode(WideString("dataNum"))->SetNodeValue(dataNum);

}
