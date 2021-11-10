#include "include.h"

/*****************************         FUNC: DBC检查         *******************************/

/*-----------------------             DBC基本属性检查              ------------------------*/
void DBC_Check_BA_DEF_BO(char *filename)
{
	string filename_str;
	filename_str.append(filename);

	bool flag_Check_BA_DEF_BO_1 = true;
	bool flag_Check_BA_DEF_BO_2 = true;
	bool flag_Check_BA_DEF_BO_3 = true;
	bool flag_Check_BA_DEF_BO_4 = true;
	bool flag_DBName_STRING = true; 
	bool flag_DBName = true;

	int i_find_BA_DEF_BO_1 = 0, NUM_BA_DEF_BO_1 = 0;
	int i_find_BA_DEF_BO_2 = 0, NUM_BA_DEF_BO_2 = 0;
	int i_find_BA_DEF_BO_3 = 0, NUM_BA_DEF_BO_3 = 0;
	int i_find_BA_DEF_BO_4 = 0, NUM_BA_DEF_BO_4 = 0;
	int i_find_DBName_STRING = 0, NUM_DBName_STRING = 0; 
	int i_find_DBName = 0, NUM_DBName = 0;

	string BA_DEF_BO_1 = "BA_DEF_ BO_  \"GenMsgILSupport\" ENUM  \"No\",\"Yes\";";
	string BA_DEF_BO_2 = "BA_DEF_ BO_  \"GenMsgCycleTime\" INT 0 ";
	string BA_DEF_BO_3 = "BA_DEF_ BO_  \"GenMsgStartDelayTime\" INT 0 100000;";
	string BA_DEF_BO_4 = "BA_DEF_ BO_  \"GenMsgDelayTime\" INT 0 300000;";
	string DBName_STRING = "BA_DEF_  \"DBName\" STRING;"; 
	string DBName = "BA_ \"DBName\"";

	string DBC_str = Read_Get_DBC(filename);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("*************************************************************************************************************************************\n");

	while (flag_DBName_STRING)
	{
		if ((i_find_DBName_STRING = DBC_str.find(DBName_STRING, i_find_DBName_STRING)) != string::npos)
		{
			NUM_DBName_STRING++;
			i_find_DBName_STRING++;
		}
		else
		{
			flag_DBName_STRING = false;
		}
	}
	while (flag_DBName)
	{
		if ((i_find_DBName = DBC_str.find(DBName, i_find_DBName)) != string::npos)
		{
			NUM_DBName++;
			i_find_DBName++;
		}
		else
		{
			flag_DBName = false;
		}
	}

	if (NUM_DBName_STRING == 0 || NUM_DBName==0)
	{
		if (NUM_DBName_STRING == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//红色
			printf("=============%s不可以修改名字，缺少 %s 信息==============\n", filename_str.c_str(), DBName_STRING.c_str());
		}
		else if (NUM_DBName == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("=============%s不可以修改名字，缺少 %s 信息==============\n", filename_str.c_str(), DBName.c_str());
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("=============%s不可以修改名字，缺少 %s 信息与 %s 信息==============\n", filename_str.c_str(), DBName_STRING.c_str(), DBName.c_str());
		}
	} 
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); //绿色
		printf("=============%s可以修改名字==============\n", filename_str.c_str());
	}

	while (flag_Check_BA_DEF_BO_1)
	{
		if ((i_find_BA_DEF_BO_1 =DBC_str.find(BA_DEF_BO_1,i_find_BA_DEF_BO_1))!=string::npos)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("=============%s中%s存在\n", filename_str.c_str(),BA_DEF_BO_1.c_str());
			NUM_BA_DEF_BO_1++;
			i_find_BA_DEF_BO_1++;
		} 
		else
		{
			flag_Check_BA_DEF_BO_1 = false;
		}
	}
	if (NUM_BA_DEF_BO_1==0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("=============%s中%s缺失！！！！！！！！！！==============\n", filename_str.c_str(), BA_DEF_BO_1.c_str());
	}

	while (flag_Check_BA_DEF_BO_2)
	{
		if ((i_find_BA_DEF_BO_2 = DBC_str.find(BA_DEF_BO_2, i_find_BA_DEF_BO_2)) != string::npos)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("=============%s中%s存在\n", filename_str.c_str(), BA_DEF_BO_2.c_str());
			NUM_BA_DEF_BO_2++;
			i_find_BA_DEF_BO_2++;
		}
		else
		{
			flag_Check_BA_DEF_BO_2 = false;
		}
	}
	if (NUM_BA_DEF_BO_2 == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("=============%s中%s缺失！！！！！！！！！！==============\n", filename_str.c_str(), BA_DEF_BO_2.c_str());
	}

	while (flag_Check_BA_DEF_BO_3)
	{
		if ((i_find_BA_DEF_BO_3 = DBC_str.find(BA_DEF_BO_3, i_find_BA_DEF_BO_3)) != string::npos)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("=============%s中%s存在\n", filename_str.c_str(), BA_DEF_BO_3.c_str());
			NUM_BA_DEF_BO_3++;
			i_find_BA_DEF_BO_3++;
		}
		else
		{
			flag_Check_BA_DEF_BO_3 = false;
		}
	}
	if (NUM_BA_DEF_BO_3 == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("=============%s中%s缺失！！！！！！！！！！==============\n", filename_str.c_str(), BA_DEF_BO_3.c_str());
	}

	while (flag_Check_BA_DEF_BO_4)
	{
		if ((i_find_BA_DEF_BO_4 = DBC_str.find(BA_DEF_BO_4, i_find_BA_DEF_BO_4)) != string::npos)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			printf("=============%s中%s存在\n", filename_str.c_str(), BA_DEF_BO_4.c_str());
			NUM_BA_DEF_BO_4++;
			i_find_BA_DEF_BO_4++;
		}
		else
		{
			flag_Check_BA_DEF_BO_4 = false;
		}
	}
	if (NUM_BA_DEF_BO_4 == 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("=============%s中%s缺失！！！！！！！！！！==============\n", filename_str.c_str(), BA_DEF_BO_4.c_str());
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("*************************************************************************************************************************************\n");
	filename_str.clear();
}

/*------------------    判断同一DBC是否有收发同一消息，确认信号Map状态   -------------------*/
void DBC_Check_SameDBC(string Node, vector<Messege> messege_vector, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	for (int i_message_Tx = 0; i_message_Tx < Tx_IECU.size(); i_message_Tx++)
	{
		for (int i_signal_Tx = 0; i_signal_Tx < Tx_IECU[i_message_Tx].Signal.size(); i_signal_Tx++)
		{
			for (int i_message_Rx = 0; i_message_Rx < Rx_IECU.size();i_message_Rx++)
			{
				for (int i_signal_Rx = 0; i_signal_Rx < Rx_IECU[i_message_Rx].Signal.size();i_signal_Rx++)
				{
					if (Tx_IECU[i_message_Tx].Signal[i_signal_Tx].name == Rx_IECU[i_message_Rx].Signal[i_signal_Rx].name)
					{
						//a++;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//红色
						printf("TX：%s（ID：%s）《=======   %s   ======》RX：%s（ID：%s）\n", Tx_IECU[i_message_Tx].name.c_str(), Tx_IECU[i_message_Tx].ID.c_str(), Tx_IECU[i_message_Tx].Signal[i_signal_Tx].name.c_str(), Rx_IECU[i_message_Rx].name.c_str(),Rx_IECU[i_message_Rx].ID.c_str());
					}
				}
			}

		}
	}

	for (int i_Same_signal_1 = 0; i_Same_signal_1 < Tx_IECU.size()-1;i_Same_signal_1++)
	{
		for (int i_Same_signal_2 = 0; i_Same_signal_2 < Tx_IECU[i_Same_signal_1].Signal.size();i_Same_signal_2++)
		{
			for (int i_Same_signal_3 = i_Same_signal_1 + 1; i_Same_signal_3 < Tx_IECU.size();i_Same_signal_3++)
			{
				for (int i_Same_signal_4 = 0; i_Same_signal_4 < Tx_IECU[i_Same_signal_3].Signal.size();i_Same_signal_4++)
				{
					if (Tx_IECU[i_Same_signal_1].Signal[i_Same_signal_2].name==Tx_IECU[i_Same_signal_3].Signal[i_Same_signal_4].name)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//红色
						printf("Tx:%s（ID：%s）《=======   %s   ======》Tx:%s（ID：%s）\n", Tx_IECU[i_Same_signal_1].name.c_str(), Tx_IECU[i_Same_signal_1].ID.c_str(), Tx_IECU[i_Same_signal_1].Signal[i_Same_signal_2].name.c_str(), Tx_IECU[i_Same_signal_3].name.c_str(), Tx_IECU[i_Same_signal_3].ID.c_str());
					}
				}
			}
		}
	}

	for (int j_Same_signal_1 = 0; j_Same_signal_1 < Rx_IECU.size() - 1;j_Same_signal_1++)
	{
		for (int j_Same_signal_2 = 0; j_Same_signal_2 < Rx_IECU[j_Same_signal_1].Signal.size();j_Same_signal_2++)
		{
			for (int j_Same_signal_3 = j_Same_signal_1 + 1; j_Same_signal_3 < Rx_IECU.size();j_Same_signal_3++)
			{
				for (int j_Same_signal_4 = 0; j_Same_signal_4 < Rx_IECU[j_Same_signal_3].Signal.size();j_Same_signal_4++)
				{
					if (Rx_IECU[j_Same_signal_1].Signal[j_Same_signal_2].name == Rx_IECU[j_Same_signal_3].Signal[j_Same_signal_4].name)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);//红色
						printf("Rx:%s（ID：%s）《=======   %s   ======》Rx:%s（ID：%s）\n", Rx_IECU[j_Same_signal_1].name.c_str(), Rx_IECU[j_Same_signal_1].ID.c_str(), Rx_IECU[j_Same_signal_1].Signal[j_Same_signal_2].name.c_str(), Rx_IECU[j_Same_signal_3].name.c_str(), Rx_IECU[j_Same_signal_3].ID.c_str());
					}
				}
			}
		}
	}

	for (int i_Map = 0; i_Map < Rx_IECU.size(); i_Map++)
	{
		for (int j_Map = 0; j_Map < messege_vector.size(); j_Map++)
		{
			if (Rx_IECU[i_Map].name == messege_vector[j_Map].name)
			{
				if (Rx_IECU[i_Map].Signal.size() != messege_vector[j_Map].Signal.size())
				{
					for (int i_Map_Signal = 0; i_Map_Signal < messege_vector[j_Map].Signal.size();i_Map_Signal++)
					{
						int a_Map = 0;
						for (int j_Map_Signal = 0; j_Map_Signal < Rx_IECU[i_Map].Signal.size();j_Map_Signal++)
						{
							if (messege_vector[j_Map].Signal[i_Map_Signal].name == Rx_IECU[i_Map].Signal[j_Map_Signal].name)
							{
								a_Map++;
							}
						}
						if (a_Map == 0)
						{
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);  //红色
							printf("RX：%s 信号Map可能异常，ID：%s\n", messege_vector[j_Map].Signal[i_Map_Signal].name.c_str(), messege_vector[j_Map].ID.c_str());
						}
					}
					
				}
				break;
			}
		}
	}
}

/*------------------            判断不同DBC是否有收发同一消息           -------------------*/
void DBC_Check_DiffDBC(vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU)
{
	int b = 0;

	for (int m = 0; m < (*Rx_IECU).size(); m++)
	{
		for (int n = (*Rx_IECU).size() - 1; n >= 0, n != m; n--)
		{
			if ((*Rx_IECU)[m].name == (*Rx_IECU)[n].name)
			{
				b++;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				printf("%s节点接收重复\n", (*Rx_IECU)[m].name.c_str());
			}
		}
	}
// 	if (b == 0)
// 	{
// 		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
// 		printf("没有重复接收节点\n");
// 		
// 	}
}

/*------------------              判断是否有消息发送周期为0             -------------------*/
void DBC_Check_Cycle0(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	for (int i_Cycle0_TX = 0; i_Cycle0_TX < Tx_IECU.size(); i_Cycle0_TX++)
	{
		if (Tx_IECU[i_Cycle0_TX].cycle == "0")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 信号的周期为0\n", Tx_IECU[i_Cycle0_TX].name.c_str());
		}
	}

	for (int i_Cycle0_RX = 0; i_Cycle0_RX < Rx_IECU.size(); i_Cycle0_RX++)
	{
		if (Rx_IECU[i_Cycle0_RX].cycle == "0")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 信号的周期为0\n", Rx_IECU[i_Cycle0_RX].name.c_str());
		}
	}
}

/*------------------                  确认信号发送类型                  -------------------*/
void DBC_Check_Sendtype(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	for (int i_Sendtype_TX = 0; i_Sendtype_TX < Tx_IECU.size(); i_Sendtype_TX++)
	{
		if (Tx_IECU[i_Sendtype_TX].sendtype == "1")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 信号的Sendtype为spontaneous\n", Tx_IECU[i_Sendtype_TX].name.c_str());
		}
	}

	for (int i_Sendtype_RX = 0; i_Sendtype_RX < Rx_IECU.size(); i_Sendtype_RX++)
	{
		if (Rx_IECU[i_Sendtype_RX].sendtype == "1")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 信号的Sendtype为spontaneous\n", Rx_IECU[i_Sendtype_RX].name.c_str());
		}
	}
}

/*------------------                    检查DLC长度                     -------------------*/
void DBC_Check_DLC(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	for (int i_DLC_Tx = 0; i_DLC_Tx < Tx_IECU.size(); i_DLC_Tx++)
	{
		int a = atoi(Tx_IECU[i_DLC_Tx].DLC.c_str());
		if (a>8)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("请检查ID：%s   %s 的ID-Format,DLC长度：%d\n", Tx_IECU[i_DLC_Tx].ID.c_str(), Tx_IECU[i_DLC_Tx].name.c_str(), a);
		}
	}
	for (int i_DLC_Rx = 0; i_DLC_Rx < Rx_IECU.size(); i_DLC_Rx++)
	{
		int b = atoi(Rx_IECU[i_DLC_Rx].DLC.c_str());
		if (b>8)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("请检查ID：%s    %s 的ID-Format,DLC长度：%d\n", Rx_IECU[i_DLC_Rx].ID.c_str(), Rx_IECU[i_DLC_Rx].name.c_str(), b);
		}
	}
}

/*------------------                 检查Longname别名                  -------------------*/
void DBC_Check_Longname(string DBC_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	bool flag_find_Longname = true;
	int position_Longname = 0;
	string flag_Longname = "BA_ \"GenSigLongName\" SG_ ";
	string Tmp_str;
	vector<string> Tmp;
	LongName Longname_str;
	vector<LongName> Longname_list;
	
	while (flag_find_Longname)
	{
		if ((position_Longname = DBC_str.find(flag_Longname, position_Longname)) != string::npos)
		{
			for (int i = position_Longname + flag_Longname.length();; i++)
			{
				if (DBC_str[i] == '\n')
				{
					Longname_str.ID = Tmp[0];
					Longname_str.Shortname = Tmp[1];
					Longname_str.Longname = Tmp[3];

					Longname_list.push_back(Longname_str);
					Tmp_str.clear();
					Tmp.clear();
					break;
				}
				else
				{
					if (DBC_str[i] == ' ')
					{
						Tmp.push_back(Tmp_str);
						Tmp_str.clear();
					}
					else
					{
						Tmp_str.push_back(DBC_str[i]);
					}
				}
			}
			position_Longname++;
		}
		else
		{
			flag_find_Longname = false;
		}
	}

	for (int m = 0; m < Longname_list.size();m++)
	{
		for (int n = 0; n < Tx_IECU.size();n++)
		{
			if (Longname_list[m].ID==Tx_IECU[n].ID)
			{
				for (int m_Signal = 0; m_Signal < Tx_IECU[n].Signal.size();m_Signal++)
				{
					int a = 0;
					if ((Longname_list[m].Shortname == Tx_IECU[n].Signal[m_Signal].name) || (Longname_list[m].Longname == Tx_IECU[n].Signal[m_Signal].name))
					{
						a = 1;
					}
					if (a == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
						printf("检查确认TX：%s 的长短名, ID： %s\n", Longname_list[m].Shortname.c_str(), Longname_list[m].ID.c_str());
					}
				}
				break;
			}
		}
		
		for (int q = 0; q < Rx_IECU.size(); q++)
		{
			if (Longname_list[m].ID == Rx_IECU[q].ID)
			{
				for (int n_Signal = 0; n_Signal < Rx_IECU[q].Signal.size(); n_Signal++)
				{
					int b = 0;
					if ((Longname_list[m].Shortname == Rx_IECU[q].Signal[n_Signal].name) || (Longname_list[m].Longname == Rx_IECU[q].Signal[n_Signal].name))
					{
						b = 1;
					}
					if (b == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
						printf("检查确认RX：%s 的长短名, ID： %s\n", Longname_list[m].Shortname.c_str(), Longname_list[m].ID.c_str());
					}
				}
				break;
			}
		}
	}
	Longname_list.clear();

}

/*------------------                检查最大值、最小值                 -------------------*/
void DBC_Check_Max_Min(vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	for (int i_Messege = 0; i_Messege < Tx_IECU.size(); i_Messege++)
	{
		for (int i_Signal = 0; i_Signal < Tx_IECU[i_Messege].Signal.size();i_Signal++)
		{
			if (Tx_IECU[i_Messege].Signal[i_Signal].maximum==Tx_IECU[i_Messege].Signal[i_Signal].minimum)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("检查Tx：%s的最大值最小值, ID：%s\n", Tx_IECU[i_Messege].Signal[i_Signal].name.c_str(), Tx_IECU[i_Messege].ID.c_str());
			}
		}
	}
	for (int j_Messege = 0; j_Messege < Rx_IECU.size(); j_Messege++)
	{
		for (int j_Signal = 0; j_Signal < Rx_IECU[j_Messege].Signal.size(); j_Signal++)
		{
			if (Rx_IECU[j_Messege].Signal[j_Signal].maximum == Rx_IECU[j_Messege].Signal[j_Signal].minimum)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				printf("检查Rx：%s的最大值最小值, ID：%s\n", Rx_IECU[j_Messege].Signal[j_Signal].name.c_str(), Rx_IECU[j_Messege].ID.c_str());
			}
		}
	}

}

/*------------------                 检查两个DBC的不同                 -------------------*/
void Compare2DBCs(char *DBC1_name, char *DBC2_name, string Node)
{
	vector<Messege> IECU_Total1, IECU_Total2;
	string DBC1_str = Read_Get_DBC(DBC1_name);
	string DBC2_str = Read_Get_DBC(DBC2_name);

	vector<Messege> vmessege_vector_1 = DBC_Extract(DBC1_str, vmessege_vector_1);
	vector<Messege> vmessege_vector_2 = DBC_Extract(DBC2_str, vmessege_vector_2);

	vector<Messege> Tx_IECU_1 = Tx_IECU_Get(DBC1_str, Node, vmessege_vector_1, Tx_IECU_1);
	vector<Messege> Tx_IECU_2 = Tx_IECU_Get(DBC1_str, Node, vmessege_vector_2, Tx_IECU_2);
	vector<Messege> Rx_IECU_1 = Rx_IECU_Get(DBC1_str, Node, vmessege_vector_1, Rx_IECU_1);
	vector<Messege> Rx_IECU_2 = Rx_IECU_Get(DBC1_str, Node, vmessege_vector_2, Rx_IECU_2);

	IECU_Total1.insert(IECU_Total1.end(), Tx_IECU_1.begin(), Tx_IECU_1.end());
	IECU_Total1.insert(IECU_Total1.end(), Rx_IECU_1.begin(), Rx_IECU_1.end());
	IECU_Total2.insert(IECU_Total2.end(), Tx_IECU_2.begin(), Tx_IECU_2.end());
	IECU_Total2.insert(IECU_Total2.end(), Rx_IECU_2.begin(), Rx_IECU_2.end());

	for (int i_Messege1 = 0; i_Messege1 < IECU_Total1.size(); i_Messege1++)
	{
		int Num_Messege = 0;
		for (int i_Messege2 = 0; i_Messege2 < IECU_Total2.size(); i_Messege2++)
		{
			if (IECU_Total1[i_Messege1].name == IECU_Total2[i_Messege2].name)
			{
				Num_Messege++;
				for (int i_Signal1 = 0; i_Signal1 < IECU_Total1[i_Messege1].Signal.size(); i_Signal1++)
				{
					int Num_Signal = 0;
					for (int i_Signa2 = 0; i_Signa2 < IECU_Total2[i_Messege2].Signal.size(); i_Signa2++)
					{
						if (IECU_Total1[i_Messege1].Signal[i_Signal1].name == IECU_Total2[i_Messege2].Signal[i_Signa2].name)
						{
							Num_Signal++;
							break;
						}
					}
					if (Num_Signal == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("%s 中%s 信号在 %s 中没有，ID：%s\n", DBC1_name, IECU_Total1[i_Messege1].Signal[i_Signal1].name.c_str(), DBC2_name, IECU_Total1[i_Messege1].ID.c_str());
					}
				}
				break;
			}
		}
		if (Num_Messege == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 中%s 报文在 %s 中没有，ID：%s\n", DBC1_name, IECU_Total1[i_Messege1].name.c_str(), DBC2_name, IECU_Total1[i_Messege1].ID.c_str());
		}
	}
	
	for (int j_Messege2 = 0; j_Messege2 < IECU_Total2.size(); j_Messege2++)
	{
		int Num_Messege = 0;
		for (int j_Messege1 = 0; j_Messege1 < IECU_Total1.size(); j_Messege1++)
		{
			if (IECU_Total2[j_Messege2].name == IECU_Total1[j_Messege1].name)
			{
				Num_Messege++;
				for (int j_Signal2 = 0; j_Signal2 < IECU_Total2[j_Messege2].Signal.size(); j_Signal2++)
				{
					int Num_Signal = 0;
					for (int j_Signa1 = 0; j_Signa1 < IECU_Total1[j_Messege1].Signal.size(); j_Signa1++)
					{
						if (IECU_Total2[j_Messege2].Signal[j_Signal2].name == IECU_Total1[j_Messege1].Signal[j_Signa1].name)
						{
							Num_Signal++;
							break;
						}
					}
					if (Num_Signal == 0)
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
						printf("%s 中%s 信号在 %s 中没有，ID：%s\n", DBC2_name, IECU_Total2[j_Messege2].Signal[j_Signal2].name.c_str(), DBC1_name, IECU_Total2[j_Messege2].ID.c_str());
					}
				}
				break;
			}
		}
		if (Num_Messege == 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			printf("%s 中%s 报文在 %s 中没有，ID：%s\n", DBC2_name, IECU_Total2[j_Messege2].name.c_str(), DBC1_name, IECU_Total2[j_Messege2].ID.c_str());
		}
	}
	
}



/*****************************        FUNC: DBC读取         *******************************/
string Read_Get_DBC(char *filename_DBC)
{	
	char DBC_buf[1000] = { 0 };
	string DBC_str;
	FILE *fp_DBC = NULL;
	fp_DBC = fopen(filename_DBC, "r");
	if (fp_DBC == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("DBC打开失败！！\n");
		goto END;
	}
	fgets(DBC_buf, sizeof(DBC_buf), fp_DBC);
	while (!feof(fp_DBC))
	{
		DBC_str = DBC_str.append(DBC_buf);
		fgets(DBC_buf, sizeof(DBC_buf), fp_DBC);
	}
	fclose(fp_DBC);
	//printf("DBC_str =\n %s\n", DBC_str.c_str());

END:
	return DBC_str;
}


/*****************************         FUNC: DBC解析         *******************************/

/*---------------------------     得到完整全部的Messege信息     ---------------------------*/
vector<Messege> DBC_Extract(string DBC_str, vector<Messege> messege_vector)
{
	Messege messege; //存放提取出来的所有Messege
	Signal_X Signal; // 存放各Signal的属性信息
	vector<string> messege_buf, signal_buf;  // 接收读取到的属性信息
	
	string BO_ = "\nBO_ ", SG_ = "\n SG_ ";
	string str_messege, str_signal;  //临时存放读取到的属性信息

	int Messege_num = 0,
		i = 0,
		j = 0,
		m = 0,
		n = 0,
		i_find_Messege = 0,
		i_find_Signal = 0,
		position_find_Messege = 0, 
		position_find_Signal = 0,
		position_find_Cycle = 0,
		position_find_Sendtype = 0;

	bool flag_find_Messege = true, 
		 flag_find_Signal = true, 
		 flag_find_Cycle = true,
		 flag_find_Sendtype = true;

	/*-------------------------------------找Messege--------------------------------------*/
	while (flag_find_Messege)
	{
		if ((position_find_Messege = DBC_str.find(BO_, position_find_Messege)) != string::npos)
		{
			//Messege_num++;  //包含无用Messege在内的总个数
			for (i_find_Messege = position_find_Messege + BO_.length(); i_find_Messege < DBC_str.length(); i_find_Messege++)
			{
				if (DBC_str[i_find_Messege] == '\n')
				{
					messege_buf.push_back(str_messege);

					messege.position = i_find_Messege;
					messege.ID = messege_buf[0];
 					messege.name = messege_buf[1];
 					messege.DLC = messege_buf[3];
 					messege.transmit = messege_buf[4];

					messege_vector.push_back(messege);
					str_messege.clear();
					messege_buf.clear();
					break;
				} 
				else
				{
					if (DBC_str[i_find_Messege] == ' ' || DBC_str[i_find_Messege] == ':')
					{
						messege_buf.push_back(str_messege);
						str_messege.clear();
					}
					else
					{
						str_messege.push_back(DBC_str[i_find_Messege]);
					}
				}
			}
			position_find_Messege++;
		} 
		else
		{
			//printf("=====================Messege没找到，将会报Vector拷贝超出地址错误=====================\n");
			flag_find_Messege = false;
		}
	}

	/*-------------------------------删除DBC中的无用Messege-------------------------------*/
	for (vector<Messege>::iterator it_trash = messege_vector.begin(); it_trash < messege_vector.end(); it_trash++)
	{
		if ((*it_trash).name == "VECTOR__INDEPENDENT_SIG_MSG")
		{
			it_trash = messege_vector.erase(it_trash);
		}
	}

	/*-------------------------------------找Signal---------------------------------------*/
	for (i = 0; i < (messege_vector.size()-1);i++)
	{
		position_find_Signal = messege_vector[i].position;
		while (position_find_Signal < messege_vector[i + 1].position)//利用之前找到的每一个Messege开始的位置，在进行Signal解读时，规定其遍历地址最大不超过下一个Messege开始的位置，这样将其成功限定在当前Messege中，注意：这样会使最后一个Messege的Signal无法读到，可在后面单独解析添加
		{
			if ((position_find_Signal = DBC_str.find(SG_, position_find_Signal)) != string::npos)
			{
					for (j = position_find_Signal + SG_.length(); j <= messege_vector[i + 1].position; j++)
					{
						if (DBC_str[j] == '\n')
						{
							signal_buf.push_back(str_signal);

							Signal.name = signal_buf[0];
							Signal.starbit = signal_buf[3];
							Signal.length = signal_buf[4];
							Signal.valuetype = signal_buf[6];
							Signal.factor = signal_buf[8];
							Signal.offset = signal_buf[9];
							Signal.minimum = signal_buf[12];
							Signal.maximum = signal_buf[13];
							Signal.unit = signal_buf[16];

							if (signal_buf.size() == 19)
							{
								Signal.recieve.push_back(signal_buf[18]);
								//printf("*********************************Signal.recieve[0]的值为：%s\n", Signal.recieve[0].c_str());
							}
							else if (signal_buf.size() > 19)
							{
								for (m = 1; m <= (signal_buf.size() - 19); m++)
								{
									Signal.recieve.push_back(signal_buf[18 + m]);
								}
							}

							messege_vector[i].Signal.push_back(Signal);

							Signal.recieve.clear();
							str_signal.clear();
							signal_buf.clear();
							break;
						}
						else
						{
							if (DBC_str[j] == ' ' ||
								DBC_str[j] == ':' ||
								DBC_str[j] == '|' ||
								DBC_str[j] == '@' ||
								(DBC_str[j] == '0'&&DBC_str[j + 1] == '+') ||
								(DBC_str[j] == '0'&&DBC_str[j + 1] == '-') ||
								(DBC_str[j] == '1'&&DBC_str[j + 1] == '+') ||
								(DBC_str[j] == '1'&&DBC_str[j + 1] == '-') ||
								DBC_str[j] == '(' ||
								DBC_str[j] == ',' ||
								DBC_str[j] == ')' ||
								DBC_str[j] == '[' ||
								DBC_str[j] == ']' ||
								DBC_str[j] == '"')
							{
								signal_buf.push_back(str_signal);
								str_signal.clear();
							}
							else
							{
								str_signal.push_back(DBC_str[j]);
							}
						}
					}
					position_find_Signal++;
					
			}
		}
	}

	/*----------------------最后一个Messege的Signal单独解析出来并加进去-------------------*/
	position_find_Signal = messege_vector[messege_vector.size()-1].position;
	while (flag_find_Signal)
	{
		if ((position_find_Signal = DBC_str.find(SG_, position_find_Signal)) != string::npos)
		{
			for (j = position_find_Signal + SG_.length(); j < DBC_str.length(); j++)
			{
				if (DBC_str[j] == '\n')
				{
					signal_buf.push_back(str_signal);

					Signal.name = signal_buf[0];
					Signal.starbit = signal_buf[3];
					Signal.length = signal_buf[4];
					Signal.valuetype = signal_buf[6];
					Signal.factor = signal_buf[8];
					Signal.offset = signal_buf[9];
					Signal.minimum = signal_buf[12];
					Signal.maximum = signal_buf[13];
					Signal.unit = signal_buf[16];
					if (signal_buf.size()==19)
					{
						Signal.recieve.push_back(signal_buf[18]);
					}
					else if (signal_buf.size() > 19)
					{
						for (m = 1; m <= (signal_buf.size() - 19); m++)
						{
							Signal.recieve.push_back(signal_buf[18+m]);
						}
					}

					messege_vector[messege_vector.size()-1].Signal.push_back(Signal);

					Signal.recieve.clear();
					str_signal.clear();
					signal_buf.clear();
					break;
				}
				else
				{
					if (DBC_str[j] == ' ' ||
						DBC_str[j] == ':' ||
						DBC_str[j] == '|' ||
						DBC_str[j] == '@' ||
						(DBC_str[j] == '0'&&DBC_str[j + 1] == '+') ||
						(DBC_str[j] == '0'&&DBC_str[j + 1] == '-') ||
						(DBC_str[j] == '1'&&DBC_str[j + 1] == '+') ||
						(DBC_str[j] == '1'&&DBC_str[j + 1] == '-') ||
						DBC_str[j] == '(' ||
						DBC_str[j] == ',' ||
						DBC_str[j] == ')' ||
						DBC_str[j] == '[' ||
						DBC_str[j] == ']' ||
						DBC_str[j] == '"')
					{
						signal_buf.push_back(str_signal);
						str_signal.clear();
					}
					else
					{
						str_signal.push_back(DBC_str[j]);
					}
				}
			}
			position_find_Signal++;
		}
		else
		{
			flag_find_Signal = false;
		}
	}

	/*--------------------------------找出Cycle并加进去--------------------------------*/
	for (int i_Messege_Cycle = 0; i_Messege_Cycle < messege_vector.size(); i_Messege_Cycle++)
	{
		string ID_Cycle = "BA_ \"GenMsgCycleTime\" BO_ " + messege_vector[i_Messege_Cycle].ID + ' ';
		//printf("ID_Cycle：%s\n", ID_Cycle.c_str());
		string Cycle;
		while (flag_find_Cycle)
		{
			if ((position_find_Cycle = DBC_str.find(ID_Cycle, position_find_Cycle)) != string::npos)
			{
				for (int i_Cycle = position_find_Cycle + ID_Cycle.length(); ; i_Cycle++)
				{
					if (DBC_str[i_Cycle] == ';')
					{
						//printf("Cycle:%s\n", Cycle.c_str());
						messege_vector[i_Messege_Cycle].cycle = Cycle;
						Cycle.clear();
						break;
					} 
					else
					{
						Cycle.push_back(DBC_str[i_Cycle]);
					}
				}
				position_find_Cycle++;
			}
			else
			{
				flag_find_Cycle = false;
			}
		}
		flag_find_Cycle = true;
		position_find_Cycle = 0;
	}

	/*--------------------------------找出Sendtype并加进去--------------------------------*/
	for (int i_Messege_Sendtype = 0; i_Messege_Sendtype < messege_vector.size(); i_Messege_Sendtype++)
	{
		string ID_Sendtype = "BA_ \"GenMsgSendType\" BO_ " + messege_vector[i_Messege_Sendtype].ID + ' ';
		//printf("ID_Cycle：%s\n", ID_Cycle.c_str());
		string Sendtype;
		while (flag_find_Sendtype)
		{
			if ((position_find_Sendtype = DBC_str.find(ID_Sendtype, position_find_Sendtype)) != string::npos)
			{
				for (int i_Sendtype = position_find_Sendtype + ID_Sendtype.length();; i_Sendtype++)
				{
					if (DBC_str[i_Sendtype] == ';')
					{
						//printf("Cycle:%s\n", Cycle.c_str());
						messege_vector[i_Messege_Sendtype].sendtype = Sendtype;
						Sendtype.clear();
						break;
					}
					else
					{
						Sendtype.push_back(DBC_str[i_Sendtype]); 
					}
				}
				position_find_Sendtype++;
			}
			else
			{
				flag_find_Sendtype = false;
			}
		}
		flag_find_Sendtype = true;
		position_find_Sendtype = 0;
	}


	return messege_vector;
}
void Printf_MessegeVector(vector<Messege> messege_vector)
{
	printf("Messege的个数为:%d\n", messege_vector.size());
	for (size_t i_find_messege = 0; i_find_messege < messege_vector.size(); i_find_messege++)
	{
		if (!messege_vector.empty())
		{
			printf("第%d个messege信息为：位置：%d ID：%s name：%s  DLC：%s  Cycle：%s  transmit：%s \n", i_find_messege + 1,
				messege_vector[i_find_messege].position,
				messege_vector[i_find_messege].ID.c_str(),
				messege_vector[i_find_messege].name.c_str(),
				messege_vector[i_find_messege].DLC.c_str(),
				messege_vector[i_find_messege].cycle.c_str(),
				messege_vector[i_find_messege].transmit.c_str());
			for (int k = 0; k < messege_vector[i_find_messege].Signal.size(); k++)
			{
				if (!messege_vector[i_find_messege].Signal.empty())
				{
					printf("	第%d个Signal信息为： name:%s  starbit:%s  length:%s  valuetype:%s  factor:%s  offset:%s  minimum:%s  maximum:%s  unit:%s  recieve:%s\n",
						k + 1,
						messege_vector[i_find_messege].Signal[k].name.c_str(),
						messege_vector[i_find_messege].Signal[k].starbit.c_str(),
						messege_vector[i_find_messege].Signal[k].length.c_str(),
						messege_vector[i_find_messege].Signal[k].valuetype.c_str(),
						messege_vector[i_find_messege].Signal[k].factor.c_str(),
						messege_vector[i_find_messege].Signal[k].offset.c_str(),
						messege_vector[i_find_messege].Signal[k].minimum.c_str(),
						messege_vector[i_find_messege].Signal[k].maximum.c_str(),
						messege_vector[i_find_messege].Signal[k].unit.c_str(),
						messege_vector[i_find_messege].Signal[k].recieve[0].c_str());
				}
				else
				{
					printf("========================messege_vector[%d].Signal是空的！！！！！！！！！========================\n", i_find_messege);
				}
			}
		}
		else
		{
			printf("========================messege_vector是空的！！！！！！！！！========================\n");
		}
	}

}

/*---------------------------     TX、RX，同时检查BO_TX_BU_     ---------------------------*/
vector<Messege> Tx_IECU_Get(string DBC_str, string Node, vector<Messege> messege_vector, vector<Messege> Tx_IECU)
{
	vector<string> BO_TX_BU_vector;
	string BO_TX_BU_ = "BO_TX_BU_ ";
	string BO_TX_BU_tmp, BO_TX_BU_ID, BO_TX_BU_TX1, BO_TX_BU_TX2;

	bool flag_find_BO_TX_BU_ = true;
	int i_find_BO_TX_BU_ = 0;

	for (int i = 0; i < messege_vector.size(); i++)
	{
		if (messege_vector[i].transmit == Node)
		{
			Tx_IECU.push_back(messege_vector[i]);
		}
	}
	while (flag_find_BO_TX_BU_)
	{
		if ((i_find_BO_TX_BU_= DBC_str.find(BO_TX_BU_,i_find_BO_TX_BU_))!=string::npos)
		{
			for (int k = i_find_BO_TX_BU_+BO_TX_BU_.length(); k < DBC_str.length();k++)
			{
				if (DBC_str[k]=='\n')
				{
					BO_TX_BU_ID = BO_TX_BU_vector[0];
					BO_TX_BU_TX1 = BO_TX_BU_vector[3];
					BO_TX_BU_TX2 = BO_TX_BU_vector[4];

					BO_TX_BU_vector.clear();
					BO_TX_BU_tmp.clear();
					break;
				} 
				else
				{
					if (DBC_str[k] == ' ' ||
						DBC_str[k] == ':' ||
						DBC_str[k] == ',' ||
						DBC_str[k] == ';')
					{
						BO_TX_BU_vector.push_back(BO_TX_BU_tmp);
						BO_TX_BU_tmp.clear();
					}
					else
					{
						BO_TX_BU_tmp.push_back(DBC_str[k]);
					}
				}


			}

			if (BO_TX_BU_TX1 == Node || BO_TX_BU_TX2 == Node)
			{
				int n = 0;
				for (int m = 0; m < Tx_IECU.size(); m++)
				{
					if (Tx_IECU[m].ID == BO_TX_BU_ID)
					{
						n++;
					}
				}
				if (n!=0)
				{
					goto END;
				} 
				else
				{
					for (int q = 0; q < messege_vector.size();q++)
					{
						if (messege_vector[q].ID==BO_TX_BU_ID)
						{
							Tx_IECU.push_back(messege_vector[q]);
							Tx_IECU[Tx_IECU.size() - 1].transmit = Node;
						}
					}
				}
			}
END:
			i_find_BO_TX_BU_++;
		} 
		else
		{
			flag_find_BO_TX_BU_ = false;
		}
	}
	return Tx_IECU;
}
void Printf_TxIECU(vector<Messege> Tx_IECU)
{
	printf("Tx_Messege的个数为:%d\n", Tx_IECU.size());
	for (size_t i_find_messege = 0; i_find_messege < Tx_IECU.size(); i_find_messege++)
	{
		if (!Tx_IECU.empty())
		{
			printf("第%d个messege信息为：位置：%d ID：%s name：%s  DLC：%s  Cycle：%s  transmit：%s \n", i_find_messege + 1,
				Tx_IECU[i_find_messege].position,
				Tx_IECU[i_find_messege].ID.c_str(),
				Tx_IECU[i_find_messege].name.c_str(),
				Tx_IECU[i_find_messege].DLC.c_str(),
				Tx_IECU[i_find_messege].cycle.c_str(),
				Tx_IECU[i_find_messege].transmit.c_str());
			for (int k = 0; k < Tx_IECU[i_find_messege].Signal.size(); k++)
			{
				if (!Tx_IECU[i_find_messege].Signal.empty())
				{
					printf("	第%d个Signal信息为： name:%s  starbit:%s  length:%s  valuetype:%s  factor:%s  offset:%s  minimum:%s  maximum:%s  unit:%s  recieve:%s\n",
						k + 1,
						Tx_IECU[i_find_messege].Signal[k].name.c_str(),
						Tx_IECU[i_find_messege].Signal[k].starbit.c_str(),
						Tx_IECU[i_find_messege].Signal[k].length.c_str(),
						Tx_IECU[i_find_messege].Signal[k].valuetype.c_str(),
						Tx_IECU[i_find_messege].Signal[k].factor.c_str(),
						Tx_IECU[i_find_messege].Signal[k].offset.c_str(),
						Tx_IECU[i_find_messege].Signal[k].minimum.c_str(),
						Tx_IECU[i_find_messege].Signal[k].maximum.c_str(),
						Tx_IECU[i_find_messege].Signal[k].unit.c_str(),
						Tx_IECU[i_find_messege].Signal[k].recieve[0].c_str());
				}
				else
				{
					printf("========================Tx_IECU[%d].Signal是空的！！！！！！！！！========================\n", i_find_messege);
				}
			}
		}
		else
		{
			printf("========================Tx_IECU是空的！！！！！！！！！========================\n");
		}
	}

}

vector<Messege> Rx_IECU_Get(string DBC_str, string Node, vector<Messege> messege_vector, vector<Messege> Rx_IECU)
{
	vector<Signal_X> RX_Signal;
	for (int i = 0; i < messege_vector.size(); i++)
	{
		int m = 0;
		for (int j = 0; j < messege_vector[i].Signal.size(); j++)
		{
			for (int k = 0; k < messege_vector[i].Signal[j].recieve.size(); k++)
			{
				if (messege_vector[i].Signal[j].recieve[k] == Node)
				{
					m++;
					RX_Signal.push_back(messege_vector[i].Signal[j]);
				}
			}
		}
		if (m != 0)
		{
			Rx_IECU.push_back(messege_vector[i]);
			Rx_IECU[Rx_IECU.size() - 1].Signal.clear();
			Rx_IECU[Rx_IECU.size() - 1].Signal = RX_Signal;
			RX_Signal.clear();
		}
	}
	
	return Rx_IECU;
}
void Printf_RxIECU(vector<Messege> Rx_IECU)
{
	printf("Rx_Messege的个数为:%d\n", Rx_IECU.size());
	for (size_t i_find_messege = 0; i_find_messege < Rx_IECU.size(); i_find_messege++)
	{
		if (!Rx_IECU.empty())
		{
			printf("第%d个messege信息为：位置：%d ID：%s name：%s  DLC：%s  Cycle：%s  transmit：%s \n", i_find_messege + 1,
				Rx_IECU[i_find_messege].position,
				Rx_IECU[i_find_messege].ID.c_str(),
				Rx_IECU[i_find_messege].name.c_str(),
				Rx_IECU[i_find_messege].DLC.c_str(),
				Rx_IECU[i_find_messege].cycle.c_str(),
				Rx_IECU[i_find_messege].transmit.c_str());
			for (int k = 0; k < Rx_IECU[i_find_messege].Signal.size(); k++)
			{
				if (!Rx_IECU[i_find_messege].Signal.empty())
				{
					printf("	第%d个Signal信息为： name:%s  starbit:%s  length:%s  valuetype:%s  factor:%s  offset:%s  minimum:%s  maximum:%s  unit:%s  recieve:%s\n",
						k + 1,
						Rx_IECU[i_find_messege].Signal[k].name.c_str(),
						Rx_IECU[i_find_messege].Signal[k].starbit.c_str(),
						Rx_IECU[i_find_messege].Signal[k].length.c_str(),
						Rx_IECU[i_find_messege].Signal[k].valuetype.c_str(),
						Rx_IECU[i_find_messege].Signal[k].factor.c_str(),
						Rx_IECU[i_find_messege].Signal[k].offset.c_str(),
						Rx_IECU[i_find_messege].Signal[k].minimum.c_str(),
						Rx_IECU[i_find_messege].Signal[k].maximum.c_str(),
						Rx_IECU[i_find_messege].Signal[k].unit.c_str(),
						Rx_IECU[i_find_messege].Signal[k].recieve[0].c_str());
				}
				else
				{
					printf("========================Rx_IECU[%d].Signal是空的！！！！！！！！！========================\n", i_find_messege);
				}
			}
		}
		else
		{
			printf("========================Rx_IECU是空的！！！！！！！！！========================\n");
		}
	}

}


void DBC_ReadANDCheck(int file_NUM, vector<Filename> FILE, string Node, string DBC_str_TEMP, string DBC_str, vector<Messege> messege_vector_tmp, vector<Messege> messege_vector, vector<Messege> Tx_IECU_tmp, vector<Messege> Rx_IECU_tmp, vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU)
{
	for (int j = 0; j < file_NUM; j++)
	{
		DBC_Check_BA_DEF_BO(FILE[j].file_path);

		DBC_str_TEMP = Read_Get_DBC(FILE[j].file_path);
		messege_vector_tmp = DBC_Extract(DBC_str_TEMP, messege_vector_tmp);
		Tx_IECU_tmp = Tx_IECU_Get(DBC_str_TEMP, Node, messege_vector_tmp, Tx_IECU_tmp);
		Rx_IECU_tmp = Rx_IECU_Get(DBC_str_TEMP, Node, messege_vector_tmp, Rx_IECU_tmp);

		DBC_Check_SameDBC(Node, messege_vector_tmp, Tx_IECU_tmp, Rx_IECU_tmp);
		DBC_Check_Cycle0(Tx_IECU_tmp, Rx_IECU_tmp);
		DBC_Check_Sendtype(Tx_IECU_tmp, Rx_IECU_tmp);
		DBC_Check_DLC(Tx_IECU_tmp, Rx_IECU_tmp);
		DBC_Check_Longname(DBC_str_TEMP, Tx_IECU_tmp, Rx_IECU_tmp);
		DBC_Check_Max_Min(Tx_IECU_tmp, Rx_IECU_tmp);

		DBC_str.append(DBC_str_TEMP);
		messege_vector.insert(messege_vector.end(), messege_vector_tmp.begin(), messege_vector_tmp.end());
		(*Tx_IECU).insert((*Tx_IECU).end(), Tx_IECU_tmp.begin(), Tx_IECU_tmp.end());
		(*Rx_IECU).insert((*Rx_IECU).end(), Rx_IECU_tmp.begin(), Rx_IECU_tmp.end());

		DBC_str_TEMP.clear();
		messege_vector_tmp.clear();
		Tx_IECU_tmp.clear();
		Rx_IECU_tmp.clear();
	}
		DBC_Check_DiffDBC(Tx_IECU, Rx_IECU);
}

void DBC_Extract_All(int file_NUM, vector<Filename> FILE, string Node, string DBC_str_TEMP, string DBC_str, vector<Messege> messege_vector_tmp, vector<Messege> messege_vector, vector<Messege> Tx_IECU_tmp, vector<Messege> Rx_IECU_tmp, vector<Messege> *Tx_IECU, vector<Messege> *Rx_IECU)
{
	for (int j = 0; j < file_NUM; j++)
	{
		DBC_str_TEMP = Read_Get_DBC(FILE[j].file_path);
		messege_vector_tmp = DBC_Extract(DBC_str_TEMP, messege_vector_tmp);
		Tx_IECU_tmp = Tx_IECU_Get(DBC_str_TEMP, Node, messege_vector_tmp, Tx_IECU_tmp);
		Rx_IECU_tmp = Rx_IECU_Get(DBC_str_TEMP, Node, messege_vector_tmp, Rx_IECU_tmp);

		DBC_str.append(DBC_str_TEMP);
		messege_vector.insert(messege_vector.end(), messege_vector_tmp.begin(), messege_vector_tmp.end());
		(*Tx_IECU).insert((*Tx_IECU).end(), Tx_IECU_tmp.begin(), Tx_IECU_tmp.end());
		(*Rx_IECU).insert((*Rx_IECU).end(), Rx_IECU_tmp.begin(), Rx_IECU_tmp.end());

		DBC_str_TEMP.clear();
		messege_vector_tmp.clear();
		Tx_IECU_tmp.clear();
		Rx_IECU_tmp.clear();
	}
}
