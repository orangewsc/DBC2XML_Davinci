#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <vector>
#include <iostream>
#include <windows.h>
using namespace std;



typedef struct Filename
{
	char *file_path;

}Filename;

typedef struct Signal_X
{
	string name;
	string starbit;
	string length;
	string valuetype;
	string factor;
	string offset;
	string minimum;
	string maximum;
	string unit;
	vector<string> recieve;
}Signal_X;

typedef struct Messege
{
	size_t position;
	string ID;
	string name;
	string DLC;
	string cycle;
	string transmit;
	string sendtype;
	vector<Signal_X> Signal;
}Messege;

typedef struct LongName
{
	string ID;
	string Shortname;
	string Longname;
}LongName;

typedef struct DE_PORT
{
	string De_NAME;
	string Dt_RECORD_NAME;
	string Dt_ARRAY_NAME;
	string C_RECORD_NAME;
	string C_ARRAY_NAME;

}DE_PORT;

typedef struct PI_PORT
{
	string Pi_NAME;
	string Pp_NAME;
	vector<DE_PORT> De_PORT;
}PI_PORT;

typedef struct Recoder_Signal
{
	string Signal_Name;
	string type_str;
	int type_int;
	int Array_Size;
	int Flag_Type;
}RECODER_SIGNAL;

typedef struct DT_RECODER
{
	string Dt_RECODER_NAME;
	vector<RECODER_SIGNAL> Recoder_Signal;
}DT_RECODER;

typedef vector<vector<DT_RECODER>> R_S_VC_ALL;

typedef struct PAD_DT_RECORD
{
	string NAME;
	int LENGTH_TOTAL;
}PAD_DT_RECORD;


/*****************************           DBC Check           *******************************/
void DBC_Check_BA_DEF_BO(char *filename);
void DBC_Check_SameDBC(string Node, vector<Messege> messege_vector, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void DBC_Check_DiffDBC(vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU);
void DBC_Check_Cycle0( vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void DBC_Check_Sendtype(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void DBC_Check_DLC(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void DBC_Check_Longname(string DBC_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void DBC_Check_Max_Min(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
void Compare2DBCs(char *DBC1_name, char *DBC2_name, string Node);

/*****************************         DBC Analysis         *******************************/
string Read_Get_DBC(char *filename_DBC);

vector<Messege> DBC_Extract(string DBC_str, vector<Messege> messege_vector);
void Printf_MessegeVector(vector<Messege> messege_vector);

vector<Messege> Tx_IECU_Get(string DBC_str, string Node, vector<Messege> messege_vector, vector<Messege> Tx_IECU);
void Printf_TxIECU(vector<Messege> TxIECU);

vector<Messege> Rx_IECU_Get(string DBC_str, string Node, vector<Messege> messege_vector, vector<Messege> Rx_IECU);
void Printf_RxIECU(vector<Messege> RxIECU);

void DBC_ReadANDCheck(int file_NUM, vector<Filename> FILE,string Node,string DBC_str_TEMP, string DBC_str, vector<Messege> messege_vector_tmp, vector<Messege> messege_vector, vector<Messege> Tx_IECU_tmp, vector<Messege> Rx_IECU_tmp, vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU);
void DBC_Extract_All(int file_NUM, vector<Filename> FILE, string Node, string DBC_str_TEMP, string DBC_str, vector<Messege> messege_vector_tmp, vector<Messege> messege_vector, vector<Messege> Tx_IECU_tmp, vector<Messege> Rx_IECU_tmp, vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU);


/*****************************         XML Generate         *******************************/
void XML_Generate(char *file_Template_Head, char *file_DataType, char *file_XML, string CtApVMS, string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
string XML_Generate_Head(char *file_Template_Head);
string XML_Generate_ComponentTypes(string CtApVMS, string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
string XML_Generate_Constants(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
string XML_Generate_DataType(string XML_str, char *file_DataType);
string XML_Generate_DataTypes(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
string XML_Generate_DaVinci(string XML_str);
string XML_Generate_PortInterfaces(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU);
string XML_Generate_Total(string XML_str, char *file_XML);

/*****************************         CtApCOM_src Generate         *******************************/
void CtApCOM_Src_Generte(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU, string Comp_COM);


/*****************************         Middleware_src Generate         *******************************/

void Aurix_Rcar_Middleware_XML_Read(string &Aurix_Middleware_str, string &Rcar_Middleware_str);
void XML_Extrat_PortAll(string &XML, vector<PI_PORT> &Port_ALL);

void Find_Recoder_Signal(string &XML, string Reference_Name, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All);
void Find_Recoder_Layers(string &XML, bool &Flag_Loop, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All);
void Find_Recoder_SignalAll(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All);

void Padding_Implem_Inseret(string &XML, string Dt_RECODER_NAME, int Position_Num, int Pad_Sig_Num, int Pad_Length);
void Padding_Implem_PushBack(string &XML, string Dt_RECODER_NAME, int Position_Num, int Pad_Sig_Num, int Pad_Length);
void Padding_Cal(string &XML, vector<int> &SOA_Message_Pad, string Dt_RECORD_Name, int &Pad_Num, int &Length_Total);
void XML_Padding(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All);
void Padding_ALL(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All);






