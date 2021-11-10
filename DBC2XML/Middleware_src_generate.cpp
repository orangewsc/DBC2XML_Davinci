#include "include.h"

/*------------------                     XML读取                     -------------------*/
void Aurix_Rcar_Middleware_XML_Read(string &Aurix_Middleware_str, string &Rcar_Middleware_str)
{
	char buf[500];

	FILE *fp_Middleware_Aurix_XML = fopen("E:/Work/DaVinci/Myself/DBC2XML/03_file/CtApMiddleware_Aurix_swc_One.arxml","r");
	//FILE *fp_Middleware_Rcar_XML = fopen("E:/Work/DaVinci/Myself/DBC2XML/03_file/CtApMiddleware_Rcar_swc_One.arxml", "r");
	//FILE *fp_Middleware_Aurix_XML_Pad = fopen("E:/Work/DaVinci/Myself/DBC2XML/02_Src/02_Middleware/CtApMiddleware_Rcar_swc_One_Padding.arxml", "w+");
	//FILE *fp_Middleware_Rcar_XML_Pad = fopen("E:/Work/DaVinci/Myself/DBC2XML/02_Src/02_Middleware/XMLCtApCom_swc.arxml", "w+");

	if (fp_Middleware_Aurix_XML == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("CtApMiddleware_Aurix_XML文件读取失败!\n");
	}


// 	if (fp_Middleware_Rcar_XML == NULL)
// 	{
// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
// 		printf("CtApMiddleware_Rcar文件读取失败!\n");
// 	}
// 	if (fp_Middleware_Aurix_XML_Pad == NULL)
// 	{
// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
// 		printf("CtApMiddleware_Aurix_XML_Pad文件创建失败!\n");
// 	}
// 	if (fp_Middleware_Rcar_XML_Pad == NULL)
// 	{
// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
// 		printf("Middleware_Rcar_XML_Pad文件创建失败!\n");
// 	}
// 
	while (!(feof(fp_Middleware_Aurix_XML)))
	{
		fgets(buf, sizeof(buf), fp_Middleware_Aurix_XML);
		Aurix_Middleware_str.append(buf);
	}
// 
// 	while (!(feof(fp_Middleware_Rcar_XML)))
// 	{
// 		fgets(buf, sizeof(buf), fp_Middleware_Rcar_XML);
// 		Rcar_Middleware_str.append(buf);
// 	}
// 
 	fclose(fp_Middleware_Aurix_XML);
// 	fclose(fp_Middleware_Rcar_XML);


}

/*------------------                    所有Port口                   -------------------*/
void XML_Extrat_PortAll(string &XML, vector<PI_PORT> &Port_ALL)
{
	static string Lab_Ports_Start = "<PORTS>";
	static string Lab_Ports_End = "</PORTS>";
	static string Lab_ShortName_Start = "<SHORT-NAME>";
	static string Lab_ShortName_End = "</SHORT-NAME>";
	static string Lab_AR_PACKGE_Start = "<AR-PACKAGE>";
	static string Lab_AR_PACKGE_End = "</AR-PACKAGE>";
	static string Lab_PortInterfaces = "<SHORT-NAME>PortInterfaces</SHORT-NAME>";
	static string Lab_PiName_UUID = "<SENDER-RECEIVER-INTERFACE UUID=";
	static string Lab_DeName_UUID = "<VARIABLE-DATA-PROTOTYPE UUID=";
	static string Lab_DataTypes_Dt_Flag = "<TYPE-TREF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_DataTypes_TREF = "</TYPE-TREF>";
	static string Lab_Dt_RECORD_Flag = "Dt_RECORD_";
	static string Lab_Dt_ARRAY_Flag = "Dt_ARRAY";
	static string Lab_C_RECORD_Flag = "C_RECORD_";
	static string Lab_C_ARRAY_Flag = "C_ARRAY_";
	static string Lab_PiName_SR = "</SENDER-RECEIVER-INTERFACE>";
	static string Lab_Dt_IMPLEMENTATION = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_IMPLEMENTATION_TREF = "</IMPLEMENTATION-DATA-TYPE-REF>";
	static string Lab_CONSTANT_Start = "<CONSTANT-REF DEST=\"CONSTANT-SPECIFICATION\">/Constants/";
	static string Lab_CONSTANT_REF = "</CONSTANT-REF>";
	static string Lab_VARIABLE_DATA_PROTOTYPE = "<DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/";
	static string Lab_DATA_ELEMENT_REF = "</DATA-ELEMENT-REF>";
	static string Lab_SUB_ELEMENTS_Start = "<SUB-ELEMENTS>";
	static string Lab_SUB_ELEMENTS_End = "</SUB-ELEMENTS>";
	static string Lab_ComponentTypes = "<SHORT-NAME>ComponentTypes</SHORT-NAME>";

	DE_PORT Stc_De_PORT;
	PI_PORT Stc_Pi_PORT;

	bool Flag_PiName = true;

	int Position_Ports_Start = 0,
		Position_Ports_End = 0,
		Position_PiName_UUID = 0,
		Position_PiName_SR = 0,
		Position_PiName_Start = 0,
		Position_PiName_End = 0,
		Position_DeName_Start = 0,
		Position_DeName_End = 0,
		Position_DataTypes_Start = 0,
		Position_DataTypes_End = 0,
		Position_Dt_RECORD_Name_Start = 0,
		Position_Dt_RECORD_Name_End = 0,
		Position_Dt_ARRAY_Name_Start = 0,
		Position_Dt_ARRAY_Name_End = 0,
		Position_PortInterfaces_Start = 0,
		Position_PortInterfaces_End = 0,
		Position_C_RECORD_Name_Start = 0,
		Position_C_ARRAY_Name_Start = 0,
		Position_PI_ARRAY_Name = 0,
		Position_SUB_ELEMENTS_Start = 0,
		Position_SUB_ELEMENTS_End = 0,
		Position_ComponentTypes = 0,
		Position_VARIABLE_DATA_PROTOTYPE = 0,
		Position_CONSTANT = 0,
		Positon_CONSTANT_REF = 0,
		Position_C_ARRAY_Start = 0,
		Position_C_RECORD_Start = 0,
		Position_C_RECORD_End = 0;

	Position_PortInterfaces_Start = XML.find(Lab_PortInterfaces, 0);
	Position_PortInterfaces_End = XML.find(Lab_AR_PACKGE_End, Position_PortInterfaces_Start);

	for (int i_Pi_Find = 0; i_Pi_Find < Position_PortInterfaces_End;i_Pi_Find++)  //第一步从PiName开始找
	{
		
		if ((Position_PiName_UUID = XML.find(Lab_PiName_UUID, i_Pi_Find)) < Position_PortInterfaces_End && (Position_PiName_UUID = XML.find(Lab_PiName_UUID, i_Pi_Find)) != string::npos)
		{
			i_Pi_Find = Position_PiName_UUID + 36;

			Position_PiName_SR = XML.find(Lab_PiName_SR, Position_PiName_UUID);
			Position_PiName_Start = XML.find(Lab_ShortName_Start, Position_PiName_UUID);
			Position_PiName_End = XML.find(Lab_ShortName_End, Position_PiName_Start);
			string PiName = XML.substr(Position_PiName_Start + Lab_ShortName_Start.length(), Position_PiName_End - Position_PiName_Start - Lab_ShortName_Start.length());
			
			Stc_Pi_PORT.Pi_NAME = PiName;

			string PiName_tmp = PiName;
			string PpName = PiName_tmp.replace(1, 1, "p");
			Stc_Pi_PORT.Pp_NAME = PpName;

			for (int i_De_Find = Position_PiName_End; i_De_Find < Position_PiName_SR; i_De_Find++)
			{
				if (XML.find(Lab_ShortName_Start, i_De_Find)<Position_PiName_SR)
				{
					Position_DeName_Start = XML.find(Lab_ShortName_Start, i_De_Find);
					Position_DeName_End = XML.find(Lab_ShortName_End, Position_DeName_Start);
					string DeName = XML.substr(Position_DeName_Start + Lab_ShortName_Start.length(), Position_DeName_End - Position_DeName_Start - Lab_ShortName_Start.length());
					Stc_De_PORT.De_NAME = DeName;

					/*------------------                  Dt_RECORD/ARRAY                    -------------------*/
					Position_DataTypes_Start = XML.find(Lab_DataTypes_Dt_Flag, Position_DeName_End);
					Position_DataTypes_End = XML.find(Lab_DataTypes_TREF, Position_DataTypes_Start);

					if ((Position_Dt_RECORD_Name_Start = XML.find(Lab_Dt_RECORD_Flag, Position_DataTypes_Start)) && (Position_Dt_RECORD_Name_Start< Position_DataTypes_End))
					{
						string Dt_RECORD_Name = XML.substr(Position_Dt_RECORD_Name_Start, Position_DataTypes_End - Position_Dt_RECORD_Name_Start);
						Stc_De_PORT.Dt_RECORD_NAME = Dt_RECORD_Name;
					}
					else if ((Position_Dt_ARRAY_Name_Start = XML.find(Lab_Dt_ARRAY_Flag, Position_DataTypes_Start)) && (Position_Dt_ARRAY_Name_Start < Position_DataTypes_End))
					{
						
						string Dt_ARRAY_Name = XML.substr(Position_Dt_ARRAY_Name_Start, Position_DataTypes_End - Position_Dt_ARRAY_Name_Start);
						Stc_De_PORT.Dt_ARRAY_NAME = Dt_ARRAY_Name;

						Position_PI_ARRAY_Name = XML.find(Lab_ShortName_Start + Dt_ARRAY_Name + Lab_ShortName_End, 0);
						Position_SUB_ELEMENTS_Start = XML.find(Lab_SUB_ELEMENTS_Start, Position_PI_ARRAY_Name);
						Position_SUB_ELEMENTS_End = XML.find(Lab_SUB_ELEMENTS_End, Position_SUB_ELEMENTS_Start);

						if ((Position_Dt_RECORD_Name_Start = XML.find(Lab_Dt_RECORD_Flag, Position_PI_ARRAY_Name))<Position_SUB_ELEMENTS_End)
						{
							
							Position_Dt_RECORD_Name_End = XML.find(Lab_IMPLEMENTATION_TREF, Position_Dt_RECORD_Name_Start);
							string Dt_RECORD_Name = XML.substr(Position_Dt_RECORD_Name_Start, Position_Dt_RECORD_Name_End - Position_Dt_RECORD_Name_Start);
							Stc_De_PORT.Dt_RECORD_NAME = Dt_RECORD_Name;
							
						}
						
						
					}
					/*-------------------------------------------------------------------------------- ----------*/

					/*------------------                  C_RECORD/C_ARRAY                    -------------------*/
					Position_ComponentTypes = XML.find(Lab_ComponentTypes, 0);
					Position_VARIABLE_DATA_PROTOTYPE = XML.find(Lab_VARIABLE_DATA_PROTOTYPE + PiName + "/" + DeName + Lab_DATA_ELEMENT_REF, Position_ComponentTypes);
					Position_CONSTANT = XML.find(Lab_CONSTANT_Start, Position_VARIABLE_DATA_PROTOTYPE);
					Positon_CONSTANT_REF = XML.find(Lab_CONSTANT_REF, Position_CONSTANT);
					
					if ((Position_C_RECORD_Name_Start = XML.find(Lab_C_RECORD_Flag, Position_CONSTANT)) < Positon_CONSTANT_REF)
					{
						
						string C_RECORD_Name = XML.substr(Position_C_RECORD_Name_Start, Positon_CONSTANT_REF - Position_C_RECORD_Name_Start);
						Stc_De_PORT.C_RECORD_NAME = C_RECORD_Name;
						
					}
					if ((Position_C_ARRAY_Name_Start = XML.find(Lab_C_ARRAY_Flag, Position_CONSTANT)) < Positon_CONSTANT_REF)
					 {
						
						string  C_ARRAY_Name = XML.substr(Position_C_ARRAY_Name_Start, Positon_CONSTANT_REF - Position_C_ARRAY_Name_Start);
						Stc_De_PORT.C_ARRAY_NAME = C_ARRAY_Name;

						
						Position_C_ARRAY_Start = XML.find(Lab_ShortName_Start + C_ARRAY_Name + Lab_ShortName_End, 0);
						Position_C_RECORD_Start = XML.find(Lab_C_RECORD_Flag, Position_C_ARRAY_Start);
						Position_C_RECORD_End = XML.find(Lab_CONSTANT_REF, Position_C_RECORD_Start);
						

						string C_RECORD_Name = XML.substr(Position_C_RECORD_Start, Position_C_RECORD_End - Position_C_RECORD_Start);
						
						Stc_De_PORT.C_RECORD_NAME = C_RECORD_Name;
						
					 }
					/*------------------------------------------------------------------------------------------*/
					
					Stc_Pi_PORT.De_PORT.push_back(Stc_De_PORT);

					Stc_De_PORT.De_NAME.clear();
					Stc_De_PORT.Dt_RECORD_NAME.clear();
					Stc_De_PORT.Dt_ARRAY_NAME.clear();
					Stc_De_PORT.C_RECORD_NAME.clear();
					Stc_De_PORT.C_ARRAY_NAME.clear();
					
					i_De_Find = Position_DeName_End;
				}
				else
				{
					break;
				}
			}

			Port_ALL.push_back(Stc_Pi_PORT);
			Stc_Pi_PORT.Pi_NAME.clear();
			Stc_Pi_PORT.Pp_NAME.clear();
			Stc_Pi_PORT.De_PORT.clear();
		}
		else
		{
			break;
		}
	} 

// 	for (int i = 0; i < Port_ALL.size();i++)
// 	{
// 		printf("******************** Port口%d ********************\n",i+1);
// 		printf("PiName：%s\n", Port_ALL[i].Pi_NAME.c_str());
// 		printf("PpName：%s\n", Port_ALL[i].Pp_NAME.c_str());
// 		for (int j = 0; j < Port_ALL[i].De_PORT.size();j++)
// 		{
// 			printf("------------ De口%d -----------\n", j + 1);
// 			printf("DeName：%s\n", Port_ALL[i].De_PORT[j].De_NAME.c_str());
// 			printf("Dt_RECORD_NAME：%s\n", Port_ALL[i].De_PORT[j].Dt_RECORD_NAME.c_str());
// 			printf("Dt_ARRAY_NAME：%s\n", Port_ALL[i].De_PORT[j].Dt_ARRAY_NAME.c_str());
// 			printf("C_RECORD_NAME：%s\n", Port_ALL[i].De_PORT[j].C_RECORD_NAME.c_str());
// 			printf("C_ARRAY_NAME：%s\n", Port_ALL[i].De_PORT[j].C_ARRAY_NAME.c_str());
// 		}
// 	}
	
	//printf("Port口总数：%d\n", Port_ALL.size());


	

}

/*------------------              单个De下的第一层属性               -------------------*/
void Find_Recoder_Signal(string &XML, string Reference_Name, vector<DT_RECODER> &Recoder_Signal_VC)
{
	static string Lab_ShortName_Start = "<SHORT-NAME>";
	static string Lab_ShortName_End = "</SHORT-NAME>";
	static string Lab_SubElem_Start = "<SUB-ELEMENTS>";
	static string Lab_SubElem_End = "</SUB-ELEMENTS>";
	static string Lab_DATA_TYPE = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_DATA_TYPE_IMPLEMENT = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
	static string Lab_DATA_TYPE_REF = "</IMPLEMENTATION-DATA-TYPE-REF>";
	static string Lab_SW_DATA_DEF = "</SW-DATA-DEF-PROPS>";
	static string Lab_Dt_RECORD = "Dt_RECORD";
	static string Lab_Dt_ARRAY = "Dt_ARRAY";
	static string Lab_ARRAY_SIZE_Start = "<ARRAY-SIZE>";
	static string Lab_ARRAY_SIZE_End = "</ARRAY-SIZE>";
	static string Lab_CATEGORY_Start = "<CATEGORY>";
	static string Lab_CATEGORY_End = "</CATEGORY>";
	static string Lab_ARRAY_Flag = "ARRAY";
	static string Lab_STRUCTURE_Flag = "STRUCTURE";


	RECODER_SIGNAL Recoder_Signal;
	DT_RECODER Dt_RECORD;
	

	Dt_RECORD.Dt_RECODER_NAME = Reference_Name;

	int Position_Reference_Name_Start = XML.find(Lab_ShortName_Start + Reference_Name + Lab_ShortName_End, 0);
	int Position_SubElem_End = XML.find(Lab_SubElem_End, Position_Reference_Name_Start);
	for (int i = Position_Reference_Name_Start + Reference_Name.length(); i < Position_SubElem_End; i++)
	{
		int Position_ShortName_Start = XML.find(Lab_ShortName_Start, i);
		int Position_ShortName_End = XML.find(Lab_ShortName_End, Position_ShortName_Start);
		int Position_SW_DATA_DEF = XML.find(Lab_SW_DATA_DEF, Position_ShortName_End);
		int Position_DATA_REF = 0;
		int Position_DATA_TYPE = 0;

		if ((Position_ShortName_Start != string::npos) && (Position_ShortName_Start < Position_SubElem_End))
		{

			string Signal_name = XML.substr(Position_ShortName_Start + Lab_ShortName_Start.length(), Position_ShortName_End - Position_ShortName_Start - Lab_ShortName_Start.length());
			Recoder_Signal.Signal_Name = Signal_name;
			

			if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE_IMPLEMENT, Position_ShortName_End))!= string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
			{
				int type_int = 0;
				Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
				string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE_IMPLEMENT.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE_IMPLEMENT.length());
				Recoder_Signal.type_str = Type;

				if (Type == "boolean" || Type == "uint8" || Type == "sint8")
				{
					type_int = 8;
				}
				else if (Type == "uint16" || Type == "sint16")
				{
					type_int = 16;
				}
				else if (Type == "uint32" || Type == "sint32" || Type == "float32")
				{
					type_int = 32;
				}
				else if (Type == "float64")
				{
					type_int = 64;
				}

				Recoder_Signal.type_int = type_int;
				Recoder_Signal.Array_Size = 0;
				Recoder_Signal.Flag_Type = 1;
			}
			else if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE, Position_ShortName_End)) != string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
			{
				Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
				if (XML.find(Lab_Dt_RECORD, Position_DATA_TYPE) < Position_SW_DATA_DEF)
				{
					string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE.length());
					Recoder_Signal.type_str = Type;
					Recoder_Signal.type_int = 0;
					Recoder_Signal.Array_Size = 0;
					Recoder_Signal.Flag_Type = 2;

				}
				else if (XML.find(Lab_Dt_ARRAY, Position_DATA_TYPE) < Position_SW_DATA_DEF)
				{
					string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE.length());
					Recoder_Signal.type_str = Type;
					Recoder_Signal.type_int = 0;
					Recoder_Signal.Array_Size = 0;
					Recoder_Signal.Flag_Type = 3;

					int Position_DT_ARRAY = XML.find(Lab_ShortName_Start + Type + Lab_ShortName_End, 0);
					int Position_DT_ARRAY_SubElem_Start = XML.find(Lab_SubElem_Start, Position_DT_ARRAY);
					int Position_DT_ARRAY_SubElem_End = XML.find(Lab_SubElem_End, Position_DT_ARRAY_SubElem_Start);
					int Position_ARRAY_SIZE_Start = XML.find(Lab_ARRAY_SIZE_Start, Position_DT_ARRAY_SubElem_Start);
					int Position_ARRAY_SIZE_End = XML.find(Lab_ARRAY_SIZE_End, Position_ARRAY_SIZE_Start);
					string ARRAY_SIZE_Str = XML.substr(Position_ARRAY_SIZE_Start + Lab_ARRAY_SIZE_Start.length(), Position_ARRAY_SIZE_End - Position_ARRAY_SIZE_Start - Lab_ARRAY_SIZE_Start.length());
					int ARRAY_SIZE_Int = atoi(ARRAY_SIZE_Str.c_str());
					Recoder_Signal.Array_Size = ARRAY_SIZE_Int;

					int Position_Dt_ARRAY_Type_Start = 0;
					int Position_Dt_ARRAY_Type_End = 0;

					if ((Position_Dt_ARRAY_Type_Start = XML.find(Lab_DATA_TYPE_IMPLEMENT, Position_DT_ARRAY_SubElem_Start)) < Position_DT_ARRAY_SubElem_End)
					{
						Position_Dt_ARRAY_Type_End = XML.find(Lab_DATA_TYPE_REF, Position_Dt_ARRAY_Type_Start);
						string ARRAY_Type = XML.substr(Position_Dt_ARRAY_Type_Start + Lab_DATA_TYPE_IMPLEMENT.length(), Position_Dt_ARRAY_Type_End - Position_Dt_ARRAY_Type_Start - Lab_DATA_TYPE_IMPLEMENT.length());
		
						if (ARRAY_Type == "boolean" || ARRAY_Type == "uint8" || ARRAY_Type == "sint8")
						{
							Recoder_Signal.type_int = 8;
						}
						else if (ARRAY_Type == "uint16" || ARRAY_Type == "sint16")
						{
							Recoder_Signal.type_int = 16;
						}
						else if (ARRAY_Type == "uint32" || ARRAY_Type == "sint32" || ARRAY_Type == "float32")
						{
							Recoder_Signal.type_int = 32;
						}
						else if (ARRAY_Type == "float64")
						{
							Recoder_Signal.type_int = 64;
						}
					}
				}
			}		
		
			Dt_RECORD.Recoder_Signal.push_back(Recoder_Signal);

			Recoder_Signal.Signal_Name.clear();
			Recoder_Signal.type_int = 0;
			Recoder_Signal.type_str.clear();
			Recoder_Signal.Array_Size = 0;
			Recoder_Signal.Flag_Type = 0;
		}

		i = Position_ShortName_End + Lab_ShortName_End.length();

	}
	Recoder_Signal_VC.push_back(Dt_RECORD);
}

/*------------------                 De的所有层属性                -------------------*/
void Find_Recoder_Layers(string &XML, bool &Flag_Loop, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All)
{
	static string Lab_ShortName_Start = "<SHORT-NAME>";
	static string Lab_ShortName_End = "</SHORT-NAME>";
	static string Lab_DATA_TYPE = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_DATA_TYPE_IMPLEMENT = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
	static string Lab_DATA_TYPE_REF = "</IMPLEMENTATION-DATA-TYPE-REF>";
	static string Lab_SW_DATA_DEF = "</SW-DATA-DEF-PROPS>";
	static string Lab_Dt_RECORD = "Dt_RECORD";
	static string Lab_Dt_ARRAY = "Dt_ARRAY";
	static string Lab_SubElem_Start = "<SUB-ELEMENTS>";
	static string Lab_SubElem_End = "</SUB-ELEMENTS>";
	static string Lab_ARRAY_SIZE_Start = "<ARRAY-SIZE>";
	static string Lab_ARRAY_SIZE_End = "</ARRAY-SIZE>";
	static string Lab_CATEGORY_Start = "<CATEGORY>";
	static string Lab_CATEGORY_End = "</CATEGORY>";
	static string Lab_ARRAY_Flag = "ARRAY";
	static string Lab_STRUCTURE_Flag = "STRUCTURE";

	vector<DT_RECODER> Recoder_Signal_VC;

	int Num_Loop = 0;
	
	for (int m = 0; m < Recoder_Signal_VC_All[Recoder_Signal_VC_All.size()-1].size(); m++)
	{
		for (int n = 0; n < Recoder_Signal_VC_All[Recoder_Signal_VC_All.size()-1][m].Recoder_Signal.size(); n++)
		{
			RECODER_SIGNAL Recoder_Signal;
			DT_RECODER Dt_RECORD;

			if (Recoder_Signal_VC_All[Recoder_Signal_VC_All.size()-1][m].Recoder_Signal[n].Flag_Type == 2)
			{
				Num_Loop++;
				string Data_Type_Reference_Name = Recoder_Signal_VC_All[Recoder_Signal_VC_All.size() - 1][m].Recoder_Signal[n].type_str;
				Dt_RECORD.Dt_RECODER_NAME = Data_Type_Reference_Name;

				int Position_Reference_Name_Start = XML.find(Lab_ShortName_Start + Data_Type_Reference_Name + Lab_ShortName_End, 0);
				int Position_SubElem_End = XML.find(Lab_SubElem_End, Position_Reference_Name_Start);

				for (int i = Position_Reference_Name_Start + Data_Type_Reference_Name.length(); i < Position_SubElem_End; i++)
				{
					int Position_ShortName_Start = XML.find(Lab_ShortName_Start, i);
					int Position_ShortName_End = XML.find(Lab_ShortName_End, Position_ShortName_Start);
					int Position_SW_DATA_DEF = XML.find(Lab_SW_DATA_DEF, Position_ShortName_End);
					int Position_DATA_REF = 0;
					int Position_DATA_TYPE = 0;

					if ((Position_ShortName_Start != string::npos) && (Position_ShortName_Start < Position_SubElem_End))
					{

						string Signal_name = XML.substr(Position_ShortName_Start + Lab_ShortName_Start.length(), Position_ShortName_End - Position_ShortName_Start - Lab_ShortName_Start.length());
						Recoder_Signal.Signal_Name = Signal_name;
						

						if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE_IMPLEMENT, Position_ShortName_End)) != string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
						{
							int type_int = 0;
							Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
							string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE_IMPLEMENT.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE_IMPLEMENT.length());
							Recoder_Signal.type_str = Type;

							if (Type == "boolean" || Type == "uint8" || Type == "sint8")
							{
								type_int = 8;
							}
							else if (Type == "uint16" || Type == "sint16")
							{
								type_int = 16;
							}
							else if (Type == "uint32" || Type == "sint32" || Type == "float32")
							{
								type_int = 32;
							}
							else if (Type == "float64")
							{
								type_int = 64;
							}

							Recoder_Signal.type_int = type_int;
							Recoder_Signal.Flag_Type = 1;
							Recoder_Signal.Array_Size = 0;
						}
						else if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE, Position_ShortName_End)) != string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
						{
							Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
							if (XML.find(Lab_Dt_RECORD, Position_DATA_TYPE) < Position_SW_DATA_DEF)
							{
								string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE.length());
								Recoder_Signal.type_str = Type;
								Recoder_Signal.Flag_Type = 2;
								Recoder_Signal.Array_Size = 0;

							}
							else if (XML.find(Lab_Dt_ARRAY, Position_DATA_TYPE) < Position_SW_DATA_DEF)
							{
								string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE.length());
								Recoder_Signal.type_str = Type;
								Recoder_Signal.Flag_Type = 3;
								

								int Position_DT_ARRAY = XML.find(Lab_ShortName_Start + Type + Lab_ShortName_End, 0);
								int Position_DT_ARRAY_SubElem_Start = XML.find(Lab_SubElem_Start, Position_DT_ARRAY);
								int Position_DT_ARRAY_SubElem_End = XML.find(Lab_SubElem_End, Position_DT_ARRAY_SubElem_Start);
								int Position_ARRAY_SIZE_Start = XML.find(Lab_ARRAY_SIZE_Start, Position_DT_ARRAY_SubElem_Start);
								int Position_ARRAY_SIZE_End = XML.find(Lab_ARRAY_SIZE_End, Position_ARRAY_SIZE_Start);
								string ARRAY_SIZE_Str = XML.substr(Position_ARRAY_SIZE_Start + Lab_ARRAY_SIZE_Start.length(), Position_ARRAY_SIZE_End - Position_ARRAY_SIZE_Start - Lab_ARRAY_SIZE_Start.length());
								int ARRAY_SIZE_Int = atoi(ARRAY_SIZE_Str.c_str());
								Recoder_Signal.Array_Size = ARRAY_SIZE_Int;

								static int Position_Dt_ARRAY_Type_Start = 0;
								static int Position_Dt_ARRAY_Type_End = 0;

								if ((Position_Dt_ARRAY_Type_Start = XML.find(Lab_DATA_TYPE_IMPLEMENT, Position_DT_ARRAY_SubElem_Start)) < Position_DT_ARRAY_SubElem_End)
								{
									Position_Dt_ARRAY_Type_End = XML.find(Lab_DATA_TYPE_REF, Position_Dt_ARRAY_Type_Start);

									string ARRAY_Type = XML.substr(Position_Dt_ARRAY_Type_Start + Lab_DATA_TYPE_IMPLEMENT.length(), Position_Dt_ARRAY_Type_End - Position_Dt_ARRAY_Type_Start - Lab_DATA_TYPE_IMPLEMENT.length());
									if (ARRAY_Type == "boolean" || ARRAY_Type == "uint8" || ARRAY_Type == "sint8")
									{
										Recoder_Signal.type_int = 8;
									}
									else if (ARRAY_Type == "uint16" || ARRAY_Type == "sint16")
									{
										Recoder_Signal.type_int = 16;
									}
									else if (ARRAY_Type == "uint32" || Type == "sint32" || ARRAY_Type == "float32")
									{
										Recoder_Signal.type_int = 32;
									}
									else if (ARRAY_Type == "float64")
									{
										Recoder_Signal.type_int = 64;
									}
								}
								else
								{
									Recoder_Signal.type_int = 0;
								}
							}
						}
					
						Dt_RECORD.Recoder_Signal.push_back(Recoder_Signal);

						Recoder_Signal.Signal_Name.clear();
						Recoder_Signal.type_int = 0;
						Recoder_Signal.type_str.clear();
						Recoder_Signal.Array_Size = 0;
						Recoder_Signal.Flag_Type = 0;
					}

					i = Position_ShortName_End + Lab_ShortName_End.length();

				}

				Recoder_Signal_VC.push_back(Dt_RECORD);
			}
			else if (Recoder_Signal_VC_All[Recoder_Signal_VC_All.size() - 1][m].Recoder_Signal[n].Flag_Type == 3 && Recoder_Signal_VC_All[Recoder_Signal_VC_All.size() - 1][m].Recoder_Signal[n].type_int == 0)
			{
				Num_Loop++;
				string Data_Type_Reference_Name = Recoder_Signal_VC_All[Recoder_Signal_VC_All.size() - 1][m].Recoder_Signal[n].type_str;
				Dt_RECORD.Dt_RECODER_NAME = Data_Type_Reference_Name;

				int Position_Reference_Name_Start = XML.find(Lab_ShortName_Start + Data_Type_Reference_Name + Lab_ShortName_End, 0);
				int Position_SubElem_End = XML.find(Lab_SubElem_End, Position_Reference_Name_Start);

				for (int i = Position_Reference_Name_Start + Data_Type_Reference_Name.length(); i < Position_SubElem_End; i++)
				{
					int Position_ShortName_Start = XML.find(Lab_ShortName_Start, i);
					int Position_ShortName_End = XML.find(Lab_ShortName_End, Position_ShortName_Start);
					int Position_SW_DATA_DEF = XML.find(Lab_SW_DATA_DEF, Position_ShortName_End);
					int Position_DATA_REF = 0;
					int Position_DATA_TYPE = 0;

					if ((Position_ShortName_Start != string::npos) && (Position_ShortName_Start < Position_SubElem_End))
					{
						string Signal_name = XML.substr(Position_ShortName_Start + Lab_ShortName_Start.length(), Position_ShortName_End - Position_ShortName_Start - Lab_ShortName_Start.length());
						Recoder_Signal.Signal_Name = Signal_name;
						
						if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE_IMPLEMENT, Position_ShortName_End)) != string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
						{
							int type_int = 0;
							Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
							string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE_IMPLEMENT.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE_IMPLEMENT.length());
							Recoder_Signal.type_str = Type;

							if (Type == "boolean" || Type == "uint8" || Type == "sint8")
							{
								type_int = 8;
							}
							else if (Type == "uint16" || Type == "sint16")
							{
								type_int = 16;
							}
							else if (Type == "uint32" || Type == "sint32" || Type == "float32")
							{
								type_int = 32;
							}
							else if (Type == "float64")
							{
								type_int = 64;
							}

							Recoder_Signal.type_int = type_int;
							Recoder_Signal.Flag_Type = 1;
							Recoder_Signal.Array_Size = 0;
							
						}
						else if (((Position_DATA_TYPE = XML.find(Lab_DATA_TYPE, Position_ShortName_End)) != string::npos) && (Position_DATA_TYPE < Position_SW_DATA_DEF))
						{
							Position_DATA_REF = XML.find(Lab_DATA_TYPE_REF, Position_DATA_TYPE);
							if (XML.find(Lab_Dt_RECORD, Position_DATA_TYPE) < Position_SW_DATA_DEF)
							{
								string Type = XML.substr(Position_DATA_TYPE + Lab_DATA_TYPE.length(), Position_DATA_REF - Position_DATA_TYPE - Lab_DATA_TYPE.length());
								Recoder_Signal.type_str = Type;
								Recoder_Signal.Flag_Type = 2;
								Recoder_Signal.Array_Size = 0;

							}
						}

						Dt_RECORD.Recoder_Signal.push_back(Recoder_Signal);

						Recoder_Signal.Signal_Name.clear();
						Recoder_Signal.type_int = 0;
						Recoder_Signal.type_str.clear();
						Recoder_Signal.Array_Size = 0;
						Recoder_Signal.Flag_Type = 0;
					}

					i = Position_ShortName_End + Lab_ShortName_End.length();

				}

				Recoder_Signal_VC.push_back(Dt_RECORD);
			}
		}
	}

	
	if (Num_Loop == 0)
	{
		Flag_Loop = false;
	}
	else
	{
		Recoder_Signal_VC_All.push_back(Recoder_Signal_VC);
	}


}

/*------------------             循环得到所有Port的Signal属性             -------------------*/
void Find_Recoder_SignalAll(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All)
{
	bool Flag_Loop = true;
	vector<DT_RECODER> Recoder_Signal_VC;
	for (int i_PiPort = 0; i_PiPort < Port_All.size(); i_PiPort++)
	{
		for (int i_DePort = 0; i_DePort < Port_All[i_PiPort].De_PORT.size(); i_DePort++)
		{
			if (!(Port_All[i_PiPort].De_PORT[i_DePort].Dt_RECORD_NAME.empty()))
			{
				string ReferenceName = Port_All[i_PiPort].De_PORT[i_DePort].Dt_RECORD_NAME;
				Find_Recoder_Signal(XML, ReferenceName, Recoder_Signal_VC);
			}
		}
	}
	Recoder_Signal_VC_All.push_back(Recoder_Signal_VC);
	
	while (Flag_Loop)
	{
		Find_Recoder_Layers(XML, Flag_Loop, Recoder_Signal_VC_All);
	}

// 	for (int i = 0; i < Recoder_Signal_VC_All.size(); i++)
// 	{
// 		for (int j = 0; j < Recoder_Signal_VC_All[i].size(); j++)
// 		{
// 			printf("第%d层 第%d个Recoder下的属性 %s\n", i + 1, j + 1, Recoder_Signal_VC_All[i][j].Dt_RECODER_NAME.c_str());
// 			for (int m = 0; m < Recoder_Signal_VC_All[i][j].Recoder_Signal.size(); m++)
// 			{
// 				printf("  第%d个信号:\n", m+1);
// 				printf("	SignalName:%s\n", Recoder_Signal_VC_All[i][j].Recoder_Signal[m].Signal_Name.c_str());
// 				printf("	TypeStr:%s\n", Recoder_Signal_VC_All[i][j].Recoder_Signal[m].type_str.c_str());
// 				printf("	Length:%d\n", Recoder_Signal_VC_All[i][j].Recoder_Signal[m].type_int);
// 				printf("	Array_Size:%d\n", Recoder_Signal_VC_All[i][j].Recoder_Signal[m].Array_Size);
// 				printf("	Flag_Type:%d\n", Recoder_Signal_VC_All[i][j].Recoder_Signal[m].Flag_Type);
// 			}
// 		}
// 	}
 	
}



void Padding_Cal(string &XML, vector<int> &SOA_Message_Pad, string Dt_RECORD_Name, int &Pad_Num, int &Length_Total)
{
	int Addr_Element = 0,
		Addr_Sum = 0,
		Addr_Sum_32 = 0,
		ret_Sum = 0,
		Flag_Byte = 0;
	

	for (int j = 0; j < SOA_Message_Pad.size();j++)
	{
		//printf("%d,", SOA_Message_Pad[j]);

		if (SOA_Message_Pad[j] == 64)
		{
			Flag_Byte++;
		}
	}

	if (Flag_Byte==0)
	{
		int Pad_Sig_Num = 0;
		/*------------------                 32位对齐                 -------------------*/
		for (int i = 0; i < SOA_Message_Pad.size() - 1; i++)
		{
			int ret = 0;
			Addr_Element += SOA_Message_Pad[i];
			if (Addr_Element <= 32 && (Addr_Element + SOA_Message_Pad[i + 1])>32)
			{
				if ((32 - Addr_Element) != 0)
				{
					ret = (32 - Addr_Element) / 8;
					switch (ret)
					{
					case 1:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 8);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 8);
						Pad_Num++;
						break;
					case 2:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 16);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 16);
						Pad_Num++;
						break;
					case 3:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 8);
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 2, 16);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 8);
						Pad_Sig_Num++;
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 2, Pad_Sig_Num, 16);
						Pad_Num++;
						break;
					}
				}
				else
				{
					Addr_Element = 0;
				}
			}
		}

		for (int m = 0; m < SOA_Message_Pad.size(); m++)
		{
			Addr_Sum += SOA_Message_Pad[m];
		}

		if ((ret_Sum = Addr_Sum % 32) != 0)
		{
			int n = SOA_Message_Pad.size();
			ret_Sum = (32 - ret_Sum) / 8;
			if (ret_Sum == 1)
			{
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(8);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, n, Pad_Sig_Num, 8);
				Pad_Num++;
			}
			else if (ret_Sum == 2)
			{
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(16);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, n, Pad_Sig_Num, 16);
				Pad_Num++;
			}
			else if (ret_Sum == 3)
			{
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(8);
				//SOA_Message_Pad.push_back(16);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, n, Pad_Sig_Num, 8);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, n + 1, Pad_Sig_Num, 16);
				Pad_Num++;
			}

		}

		for (int m = 0; m < SOA_Message_Pad.size(); m++)
		{
			Length_Total += SOA_Message_Pad[m];
		}
		
	} 

	else
	{
		int Pad_Sig_Num = 0;
		/*------------------                 64位对齐                 -------------------*/
		for (int i = 0; i < SOA_Message_Pad.size() - 1; i++)
		{
			int ret = 0;
			Addr_Element += SOA_Message_Pad[i];
			if (Addr_Element <= 32 && (Addr_Element + SOA_Message_Pad[i + 1])>32)
			{
				if ((32 - Addr_Element) != 0)
				{
					ret = (32 - Addr_Element) / 8;
					switch (ret)
					{
					case 1:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 8);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 8);
						Pad_Num++;
						break;
					case 2:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 16);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 16);
						Pad_Num++;
						break;
					case 3:
						Pad_Sig_Num++;
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 1, 8);
						//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + i + 2, 16);
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 1, Pad_Sig_Num, 8);
						Pad_Sig_Num++;
						Padding_Implem_Inseret(XML, Dt_RECORD_Name, i + 2, Pad_Sig_Num, 16);
						Pad_Num++;
						break;
					}
				}
				else
				{
					Addr_Element = 0;
				}
			}
		}

		/*------------------                 整体对齐                 -------------------*/
		for (int n = 0; n < SOA_Message_Pad.size();n++)
		{
			Addr_Sum_32 += SOA_Message_Pad[n];
			if (SOA_Message_Pad[n]==64)
			{
				if ((Addr_Sum_32%64)!=0)
				{
					Pad_Sig_Num++;
					//SOA_Message_Pad.insert(SOA_Message_Pad.begin() + n, 32);
					Padding_Implem_Inseret(XML, Dt_RECORD_Name, n + 1, Pad_Sig_Num, 32);
					Pad_Num++;
					Addr_Sum_32 += 32;
				}
			}
		}

		for (int m = 0; m < SOA_Message_Pad.size(); m++)
		{
			Addr_Sum += SOA_Message_Pad[m];
		}

		if ((ret_Sum = Addr_Sum % 64) != 0)
		{
			int m = SOA_Message_Pad.size();
			ret_Sum = (64 - ret_Sum) / 8;
			switch (ret_Sum)
			{
			case 1:
				Pad_Sig_Num++;
 				//SOA_Message_Pad.push_back(8);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 8);
				Pad_Num++;
				break;
			case 2:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(16);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 16);
				Pad_Num++;
				break;
			case 3:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(8);
				//SOA_Message_Pad.push_back(16);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 8);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m + 1, Pad_Sig_Num, 16);
				Pad_Num++;
				break;
			case 4:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(32);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 32);
				Pad_Num++;
				break;
			case 5:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(8);
				//SOA_Message_Pad.push_back(32);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 8);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m + 1, Pad_Sig_Num, 32);
				Pad_Num++;
				break;
			case 6:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(16);
				//SOA_Message_Pad.push_back(32);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 16);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m + 1, Pad_Sig_Num, 32);
				Pad_Num++;
				break;
			case 7:
				Pad_Sig_Num++;
				//SOA_Message_Pad.push_back(8);
				//SOA_Message_Pad.push_back(16);
				//SOA_Message_Pad.push_back(32);
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m, Pad_Sig_Num, 8);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m + 1, Pad_Sig_Num, 16);
				Pad_Sig_Num++;
				Padding_Implem_PushBack(XML, Dt_RECORD_Name, m + 2, Pad_Sig_Num, 32);
				Pad_Num++;
				break;
			}
		}

		for (int m = 0; m < SOA_Message_Pad.size(); m++)
		{
			Length_Total += SOA_Message_Pad[m];
		}

 	}

// 	printf("Padding后：");
// 	for (int k = 0; k < SOA_Message_Pad.size(); k++)
// 	{
// 		printf("%d,", SOA_Message_Pad[k]);
// 	}
}

void Padding_Implem_Inseret(string &XML, string Dt_RECODER_NAME, int Position_Num, int Pad_Sig_Num, int Pad_Length)
{
	static string Lab_ShortName_Start = "<SHORT-NAME>";
	static string Lab_ShortName_End = "</SHORT-NAME>";
	static string Lab_SubElem_Start = "<SUB-ELEMENTS>";
	static string Lab_SubElem_End = "</SUB-ELEMENTS>";
	static string Lab_DATA_TYPE = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_DATA_TYPE_IMPLEMENT = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
	static string Lab_DATA_TYPE_REF = "</IMPLEMENTATION-DATA-TYPE-REF>";
	static string Lab_SW_DATA_DEF = "</SW-DATA-DEF-PROPS>";
	static string Lab_CONSTANT_SPECIFICATION_End = "</CONSTANT-SPECIFICATION>";
	static string Lab_SHORTLABEL_Start = "<SHORT-LABEL>";
	static string Lab_SHORTLABEL_End = "</SHORT-LABEL>";
	static string Lab_IMPLEM_UUID_Start = "<IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=";
	static string Lab_IMPLEM_UUID_End = "</IMPLEMENTATION-DATA-TYPE-ELEMENT>";
	static string Lab_NUMERICAL_VALUE_Start = "<NUMERICAL-VALUE-SPECIFICATION>";
	static string Lab_NUMERICAL_VALUE_End = "</NUMERICAL-VALUE-SPECIFICATION>";

	int Short_Name_Num = 0;
	int Short_Label_Num = 0;

	/*------------------                       Padding_Dt_RECORD                      -------------------*/
	int Position_Reference_Name_Start = XML.find(Lab_ShortName_Start + Dt_RECODER_NAME + Lab_ShortName_End, 0);
	int Position_SubElem_Start = XML.find(Lab_SubElem_Start, Position_Reference_Name_Start);
	int Position_SubElem_End = XML.find(Lab_SubElem_End, Position_Reference_Name_Start);

	for (int i = Position_Reference_Name_Start + Dt_RECODER_NAME.length(); i < Position_SubElem_End; i++)
	{
		string Padding_Signal_Name;
		string Padding_Contents;
		string C_RECORD_PadContents;
		int Position_IMPLEM_Start = XML.find(Lab_IMPLEM_UUID_Start, i);
		int Position_IMPLEM_End = XML.find(Lab_IMPLEM_UUID_End, Position_IMPLEM_Start);

		if ((Position_IMPLEM_Start != string::npos) && (Position_IMPLEM_Start < Position_SubElem_End))
		{
			Short_Name_Num++;
			if (Short_Name_Num == Position_Num)
			{
				string Pad_Type;
				string Pad_Num_str;
				string Length_str;

				char Pad_Num_str_tmp[10];
				char Length_str_tmp[10];
				_itoa(Pad_Sig_Num, Pad_Num_str_tmp, 10);
				_itoa(Pad_Length, Length_str_tmp, 10);

				Pad_Num_str.append(Length_str_tmp);
				Length_str.append(Length_str_tmp);

				if (Pad_Length == 8)
				{
					Pad_Type = "uint8";
				}
				else if (Pad_Length == 16)
				{
					Pad_Type = "uint16";
				}
				else if (Pad_Length == 32)
				{
					Pad_Type = "uint32";
				}

				Padding_Signal_Name = "PaddingGap" + Length_str + "_" + Pad_Num_str;
				Padding_Contents = "            <IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=\"39CB8D9F-7662-46F8-AD26-8B29B0B70B13\">\n\
              <SHORT-NAME>" + Padding_Signal_Name + "</SHORT-NAME>\n"+
"              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/"+Pad_Type+"</IMPLEMENTATION-DATA-TYPE-REF>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n";

				XML.insert(Position_IMPLEM_Start, Padding_Contents);

					/*------------------                       Padding_C_RECORD                      -------------------*/

				string C_RECORD_Name = Dt_RECODER_NAME;
				C_RECORD_Name.replace(0, 2, "C");

				int Position_C_RECORD_Start = XML.find(Lab_ShortName_Start + C_RECORD_Name + Lab_ShortName_End, 0);
				int Position_CONSTANT_SPECIFICATION_End = XML.find(Lab_CONSTANT_SPECIFICATION_End, Position_C_RECORD_Start);

				for (int i = Position_C_RECORD_Start + C_RECORD_Name.length(); i < Position_CONSTANT_SPECIFICATION_End; i++)
				{
					int Position_NUMERICALVALUE_Start = XML.find(Lab_NUMERICAL_VALUE_Start, i);
					int Position_NUMERICALVALUE_End = XML.find(Lab_NUMERICAL_VALUE_End, Position_NUMERICALVALUE_Start);

					if ((Position_NUMERICALVALUE_Start != string::npos) && (Position_NUMERICALVALUE_Start < Position_SubElem_End))
					{
						Short_Label_Num++;
						if (Short_Label_Num == Position_Num)
						{
							C_RECORD_PadContents = "<NUMERICAL-VALUE-SPECIFICATION>\n\
                  <SHORT-LABEL>"+Padding_Signal_Name+"</SHORT-LABEL>\n\
                  <VALUE>0</VALUE>\n\
                </NUMERICAL-VALUE-SPECIFICATION>\n";

							XML.insert(Position_NUMERICALVALUE_Start, C_RECORD_PadContents);

						}
					}

					i = Position_NUMERICALVALUE_Start + C_RECORD_PadContents.length();

				}

				break;
			}
		}

		i = Position_IMPLEM_Start + Padding_Contents.length();
	}
}

void Padding_Implem_PushBack(string &XML, string Dt_RECODER_NAME, int Position_Num, int Pad_Sig_Num, int Pad_Length)
{
	static string Lab_ShortName_Start = "<SHORT-NAME>";
	static string Lab_ShortName_End = "</SHORT-NAME>";
	static string Lab_SubElem_Start = "<SUB-ELEMENTS>";
	static string Lab_SubElem_End = "</SUB-ELEMENTS>";
	static string Lab_DATA_TYPE = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/";
	static string Lab_DATA_TYPE_IMPLEMENT = "<IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
	static string Lab_DATA_TYPE_REF = "</IMPLEMENTATION-DATA-TYPE-REF>";
	static string Lab_SW_DATA_DEF = "</SW-DATA-DEF-PROPS>";
	static string Lab_CONSTANT_SPECIFICATION_End = "</CONSTANT-SPECIFICATION>";
	static string Lab_SHORTLABEL_Start = "<SHORT-LABEL>";
	static string Lab_SHORTLABEL_End = "</SHORT-LABEL>";
	static string Lab_IMPLEM_UUID_Start = "<IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=";
	static string Lab_IMPLEM_UUID_End = "</IMPLEMENTATION-DATA-TYPE-ELEMENT>";
	static string Lab_NUMERICAL_VALUE_Start = "<NUMERICAL-VALUE-SPECIFICATION>";
	static string Lab_NUMERICAL_VALUE_End = "</NUMERICAL-VALUE-SPECIFICATION>";

	int Short_Name_Num = 0;
	int Short_Label_Num = 0;
	int Find_Repeat_Num = 0;

	/*------------------                       Padding_Dt_RECORD                      -------------------*/
	int Position_Reference_Name_Start = XML.find(Lab_ShortName_Start + Dt_RECODER_NAME + Lab_ShortName_End, 0);
	int Position_SubElem_Start = XML.find(Lab_SubElem_Start, Position_Reference_Name_Start);
	int Position_SubElem_End = XML.find(Lab_SubElem_End, Position_Reference_Name_Start);

	for (int i = Position_Reference_Name_Start + Dt_RECODER_NAME.length(); i < Position_SubElem_End; i++)
	{
		string Padding_Signal_Name;
		string Padding_Contents;
		string C_RECORD_PadContents;
		int Position_IMPLEM_Start = XML.find(Lab_IMPLEM_UUID_Start, i);
		int Position_IMPLEM_End = XML.find(Lab_IMPLEM_UUID_End, Position_IMPLEM_Start);

		if ((Position_IMPLEM_Start != string::npos) && (Position_IMPLEM_Start < Position_SubElem_End))
		{
			Short_Name_Num++;
			if (Short_Name_Num == Position_Num)
			{
				string Pad_Type;
				string Pad_Num_str;
				string Length_str;

				int Position_IMPLEM_Last_PushBack = Position_IMPLEM_End + Lab_IMPLEM_UUID_End.length();

				char Pad_Num_str_tmp[10];
				char Length_str_tmp[10];
				_itoa(Pad_Sig_Num, Pad_Num_str_tmp, 10);
				_itoa(Pad_Length, Length_str_tmp, 10);

				Pad_Num_str.append(Length_str_tmp);
				Length_str.append(Length_str_tmp);

				if (Pad_Length == 8)
				{
					Pad_Type = "uint8";
				}
				else if (Pad_Length == 16)
				{
					Pad_Type = "uint16";
				}
				else if (Pad_Length == 32)
				{
					Pad_Type = "uint32";
				}

				Padding_Signal_Name = "PaddingGap" + Length_str + "_" + Pad_Num_str;
				Padding_Contents = "            <IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=\"39CB8D9F-7662-46F8-AD26-8B29B0B70B13\">\n\
              <SHORT-NAME>" + Padding_Signal_Name + "</SHORT-NAME>\n"+
"              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/"+Pad_Type+"</IMPLEMENTATION-DATA-TYPE-REF>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n";

				XML.insert(Position_IMPLEM_Last_PushBack + 1, "\n" + Padding_Contents);

				/*------------------                       Padding_C_RECORD                      -------------------*/

				string C_RECORD_Name = Dt_RECODER_NAME;
				C_RECORD_Name.replace(0, 2, "C");

				int Position_C_RECORD_Start = XML.find(Lab_ShortName_Start + C_RECORD_Name + Lab_ShortName_End, 0);
				int Position_CONSTANT_SPECIFICATION_End = XML.find(Lab_CONSTANT_SPECIFICATION_End, Position_C_RECORD_Start);

				for (int i = Position_C_RECORD_Start + C_RECORD_Name.length(); i < Position_CONSTANT_SPECIFICATION_End; i++)
				{
					int Position_NUMERICALVALUE_Start = XML.find(Lab_NUMERICAL_VALUE_Start, i);
					int Position_NUMERICALVALUE_End = XML.find(Lab_NUMERICAL_VALUE_End, Position_NUMERICALVALUE_Start);

					if ((Position_NUMERICALVALUE_Start != string::npos) && (Position_NUMERICALVALUE_Start < Position_SubElem_End))
					{
						Short_Label_Num++;
						if (Short_Label_Num == Position_Num)
						{
							int Position_NUMERICALVALUE_Last_PushBack = Position_NUMERICALVALUE_End + Lab_NUMERICAL_VALUE_End.length();

							C_RECORD_PadContents = "<NUMERICAL-VALUE-SPECIFICATION>\n\
                  <SHORT-LABEL>"+Padding_Signal_Name+"</SHORT-LABEL>\n\
                  <VALUE>0</VALUE>\n\
                </NUMERICAL-VALUE-SPECIFICATION>\n";

							XML.insert(Position_NUMERICALVALUE_Last_PushBack + 1, "\n" + C_RECORD_PadContents);
						}
					}
					i = Position_NUMERICALVALUE_Start + C_RECORD_PadContents.length();
				}
				break;
			}
		}
		i = Position_IMPLEM_Start + Padding_Contents.length();
	}
}

/*------------------                       Padding                       -------------------*/
void XML_Padding(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All)
{
	vector<int> Signal_X_Length;
	PAD_DT_RECORD Pad_Dt_RECORD_tmp;
	vector<PAD_DT_RECORD> Pad_Dt_RECORD;
	string Dt_RECORD_Name;

	int Num_Last_Layer = Recoder_Signal_VC_All.size() - 1;
	int Num_Last_Layer_Dt_RECORD = Recoder_Signal_VC_All[Num_Last_Layer].size();

	/*------------------                 最后一层先填充                 -------------------*/
	for (int m_Dt_RECORD = 0; m_Dt_RECORD < Num_Last_Layer_Dt_RECORD; m_Dt_RECORD++)
	{
		int Pad_Num = 0;
		int Find_Repeat_Num = 0;
		int Length_Total = 0;
		int Length_X = 0;
		Dt_RECORD_Name = Recoder_Signal_VC_All[Num_Last_Layer][m_Dt_RECORD].Dt_RECODER_NAME;

		for (int i_Find_Repeat = 0; i_Find_Repeat < Pad_Dt_RECORD.size(); i_Find_Repeat++)
		{
			if (Dt_RECORD_Name == Pad_Dt_RECORD[i_Find_Repeat].NAME)
			{
				Find_Repeat_Num++;
			}
		}
		if (Find_Repeat_Num != 0)
		{
			goto END1;
		}
		else
		{
			for (int m_Last_Layer_Signal = 0; m_Last_Layer_Signal < Recoder_Signal_VC_All[Num_Last_Layer][m_Dt_RECORD].Recoder_Signal.size(); m_Last_Layer_Signal++)
			{
				Length_X = Recoder_Signal_VC_All[Num_Last_Layer][m_Dt_RECORD].Recoder_Signal[m_Last_Layer_Signal].type_int;
				Signal_X_Length.push_back(Length_X);
			}
			Padding_Cal(XML, Signal_X_Length, Dt_RECORD_Name, Pad_Num, Length_Total);


			Signal_X_Length.clear();


			Pad_Dt_RECORD_tmp.NAME = Dt_RECORD_Name;
			Pad_Dt_RECORD_tmp.LENGTH_TOTAL = Length_Total;
			Pad_Dt_RECORD.push_back(Pad_Dt_RECORD_tmp);

		}
	END1:
		return;
	}

	/*------------------                  各层分别填充                  -------------------*/
	for (int i = Num_Last_Layer - 1; i >= 0; i--)
	{
		for (int j = 0; j < Recoder_Signal_VC_All[i].size() - 1; j++)
		{
			int Pad_Num = 0;
			int Find_Repeat_Num = 0;
			int Length_Total = 0;
			Dt_RECORD_Name = Recoder_Signal_VC_All[i][j].Dt_RECODER_NAME;

			for (int i_Find_Repeat = 0; i_Find_Repeat < Pad_Dt_RECORD.size(); i_Find_Repeat++)
			{
				if (Dt_RECORD_Name == Pad_Dt_RECORD[i_Find_Repeat].NAME)
				{
					Find_Repeat_Num++;
				}
			}
			if (Find_Repeat_Num != 0)
			{
				goto END2;
			}
			else
			{
				for (int m_Last_Layer_Signal = 0; m_Last_Layer_Signal < Recoder_Signal_VC_All[i][j].Recoder_Signal.size(); m_Last_Layer_Signal++)
				{
					int Length_X = 0;
					int Flag_Type = Recoder_Signal_VC_All[i][j].Recoder_Signal[m_Last_Layer_Signal].Flag_Type;
					string name = Recoder_Signal_VC_All[i][j].Recoder_Signal[m_Last_Layer_Signal].type_str;
					int Type_int = Recoder_Signal_VC_All[i][j].Recoder_Signal[m_Last_Layer_Signal].type_int;
					int ARRAY_Size = Recoder_Signal_VC_All[i][j].Recoder_Signal[m_Last_Layer_Signal].Array_Size;

					if (Flag_Type == 2)
					{
						for (int i_Find = 0; i_Find < Pad_Dt_RECORD.size(); i_Find++)
						{
							if (name == Pad_Dt_RECORD[i_Find].NAME)
							{
								Length_X = Pad_Dt_RECORD[i_Find].LENGTH_TOTAL;
								Signal_X_Length.push_back(Length_X);
							}
						}
					}
					else if (Flag_Type == 3 && Type_int != 0)
					{
						for (int i_Find = 0; i_Find < Pad_Dt_RECORD.size(); i_Find++)
						{
							if (name == Pad_Dt_RECORD[i_Find].NAME)
							{
								Length_X = ARRAY_Size * Pad_Dt_RECORD[i_Find].LENGTH_TOTAL;
								Signal_X_Length.push_back(Length_X);
							}
						}
					}
					else if (Flag_Type == 3 && Type_int == 0)
					{
						int Position_Array_Name = XML.find("<SHORT-NAME>" + name + "</SHORT-NAME>", 0);
						int Position_IMPLEM_END = XML.find("</IMPLEMENTATION-DATA-TYPE-REF>", Position_Array_Name);
						int Position_Record_Name = XML.find("Dt_RECORD_", Position_Array_Name);
						if (Position_Record_Name < Position_IMPLEM_END)
						{
							static string Record_Name = XML.substr(Position_Record_Name, Position_IMPLEM_END - Position_Record_Name);
							for (int i_Find = 0; i_Find < Pad_Dt_RECORD.size(); i_Find++)
							{
								if (Record_Name == Pad_Dt_RECORD[i_Find].NAME)
								{
									Length_X = ARRAY_Size * Pad_Dt_RECORD[i_Find].LENGTH_TOTAL;
									Signal_X_Length.push_back(Length_X);
								}
							}
						}
						else
						{
							printf("%s的类型为ARAAY，但其下没找到对应的Record\n", Dt_RECORD_Name);
						}
					}
					else
					{
						Signal_X_Length.push_back(Type_int);
					}

				}

				Padding_Cal(XML, Signal_X_Length, Dt_RECORD_Name, Pad_Num, Length_Total);


				Signal_X_Length.clear();


				Pad_Dt_RECORD_tmp.NAME = Dt_RECORD_Name;
				Pad_Dt_RECORD_tmp.LENGTH_TOTAL = Length_Total;
				Pad_Dt_RECORD.push_back(Pad_Dt_RECORD_tmp);

			}
		END2:
			return;
		}
	}
}




void Padding_ALL(string &XML, vector<PI_PORT> &Port_All, vector<vector<DT_RECODER>> &Recoder_Signal_VC_All)
{
	XML_Extrat_PortAll(XML, Port_All);
	Find_Recoder_SignalAll(XML, Port_All, Recoder_Signal_VC_All);
	XML_Padding(XML, Port_All, Recoder_Signal_VC_All);
}


