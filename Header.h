#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<string>

#define inf 1000000000
#define maxPrice 5000000
#define MATSIZE 100
using namespace std;

class Airport {
private:
	float AdjacencyMatrix[MATSIZE][MATSIZE];//The Adjancency Matrix That Flight Costs Will Store In It
	int CityCount;//Number Of Cities Will Store In It
	int Beginning;//Index Of Beginning Of Travel 
	int Destination;//Index Of Destination Of Travel
	bool Checked[MATSIZE];//An Array For Node Checking Flag
	float Cost[MATSIZE];//Array Of Costs Of Travel
	string CityName[MATSIZE];//Array Of Names
	string tpath;//An String That Latest Path Will Store In It
	int Parent[MATSIZE];//An Array For Parents Of Nodes
	bool AdjacencyMatrixEnter;//The Adjacency Matrix Is Entered Or Not
public:
	Airport();//Constructor
	void data_Entery();//Read Data And Adjacency Matrix
	void algorithm_Initializer();//Initialize Data For Algorithm
	void low_Cost_Calculator();//Calculates The Lowest Cost Path
	void set_Beginning();//Set Beginning Of Travel
	void set_Destination();//Set Destination Of Travel
	void result();//Shows The Lowest Cost Path
	void path(int);//A Function For Result Function
	int city_To_Number(string);//Returns Index Of City Name
	int next_Near_Node();//Returns The Next Near Node
	string get_AdjacencyMatrix(int, int);//Returns The Adjacency Matrix
	int get_CityCount();//Returns Number Of Cities
	bool isEntered_S(string);//Checks A City Name Is Already Entered Or Not
	bool get_Adjacency_Matrix_Enter();//Checks The Adjacency Matrix Is Entered Or Not
	bool validCharacter(string);//List Of Valid Characters That We Can Use
	string get_CityName(int);//Returns A Name For Each City
	string capitalize(string);//Capitalize City Names To Store
	string get_Path();//Shows Latest Calculated Path
};
Airport::Airport(){
	AdjacencyMatrixEnter = false;//The Adjacency Matrix Is Not Entered
}
void Airport::data_Entery(){
	int ctemp;//A Temporary Variable For City Count
	float cftemp;// A Temporary Variable For Costs
	bool intfail = false;
	bool floatfail = false;
	system("CLS");
	cout << "	    Airport Simulation With Adjacency Matrix \n";
	cout << "  -------------------------------------------------------------";
	cout << "\n| Please Enter Number Of Cities \"It Must Be Positive\"		|" << endl;
	cout << "\n  -------------------------------------------------------------"<<endl;
	cout << "| ";
	cin >> ctemp;
	if (cin.fail()){
		intfail = true;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	while ((ctemp <= 0)||(intfail==true)){//City Count Should Be Positive
		cout << "\n  -------------------------------------------------------------" << endl;
		cout << "\n| You Made Mistake , Enter A Positive Number ( > 0)		|" << endl;
		cout << "\n  -------------------------------------------------------------" << endl;
		cout << "| ";
		cin >> ctemp;
		if (!cin.fail())
			intfail = false;
		if (cin.fail()){
			intfail = true;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
	}
	CityCount = ctemp;
	cout << "  -------------------------------------------------------------" << endl;
	cout << "| Please Enter The Cities Names :				|" << endl;
	cout << "| Valid Characters: (A-Z,a-z,space)				|" << endl;
	cout << "  -------------------------------------------------------------" << endl;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');//Reads Only Certain Numbers Of Characters For The Maximum Of Characters
	for (int k = 0; k < CityCount; k++){
		string stemp;
		cout << "| Please Enter The Name Of City Number " << k+1 << " :" << endl;
		cout << "| ";
		getline(cin,stemp);//Gets String
		stemp = capitalize(stemp);//Capitalize Name
		while ((isEntered_S(stemp)) ||(!validCharacter(stemp))||(stemp.compare("")==0)){//If Entered String Contains Invalid Character Or Already Entered Or Null
			if (!validCharacter(stemp)){
				cout << "| The City Name Contains Invalid Character! Try Again :" << endl;
				cout << "| ";
				getline(cin, stemp);//Gets String
				stemp = capitalize(stemp);//Capitalize Name
			}
			else if (stemp.compare("") == 0){
				cout << "| Null String! Try Again With City Number " << k + 1 << " :" << endl;
				cout << "| ";
				getline(cin, stemp);//Gets String
				stemp = capitalize(stemp);//Capitalize Name
			}
			else {
				cout << "| You Already Entered This City! Try Again With City Number " << k + 1 << " :" << endl;
				cout << "| ";
				getline(cin, stemp);//Gets String
				stemp = capitalize(stemp);//Capitalize Name
			}
		}
		CityName[k] = stemp;
		
	}
	if (CityCount == 1){//If Only A City Exist , Do Not Run Matrix Getter
		AdjacencyMatrix[0][0] = 0;
		goto L1;
	}
	cout << "\n  -------------------------------------------------------------" << endl;
	cout << "| Please Enter The Adjacency Matrix :				|" << endl;
	cout << "| Please Enter Costs In The Range [0," << maxPrice << "] Rials.		|" << endl;
	cout << "| The One And Only Negative Number Can Be Used is -1.		|" << endl;
	cout << "| For A No Flight Condition, Enter -1.				|" << endl;
	cout << "  -------------------------------------------------------------" << endl;
	for (int i = 0; i < CityCount; i++){
		for (int j = 0; j < CityCount; j++){
			if (i == j){//Fills Automatically (i=j) s
				AdjacencyMatrix[i][j] = 0;
				continue;
			}
			cout << "| Enter The Cost For Travelling From " << CityName[i] << " To " << CityName[j] <<" :"<< endl;
			cout << "| ";
			cin >> cftemp;
			if (cin.fail()){
				floatfail = true;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			//cin.ignore(numeric_limits<streamsize>::max(), '\n');
			while (((cftemp < 0) && (cftemp != -1)) || (cftemp>maxPrice)||(floatfail==true)){
				
				if (cftemp>maxPrice)
					cout << "| The Cost Is Too High! Please Enter Correct Value :		|" << endl;
				else if (floatfail==true)
					cout << "| Please Enter A Valid Float Number :				|" << endl;
				else if (((cftemp < 0) && (cftemp != -1)))
					cout << "| The One And Only Negative Number Can Be Used is -1.		| \n| Please Enter Correct Value :					|" << endl;
				cout << "| ";
				cin >> cftemp;
				if (!cin.fail())
					floatfail = false;
				if (cin.fail()){
					floatfail = true;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				
			}
			if (cftemp == -1)
				AdjacencyMatrix[i][j] = inf;//Swap -1 With Infinity
			else
				AdjacencyMatrix[i][j] = cftemp;
		}
	}
	L1:AdjacencyMatrixEnter = true;

}
void Airport::algorithm_Initializer(){
	for (int k = 0; k < CityCount; k++){
		Checked[k] = false;//All Nodes Are Not Checked
		Parent[k] = -1;//All Nodes Are Not Checked
		Cost[k] = inf;//All Costs Are Infinity
	}
	Cost[Beginning] = 0;//Cost For Beginning Is 0
}
void Airport::low_Cost_Calculator(){
	algorithm_Initializer();
	int CloseUncheckedNode;
	int counter = 0;
	while (counter < CityCount){
		CloseUncheckedNode = next_Near_Node();//Calculate Next Near Node
		Checked[CloseUncheckedNode] = true;//Mark Node As Checked
		for (int k = 0; k < CityCount; k++){
			if ((!Checked[k]) && (AdjacencyMatrix[CloseUncheckedNode][k])>0){
				if (Cost[k] >(Cost[CloseUncheckedNode] + AdjacencyMatrix[CloseUncheckedNode][k])){
					Cost[k] = (Cost[CloseUncheckedNode] + AdjacencyMatrix[CloseUncheckedNode][k]);
					Parent[k] = CloseUncheckedNode;
				}
			}
		}
		counter++;
	}
}
void Airport::set_Beginning(){
	string stemp;
	int ctemp;
	if (CityCount == 1){//If Only One City Exists The Beginning Of Travel Is 0
		Beginning = 0;
		goto END;
	}
	cout << "  -------------------------------------------------------------" << endl;
	cout << "| Enter The Beginning Of Travel :				|" << endl;
	cout << "| ";
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');//Reads Only Certain Numbers Of Characters For The Maximum Of Characters
	getline(cin,stemp);//Gets String
	stemp = capitalize(stemp);//Capitalize Name
	ctemp = city_To_Number(stemp);
	while(ctemp == -10){
			cout << "| Your Entered City Name Doesn't Exist In The List! Try Again :	|" << endl;
			cout << "| ";
			getline(cin,stemp);//Gets String
			stemp = capitalize(stemp);//Capitalize Name
			ctemp = city_To_Number(stemp);
		}
	Beginning = ctemp;
	cout << "  -------------------------------------------------------------" << endl;
END:cout << flush;//Flushes Output Stream
}
void Airport::set_Destination(){
	string stemp;
	int ctemp;
	if (CityCount == 1)//If Only One City Exists , There Is No Destination
		goto END;
	if (CityCount == 2){//If 2 Cities Are Existed, The Destination Is Other One
		if (Beginning == 0)
			Destination = 1;
		else
			Destination = 0;
		goto END;
	}
	cout << "  -------------------------------------------------------------" << endl;
	cout << "| Enter The Destination Of Travel :				|" << endl;
	cout << "| ";
	
	getline(cin,stemp);//Gets String
	stemp = capitalize(stemp);//Capitalize String
	ctemp = city_To_Number(stemp);//Converts String To Index
	while ((ctemp == -10)||(ctemp==Beginning)){
		if (ctemp == Beginning){
			cout << "| The Destination And Beginning Are The Same, Try Again !	|" << endl;
			cout << "| ";
			getline(cin,stemp);//Gets String
			stemp = capitalize(stemp);//Capitalize String
			ctemp = city_To_Number(stemp);//Converts String To Index
		}
		else{
			cout << "| Your Entered City Name Doesn't Exist In The List! Try Again :	|" << endl;
			cout << "| ";
			getline(cin,stemp);//Gets String
			stemp = capitalize(stemp);//Capitalize String
			ctemp = city_To_Number(stemp);//Converts String To Index
		}
	}
	Destination = ctemp;
	cout << "  -------------------------------------------------------------" << endl;
END:cout << flush;//Flushes Output Stream

}
int Airport::city_To_Number(string s){
	for (int k = 0; k < CityCount; k++){
		if (CityName[k] == s)
			return k;//Returns Index Of City Name
	}
	return -10;//Shows That The Name Isn't In The City Names
}
int Airport::next_Near_Node(){
	float Minimum_Cost = inf;
	int CloseUncheckedNode;
	for (int k = 0; k < CityCount; k++){
		if ((!Checked[k]) && (Minimum_Cost >= Cost[k])){
			Minimum_Cost = Cost[k];
			CloseUncheckedNode = k;
		}
	}
	return CloseUncheckedNode;
}
int Airport::get_CityCount(){
	return CityCount;//Returns Number Of Cities
}
void Airport::result(){
	tpath = "";
	if (CityCount == 1){
		cout << "| You Can Stay Home For Free !";
		tpath += "| You Can Stay Home For Free !";//It's For Log File
		goto END;
	}
	cout << "| Lowest Cost Path : ";
	tpath += "| Lowest Cost Path : ";
		path(Destination);
		if (Cost[Destination] != inf){	
			cout << "\t" << "| Cost : " << Cost[Destination] << endl;
			tpath += "\t| Cost : ";//It's For Log File
			tpath += to_string(Cost[Destination]);//It's For Log File
		}
END:cout << endl;
}
void Airport::path(int p){
	if (p == Beginning){
		cout << CityName[Beginning];
		tpath += CityName[Beginning];//It's For Log File
	}
	else if (Parent[p] == -1){
		cout << "| There Is No Path From " << CityName[Beginning] << " To " << CityName[p] << " !" << endl;
		tpath += "| There Is No Path From ";//It's For Log File
		tpath += CityName[Beginning];//It's For Log File
		tpath += " To ";//It's For Log File
		tpath += CityName[p];//It's For Log File
		tpath += " !";//It's For Log File
	}
	else{
		path(Parent[p]);//Recursive Fuction Call
		cout << "->" << CityName[p];
		tpath += "->";//It's For Log File
		tpath += CityName[p];//It's For Log File
	}
}
bool Airport::get_Adjacency_Matrix_Enter(){
	return AdjacencyMatrixEnter;//Indicates That Matrix Is Entered Or Not
}
bool Airport::isEntered_S(string s){
	for (int k = 0; k < CityCount; k++){
		if (CityName[k].compare(s)==0)
			return true;//If The Strings Are Equal , Return True
	}
		return false;//If The Strings Are Not Equal
}
bool Airport::validCharacter(string s){
	bool error=false;
	for (unsigned int k = 0; k < s.length(); k++){
		if (!(((s[k] >= 65) && (s[k] <= 90)) || ((s[k] >= 97) && (s[k] <= 122))||(s[k]==' ')||(s[k]=='.'))){
			error = true;
			break;
		}
	}
	return !error;//Returns 1 If There Is No Error
}
string Airport::get_AdjacencyMatrix(int i, int j){
	if ((AdjacencyMatrix[i][j]) == inf)
		return "#";
	else if ((AdjacencyMatrix[i][j]) == (int)(AdjacencyMatrix[i][j])){
		return to_string((int)(AdjacencyMatrix[i][j]));
	}
	else
	return to_string(AdjacencyMatrix[i][j]);
}
string Airport::get_CityName(int k){
	return CityName[k];
}
string Airport::capitalize(string s){
	string stemp;
	for (unsigned int k = 0; k < s.length(); k++){
		if ((s[k] <= 122) && (s[k] >= 97))
			s[k] -= 32;
	}
	stemp = s;
	return stemp;
}
string Airport::get_Path(){
	return tpath;//Returns Saved Path
}
#endif

