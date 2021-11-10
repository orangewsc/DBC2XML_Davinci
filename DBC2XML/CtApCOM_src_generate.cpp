#include "include.h"



void CtApCOM_Src_Generte(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU, string Comp_COM)
{
	printf("CtApCOM代码生成中...\n\n");

    #define FSDA_FRP_00        0
	#define RADAR_FRP_00       1
	string FSDA_DBC = "FSDA_FrP";
	string RADAR_DBC = "RADAR_SecCH_FrP";
	int ARRAY_NUM = 32;

	string PiName_FSDA_Position = "<SHORT-NAME>Pi" + Comp_COM + "_" + FSDA_DBC;
	string PiName_RADAR_Position = "<SHORT-NAME>Pi" + Comp_COM + "_" + RADAR_DBC;
	string ARRAY_FSDA_Position = "Dt_ARRAY_32_" + FSDA_DBC + "</TYPE-TREF>";
	string ARRAY_RADAR_Position = "Dt_ARRAY_32_" + RADAR_DBC + "</TYPE-TREF>";
	string DeFSDA_Position = "<SHORT-NAME>De" + FSDA_DBC + "</SHORT-NAME>";    //注意根据DBC格式的不同，可能报文名字的定义格式不一致。
	string DeRADAR_Position = "<SHORT-NAME>De" + RADAR_DBC  + "</SHORT-NAME>";  //注意根据DBC格式的不同，可能报文名字的定义格式不一致。
	string Dt_RECORD_FSDA_Position = "Dt_RECORD_" + FSDA_DBC + "</SHORT-NAME>";
	string Dt_RECORD_RADAR_Position = "Dt_RECORD_" + RADAR_DBC + "</SHORT-NAME>";
	string SHORT_NAME_FSDA = "<SHORT-NAME>";
	string SHORT_NAME_RADAR = "<SHORT-NAME>";
	string IMPLEMENTATION_DATA_TYPE = "</IMPLEMENTATION-DATA-TYPE>";

	vector<Messege> VC_FSDA_ARRAY,
					VC_RADAR_ARRAY;

	vector<string>	VC_FSDA_ARRAY_SignalName,
					VC_RADAR_ARRAY_SignalName;

	bool flag_FSDA_ARRAY_Signal = true,
		 flag_RADAR_ARRAY_Signal = true;

	int i_Find_FSDA_Pi_Start = 0,
		i_Find_FSDA_Pi_End = 0,
		i_Find_FSDA_ARRAY_Start = 0,
		i_Find_FSDA_ARRAY_End = 0,
		i_Find_RADAR_Pi_Start = 0,
		i_Find_RADAR_Pi_End = 0,
		i_Find_RADAR_ARRAY_Start = 0,
		i_Find_RADAR_ARRAY_End = 0,
		i_Find_DeFSDA_Start = 0,
		i_Find_DeFSDA_End = 0,
		i_Find_DeRADAR_Start = 0,
		i_Find_DeRADAR_End = 0,
		i_Find_Dt_RECORD_FSDA_Start = 0,
		i_Find_Dt_RECORD_FSDA_End = 0,
		i_Find_Dt_RECORD_RADAR_Start = 0,
		i_Find_Dt_RECORD_RADAR_End = 0,
		i_Find_FSDA_SHORTNAME_END = 0,
		i_Find_RADAR_SHORTNAME_END = 0,
		j_FSDA = 0,
		j_RADAR = 0,
		FSDA_Signal_Position = 0,
		RADAR_Signal_Position = 0;



	string PiName_FSDA,
		   PiName_RADAR,
		   ArrayName_FSDA,
		   ArrayName_RADAR,
		   DeName_FSDA,
		   DeName_RADAR,
		   ArraySignalName_FSDA,
		   ArraySignalName_RADAR,
		   Signal_CutOff_FSDA,
		   Signal_CutOff_RADAR,
		   ArraySignal_CutOff_FSDA,
		   ArraySignal_CutOff_RADAR;


	char buf[500];
	string str_CtApCOM, 
		   str_CtApCOM_D_h, 
		   str_CtApCOM_D_c, 
		   str_CtApCOM_c;


	FILE *fp_CtApCOM_XML = fopen("G:/1111111111111111111/0819/CtApCom_swc.arxml", "r");
	FILE *fp_CtApCOM_D_h = fopen("E:/Work/DaVinci/Myself/DBC2XML/02_Src/01_CtApCOM/CtApCom_D.h", "w+");
	FILE *fp_CtApCOM_D_c = fopen("E:/Work/DaVinci/Myself/DBC2XML/02_Src/01_CtApCOM/CtApCom_D.c", "w+");
	FILE *fp_CtApCOM_c = fopen("E:/Work/DaVinci/Myself/DBC2XML/02_Src/01_CtApCOM/CtApCom.c", "w+");

	if (fp_CtApCOM_XML == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("CtApCOM_XML文件读取失败!\n");
	}

	if (fp_CtApCOM_D_h == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("CtApCOM_D_h文件创建失败!\n");
	}

	if (fp_CtApCOM_D_c == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("CtApCOM_D_c文件创建失败!\n");
	}

	if (fp_CtApCOM_c == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("CtApCOM_c文件创建失败!\n");
	}


	while (!(feof(fp_CtApCOM_XML)))
	{
		fgets(buf, sizeof(buf), fp_CtApCOM_XML);
		str_CtApCOM.append(buf);
	}
	fclose(fp_CtApCOM_XML);

	//printf("COM: %s\n", str_CtApCOM.c_str());

	str_CtApCOM_D_h += "#include \"Std_Types.h\"\n\
#include \"Rte_Type.h\"\n\n";

	str_CtApCOM_D_c += "#include \"CtApCom_D.h\"\n\n";

	str_CtApCOM_c += "#include \"Rte_CtApCom.h\"\n\
#include \"CtApCom_D.h\"\n\
#include \"Com.h\"\n\n\
#define CtApCom_START_SEC_CODE\n\
#include \"CtApCom_MemMap.h\"\n\n\n\n";
	
/*****************************         RComRX_10ms         *******************************/
	
	str_CtApCOM_c += "FUNC(void, CtApCom_CODE) RComRX_10ms(void)\n\
{\n\
    uint8 Var_U8;\n\
	uint16 Var_U16;\n\
	uint32 Var_U32;\n\
	uint64 Var_U64;\n\
	sint8 Var_S8;\n\
	sint16 Var_S16;\n\
	sint32 Var_S32;\n\
	sint64 Var_S64;\n\
	float32 Var_F32;\n\
	float64 Var_F64;\n\
	static uint16 RComRx_cnt = 0;\n\
	if (RComRx_cnt == 3000)\n\
	{\n\
		RComRx_cnt = 10;\n\
	}\n\
	else\n\
	{\n\
		RComRx_cnt += 10;\n\
	}\n";


	/*************************                  报文查找提取            **************************/
	for (int i = 0; i < ARRAY_NUM; i++)  
	{
		char Ch_X_FSDA[3],
			 Ch_X_RADAR[3],
			 Ch_X_FSDA_00[3],
			 Ch_X_RADAR_00[3];

		string FSDA_FrPx,
			   RADAR_FrPx;

		if (FSDA_FRP_00 == 0)
		{
			_itoa(i, Ch_X_FSDA, 10);
			FSDA_FrPx = FSDA_DBC + "_" + Ch_X_FSDA;
		}
		else
		{
			_itoa(i, Ch_X_FSDA, 10);
			sprintf(Ch_X_FSDA_00, "%2s", Ch_X_FSDA);
			FSDA_FrPx = FSDA_DBC + "_" + Ch_X_FSDA_00;	//注意根据DBC格式的不同，可能报文名字的定义格式不一致。
		}

		if (RADAR_FRP_00 == 0)
		{
			_itoa(i, Ch_X_RADAR, 10);
			RADAR_FrPx = RADAR_DBC + "_" + Ch_X_RADAR;   //注意根据DBC格式的不同，可能报文名字的定义格式不一致。
		}
		else
		{
			_itoa(i, Ch_X_RADAR, 10);
			sprintf(Ch_X_RADAR_00, "%02s", Ch_X_RADAR);
			RADAR_FrPx = RADAR_DBC + Ch_X_RADAR_00;
		}

		for ( int i_RX = 0; i_RX < Rx_IECU.size(); i_RX++)
		{
			if (Rx_IECU[i_RX].name == FSDA_FrPx )
			{
				VC_FSDA_ARRAY.push_back(Rx_IECU[i_RX]);
			}
			else if (Rx_IECU[i_RX].name == RADAR_FrPx)
			{
				VC_RADAR_ARRAY.push_back(Rx_IECU[i_RX]);
			}
		}
	}

	printf("VC_FSDA_ARRAY size:%d\n\n", VC_FSDA_ARRAY.size());
	printf("VC_RADAR_ARRAY size:%d\n\n", VC_RADAR_ARRAY.size());

// 	for (int i = 0; i < VC_FSDA_ARRAY.size();i++)
// 	{
// 		printf("VC_FSDA_ARRAY[%d]:%s\n", i, VC_FSDA_ARRAY[i].name.c_str());
// 		for (int j = 0; j < VC_FSDA_ARRAY[i].Signal.size();j++)
// 		{
// 			printf("%s\n", VC_FSDA_ARRAY[i].Signal[j].name.c_str());
// 		}
// 	}
	


	/*************************                   普通报文             **************************/
	for (int j_RX = 0; j_RX < Rx_IECU.size();j_RX++)  //普通数据的.c生成
	{
		int a = 0;
		for (int j_VC_FSDA = 0,  j_VC_RADAR = 0; j_VC_FSDA < VC_FSDA_ARRAY.size(), j_VC_RADAR < VC_RADAR_ARRAY.size();j_VC_FSDA++,j_VC_RADAR++)
		{
			if (VC_FSDA_ARRAY[j_VC_FSDA].name==Rx_IECU[j_RX].name || VC_RADAR_ARRAY[j_VC_RADAR].name==Rx_IECU[j_RX].name)
			{
				a++;
			}
		}
		
		if (a == 0)
		{
			str_CtApCOM_D_h += "extern Dt_RECORD_" + Rx_IECU[j_RX].name + " Var_CtApCom_" + "PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + ";\n";
			str_CtApCOM_D_c += "Dt_RECORD_" + Rx_IECU[j_RX].name + " Var_CtApCom_" + "PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + ";\n";

			str_CtApCOM_c += "    if(RComRx_cnt%" + Rx_IECU[j_RX].cycle + "==0)\n";
			str_CtApCOM_c += "    {\n";
			for (int i_Signal_RX = 0; i_Signal_RX < Rx_IECU[j_RX].Signal.size(); i_Signal_RX++)
			{
				int length = atoi(Rx_IECU[j_RX].Signal[i_Signal_RX].length.c_str());
				string factor = Rx_IECU[j_RX].Signal[i_Signal_RX].factor.c_str();
				string offest = Rx_IECU[j_RX].Signal[i_Signal_RX].offset.c_str();
				string ValueType = Rx_IECU[j_RX].Signal[i_Signal_RX].valuetype.c_str();

				string Var_DataType;

				if (length < 33)
				{
					if (ValueType == "-")
					{
						if (0 < length && length <= 8)
						{
							Var_DataType = "Var_S8";
						}
						else if (8 < length && length <= 17)
						{
							Var_DataType = "Var_S16";
						}
						else
						{
							Var_DataType = "Var_S32";
						}
					}
					else if (ValueType == "+")
					{
						if (0 < length && length <= 8)
						{
							Var_DataType = "Var_U8";
						}
						else if (8 < length && length <= 17)
						{
							Var_DataType = "Var_U16";
						}
						else
						{
							Var_DataType = "Var_U32";
						}
					}

					str_CtApCOM_c += "        (void)Rte_Read_DPpBusIn_" + Rx_IECU[j_RX].Signal[i_Signal_RX].name + "(&(" + Var_DataType + "));\n";
					str_CtApCOM_c += "        Var_CtApCom_PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + "." + Rx_IECU[j_RX].Signal[i_Signal_RX].name + " = " + Var_DataType + ";\n";
					str_CtApCOM_c += "        Var_CtApCom_PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + "." + Rx_IECU[j_RX].Signal[i_Signal_RX].name + " = (" + factor + ")*Var_CtApCom_PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + "." + Rx_IECU[j_RX].Signal[i_Signal_RX].name + "+(" + offest + ");\n\n";
				}
				else
				{
					Var_DataType = "Var_CtApCom_PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + "." + Rx_IECU[j_RX].Signal[i_Signal_RX].name;
					str_CtApCOM_c += "        (void)Rte_Read_DPpBusIn_" + Rx_IECU[j_RX].Signal[i_Signal_RX].name + "(&(" + Var_DataType + "));\n";
					
				}
			}

			str_CtApCOM_c += "        (void)Rte_Write_PpCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + "(&Var_CtApCom_PiCom_" + Rx_IECU[j_RX].name + "_" + Rx_IECU[j_RX].cycle + "ms_De" + Rx_IECU[j_RX].name + ");\n";
			str_CtApCOM_c += "    }\n";
		}
	}

	
	/*************************              ARAAY单独加               **************************/

	/*------------------                       FSDA                         -------------------*/
	i_Find_FSDA_Pi_Start = str_CtApCOM.find(PiName_FSDA_Position, i_Find_FSDA_Pi_Start);
	i_Find_FSDA_ARRAY_Start = str_CtApCOM.find(ARRAY_FSDA_Position, i_Find_FSDA_ARRAY_Start);
	i_Find_DeFSDA_Start = str_CtApCOM.find(DeFSDA_Position, i_Find_DeFSDA_Start);
	i_Find_Dt_RECORD_FSDA_Start = str_CtApCOM.find(Dt_RECORD_FSDA_Position, i_Find_Dt_RECORD_FSDA_Start);

	
	for (int i_FSDA_Pi = i_Find_FSDA_Pi_Start; i_FSDA_Pi < str_CtApCOM.size(); i_FSDA_Pi++)
	{
		if (str_CtApCOM[i_FSDA_Pi] == '>'&& str_CtApCOM[i_FSDA_Pi+1] == '\n')
		{
			i_Find_FSDA_Pi_End = i_FSDA_Pi+1;
			break;
		}
	}
	
	for (int i_FSDA_Array = i_Find_FSDA_ARRAY_Start; i_FSDA_Array < str_CtApCOM.size();i_FSDA_Array++)
	{
		if (str_CtApCOM[i_FSDA_Array]=='\n')
		{
			i_Find_FSDA_ARRAY_End = i_FSDA_Array;
			break;		
		}
	}
	
	for (int i_FSDA_De = i_Find_DeFSDA_Start; i_FSDA_De< str_CtApCOM.size(); i_FSDA_De++)
	{
		if (str_CtApCOM[i_FSDA_De] == '\n')
		{
			i_Find_DeFSDA_End = i_FSDA_De;
			break;
		}
	}
	
	PiName_FSDA = str_CtApCOM.substr(i_Find_FSDA_Pi_Start + 12, i_Find_FSDA_Pi_End - i_Find_FSDA_Pi_Start - 25);
	ArrayName_FSDA = str_CtApCOM.substr(i_Find_FSDA_ARRAY_Start, i_Find_FSDA_ARRAY_End - i_Find_FSDA_ARRAY_Start - 12);
	DeName_FSDA = str_CtApCOM.substr(i_Find_DeFSDA_Start + 12, i_Find_DeFSDA_End - i_Find_DeFSDA_Start - 25);

	j_FSDA = i_Find_Dt_RECORD_FSDA_Start;
	i_Find_FSDA_SHORTNAME_END = str_CtApCOM.find(IMPLEMENTATION_DATA_TYPE, j_FSDA);

	
	while (j_FSDA < i_Find_FSDA_SHORTNAME_END)
	{
		if ((j_FSDA = str_CtApCOM.find(SHORT_NAME_FSDA, j_FSDA)) != string::npos)
		{
			for (int j_FSDA_END = j_FSDA; j_FSDA_END < i_Find_FSDA_SHORTNAME_END; j_FSDA_END++)
			{
				if (str_CtApCOM[j_FSDA_END] == '\n')
				{
					ArraySignalName_FSDA = str_CtApCOM.substr(j_FSDA + SHORT_NAME_FSDA.length(), j_FSDA_END - j_FSDA - 25);
					VC_FSDA_ARRAY_SignalName.push_back(ArraySignalName_FSDA);
					break;
				}
			}
			j_FSDA++;
		}
	}
// 	for (int i = 0; i < VC_FSDA_ARRAY_SignalName.size();i++)
// 	{
// 		printf("%s\n", VC_FSDA_ARRAY_SignalName[i].c_str());
// 	}
// 	printf("%d\n", VC_FSDA_ARRAY_SignalName.size());

	str_CtApCOM_D_h += "extern " + ArrayName_FSDA + " Var_CtApCom_" + PiName_FSDA  + "_" + DeName_FSDA + ";\n";
	str_CtApCOM_D_c += ArrayName_FSDA + " Var_CtApCom_" + PiName_FSDA + "_" + DeName_FSDA + ";\n";

	str_CtApCOM_c += "    if(RComRx_cnt%" + VC_FSDA_ARRAY[0].cycle + "==0)\n";
	str_CtApCOM_c += "    {\n";
	
	for (int i_Message_FSDA = 0; i_Message_FSDA < VC_FSDA_ARRAY.size(); i_Message_FSDA++)
	{
		char Ch_i_Message_FSDA[3];
		_itoa(i_Message_FSDA, Ch_i_Message_FSDA, 10);
		
		for (int i_Signal_FSDA = 0; i_Signal_FSDA < VC_FSDA_ARRAY[i_Message_FSDA].Signal.size();i_Signal_FSDA++)
		{
			int length_FSDA = atoi(VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].length.c_str());
			string factor_FSDA = VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].factor.c_str();
			string offest_FSDA = VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].offset.c_str();
			string ValueType_FSDA = VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].valuetype.c_str();
			string Var_DataType_FSDA;

			if (length_FSDA < 33)
			{
				if (ValueType_FSDA == "-")
				{
					if (0 < length_FSDA && length_FSDA <= 8)
					{
						Var_DataType_FSDA = "Var_S8";
					}
					else if (8 < length_FSDA && length_FSDA <= 16)
					{
						Var_DataType_FSDA = "Var_S16";
					}
					else
					{
						Var_DataType_FSDA = "Var_S32";
					}
				}
				else if (ValueType_FSDA == "+")
				{
					if (0 < length_FSDA && length_FSDA <= 8)
					{
						Var_DataType_FSDA = "Var_U8";
					}
					else if (8 < length_FSDA && length_FSDA <= 16)
					{
						Var_DataType_FSDA = "Var_U16";
					}
					else
					{
						Var_DataType_FSDA = "Var_U32";
					}
				}
			}
			else
			{
				Var_DataType_FSDA = "Var_U64";
			}
			
			for (int j_ArraySignal_FSDA = 0; j_ArraySignal_FSDA < VC_FSDA_ARRAY_SignalName.size(); j_ArraySignal_FSDA++)
			{
				if (strstr(VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].name.c_str(), VC_FSDA_ARRAY_SignalName[j_ArraySignal_FSDA].c_str()))
				{
					str_CtApCOM_c += "        (void)Rte_Read_DPpBusIn_" + VC_FSDA_ARRAY[i_Message_FSDA].Signal[i_Signal_FSDA].name + "(&(" + Var_DataType_FSDA + "));\n";

					str_CtApCOM_c += "        Var_CtApCom_" + PiName_FSDA + "_" + DeName_FSDA + "[" + Ch_i_Message_FSDA + "]" + "." + VC_FSDA_ARRAY_SignalName[j_ArraySignal_FSDA] + " = " + Var_DataType_FSDA + ";\n";
				
					str_CtApCOM_c += "        Var_CtApCom_" + PiName_FSDA + "_" + DeName_FSDA + "[" + Ch_i_Message_FSDA + "]" + "." + VC_FSDA_ARRAY_SignalName[j_ArraySignal_FSDA] + " = (" + factor_FSDA + ")*Var_CtApCom_" + PiName_FSDA + "_" + DeName_FSDA + "[" + Ch_i_Message_FSDA + "]" + "." + VC_FSDA_ARRAY_SignalName[j_ArraySignal_FSDA] + "+(" + offest_FSDA + ");\n\n";
				}
			}
		}
	}
	
	str_CtApCOM_c += "        (void)Rte_Write_Pp"+ Comp_COM +"_" + FSDA_DBC + "_" + VC_FSDA_ARRAY[0].cycle + "ms_" + DeName_FSDA + "(Var_CtApCom_" + PiName_FSDA + "_" + DeName_FSDA + ");\n";
	str_CtApCOM_c += "    }\n";
	/*------------------------------------------------------------------------------------------*/

	
	
	/*------------------                       RADAR                         -------------------*/

	i_Find_RADAR_Pi_Start = str_CtApCOM.find(PiName_RADAR_Position, i_Find_RADAR_Pi_Start);
	i_Find_RADAR_ARRAY_Start = str_CtApCOM.find(ARRAY_RADAR_Position, i_Find_RADAR_ARRAY_Start);
	i_Find_DeRADAR_Start = str_CtApCOM.find(DeRADAR_Position, i_Find_DeRADAR_Start);
	i_Find_Dt_RECORD_RADAR_Start = str_CtApCOM.find(Dt_RECORD_RADAR_Position, i_Find_Dt_RECORD_RADAR_Start);


	for (int i_RADAR_Pi = i_Find_RADAR_Pi_Start; i_RADAR_Pi < str_CtApCOM.size(); i_RADAR_Pi++)
	{
		if (str_CtApCOM[i_RADAR_Pi] == '\n')
		{
			i_Find_RADAR_Pi_End = i_RADAR_Pi;
			break;
		}
	}

	for (int i_RADAR_Array = i_Find_RADAR_ARRAY_Start; i_RADAR_Array < str_CtApCOM.size(); i_RADAR_Array++)
	{
		if (str_CtApCOM[i_RADAR_Array] == '\n')
		{
			i_Find_RADAR_ARRAY_End = i_RADAR_Array;
			break;
		}
	}
	
	for (int i_RADAR_De = i_Find_DeRADAR_Start;; i_RADAR_De++)
	{
		if (str_CtApCOM[i_RADAR_De] == '\n')
		{
			i_Find_DeRADAR_End = i_RADAR_De;
			break;
		}
	}
	
	PiName_RADAR = str_CtApCOM.substr(i_Find_RADAR_Pi_Start + 12, i_Find_RADAR_Pi_End - i_Find_RADAR_Pi_Start - 25);
	ArrayName_RADAR = str_CtApCOM.substr(i_Find_RADAR_ARRAY_Start, i_Find_RADAR_ARRAY_End - i_Find_RADAR_ARRAY_Start - 12);
	DeName_RADAR = str_CtApCOM.substr(i_Find_DeRADAR_Start + 12, i_Find_DeRADAR_End - i_Find_DeRADAR_Start - 25);

	j_RADAR = i_Find_Dt_RECORD_RADAR_Start;
	i_Find_RADAR_SHORTNAME_END = str_CtApCOM.find(IMPLEMENTATION_DATA_TYPE, j_RADAR);

	while (j_RADAR < i_Find_RADAR_SHORTNAME_END)
	{
		if ((j_RADAR = str_CtApCOM.find(SHORT_NAME_RADAR, j_RADAR)) != string::npos)
		{
			for (int j_RADAR_END = j_RADAR; j_RADAR_END < i_Find_RADAR_SHORTNAME_END; j_RADAR_END++)
			{
				if (str_CtApCOM[j_RADAR_END] == '\n')
				{
					ArraySignalName_RADAR = str_CtApCOM.substr(j_RADAR + SHORT_NAME_RADAR.length(), j_RADAR_END - j_RADAR - 25);
					VC_RADAR_ARRAY_SignalName.push_back(ArraySignalName_RADAR);
					break;
				}
			}
			j_RADAR++;
		}
	}

	str_CtApCOM_D_h += "extern " + ArrayName_RADAR + " Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + ";\n";
	str_CtApCOM_D_c += ArrayName_RADAR + " Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + ";\n";

	str_CtApCOM_c += "    if(RComRx_cnt%" + VC_RADAR_ARRAY[0].cycle + "==0)\n";
	str_CtApCOM_c += "    {\n";

	for (int i_Message_RADAR = 0; i_Message_RADAR < VC_RADAR_ARRAY.size(); i_Message_RADAR++)
	{
		char Ch_i_Message_RADAR[3];
		_itoa(i_Message_RADAR, Ch_i_Message_RADAR, 10);

		for (int i_Signal_RADAR = 0; i_Signal_RADAR < VC_RADAR_ARRAY[i_Message_RADAR].Signal.size(); i_Signal_RADAR++)
		{
			int length_RADAR = atoi(VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].length.c_str());
			string factor_RADAR = VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].factor.c_str();
			string offest_RADAR = VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].offset.c_str();
			string ValueType_RADAR = VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].valuetype.c_str();
			string Var_DataType_RADAR;

			if (length_RADAR < 33)
			{
				if (ValueType_RADAR == "-")
				{
					if (0 < length_RADAR && length_RADAR <= 8)
					{
						Var_DataType_RADAR = "Var_S8";
					}
					else if (8 < length_RADAR && length_RADAR <= 17)
					{
						Var_DataType_RADAR = "Var_S16";
					}
					else
					{
						Var_DataType_RADAR = "Var_S32";
					}
				}
				else if (ValueType_RADAR == "+")
				{
					if (0 < length_RADAR && length_RADAR <= 8)
					{
						Var_DataType_RADAR = "Var_U8";
					}
					else if (8 < length_RADAR && length_RADAR <= 17)
					{
						Var_DataType_RADAR = "Var_U16";
					}
					else
					{
						Var_DataType_RADAR = "Var_U32";
					}
				}
			}
			else
			{
				Var_DataType_RADAR = "Var_U64";
			}

			for (int j_ArraySignal_RADAR = 0; j_ArraySignal_RADAR < VC_RADAR_ARRAY_SignalName.size(); j_ArraySignal_RADAR++)
			{
// 				int RADAR_ArraySignal_Position = 0;
// 
// 				RADAR_ArraySignal_Position = VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR].find(RADAR_DBC, RADAR_ArraySignal_Position);
// 				ArraySignal_CutOff_RADAR = VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR].substr(RADAR_ArraySignal_Position + RADAR_DBC.length(), VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR].length() - RADAR_ArraySignal_Position - RADAR_DBC.length());

				char *ret = strstr((char*)VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].name.c_str(), (char*)VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR].c_str());
				if (ret != NULL)
				{
					str_CtApCOM_c += "        (void)Rte_Read_DPpBusIn_" + VC_RADAR_ARRAY[i_Message_RADAR].Signal[i_Signal_RADAR].name + "(&(" + Var_DataType_RADAR + "));\n";
					str_CtApCOM_c += "        Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + "[" + Ch_i_Message_RADAR + "]" + "." + VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR] + " = " + Var_DataType_RADAR + ";\n";
					str_CtApCOM_c += "        Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + "[" + Ch_i_Message_RADAR + "]" + "." + VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR] + " = (" + factor_RADAR + ")*Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + "[" + Ch_i_Message_RADAR + "]" + "." + VC_RADAR_ARRAY_SignalName[j_ArraySignal_RADAR] + "+(" + offest_RADAR + ");\n\n";
				}
			}
		}
	}

	str_CtApCOM_c += "        (void)Rte_Write_Pp" + Comp_COM + "_" + RADAR_DBC + "_" + VC_RADAR_ARRAY[0].cycle + "ms_" + DeName_RADAR + "(Var_CtApCom_" + PiName_RADAR + "_" + DeName_RADAR + ");\n";
	str_CtApCOM_c += "    }\n";

	

	/*------------------------------------------------------------------------------------------*/

	str_CtApCOM_c += "}\n\n\n\n";


/*****************************         RComTX_10ms         *******************************/
	str_CtApCOM_c += "FUNC(void, CtApCom_CODE) RComTX_10ms(void)\n\
{\n\
    uint8 Var_U8;\n\
	uint16 Var_U16;\n\
	uint32 Var_U32;\n\
	uint64 Var_U64;\n\
	sint8 Var_S8;\n\
	sint16 Var_S16;\n\
	sint32 Var_S32;\n\
	sint64 Var_S64;\n\
	float32 Var_F32;\n\
	float64 Var_F64;\n\
	static uint16 RComTx_cnt = 0;\n\
	if (RComTx_cnt == 3000)\n\
	{\n\
		RComTx_cnt = 10;\n\
	}\n\
	else\n\
	{\n\
		RComTx_cnt += 10;\n\
	}\n\n";

	for (int i_Tx = 0; i_Tx < Tx_IECU.size(); i_Tx++)
	{
		str_CtApCOM_D_h += "extern Dt_RECORD_" + Tx_IECU[i_Tx].name + " Var_CtApCom_" + "PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + ";\n";
		str_CtApCOM_D_c += "Dt_RECORD_" + Tx_IECU[i_Tx].name + " Var_CtApCom_" + "PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + ";\n";
		
		str_CtApCOM_c += "    (void)Rte_Read_PpVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + "(&Var_CtApCom_PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + ");\n";
		str_CtApCOM_c += "    if(RComTx_cnt%" + Tx_IECU[i_Tx].cycle + "==0)\n";
		str_CtApCOM_c += "    {\n";

		for (int i_Signal_Tx = 0; i_Signal_Tx < Tx_IECU[i_Tx].Signal.size(); i_Signal_Tx++)
		{
			int length = atoi(Tx_IECU[i_Tx].Signal[i_Signal_Tx].length.c_str());
			string factor = Tx_IECU[i_Tx].Signal[i_Signal_Tx].factor.c_str();
			string offest = Tx_IECU[i_Tx].Signal[i_Signal_Tx].offset.c_str();
			string ValueType = Tx_IECU[i_Tx].Signal[i_Signal_Tx].valuetype.c_str();

			string Var_DataType;

			if (length < 33)
			{
				if (ValueType == "-")
				{
					if (0 < length && length <=8)
					{
						Var_DataType = "Var_S8";
					}
					else if (8 < length && length <=17)
					{
						Var_DataType = "Var_S16";
					}
					else
					{
						Var_DataType = "Var_S32";
					}
				}
				else if (ValueType == "+")
				{
					if (0 < length && length <=8)
					{
						Var_DataType = "Var_U8";
					}
					else if (8 < length && length <=17)
					{
						Var_DataType = "Var_U16";
					}
					else
					{
						Var_DataType = "Var_U32";
					}
				}

				str_CtApCOM_c += "        Var_CtApCom_PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + "." + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + "-=" + offest + ";\n";
				str_CtApCOM_c += "        Var_CtApCom_PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + "." + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + "/=" + factor + ";\n";
				str_CtApCOM_c += "        " + Var_DataType + " = Var_CtApCom_PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + "." + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + ";\n";
				str_CtApCOM_c += "        (void)Rte_Write_DPpBusOut_" + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + "(" + Var_DataType + ");\n\n";

			}
			else
			{
				Var_DataType = "Var_U64";

				str_CtApCOM_c += "        (void)Rte_Write_DPpBusOut_" + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + "(" + "Var_CtApCom_PiVMS_" + Tx_IECU[i_Tx].name + "_" + Tx_IECU[i_Tx].cycle + "ms_De" + Tx_IECU[i_Tx].name + "." + Tx_IECU[i_Tx].Signal[i_Signal_Tx].name + "); \n\n";
			}
		}
		str_CtApCOM_c += "    }\n";

	}

	str_CtApCOM_c += "}\n";
	str_CtApCOM_c += "#define CtApCom_STOP_SEC_CODE\n\
#include \"CtApCom_MemMap.h\"\n\n";


	fprintf(fp_CtApCOM_D_h, "%s", str_CtApCOM_D_h.c_str());
	fclose(fp_CtApCOM_D_h);

	fprintf(fp_CtApCOM_D_c, "%s", str_CtApCOM_D_c.c_str());
	fclose(fp_CtApCOM_D_c);

	fprintf(fp_CtApCOM_c, "%s", str_CtApCOM_c.c_str());
	fclose(fp_CtApCOM_c);

	printf("Successful!!\n");
}

