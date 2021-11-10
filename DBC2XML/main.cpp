#include "include.h"

#define file_NUM                    5        // DBC个数
#define Node                      "iECU"     // 节点名称
#define CtApVMS                  "CtApBusInOut" // SWC模块名
#define Comp_COM				   "Com"     //Pi接口里的模块名，主要是CtApCom.c里的源码
#define Comp_VMS				   "VMS"     //Pi接口里的模块名

#define DBC_READ_AND_CHECK          0      // DBC检查
#define XML_GENERATE                1     // XML生成
#define COMPARE_2DBC                0      // DBC比对
#define CtApCOM_SRC_GENERATE        0      // CtApCOM源码
#define Middleware_SRC_GENERATE     0      // Middleware源码

//#pragma comment(linker,"/STACK:1024000000,1024000000")

void main()
{
	long start = GetTickCount();

	Filename	filename1,
				filename2,
				filename3,
				filename4,
				filename5,
				filename6;
	/*===========                  DBC路径                ===============*/
	filename1.file_path = "C:\\Users\\liugu\\Desktop\\dbc\\CH.dbc";
	filename2.file_path = "C:\\Users\\liugu\\Desktop\\dbc\\FSDA.dbc";
	filename3.file_path = "C:\\Users\\liugu\\Desktop\\dbc\\Info.dbc";
	filename4.file_path = "C:\\Users\\liugu\\Desktop\\dbc\\SecCH.dbc";
	filename5.file_path = "C:\\Users\\liugu\\Desktop\\dbc\\SecInfo.dbc";
//	filename6.file_path = "G:\\111111111111111111111111111\\0909\\DBCs\\EP21H2_EP_SecInfoV01_191018.dbc";
// 	filename1.file_path = "E:/Project/AIT/ARC Mule/01_DBCs/AIT_Arcmule_iECU1.0_2#-Pegasus_CAN_V1.1_0508.dbc";
// 	filename2.file_path = "E:/Project/AIT/ARC Mule/01_DBCs/CVTC_DK11_AIT_CMX_PT_V1.4_20200406_iECU_2.dbc";
// 	filename3.file_path = "E:/Project/AIT/ARC Mule/01_DBCs/CVTC_DK11_AIT_CMX_CH_V1.4_20200406_iECU2.dbc";
// 	filename4.file_path = "E:/Project/AIT/ARC Mule/01_DBCs/20200508_AIT_FSDA-IECU_V1.1.dbc";
 	

	/*===========                  生成的XML路径                ===============*/
	char *file_XML = "C:/Users/liugu/Desktop/output/CtApBusInOut.arxml";

	/*===========               Template路径              ===============*/
	char *file_Template_Head = "C:/Users/liugu/Desktop/temp/Template_Head.txt";
	char *file_DataType = "C:/Users/liugu/Desktop/temp//DataType.txt";
	
	string DBC_str_TEMP, DBC_str, XML_str;
	vector<Messege> messege_vector_tmp,
					messege_vector,
					Tx_IECU_tmp,
					Tx_IECU,
					Rx_IECU_tmp,
					Rx_IECU;

	vector<Filename> FILE_DBC;
	FILE_DBC.push_back(filename1);
	FILE_DBC.push_back(filename2);
	FILE_DBC.push_back(filename3);
	FILE_DBC.push_back(filename4);
	FILE_DBC.push_back(filename5);
	FILE_DBC.push_back(filename6);

#if DBC_READ_AND_CHECK == 1

	DBC_ReadANDCheck(file_NUM, FILE_DBC, Node, DBC_str_TEMP, DBC_str, messege_vector_tmp, messege_vector, Tx_IECU_tmp, Rx_IECU_tmp, &Tx_IECU, &Rx_IECU);

#endif

#if XML_GENERATE == 1

	DBC_Extract_All(file_NUM, FILE_DBC, Node, DBC_str_TEMP, DBC_str, messege_vector_tmp, messege_vector, Tx_IECU_tmp, Rx_IECU_tmp, &Tx_IECU, &Rx_IECU);
	XML_Generate(file_Template_Head, file_DataType, file_XML, CtApVMS, XML_str, Tx_IECU, Rx_IECU);

#endif

#if CtApCOM_SRC_GENERATE == 1

	DBC_Extract_All(file_NUM, FILE_DBC, Node, DBC_str_TEMP, DBC_str, messege_vector_tmp, messege_vector, Tx_IECU_tmp, Rx_IECU_tmp, &Tx_IECU, &Rx_IECU);
	CtApCOM_Src_Generte(Tx_IECU, Rx_IECU, Comp_COM);

#endif

#if Middleware_SRC_GENERATE == 1

	string Aurix_Middleware_str;
	string Rcar_Middleware_str;
	vector<PI_PORT> Port_ALL_Aurix;
	vector<vector<DT_RECODER>> Recoder_Signal_VC_All_Aurix, Recoder_Signal_VC_All_Rcar;


	Aurix_Rcar_Middleware_XML_Read(Aurix_Middleware_str, Rcar_Middleware_str);

	Padding_ALL(Aurix_Middleware_str, Port_ALL_Aurix, Recoder_Signal_VC_All_Aurix);
	printf("Padding后的:%s\n", Aurix_Middleware_str.c_str());
	//printf("读取成功！\n");
	

#endif

#if COMPARE_2DBC == 1

	Compare2DBCs(FILE[0].file_path, FILE[1].file_path, Node);  

#endif
//*****************************    打印解析出来的信息    *******************************/
// 	printf("DBC_str=\n%s", DBC_str.c_str());
// 	Printf_MessegeVector(messege_vector);
//  Printf_TxIECU(Tx_IECU);
//  Printf_RxIECU(Rx_IECU);
	
	long finish = GetTickCount();
	long Time = finish - start;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);  //6黄色, 7白色
	printf("Runtime:%ld ms\n", Time);

	system("pause");
}

