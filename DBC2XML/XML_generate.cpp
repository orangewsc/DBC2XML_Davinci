
#include "include.h"


/*------------------                 AUTOSAR_Platform                 -------------------*/
string XML_Generate_Head(char *file_Template_Head)
{
	char buf[500];
	
	string XML_str, XML_AUTOSAR_Platform;
	FILE *fp_Template_Head, *fp_XML = NULL;

	fp_Template_Head = fopen(file_Template_Head, "r");
	
	if (fp_Template_Head == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("Head模板打开失败!\n");
		return 0;
	}

	fgets(buf, sizeof(buf), fp_Template_Head);
	while (!(feof(fp_Template_Head)))
	{
		XML_AUTOSAR_Platform.append(buf);
		fgets(buf, sizeof(buf), fp_Template_Head);
	}
	fclose(fp_Template_Head);

	XML_str.append(XML_AUTOSAR_Platform);
	return XML_str;
}

/*------------------                 ComponentTypes                 -------------------*/
string XML_Generate_ComponentTypes(string CtApVMS, string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	XML_str += "    <AR-PACKAGE>\n\
      <SHORT-NAME>ComponentTypes</SHORT-NAME>\n\
      <ELEMENTS>\n\
        <APPLICATION-SW-COMPONENT-TYPE UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
          <SHORT-NAME>"+CtApVMS+"</SHORT-NAME>\n\
          <PORTS>\n"; //第三层-1

	/*------------------                 Busout                 -------------------*/
	XML_str += "            <P-PORT-PROTOTYPE UUID=\"07AC0B9A-FCC1-46A1-9041-97753C1EA36F\">\n\
              <SHORT-NAME>DPpBusOut</SHORT-NAME>\n\
              <PROVIDED-COM-SPECS>\n";
	for (int i_messege_Busout = 0; i_messege_Busout < Tx_IECU.size(); i_messege_Busout++)
	{
		for (int i_signal_Busout = 0; i_signal_Busout < Tx_IECU[i_messege_Busout].Signal.size(); i_signal_Busout++)
		{
			int legnth_Busout = atoi(Tx_IECU[i_messege_Busout].Signal[i_signal_Busout].length.c_str());
			if (legnth_Busout<33)
			{
				XML_str += "                <NONQUEUED-SENDER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusOut/"+Tx_IECU[i_messege_Busout].Signal[i_signal_Busout].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <INIT-VALUE>\n\
                    <CONSTANT-REFERENCE>\n\
                      <CONSTANT-REF DEST=\"CONSTANT-SPECIFICATION\">/DaVinci/InitValueSpec_Reserved</CONSTANT-REF>\n\
                    </CONSTANT-REFERENCE>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-SENDER-COM-SPEC>\n";
			}
			else
			{
				XML_str += "                <NONQUEUED-SENDER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusOut/"+Tx_IECU[i_messege_Busout].Signal[i_signal_Busout].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <INIT-VALUE>\n\
                    <ARRAY-VALUE-SPECIFICATION>\n\
                      <ELEMENTS>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
				 		<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
						<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
						<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                      </ELEMENTS>\n\
                    </ARRAY-VALUE-SPECIFICATION>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-SENDER-COM-SPEC>\n";
			}
		}
	}
	XML_str += "              </PROVIDED-COM-SPECS>\n\
              <PROVIDED-INTERFACE-TREF DEST=\"SENDER-RECEIVER-INTERFACE\">/PortInterfaces/DPiBusOut</PROVIDED-INTERFACE-TREF>\n\
            </P-PORT-PROTOTYPE>\n";
	/*-----------------------------------------------------------------------------*/

	for (int i_port_Tx = 0; i_port_Tx < Tx_IECU.size();i_port_Tx++)
	{
		XML_str += "            <P-PORT-PROTOTYPE UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
              <SHORT-NAME>PpVMS_" + Tx_IECU[i_port_Tx].name + "_" +Tx_IECU[i_port_Tx].cycle+"ms</SHORT-NAME>\n"+
			  "              <PROVIDED-COM-SPECS>\n\
                <NONQUEUED-SENDER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/PiVMS_"+ Tx_IECU[i_port_Tx].name + "_" +Tx_IECU[i_port_Tx].cycle+"ms/De"+Tx_IECU[i_port_Tx].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <INIT-VALUE>\n\
                    <CONSTANT-REFERENCE>\n\
                      <CONSTANT-REF DEST=\"CONSTANT-SPECIFICATION\">/Constants/C_RECORD_"+Tx_IECU[i_port_Tx].name+"</CONSTANT-REF>\n"+
					  "                    </CONSTANT-REFERENCE>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-SENDER-COM-SPEC>\n\
              </PROVIDED-COM-SPECS>\n\
              <PROVIDED-INTERFACE-TREF DEST=\"SENDER-RECEIVER-INTERFACE\">/PortInterfaces/PiVMS_"+ Tx_IECU[i_port_Tx].name + "_" +Tx_IECU[i_port_Tx].cycle+"ms</PROVIDED-INTERFACE-TREF>\n"+
			  "            </P-PORT-PROTOTYPE>\n";
	}

	/*------------------                 Busin                 -------------------*/
	XML_str += "            <R-PORT-PROTOTYPE UUID=\"E229523B-4BB1-46DF-91DD-FC1CCEBA761F\">\n\
              <SHORT-NAME>DPpBusIn</SHORT-NAME>\n\
              <REQUIRED-COM-SPECS>\n";
	for (int i_messege_Busin = 0; i_messege_Busin < Rx_IECU.size(); i_messege_Busin++)
	{
		for (int i_signal_Busin = 0; i_signal_Busin < Rx_IECU[i_messege_Busin].Signal.size(); i_signal_Busin++)
		{
			int length_Busin = atoi(Rx_IECU[i_messege_Busin].Signal[i_signal_Busin].length.c_str());
			if (length_Busin<33)
			{
				XML_str += "                <NONQUEUED-RECEIVER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusIn/"+Rx_IECU[i_messege_Busin].Signal[i_signal_Busin].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <ALIVE-TIMEOUT>0</ALIVE-TIMEOUT>\n\
                  <ENABLE-UPDATE>false</ENABLE-UPDATE>\n\
                  <FILTER>\n\
                    <DATA-FILTER-TYPE>ALWAYS</DATA-FILTER-TYPE>\n\
                  </FILTER>\n\
                  <HANDLE-NEVER-RECEIVED>false</HANDLE-NEVER-RECEIVED>\n\
                  <INIT-VALUE>\n\
                    <CONSTANT-REFERENCE>\n\
                      <CONSTANT-REF DEST=\"CONSTANT-SPECIFICATION\">/DaVinci/InitValueSpec_Reserved</CONSTANT-REF>\n\
                    </CONSTANT-REFERENCE>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-RECEIVER-COM-SPEC>\n";
			}
			else
			{
				XML_str += "                <NONQUEUED-RECEIVER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusIn/"+Rx_IECU[i_messege_Busin].Signal[i_signal_Busin].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <ALIVE-TIMEOUT>0</ALIVE-TIMEOUT>\n\
                  <ENABLE-UPDATE>false</ENABLE-UPDATE>\n\
                  <FILTER>\n\
                    <DATA-FILTER-TYPE>ALWAYS</DATA-FILTER-TYPE>\n\
                  </FILTER>\n\
                  <HANDLE-NEVER-RECEIVED>false</HANDLE-NEVER-RECEIVED>\n\
                  <INIT-VALUE>\n\
                    <ARRAY-VALUE-SPECIFICATION>\n\
                      <ELEMENTS>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
						<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
						<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
						<NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                        <NUMERICAL-VALUE-SPECIFICATION>\n\
                          <VALUE>0</VALUE>\n\
                        </NUMERICAL-VALUE-SPECIFICATION>\n\
                      </ELEMENTS>\n\
                    </ARRAY-VALUE-SPECIFICATION>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-RECEIVER-COM-SPEC>\n";
			}
		}
	}
	XML_str += "              </REQUIRED-COM-SPECS>\n\
              <REQUIRED-INTERFACE-TREF DEST=\"SENDER-RECEIVER-INTERFACE\">/PortInterfaces/DPiBusIn</REQUIRED-INTERFACE-TREF>\n\
            </R-PORT-PROTOTYPE>\n";
	/*-----------------------------------------------------------------------------*/

	for (int i_port_Rx = 0; i_port_Rx < Rx_IECU.size(); i_port_Rx++)
	{
		XML_str += "            <R-PORT-PROTOTYPE UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
              <SHORT-NAME>PpCom_"+Rx_IECU[i_port_Rx].name + "_" + Rx_IECU[i_port_Rx].cycle + "ms</SHORT-NAME>\n"
			  +"              <REQUIRED-COM-SPECS>\n\
                <NONQUEUED-RECEIVER-COM-SPEC>\n\
                  <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/PiCom_"+ Rx_IECU[i_port_Rx].name + "_" + Rx_IECU[i_port_Rx].cycle+"ms/De" + Rx_IECU[i_port_Rx].name+"</DATA-ELEMENT-REF>\n"+
				  "                  <USES-END-TO-END-PROTECTION>false</USES-END-TO-END-PROTECTION>\n\
                  <ALIVE-TIMEOUT>0</ALIVE-TIMEOUT>\n\
                  <ENABLE-UPDATE>false</ENABLE-UPDATE>\n\
                  <FILTER>\n\
                    <DATA-FILTER-TYPE>ALWAYS</DATA-FILTER-TYPE>\n\
                  </FILTER>\n\
                  <HANDLE-NEVER-RECEIVED>false</HANDLE-NEVER-RECEIVED>\n\
                  <INIT-VALUE>\n\
                    <CONSTANT-REFERENCE>\n\
                      <CONSTANT-REF DEST=\"CONSTANT-SPECIFICATION\">/Constants/C_RECORD_"+ Rx_IECU[i_port_Rx].name + "</CONSTANT-REF>\n"+
					  "                    </CONSTANT-REFERENCE>\n\
                  </INIT-VALUE>\n\
                </NONQUEUED-RECEIVER-COM-SPEC>\n\
              </REQUIRED-COM-SPECS>\n\
              <REQUIRED-INTERFACE-TREF DEST=\"SENDER-RECEIVER-INTERFACE\">/PortInterfaces/PiCom_"+ Rx_IECU[i_port_Rx].name + "_" + Rx_IECU[i_port_Rx].cycle + "ms</REQUIRED-INTERFACE-TREF>\n"+
			  "            </R-PORT-PROTOTYPE>\n";
	}

	XML_str += "          </PORTS>\n\
          <INTERNAL-BEHAVIORS>\n\
            <SWC-INTERNAL-BEHAVIOR UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
              <SHORT-NAME>"+ CtApVMS + "_InternalBehavior</SHORT-NAME>\n\
              <SUPPORTS-MULTIPLE-INSTANTIATION>false</SUPPORTS-MULTIPLE-INSTANTIATION>\n\
            </SWC-INTERNAL-BEHAVIOR>\n\
          </INTERNAL-BEHAVIORS>\n\
        </APPLICATION-SW-COMPONENT-TYPE>\n\
        <SWC-IMPLEMENTATION UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
          <SHORT-NAME>" + CtApVMS + "_Implementation</SHORT-NAME>\n\
          <CODE-DESCRIPTORS>\n\
            <CODE>\n\
              <SHORT-NAME>Default</SHORT-NAME>\n\
              <ARTIFACT-DESCRIPTORS>\n\
                <AUTOSAR-ENGINEERING-OBJECT>\n\
                  <SHORT-LABEL>Default</SHORT-LABEL>\n\
                  <CATEGORY>SWSRC</CATEGORY>\n\
                </AUTOSAR-ENGINEERING-OBJECT>\n\
              </ARTIFACT-DESCRIPTORS>\n\
            </CODE>\n\
          </CODE-DESCRIPTORS>\n\
		  <BEHAVIOR-REF DEST=\"SWC-INTERNAL-BEHAVIOR\">/ComponentTypes/"+ CtApVMS + "/" + CtApVMS + "_InternalBehavior</BEHAVIOR-REF>\n\
        </SWC-IMPLEMENTATION>\n\
      </ELEMENTS>\n\
    </AR-PACKAGE>\n";

	return XML_str;
}
	
/*------------------                   Constants                     -------------------*/
string XML_Generate_Constants(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	vector<Messege> Total_Messege;
	Total_Messege.insert(Total_Messege.end(), Tx_IECU.begin(), Tx_IECU.end());
	Total_Messege.insert(Total_Messege.end(), Rx_IECU.begin(), Rx_IECU.end());

	XML_str += "    <AR-PACKAGE>\n\
      <SHORT-NAME>Constants</SHORT-NAME>\n\
      <ELEMENTS>\n";

	for (int i_messege = 0; i_messege < Total_Messege.size(); i_messege++)
	{
		XML_str += "        <CONSTANT-SPECIFICATION UUID=\"6B659368-4A04-47EE-9D2B-34265A8E462B\">\n\
          <SHORT-NAME>C_RECORD_"+Total_Messege[i_messege].name+"</SHORT-NAME>\n"+
		  "          <VALUE-SPEC>\n\
            <RECORD-VALUE-SPECIFICATION>\n\
              <FIELDS>\n";
		for (int i_signal = 0; i_signal < Total_Messege[i_messege].Signal.size();i_signal++)
		{
			int length = atoi(Total_Messege[i_messege].Signal[i_signal].length.c_str());

			if (length<=32)
			{
				XML_str += "                <NUMERICAL-VALUE-SPECIFICATION>\n\
                  <SHORT-LABEL>"+Total_Messege[i_messege].Signal[i_signal].name+"</SHORT-LABEL>\n"+
				  "                  <VALUE>0</VALUE>\n\
                </NUMERICAL-VALUE-SPECIFICATION>\n";
			} 
			else 
			{
				XML_str += "                <ARRAY-VALUE-SPECIFICATION>\n\
                  <SHORT-LABEL>"+Total_Messege[i_messege].Signal[i_signal].name+"</SHORT-LABEL>\n"+
				  "                  <ELEMENTS>\n\
                    <NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
                    <NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
					<NUMERICAL-VALUE-SPECIFICATION>\n\
                      <VALUE>0</VALUE>\n\
                    </NUMERICAL-VALUE-SPECIFICATION>\n\
                  </ELEMENTS>\n\
                </ARRAY-VALUE-SPECIFICATION>\n";
			}
		}

	XML_str += "              </FIELDS>\n\
            </RECORD-VALUE-SPECIFICATION>\n\
          </VALUE-SPEC>\n\
        </CONSTANT-SPECIFICATION>\n";
	}

	XML_str += "      </ELEMENTS>\n\
    </AR-PACKAGE>\n";

	return XML_str;
}

/*------------------                   DataType                      -------------------*/
string XML_Generate_DataType(string XML_str, char *file_DataType)
{
	char buf[1000];
	string XML_DataType;
	FILE *fp_DataType = NULL;
	fp_DataType = fopen(file_DataType, "r");
	if (fp_DataType == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("DtaaType模板打开失败!\n");
	}
	fgets(buf, sizeof(buf), fp_DataType);
	while (!(feof(fp_DataType)))
	{
		XML_DataType.append(buf);
		fgets(buf, sizeof(buf), fp_DataType);
	}
	fclose(fp_DataType);
	XML_str.append(XML_DataType);
	return XML_str;
}

/*------------------                  DataTypes                      -------------------*/
string XML_Generate_DataTypes(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	vector<Messege> Total_Messege;
	Total_Messege.insert(Total_Messege.end(), Tx_IECU.begin(), Tx_IECU.end());
	Total_Messege.insert(Total_Messege.end(), Rx_IECU.begin(), Rx_IECU.end());

	XML_str += "    <AR-PACKAGE>\n\
      <SHORT-NAME>DataTypes</SHORT-NAME>\n\
      <ELEMENTS>\n";

	/*------------------                生成BusIn和BusOut的Dt                  -------------------*/
	for (int i_message_BusInOut = 0; i_message_BusInOut < Total_Messege.size(); i_message_BusInOut++)
	{
		for (int i_signal_BusInOut = 0; i_signal_BusInOut < Total_Messege[i_message_BusInOut].Signal.size(); i_signal_BusInOut++)
		{
			int length_Busin = atoi(Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].length.c_str());
			string ValueType_BusinOut = Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].valuetype.c_str();
			//double factor_Busin = atof(Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].factor.c_str());
			//double offest_Busin = atof(Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].offset.c_str());
			if (length_Busin<33)
			{
				XML_str += "        <IMPLEMENTATION-DATA-TYPE UUID=\"B4BFF8C9-F0DB-463D-A3A4-2176E4E59A52\">\n\
          <SHORT-NAME>Dt_"+Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].name+"</SHORT-NAME>\n"+
		  "          <CATEGORY>VALUE</CATEGORY>\n\
          <SW-DATA-DEF-PROPS>\n\
            <SW-DATA-DEF-PROPS-VARIANTS>\n\
              <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                <BASE-TYPE-REF DEST=\"SW-BASE-TYPE\">/DataType/";

				if (ValueType_BusinOut=="+")
				{
					if (0 < length_Busin && length_Busin < 2)
					{
						XML_str += "boolean";
					}
					else if (1 < length_Busin && length_Busin < 9)
					{
						XML_str += "uint8";
					}
					else if (8 < length_Busin && length_Busin < 17)
					{
						XML_str += "uint16";
					}
					else
					{
						XML_str += "uint32";
					}
				} 
				else if (ValueType_BusinOut == "-")
				{
					if (0 < length_Busin && length_Busin < 2)
					{
						XML_str += "boolean";
					}
					else if (1 < length_Busin && length_Busin < 9)
					{
						XML_str += "sint8";
					}
					else if (8 < length_Busin && length_Busin < 17)
					{
						XML_str += "sint16";
					}
					else
					{
						XML_str += "sint32";
					}
				}

			XML_str += "</BASE-TYPE-REF>\n\
                <SW-CALIBRATION-ACCESS>READ-ONLY</SW-CALIBRATION-ACCESS>\n\
              </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
            </SW-DATA-DEF-PROPS-VARIANTS>\n\
          </SW-DATA-DEF-PROPS>\n\
          <TYPE-EMITTER>RTE</TYPE-EMITTER>\n\
        </IMPLEMENTATION-DATA-TYPE>\n";	
			}
			else
			{
				XML_str += "        <IMPLEMENTATION-DATA-TYPE UUID=\"B4BFF8C9-F0DB-463D-A3A4-2176E4E59A52\">\n\
          <SHORT-NAME>Dt_"+Total_Messege[i_message_BusInOut].Signal[i_signal_BusInOut].name+"</SHORT-NAME>\n"+
		  "          <CATEGORY>ARRAY</CATEGORY>\n\
          <SW-DATA-DEF-PROPS>\n\
            <SW-DATA-DEF-PROPS-VARIANTS>\n\
              <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                <SW-CALIBRATION-ACCESS>READ-ONLY</SW-CALIBRATION-ACCESS>\n\
              </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
            </SW-DATA-DEF-PROPS-VARIANTS>\n\
          </SW-DATA-DEF-PROPS>\n\
          <SUB-ELEMENTS>\n\
            <IMPLEMENTATION-DATA-TYPE-ELEMENT>\n\
              <SHORT-NAME>Element</SHORT-NAME>\n\
              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <ARRAY-SIZE>8</ARRAY-SIZE>\n\
              <ARRAY-SIZE-SEMANTICS>FIXED-SIZE</ARRAY-SIZE-SEMANTICS>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";

				   XML_str += "uint8";

			   XML_str += "</IMPLEMENTATION-DATA-TYPE-REF>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n\
          </SUB-ELEMENTS>\n\
          <TYPE-EMITTER>RTE</TYPE-EMITTER>\n\
        </IMPLEMENTATION-DATA-TYPE>\n";
			}
		}
	}


	/*------------------               生成普通接口的Dt_RECORD               -------------------*/
	for (int i_messege = 0; i_messege < Total_Messege.size();i_messege++)
	{
		XML_str += "        <IMPLEMENTATION-DATA-TYPE UUID=\"B4BFF8C9-F0DB-463D-A3A4-2176E4E59A52\">\n\
          <SHORT-NAME>Dt_RECORD_"+Total_Messege[i_messege].name+"</SHORT-NAME>\n"+
		  "          <CATEGORY>STRUCTURE</CATEGORY>\n\
          <SW-DATA-DEF-PROPS>\n\
            <SW-DATA-DEF-PROPS-VARIANTS>\n\
              <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                <SW-CALIBRATION-ACCESS>READ-ONLY</SW-CALIBRATION-ACCESS>\n\
              </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
            </SW-DATA-DEF-PROPS-VARIANTS>\n\
          </SW-DATA-DEF-PROPS>\n\
          <SUB-ELEMENTS>\n";
		for (int i_signal = 0; i_signal < Total_Messege[i_messege].Signal.size();i_signal++)
		{
			int length = atoi(Total_Messege[i_messege].Signal[i_signal].length.c_str());
			double factor = atof(Total_Messege[i_messege].Signal[i_signal].factor.c_str());
			double offest = atof(Total_Messege[i_messege].Signal[i_signal].offset.c_str());
			string ValueType = Total_Messege[i_messege].Signal[i_signal].valuetype.c_str();

			if (length<33)
			{
			XML_str += "            <IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=\"CB574025-4D02-46F1-A243-5A845494FAA0\">\n\
              <SHORT-NAME>"+Total_Messege[i_messege].Signal[i_signal].name+"</SHORT-NAME>\n"+
			  "              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
				if ((factor - (int)factor) == 0 && (offest - (int)offest)==0)
				{
					if (ValueType=="-")
					{
						if (0 < length && length < 2)
						{
							XML_str += "boolean";
						}
						else if (1 < length && length < 9)
						{
							XML_str += "sint8";
						}
						else if (8 < length && length < 17)
						{
							XML_str += "sint16";
						}
						else
						{
							XML_str += "sint32";
						}
					} 
					else if (ValueType == "+")
					{
						if (0 < length && length < 2)
						{
							XML_str += "boolean";
						}
						else if (1 < length && length < 9)
						{
							if (offest < 0 && factor==1)
							{
								XML_str += "sint8";
							}
							else if (offest < 0 && factor > 1)
							{
								XML_str += "sint16";
							}
							else
							{
								XML_str += "uint8";
							}
						}
						else if (8 < length && length < 17)
						{
							if (offest < 0)
							{
								XML_str += "sint16";
							}
							else
							{
								XML_str += "uint16";
							}
						}
						else
						{
							if (offest < 0)
							{
								XML_str += "sint32";
							}
							else
							{
								XML_str += "uint32";
							}
						}
					}
				}
				else
				{
					XML_str += "float32";
				}
				XML_str += "</IMPLEMENTATION-DATA-TYPE-REF>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n";
			}
			else
			{
				XML_str += "            <IMPLEMENTATION-DATA-TYPE-ELEMENT UUID=\"CB574025-4D02-46F1-A243-5A845494FAA0\">\n\
              <SHORT-NAME>"+Total_Messege[i_messege].Signal[i_signal].name+"</SHORT-NAME>\n"+
			  "              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/Dt_ARRAY_8_"+Total_Messege[i_messege].Signal[i_signal].name+ "</IMPLEMENTATION-DATA-TYPE-REF>\n"+
					"                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n";
			}
		}

		XML_str += "          </SUB-ELEMENTS>\n\
          <TYPE-EMITTER>RTE</TYPE-EMITTER>\n\
        </IMPLEMENTATION-DATA-TYPE>\n";
	}


	/*------------------                   生成ARRAY的Dt_ARRAY                     -------------------*/
	for (int i_message_ARRAY = 0; i_message_ARRAY < Total_Messege.size(); i_message_ARRAY++)
	{
		for (int i_signal_ARRAY = 0; i_signal_ARRAY < Total_Messege[i_message_ARRAY].Signal.size(); i_signal_ARRAY++)
		{
			int length_ARRAY = atoi(Total_Messege[i_message_ARRAY].Signal[i_signal_ARRAY].length.c_str());
			double factor_ARRAY = atof(Total_Messege[i_message_ARRAY].Signal[i_signal_ARRAY].factor.c_str());
			string ValueType = Total_Messege[i_message_ARRAY].Signal[i_signal_ARRAY].valuetype.c_str();
			if (length_ARRAY>32)
			{
			   XML_str += "        <IMPLEMENTATION-DATA-TYPE UUID=\"B4BFF8C9-F0DB-463D-A3A4-2176E4E59A52\">\n\
          <SHORT-NAME>Dt_ARRAY_8_"+Total_Messege[i_message_ARRAY].Signal[i_signal_ARRAY].name+"</SHORT-NAME>\n"+
		  "          <CATEGORY>ARRAY</CATEGORY>\n\
          <SW-DATA-DEF-PROPS>\n\
            <SW-DATA-DEF-PROPS-VARIANTS>\n\
              <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                <SW-CALIBRATION-ACCESS>READ-ONLY</SW-CALIBRATION-ACCESS>\n\
              </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
            </SW-DATA-DEF-PROPS-VARIANTS>\n\
          </SW-DATA-DEF-PROPS>\n\
          <SUB-ELEMENTS>\n\
            <IMPLEMENTATION-DATA-TYPE-ELEMENT>\n\
              <SHORT-NAME>Element</SHORT-NAME>\n\
              <CATEGORY>TYPE_REFERENCE</CATEGORY>\n\
              <ARRAY-SIZE>8</ARRAY-SIZE>\n\
              <ARRAY-SIZE-SEMANTICS>FIXED-SIZE</ARRAY-SIZE-SEMANTICS>\n\
              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <IMPLEMENTATION-DATA-TYPE-REF DEST=\"IMPLEMENTATION-DATA-TYPE\">/AUTOSAR_Platform/ImplementationDataTypes/";
// 			   if (ValueType=="-")
// 			   {
// 				   XML_str += "uint8";
// 			   }
// 			   else if (ValueType == "+")
// 			   {
// 				   if (factor_ARRAY == 1)
// 				   {
					   XML_str += "uint8";
// 				   }
// 				   else
// 				   {
// 					   XML_str += "sint8";
// 				   }
// 			   }
			   
			   XML_str += "</IMPLEMENTATION-DATA-TYPE-REF>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
            </IMPLEMENTATION-DATA-TYPE-ELEMENT>\n\
          </SUB-ELEMENTS>\n\
          <TYPE-EMITTER>RTE</TYPE-EMITTER>\n\
        </IMPLEMENTATION-DATA-TYPE>\n";
			}
		}
	}

	XML_str += "      </ELEMENTS>\n\
    </AR-PACKAGE>\n";

	return XML_str;
}

/*------------------                   DaVinci                     -------------------*/
string XML_Generate_DaVinci(string XML_str)
{
	XML_str += "    <AR-PACKAGE>\n\
      <SHORT-NAME>DaVinci</SHORT-NAME>\n\
      <ELEMENTS>\n\
        <CONSTANT-SPECIFICATION UUID=\"74307640-8C11-4A16-8FE0-50B2C7201B41\">\n\
          <SHORT-NAME>InitValueSpec_Reserved</SHORT-NAME>\n\
          <VALUE-SPEC>\n\
            <NUMERICAL-VALUE-SPECIFICATION>\n\
              <VALUE>0</VALUE>\n\
            </NUMERICAL-VALUE-SPECIFICATION>\n\
          </VALUE-SPEC>\n\
        </CONSTANT-SPECIFICATION>\n\
      </ELEMENTS>\n\
    </AR-PACKAGE>\n";

	return XML_str;
}

/*------------------                PortInterfaces                   -------------------*/
string XML_Generate_PortInterfaces(string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	vector<Messege> Total_Messege;
	Total_Messege.insert(Total_Messege.end(), Tx_IECU.begin(), Tx_IECU.end());
	Total_Messege.insert(Total_Messege.end(), Rx_IECU.begin(), Rx_IECU.end());

	XML_str += "    <AR-PACKAGE>\n\
      <SHORT-NAME>PortInterfaces</SHORT-NAME>\n\
      <ELEMENTS>\n";

	/*------------------          生成BusIn的PortInterfaces           -------------------*/
	XML_str += "        <SENDER-RECEIVER-INTERFACE UUID=\"ED4330C3-0EB2-4753-B871-A8E6BC0AD0E4\">\n\
          <SHORT-NAME>DPiBusIn</SHORT-NAME>\n\
          <IS-SERVICE>false</IS-SERVICE>\n\
          <DATA-ELEMENTS>\n";

	for (int i_messege_Busin = 0; i_messege_Busin < Rx_IECU.size(); i_messege_Busin++)
	{
		for (int i_signal_Busin = 0; i_signal_Busin < Rx_IECU[i_messege_Busin].Signal.size(); i_signal_Busin++)
		{
			XML_str += "            <VARIABLE-DATA-PROTOTYPE UUID=\"6077ED32-B412-4800-AA7F-AB6FC81AEF9C\">\n\
              <SHORT-NAME>"+Rx_IECU[i_messege_Busin].Signal[i_signal_Busin].name+"</SHORT-NAME>\n"+
			  "              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <SW-CALIBRATION-ACCESS>NOT-ACCESSIBLE</SW-CALIBRATION-ACCESS>\n\
                    <SW-IMPL-POLICY>STANDARD</SW-IMPL-POLICY>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
              <TYPE-TREF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/Dt_"+Rx_IECU[i_messege_Busin].Signal[i_signal_Busin].name+"</TYPE-TREF>\n\
            </VARIABLE-DATA-PROTOTYPE>\n";
		}
	}

	XML_str += "          </DATA-ELEMENTS>\n";
	XML_str += "          <INVALIDATION-POLICYS>\n";

	for (int j_message_Busin = 0; j_message_Busin < Rx_IECU.size(); j_message_Busin++)
	{
		for (int j_signal_Busin = 0; j_signal_Busin < Rx_IECU[j_message_Busin].Signal.size();j_signal_Busin++)
		{
			XML_str += "            <INVALIDATION-POLICY>\n\
              <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusIn/"+Rx_IECU[j_message_Busin].Signal[j_signal_Busin].name+"</DATA-ELEMENT-REF>\n"+
			  "              <HANDLE-INVALID>DONT-INVALIDATE</HANDLE-INVALID>\n\
            </INVALIDATION-POLICY>\n";
		}
	}

	XML_str += "          </INVALIDATION-POLICYS>\n";
	XML_str += "        </SENDER-RECEIVER-INTERFACE>\n";
	/*-------------------------------------------------------------------------------------*/

	/*------------------          生成BusOut的PortInterfaces           -------------------*/
	XML_str += "        <SENDER-RECEIVER-INTERFACE UUID=\"ED4330C3-0EB2-4753-B871-A8E6BC0AD0E4\">\n\
          <SHORT-NAME>DPiBusOut</SHORT-NAME>\n\
          <IS-SERVICE>false</IS-SERVICE>\n\
          <DATA-ELEMENTS>\n";

	for (int i_messege_Busout = 0; i_messege_Busout < Tx_IECU.size(); i_messege_Busout++)
	{
		for (int i_signal_Busout = 0; i_signal_Busout < Tx_IECU[i_messege_Busout].Signal.size(); i_signal_Busout++)
		{
			XML_str += "            <VARIABLE-DATA-PROTOTYPE UUID=\"6077ED32-B412-4800-AA7F-AB6FC81AEF9C\">\n\
              <SHORT-NAME>"+Tx_IECU[i_messege_Busout].Signal[i_signal_Busout].name+"</SHORT-NAME>\n"+
			  "              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <SW-CALIBRATION-ACCESS>NOT-ACCESSIBLE</SW-CALIBRATION-ACCESS>\n\
                    <SW-IMPL-POLICY>STANDARD</SW-IMPL-POLICY>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
              <TYPE-TREF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/Dt_"+Tx_IECU[i_messege_Busout].Signal[i_signal_Busout].name+"</TYPE-TREF>\n\
            </VARIABLE-DATA-PROTOTYPE>\n";
		}
	}

	XML_str += "          </DATA-ELEMENTS>\n";
	XML_str += "          <INVALIDATION-POLICYS>\n";

	for (int j_message_Busout = 0; j_message_Busout < Tx_IECU.size(); j_message_Busout++)
	{
		for (int j_signal_Busout = 0; j_signal_Busout < Tx_IECU[j_message_Busout].Signal.size(); j_signal_Busout++)
		{
			XML_str += "            <INVALIDATION-POLICY>\n\
              <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/DPiBusOut/"+Tx_IECU[j_message_Busout].Signal[j_signal_Busout].name+"</DATA-ELEMENT-REF>\n"+
			  "              <HANDLE-INVALID>DONT-INVALIDATE</HANDLE-INVALID>\n\
            </INVALIDATION-POLICY>\n";
		}
	}

	XML_str += "          </INVALIDATION-POLICYS>\n";
	XML_str += "        </SENDER-RECEIVER-INTERFACE>\n";
	/*-------------------------------------------------------------------------------------*/

	for (int i_messege_Rx = 0; i_messege_Rx < Rx_IECU.size();i_messege_Rx++)
	{
		XML_str += "        <SENDER-RECEIVER-INTERFACE UUID=\"ED4330C3-0EB2-4753-B871-A8E6BC0AD0E4\">\n\
          <SHORT-NAME>PiCom_"+Rx_IECU[i_messege_Rx].name+"_"+Rx_IECU[i_messege_Rx].cycle+"ms</SHORT-NAME>\n"+
		  "          <IS-SERVICE>false</IS-SERVICE>\n\
          <DATA-ELEMENTS>\n\
            <VARIABLE-DATA-PROTOTYPE>\n\
              <SHORT-NAME>De"+Rx_IECU[i_messege_Rx].name+"</SHORT-NAME>\n"+
			  "              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <SW-CALIBRATION-ACCESS>NOT-ACCESSIBLE</SW-CALIBRATION-ACCESS>\n\
                    <SW-IMPL-POLICY>STANDARD</SW-IMPL-POLICY>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
              <TYPE-TREF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/Dt_RECORD_"+Rx_IECU[i_messege_Rx].name+"</TYPE-TREF>\n"+
			  "            </VARIABLE-DATA-PROTOTYPE>\n\
          </DATA-ELEMENTS>\n\
          <INVALIDATION-POLICYS>\n\
            <INVALIDATION-POLICY>\n\
              <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/PiCom_"+Rx_IECU[i_messege_Rx].name+"_"+Rx_IECU[i_messege_Rx].cycle+"ms/De"+Rx_IECU[i_messege_Rx].name+"</DATA-ELEMENT-REF>\n"+
			  "              <HANDLE-INVALID>DONT-INVALIDATE</HANDLE-INVALID>\n\
            </INVALIDATION-POLICY>\n\
          </INVALIDATION-POLICYS>\n\
        </SENDER-RECEIVER-INTERFACE>\n";
	}

	for (int i_messege_Tx = 0; i_messege_Tx < Tx_IECU.size();i_messege_Tx++)
	{
		XML_str += "        <SENDER-RECEIVER-INTERFACE UUID=\"ED4330C3-0EB2-4753-B871-A8E6BC0AD0E4\">\n\
          <SHORT-NAME>PiVMS_"+Tx_IECU[i_messege_Tx].name+"_"+Tx_IECU[i_messege_Tx].cycle+"ms</SHORT-NAME>\n"+
		  "          <IS-SERVICE>false</IS-SERVICE>\n\
          <DATA-ELEMENTS>\n\
            <VARIABLE-DATA-PROTOTYPE UUID=\"ED4330C3-0EB2-4753-B871-A8E6BC0AD0E4\">\n\
              <SHORT-NAME>De"+Tx_IECU[i_messege_Tx].name+"</SHORT-NAME>\n"+
			  "              <SW-DATA-DEF-PROPS>\n\
                <SW-DATA-DEF-PROPS-VARIANTS>\n\
                  <SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                    <SW-CALIBRATION-ACCESS>NOT-ACCESSIBLE</SW-CALIBRATION-ACCESS>\n\
                    <SW-IMPL-POLICY>STANDARD</SW-IMPL-POLICY>\n\
                  </SW-DATA-DEF-PROPS-CONDITIONAL>\n\
                </SW-DATA-DEF-PROPS-VARIANTS>\n\
              </SW-DATA-DEF-PROPS>\n\
              <TYPE-TREF DEST=\"IMPLEMENTATION-DATA-TYPE\">/DataTypes/Dt_RECORD_"+Tx_IECU[i_messege_Tx].name+"</TYPE-TREF>\n"+
			  "            </VARIABLE-DATA-PROTOTYPE>\n\
          </DATA-ELEMENTS>\n\
          <INVALIDATION-POLICYS>\n\
            <INVALIDATION-POLICY>\n\
              <DATA-ELEMENT-REF DEST=\"VARIABLE-DATA-PROTOTYPE\">/PortInterfaces/PiVMS_"+Tx_IECU[i_messege_Tx].name+"_"+Tx_IECU[i_messege_Tx].cycle+"ms/De"+Tx_IECU[i_messege_Tx].name+"</DATA-ELEMENT-REF>\n"+
			  "              <HANDLE-INVALID>DONT-INVALIDATE</HANDLE-INVALID>\n\
            </INVALIDATION-POLICY>\n\
          </INVALIDATION-POLICYS>\n\
        </SENDER-RECEIVER-INTERFACE>\n";
	}

	XML_str += "      </ELEMENTS>\n\
    </AR-PACKAGE>\n";

	return XML_str;
}

/*------------------                    Total                       -------------------*/
string XML_Generate_Total(string XML_str, char *file_XML)
{
	XML_str += "  </AR-PACKAGES>\n\
</AUTOSAR>";

	FILE *fp_XML = NULL;

	int position_find_UUID = 0,
		position_find_Repeat = 0,
		position_replace = 0,
		find_Repeat_Nub = 0,
		Repeat_NUM = 0,
		Replace_NUM = 0;

	char Replace_Val[10], override[10];

	string UUID_xml,
		   buf_UUID;

	bool flag_find_UUID = true, flag_find_Repeat = true, flag_Replace = true;

	while (flag_find_UUID)
	{
		if ((position_find_UUID = XML_str.find("UUID=", position_find_UUID)) != string::npos)
		{
			buf_UUID = XML_str.substr(position_find_UUID + 6, 36);
			UUID_xml = UUID_xml.append(buf_UUID);
			UUID_xml += '\n';
			position_find_UUID++;
		}
		else
		{
			flag_find_UUID = false;
		}
	}

	while (find_Repeat_Nub < strlen(UUID_xml.c_str()))
	{
		buf_UUID = UUID_xml.substr(find_Repeat_Nub, 36);
		while (flag_find_Repeat)
		{
			if ((position_find_Repeat = XML_str.find(buf_UUID, position_find_Repeat)) != string::npos)
			{
				Repeat_NUM++;
				position_find_Repeat++;
			}
			else
			{
				flag_find_Repeat = false;
			}
		}
		if (Repeat_NUM > 1)
		{
			while (flag_Replace)
			{
				if ((position_replace = XML_str.find(buf_UUID, position_replace)) != string::npos)
				{
					Replace_NUM++;
					_itoa(Replace_NUM, Replace_Val, 10);
					sprintf(override, "%05s", Replace_Val);
					XML_str.replace(position_replace + strlen(buf_UUID.c_str()) - 5, 5, override);
					position_replace++;
				}
				else
				{
					flag_Replace = false;
				}
			}
		}
		flag_find_Repeat = true;
		flag_Replace = true;
		Repeat_NUM = 0;
		Replace_NUM = 0;
		position_find_Repeat = 0;
		position_replace = 0;
		find_Repeat_Nub += 37;
	}

	fp_XML = fopen(file_XML, "w+");

	if (fp_XML == NULL)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("XML文件创建失败!\n");
		return 0;
	}

	fprintf(fp_XML, "%s", XML_str.c_str());

	fclose(fp_XML);
	XML_str += "";
	return XML_str;
}


void XML_Generate(char *file_Template_Head, char *file_DataType, char *file_XML, string CtApVMS, string XML_str, vector<Messege> Tx_IECU, vector<Messege> Rx_IECU)
{
	printf("XML正在生成中...\n");
	 XML_str = XML_Generate_Head(file_Template_Head);
 	 XML_str = XML_Generate_ComponentTypes(CtApVMS, XML_str, Tx_IECU, Rx_IECU);
 	 XML_str = XML_Generate_Constants(XML_str, Tx_IECU, Rx_IECU);
  	 XML_str = XML_Generate_DataType(XML_str, file_DataType);
  	 XML_str = XML_Generate_DataTypes(XML_str, Tx_IECU, Rx_IECU);
 	 XML_str = XML_Generate_DaVinci(XML_str);
 	 XML_str = XML_Generate_PortInterfaces(XML_str, Tx_IECU, Rx_IECU);
	 XML_str = XML_Generate_Total(XML_str, file_XML);
}


