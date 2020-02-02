#include<iostream>
#include<string>
#include"Header.h"
#include<fstream>
#include<ctime>

using namespace std;

int main(){
	time_t t;//A Time Variable
	time(&t);//Initialize t Variable
	tm lt;//A Structure For Now (Time)
	localtime_s(&lt,&t);//Initialize lt Struct
	Airport A1;//A1 From Airport
	ofstream log;//log Variable For Log File Writing
	short int CalcCounter = 1;//Calculates Number Of Path Calculation
	short int MatCounter = 0;//Number Of Atempts To Create The Adjacency Matrix
	char Continue_Condition;// Continue Condition If Failed To Write Log File
	string AdjacencyM[MATSIZE][MATSIZE];//A Matrix For Log File
	string path = "";//The Path Of Saving Log File
	int CellAdjustCounter;
	path += "Shortest_Path_Log_File_";//Prefix Of Log File Name
	path += to_string(t);//Time Variable For Log File Name
	path += ".log";//Log File Format
	log.open(path);//Create Log File
	log << "	Airport Simulation With Adjacency Matrix \n";
	log << "  -------------------------------------------------------------";
	log << "\n			Log File";
	log << "\n  -------------------------------------------------------------";
	if (!log.is_open()){//If Failed To Create Log File
		cout << "	    Airport Simulation With Adjacency Matrix \n";
		cout << "  -------------------------------------------------------------";
		cout << "\n| Unable To Save Log File! For Continue Press C For Exit Press E|";
		cout << "| ";
		cin >> Continue_Condition;
		switch (Continue_Condition)
		{
		case'c':
			goto WH;
			break;
		case'C':
			goto WH;
			break;
		case'E':
			exit(1);
			break;
		case'e':
			exit(1);
			break;
		default:
			cout << "\n| Enter a Valid Character :					|\n" << endl;
			system("PAUSE");
			break;
		}
		system("PAUSE");
	}
WH:	while (1){ // an infinite loop
		int switcher;
		system("CLS");
		cout << "	    Airport Simulation With Adjacency Matrix \n";
		cout << "  -------------------------------------------------------------";
		cout << "\n| Select One Of The Operations Or Exit:				|";
		cout << "\n| 1.Enter The Adjacency Matrix					|";
		cout << "\n| 2.Calculate Lowest Cost Travel				|";
		cout << "\n| 3.Show The List Of Cities					|";
		cout << "\n| 4.Exit							|";
		cout << "\n| This Application Captures What Satisfies It In Inputs		|";
		cout << "\n| Such As:3x It Captures Only 3 If It's Propriate To Continue	|";
		cout << "  \n  -------------------------------------------------------------" << endl;
		cout << "| ";
		cin >> switcher;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		switch (switcher)
		{
		case 1:
			if (A1.get_Adjacency_Matrix_Enter())
				cout << "| You Entered The Adjacency Matrix Before !			|" << endl;
			else
			A1.data_Entery();
			system("PAUSE");
			if (MatCounter == 0){
				log << "\n		The Entered Adjacency Matrix";
				log << "\n			# Means No Flight." << endl;
				for (int k = 0; k <= A1.get_CityCount(); k++){
					if (k == 0){
						AdjacencyM[k][0] = "\t";
					}
					else{
						AdjacencyM[k][0] = A1.get_CityName(k - 1);
					}
				}
				for (int k = 0; k <= A1.get_CityCount(); k++){
					if (k == 0){
						AdjacencyM[0][k] = "\t";
					}
					else{
						AdjacencyM[0][k] = A1.get_CityName(k - 1);
					}
				}
				for (int i = 1; i <= A1.get_CityCount(); i++){
					for (int j = 1; j <= A1.get_CityCount(); j++){
						AdjacencyM[i][j] = A1.get_AdjacencyMatrix(i - 1, j - 1);
					}
				}
				log << "\n|		";
				for (int i = 0; i <= A1.get_CityCount(); i++){
					for (int j = 0; j <= A1.get_CityCount(); j++){

						if ((j == 0) && (i == 0)){
							log << AdjacencyM[i][j];
						}
						else {
								log << AdjacencyM[i][j] << "\t";
						}
						if ((j == A1.get_CityCount()))
							log << "\n|		";
					}
				}
				log << "\n  -------------------------------------------------------------";
			}
			MatCounter++;
			switcher = 5;
			break;
		case 2:
			if (!A1.get_Adjacency_Matrix_Enter())
				cout << "| You Didn't Entered The Adjacency Matrix Before !		|" << endl;
			else
			{
				A1.set_Beginning();
				A1.set_Destination();
				A1.low_Cost_Calculator();
				A1.result();
				log << "\n  Lowest Cost Path Calculation|Number " << CalcCounter << endl;
				log << A1.get_Path();
				log << "\n  -------------------------------------------------------------";
				CalcCounter++;
			}
			system("PAUSE");
			switcher = 5;
			break;
		case 3:
			if (!A1.get_Adjacency_Matrix_Enter()){
				cout << "| You Didn't Entered The Adjacency Matrix Before !		|" << endl;
			}
			else{
				cout << "| You Entered Cities Below :					|" << endl;
				cout << "| ";
				CellAdjustCounter = 0;
				for (int k = 0; k < A1.get_CityCount(); k++){
					if (k == A1.get_CityCount() - 1)
						cout << A1.get_CityName(k);
					else
						cout << A1.get_CityName(k) << ",";
					CellAdjustCounter++;
					if (CellAdjustCounter == 7)
						cout << "\n| ";
				}
			}
			cout << endl;
			system("PAUSE");
			switcher = 5;
			break;
		case 4:
			goto Exit; // Exit
			break;
		default:
			cout << "\n| Enter a Valid Number :					|\n" << endl;
			
			if (cin.fail()){
						cin.clear();
						cin.ignore(256, '\n');
			}
			system("PAUSE");
			break;
		}
	}
Exit://system("PAUSE");
	log << "\n  -------------------------------------------------------------";
	log << "\n| Executed Successfully						|";
	log << "\n  -------------------------------------------------------------";
	log << "\n| This Log Is Generated By Lowest Cost Path Finder Application	|";
	log << "\n| Executed On : ";
	log << lt.tm_mday << "/" << lt.tm_mon + 1 << "/" << lt.tm_year + 1900;
	log << "|";
	log << lt.tm_hour<< ':' << lt.tm_min << ':' << lt.tm_sec;
	log << "				|";
	log.close();
	return EXIT_SUCCESS;
}
