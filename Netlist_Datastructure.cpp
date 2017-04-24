#include "PA3.h"			 // Project header file

/*------------------------------------  Function Declaration  -----------------------------------------------------*/
extern void createNetCellList(ifstream &netFile);
extern void saveTextFile(ofstream &textFile);
/*------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------  Globle Variables  ----------------------------------------------------------*/
NODE *MODULE,*NET;
unsigned int rangeMin=0,rangeMax=0;
unsigned int moduleCount=0,cellCount=0,padCount=0,netCount=0,lineCount=0,offset=0,base=0,sideATotal=0,sideBTotal=0;
/*------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------
Function 	 : createNetCellList
Description 	 : This function creates Netlist and Celllist Linked list structure.
Parameters  
   a) Inputs     : 1)(ifstream) &netFile   -  (.net) file input from use
   b) Return     : NULL 
------------------------------------------------------------------------------------------------------------------*/
void createNetCellList(ifstream &netFile)
{
	//Local variables
	int pos=0;
	char cellName[10],netName[10];
	string line,offsetStr;
	unsigned long cellCounter=0,netCounter=0,i=0; 
	NODE *headNetList=0,*tempNetList=0,*firstNetList; 
	NODE *headCellList=0,*tempCellList=0; 

	while (getline (netFile,line))
	{
		lineCount++;
		if(lineCount==3)
		{
			netCount=atoi(line.c_str());
			NET=new NODE[netCount];					//Creating dynamic memory for Netlist
		}
		if(lineCount==4)
		{
			moduleCount=atoi(line.c_str());
		}
		if(lineCount==5)
		{
			cellCount=atoi(line.c_str())+1;
			padCount=moduleCount-cellCount;
			MODULE=new NODE[moduleCount];				//Creating dynamic memory for Netlist
			for(i=0;i<cellCount;i++)
			{
				sprintf(cellName,"a%d",i);
    				MODULE[cellCounter].value=cellName;
				MODULE[cellCounter].next=NULL;
				cellCounter++;
			}
			for(i=1;i<=padCount;i++)
			{
				sprintf(cellName,"p%d",i);
				MODULE[cellCounter].value=cellName;
    				MODULE[cellCounter].next=NULL;
				cellCounter++;
			}
		}
					
		if(line[0]=='a' || line[0]=='p' )    				// Checking valid module
		{
			if(line[0]=='a')					 
				base=0;
			else
				base=cellCount-1;
			pos=line.find(" ");
			string offsetStr(line,1,pos);
                    	offset=atoi(offsetStr.c_str());
			headNetList=new NODE;
			pos=line.find("s 1");
			if(pos!=std::string::npos)				 //Creating new linked list of cells assosiated with every net 
			{
				headNetList=new NODE;
				string cellName(line,0,(pos-1));		
				headNetList->value=cellName;			
				headNetList->next =NULL;
				firstNetList=tempNetList=headNetList;
			
				NET[netCounter].next= firstNetList;
				sprintf(netName,"net %ld",netCounter);
    				NET[netCounter].value=netName;
				netCounter++;
			}
			else							//Appending cells to the linked list created in above loop 
			{
				pos=line.find(" ");
				headNetList=new NODE;
				headNetList->next=NULL;
				string cellName(line,0,pos);
				headNetList->value=cellName;
				tempNetList->next=headNetList;
				tempNetList=headNetList;			
			}			

			tempCellList=&MODULE[base+offset];			//Appending net number specific module 
			while(tempCellList->next!=NULL)
				tempCellList=tempCellList->next;
			headCellList=new NODE;
			tempCellList->next=headCellList;
			sprintf(cellName,"net %d",(netCounter-1));
			headCellList->value=cellName;
			
		}
	}
}

/*------------------------------------------------------------------------------------------------------------------
Function 	 : saveTextFile
Description 	 : This function saves previously created datastructure to output file.
Parameters  
   a) Inputs     : ofstream &textFile   -  (.txt) output file name 
   b) Return     : NULL 
------------------------------------------------------------------------------------------------------------------*/
void saveTextFile(ofstream &textFile)
{
	int i=0;
	NODE *tempNetList=0;
	
	textFile <<"\nNetlist : \n"<<endl;
	for(i=0;i<netCount;i++)							// Writing Netlist into output file
	{
		tempNetList= &NET[i];
		textFile << "  " << NET[i].value << " : ";
		while(tempNetList->next!=0)
		{
		   tempNetList=tempNetList->next;
		   textFile<< tempNetList->value << " ";
		}
		textFile<< "\n";
	}

	textFile<<"\nCellList : \n"<< endl;
	for(i=0;i<moduleCount;i++)						// Writing Celllist into output file
	{
		tempNetList= &MODULE[i];
		textFile<< "  " << MODULE[i].value << " : ";
		while(tempNetList->next!=0)
		{
		   tempNetList=tempNetList->next;
		   textFile<< tempNetList->value << " ";
		}
		textFile<< "\n";
	}
	textFile.close();
}
