
#ifndef   BSSxmlH
#define   BSSxmlH

#include <System.hpp>
#include <xmldom.hpp>
#include <XMLDoc.hpp>
#include <XMLIntf.hpp>
#include <XMLNodeImp.h>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdFTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <ADODB.hpp>

/**
 * rbu data struct
 */
typedef struct rbudatatype {
 unsigned int recordID;
 AnsiString product;
 float productDev;
 float sand;
 float macadam;
 double chemical;
 float cement;
 float water;
 WideString day;
 WideString time;
}RbuDataType;


/**
 * create new xml with root
 */
_di_IXMLDocument __fastcall  NewXML(WideString factoryName);



/**
 * add data to record
 */
void __fastcall  setValueRbu(RbuDataType data);


/**
 * create data struct
 */
RbuDataType __fastcall  createDataStruct();

/**
 * read data to sql
 */
void __fastcall  readRbuData(WideString xmlName, TComponent *owner);


#endif
