/*-----------------------------------------------------------------------------------------------------------
Project     	  : Implementation Simmulated Annealing Placement Algorithm
Description 	  : A) This project includes reading benchmark file provided by the user and creating linked 
		       list based data structure for storing the information of all the nets and modules in 
		       file. It creates two different dynamic data structure as follows:
			 a) Net List : All the cells connected for each net
			 b) Cell List: All the nets connected to every module(pads and cells)
      		       Also, location x,y(co-ordinates) are appened to every module.
		    B) Using the datastructures, Simmulated Annealing placement algorithm is implement to 
		       minimize the total wirelength.  
------------------------------------------------------------------------------------------------------------*/

#include "PA3.h"                     // Project header file

/*------------------------------------------------------------------------------------------------------------
Function 	 : main function
Description 	 : This is main function executes main task of this project
Parameters  
   a) Inputs     : name of netlist file(.net)
   b) Return     : return 0 on successful implementation. 
------------------------------------------------------------------------------------------------------------*/

int main (int argc, char *argv[]) 
{	
	int i=0;
	char benchmarkName[40],inNetFile[40],outListFile[40],outResultFile[40],outResultFile2[40];
	
	if(argc<2)
	{
		cout<<"\n\nToo few arguments to main function.Please go through Readme File.\n\n"<<endl;
		return 1;
	}
	if(argc>2)
	{
		cout<<"\n\nToo many arguments to main function.Please go through Readme File.\n\n"<<endl;
		return 1;
	}
	while(argv[1][i]!='.')
	{
		benchmarkName[i]=argv[1][i];
		i++;
	}
	benchmarkName[i]='\0';
	strcpy(inNetFile,"./");
	strcat(inNetFile,argv[1]);
	strcpy(outListFile,"./");
	strcat(outListFile,"Amin_Bhagwat_");
	strcat(outListFile,benchmarkName);
	strcat(outListFile,".txt");

	strcpy(outResultFile,"./");
	strcat(outResultFile,"Amin_Bhagwat_Placement_");
	strcat(outResultFile,benchmarkName);
	strcat(outResultFile,".txt");

	strcpy(outResultFile2,"./");
	strcat(outResultFile2,"Amin_Bhagwat_Results_");
	strcat(outResultFile2,benchmarkName);
	strcat(outResultFile2,".txt");

	ifstream netFile (inNetFile);
	if (netFile.is_open())
	{	
		createNetCellList(netFile);					//Create Linked List Based Datastructure
#ifdef SAVEDATASTRUCTURES		
		ofstream textFile (outListFile);
		if (textFile.is_open())
			saveTextFile(textFile);					//Save Datastructure
		else
			cout<<"\nUnable to creat Netlist Datastructure output file\n"<<endl;
#endif
		netFile.close();
	}
	else 
	{
		cout << "\nUnable to open Input File/s\n"<<endl; 
		return 1;					
	}

	simmulatedAnnealing();							//Run Simmulated Annealing Algorithm
	createResultFile(outResultFile,benchmarkName);				//Create Result File(X-Y co-ordinates)
	createOutputFile(outResultFile2,benchmarkName);				//Create Result File(Algorithm statistics) 
	return 0;
}

