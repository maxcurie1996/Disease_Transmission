//File name: COVID.cpp
//Calculate the infection tranmission simulation
//Created by Max Curie on 11/21/2020
#include <iostream> 
#include <vector>
#include <math.h> /* pow */

using std:: string ; 
using std:: vector ;
using std:: cin ;
using std:: cout ;
using std:: endl ;


//*************Comments*********************
//Example for compiling and running: icpc -o a.bin COVID.cpp && ./a.bin >> COVID.csv


//***************Start of user block*************

int n_neighbor=20;	//Totall amount of neighbor a person has
int population=40000;	//Total population
float Vaccination_rate=0.; 	//Ratio of population that are Vaccinated
int total_day=1000;	//Total time steps 
float Infecction_rate=0.02;  //probability of getting infected [0,1]
int printing_type=1;  	// 0: print all data, 1: print python readable data(csv file)

//****************End of user block**************



class Human_info{
	//Not avaible to public
	private: 
		int name;
		vector <int> neighbor_list;
		string status;
			// "Susceptible"
			// "Infected"	("Sick")
			// "Recovered"
			// "Vaccinated" ("inoculated")
		int days;

	//required to be inputed from outside
	public:
		//kinda like structure
		//default values
		Human_info(){
			name=0;
			neighbor_list={0};			
			status="Susceptible";
			days=-1;
		}

		//public input
		Human_info(int p_name, vector <int> p_neighbor, 
					string p_status, int p_day){
			name=p_name;
			neighbor_list=p_neighbor;
			status=p_status;
			days=p_day;
		}


		
		//***Start of Geter and setter***
		int get_name(){
			return name;
		}
		vector <int> get_neighbor(){
			return neighbor_list;
		}
		int get_day(){
			return days;
		}
		string get_status(){
			return status;
		}

		int set_name(int p_name){
			name=p_name;
		}
		vector <int> set_neighbor(vector <int> p_neighbor_list){
			neighbor_list=p_neighbor_list;
		}
		int set_day(int p_days){
			days=p_days;
		}
		string set_status(int p_status){
			status=p_status;
		}

		//***End of Geter and setter***

		void infected(){  //Call this function after one is infected
			status="Infected";
			days=7;
		}

		//Function of day later
		void day_later(){
			if (days==0){
				exit; 
			}
			else if (days==1){
				days=days-1;
				status="Recovered";
			}
			else if (days>1){
				days=days-1;
			} 
			else{
				exit;
			}
		}

		void print_human(){		//print the info about the person
			cout<<"*****************"<<name<<"*****************"<<endl;
			cout <<"status " <<	status << " days: "<<days<<endl;
			cout << "neighbor_list: ";
			for (int i : neighbor_list){
				cout<< i <<" ";  			//print the neighbor_list
			}
			cout<<endl;
		}

};



vector<Human_info> init_Human_info(int n_neighbor,int population,float Vaccination_rate);	//Initiate the list of Human 
vector<Human_info> Next_day(vector<Human_info> Human_info_list, float Infecction_rate);		//Propagate to the next day 
vector <int> Print_Human_list(vector <Human_info> Human_info_list, int printing_type);				//print out the info

int main() {

	vector <Human_info> Human_info_list(0);

	Human_info_list=init_Human_info(n_neighbor,population,Vaccination_rate);		//Initiate the list of Human 
	cout<<"days"<<","<<"Susceptible"<<","<<"Infected"<<","<<"Recovered"<<","<<"Vaccinated"<<endl;
	cout<<0<<",";
	Print_Human_list(Human_info_list,printing_type);//print out the info
	cout<<endl;							
	for(int i =0; i<total_day; i++){
		Human_info_list=Next_day(Human_info_list, Infecction_rate);
		cout<<i+1<<",";
		vector <int> temp=Print_Human_list(Human_info_list,printing_type);//print out the info
		cout<<endl;
		if(temp[1]==0){//If infectored =0, then stop the loop
			break;
		}

	}

	return 0;  //return 0 indicates that everythin went well
} 




vector<Human_info> init_Human_info(int n_neighbor,int population,float Vaccination_rate){  //Initiate the list of Human 

	vector <Human_info> Human_info_list(0);
	//cout<<"********"<<Vaccination_rate<<endl;
	int Vaccinated_population=int(Vaccination_rate*float(population));
	//cout<<"******"<<Vaccinated_population<<endl;
	for(int i=0;i<population;i++){

		vector <int> neighbor_list(0);
		for (int j=0;j<n_neighbor;j++){
			int neighbor_temp=rand() % population;	
			neighbor_list.push_back(neighbor_temp);
		}			
		if (i==0){		//Patient Zero
			Human_info_list.push_back(Human_info(i, neighbor_list, "Infected", 7));
										//name, neighbor ,   status,       days 
		}
		else if(Vaccinated_population!=0){
			//cout<<"Vaccinated person"<<endl;
			Human_info_list.push_back(Human_info(i, neighbor_list, "Vaccinated", -1));
			Vaccinated_population=Vaccinated_population-1;
		}
		else{
			Human_info_list.push_back(Human_info(i, neighbor_list, "Susceptible", -1));
										//name, neighbor ,   status,       days 
		}
		
	}
	return Human_info_list;
}

vector<Human_info> Next_day(vector<Human_info> Human_info_list, float Infecction_rate){
	vector<Human_info> Human_info_list_temp(0);
	for (Human_info i:  Human_info_list){
		i.day_later();	//Propagate to the next day using the function in the object 
		vector <int> neighbor_temp=i.get_neighbor();	//Get the list of the neighbor
		float infected_count=0;
		for (int j : neighbor_temp){
			if (Human_info_list[j].get_status()=="Infected"){
				infected_count=infected_count+1;
			}
		}
		float probability=1.- pow((1.-Infecction_rate), infected_count);
		float r = ((float) rand() / (RAND_MAX)) ;   //random number from 0 to 1: https://stackoverflow.com/questions/9878965/rand-between-0-and-1
		//cout<<"probability: "<<probability<<endl;
		//cout<<"r: "<<r<<endl;
		if (r<probability && i.get_status()=="Susceptible"){
			//cout<<"Infected"<<endl;
			i.infected();
		}
		Human_info_list_temp.push_back(i);
	}
	//Print_Human_list(Human_info_list_temp,1);
	//cout<<endl;
	return Human_info_list_temp;
}


vector <int> Print_Human_list(vector <Human_info> Human_info_list, int printing_type){
	vector <int> temp(0);
	if (printing_type==0){
		for (Human_info i: Human_info_list){
			i.print_human();
		}
		int S=0; 	// "Susceptible"
		int I=0; 	// "Infected"
		int R=0; 	// "Recovered"
		int V=0; 	// "Vaccinated"
		for (Human_info i: Human_info_list){
			if (i.get_status()=="Susceptible"){
				S=S+1;
			}
			else if (i.get_status()=="Infected"){
				I=I+1;
			}
			else if (i.get_status()=="Recovered"){
				R=R+1;
			}
			else if (i.get_status()=="Vaccinated"){
				V=V+1;
			}
		}
		cout<<S<<","<<I<<","<<R<<","<<V;
		temp.push_back(S);
		temp.push_back(I);
		temp.push_back(R);
		temp.push_back(V);
	}
	else if (printing_type==1){
		int S=0; 	// "Susceptible"
		int I=0; 	// "Infected"
		int R=0; 	// "Recovered"
		int V=0; 	// "Vaccinated"
		for (Human_info i: Human_info_list){
			if (i.get_status()=="Susceptible"){
				S=S+1;
			}
			else if (i.get_status()=="Infected"){
				I=I+1;
			}
			else if (i.get_status()=="Recovered"){
				R=R+1;
			}
			else if (i.get_status()=="Vaccinated"){
				V=V+1;
			}
		}
		cout<<S<<","<<I<<","<<R<<","<<V;
		temp.push_back(S);
		temp.push_back(I);
		temp.push_back(R);
		temp.push_back(V);
	}

	return temp;
}