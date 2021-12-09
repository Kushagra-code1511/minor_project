#include<bits/stdc++.h>

using namespace std;

int max_value(int a,int b){
	return (a>b)?a:b;
}

void check(float a){
	if(a==0){cout<<"Amount can't be zero"<<endl;}
	else{cout<<"Amount can't be negative"<<endl;}
}

class node{
	public:
		int price,profit;
		string item;
		node* link;
};

class node_pointers{
	protected:
		node* temp=NULL;
		node* front=NULL;
		node* rear=NULL;
		node* dummy=NULL;
};

class login_and_registration{
	public:
		login_and_registration(){
			fstream file;
			file.open("user_logins.txt",ios::in);
			if(!file){
				file.close();
				file.open("user_logins.txt",ios::out);
			}
			file.close();
		}
	private:
		string email_id,password,check_pw,g_email,g_pw;
		//the g_email and the g_password is here because to check if the
	     	//enterd email email already  exist at the time of writing the code it not working
	public:
		int login(){
			cout<<"Enter email: ";cin>>email_id;
			cout<<"Password: ";cin>>password;
			fstream file;
			file.open("user_logins.txt",ios::in);
			file.seekg(0);
			while(file){
				getline(file,g_email);
				getline(file,g_pw);
				if(g_email==email_id && g_pw==password){
					cout<<"successful login"<<endl;return 1;
				}
				else if(g_email==email_id && g_pw!=password){
					do{
						cout<<"Password incorrect re-enter password: ";cin>>password;
					}while(g_pw!=password);
					cout<<"Login Successful"<<endl;return 1;
				}
			}
			cout<<"Email and password incorrect"<<endl;
			file.close();
			return 0;
		}

		void signup(){
			int flag;
			fstream file;
			file.open("user_logins.txt",ios::in);

			cout<<"Enter your email address: ";cin>>email_id;
			do{
				file.seekg(0);
				while(file){
					flag=1;
					getline(file,g_email);
					getline(file,g_pw);
					if(g_email==email_id){flag=0;break;}
				}
					if(flag==0){
						cout<<"already exist"<<endl;
						cout<<"enter another email"<<endl;
						cin>>email_id;
					}
			}while(flag==0);
			file.close();
			file.open("user_logins.txt",ios::out|ios::app);
			cout<<"enter the password: ";cin>>password;
			cout<<"enter the password again: ";cin>>check_pw;
			while(check_pw!=password){
				cout<<"Wrong password enter again:";cin>>password;
				cout<<"Re-enter password: ";cin>>check_pw;
			}
			file<<endl<<email_id<<endl<<password;
			cout<<"account created"<<endl;
			file.close();

		}
};

class input_and_changes_in_item : protected node_pointers {
	private:
		string product,element;
		int weight,flag,count=0,price_from_file,profit_from_file,profit;
	public:
		void input_stock_items(){
			fstream file;
			file.open("stocks.txt",ios::out|ios::app);
			char ch='y';

			while(ch=='y'||ch=='Y'){
				cout<<"Enter the item name: ";
					cin>>product;
				do{
					flag=1;
					temp=front;
					while(temp!=NULL){
						if(temp->item==product){
							flag=0;
							break;
						}
						temp=temp->link;
					}
					if(flag==0){
						cout<<"Item alread exist"<<endl;
						cout<<"enter the item name: ";cin>>product;
					}
				}while(flag==0);
				cout<<"Enter the price of the item: ";cin>>weight;
				while(1){
					if(weight>0){break;}
					else{check(weight);}
					cout<<"Re-enter the price: ";cin>>weight;
				}
				cout<<"Enter the item profit";cin>>profit;
				while(1){
					if(profit>0){break;}
					else{check(profit);}
					cout<<"re-enter the item profit: ";cin>>profit;
				}
				cout<<endl;
				file<<endl<<product<<endl<<weight<<endl<<profit;
				cout<<"Do you want to continue (Y/n)?: ";cin>>ch;
			}
			cout<<endl;
			file.close();
		}

		void delete_stocks_for_max_profit(int W){
			if(count==0)
				cout<<"stock list empty"<<endl;
			else{
				int i=0,j,w;
				int k[count+1][W+1],val[count+1],wt[count+1];
				char item[count+1][30];
				fstream f;
				f.open("stocks.txt",ios::in);
				f.seekg(0);
				while(f){
					getline(f,product);
					if(product=="")
						break;
					strcpy(item[i],product.c_str());
					f>>wt[i];
					f>>val[i];
					i++;
				}
				f.close();
				for(i=0;i<=count;i++){
					for(w=0;w<=W;w++){
						if(i==0||w==0)
							{k[i][w]=0;}
						else if(wt[i-1]<=w)
							{k[i][w]=max_value(val[i-1]+k[i-1][w-wt[i-1]],k[i-1][w]);}
						else{k[i][w]=k[i-1][w];}


					}//end of second loop
				}//end of first loop
				int res=k[count][W];
				fstream t;
				t.open("temp.txt",ios::out|ios::app);
				for(i=count;(i>0)&&(res>0);i--){
					if(res==k[i-1][w]){continue;}
					else{
						t<<endl<<item[i-1]<<endl<<wt[i-1]<<endl<<val[i-1];
						res=res-val[i-1];
						w=w-wt[i-1];
					}
				}//end of loop
				t.close();
				remove("stocks.txt");
				rename("temp.txt","stocks.txt");
				cout<<endl;
			}//end of else
		}//endl of function

		void delete_a_given_stock(){
			temp=front;
			cout<<"Enter the stocks you want to delete: ";cin>>element;
			cout<<endl;
			if(temp==NULL){
				cout<<"There is no element to delete"<<endl;}
			else{
				fstream file;
				file.open("stocks.txt",ios::in);
				file.seekg(0);
				while(file){
					getline(file,product);
					if(product==""){flag=0;break;}
					else if(product==element){
						flag=1;
						break;
					}
					file>>price_from_file;
					file>>profit_from_file;
				}
				file.close();
				if(flag==1){
					temp=front;
					if(temp->item==element && temp==front){
						temp=temp->link;
						delete front;
						front=temp;
					}else{
						while(temp!=NULL){
							if(temp->link->item==element){
								dummy=temp->link;
								temp->link=temp->link->link;
								delete dummy;
								break;
							}
							else{temp=temp->link;}
						}
					}
					cout<<"Deleted successfully"<<endl;
				}
				else{cout<<"given item not available"<<endl;}
			}
			if(flag==1){
				fstream file;
				file.open("temp.txt",ios::out|ios::app);
				dummy=front;
				while(dummy!=NULL){
					file<<endl<<dummy->item<<endl<<dummy->price<<endl<<dummy->profit;
					dummy=dummy->link;
				}
				file.close();
				remove("stocks.txt");
				rename("temp.txt","stocks.txt");
			}
		}

		void delete_entire_stock_item(){
			if(count==0){cout<<"Already empty"<<endl;}
			else{
				remove("stocks.txt");
				cout<<"The entire stock are deleted"<<endl;
			}
		}

		void free_up_memory(){
			temp=front;
			while(temp!=NULL){
				temp=temp->link;
				delete front;
				front=temp;
			}
			front=NULL;
			rear=NULL;
		}

		void read_file(){
			count=0;
			fstream file;
			file.open("stocks.txt",ios::in);
			file.seekg(0);
			while(file){
				temp=new node;
				getline(file,temp->item);
				if(temp->item==""){delete temp;
					break;
				}
				file>>temp->price;
				file>>temp->profit;
				if(rear==NULL){
					temp->link=NULL;
					front=rear;
				}else{
					rear->link=temp;
					temp->link=NULL;
					rear=temp;
				}
				count++;
			}
			file.close();
		}
		
		void display_item(){
			temp=front;
			int i=1;
			if(temp==NULL){
				cout<<"\t\t no stocks are avilable\n";
			}
			else{
				cout<<"The stock items are: "<<endl;
				cout<<"\t\t ______________________________________________________\n";
				cout<<"\t\t|S.No. |     item name            |price    | profit   |\n";
				cout<<"\t\t|______|__________________________|_________|__________|\n";
				while(temp!=NULL){
					 cout<<"\t\t|"<<setw(4)<<i<<"|"<<setw(5)<<"|"<<setw(48)<<temp->item<<setw(6)<<"|"<<setw(14)<<temp->price<<setw(10)<<"|"<<setw(12)<<temp->profit<<setw(8)<<"|"<<endl;
           				 temp=temp->link;
           				 i++;
		}
				cout<<"\t\t|______|__________________________|_________|__________|\n";
			}
			cout<<endl;
		}		
};

class open_menu{
	/*This class is made to display the command line menu of this program*/
	public:
		void start_menu(){
			cout<<"\t\t _____________\n";
			cout<<"\t\t|1. For login |\n";
			cout<<"\t\t|2. For signup|\n";
			cout<<"\t\t|3. Exit      |\n";
			cout<<"\t\t|_____________|\n";
		}

		void main_menu(){
			cout<<"\t\t ______________________________________________________\n";
			cout<<"\t\t|1. Input elements                                     |\n";
			cout<<"\t\t|2. Display elements                                   |\n";
			cout<<"\t\t|3. Delete all the elements                            |\n";
			cout<<"\t\t|4. Display element for maximum profit                 |\n";//knapsack problem program
			cout<<"\t\t|5. Modify price or profit of the elements             |\n";
			cout<<"\t\t|6. Delete an element                                  |\n";
			cout<<"\t\t|7. Exit                                               |\n";
			cout<<"\t\t|1. Input elements                                     |\n";
			cout<<"\t\t|______________________________________________________|\n";

		}

		void thank_you_screen(){
			 cout<<"\t\t _________\n";
                         cout<<"\t\t|thank you|\n";
                         cout<<"\t\t|_________|\n";
		}
};

int main(){
	int input_choices,W,n,flag;
	char s;
	open_menu menu;
	login_and_registration log;

	cout<<"Welcome"<<endl;
	do{
		cout<<endl;
		menu.start_menu();
		cin>>input_choices;
		switch(input_choices){
			case 1:
				flag=log.login();
				break;
			case 2:
				log.signup();
				cout<<"Do you want to login?(y/N): ";
				cin>>s;
				if(s=='y'||s=='Y'){flag=log.login();}
				else{
					menu.thank_you_screen();
					exit(1);
				}
				break;
			case 3:
				menu.thank_you_screen();
				exit(0);
				break;
			default:
				cout<<"Incorrect choice"<<endl;
				break;
		}
	}while(flag!=1);
	if(flag==1){
		cout<<"Enter the max amount: ";
		cin>>W;
		cout<<endl;
		while(1){
			menu.main_menu();
			cin>>input_choices;
			input_and_changes_in_item ob1;
			switch(input_choices){
				case 1:
					ob1.free_up_memory();
					ob1.read_file();
					ob1.input_stock_items();
					ob1.free_up_memory();
					cout<<endl;
					break;
				case 2:
					ob1.free_up_memory();
                                        ob1.read_file();
                                        ob1.display_item();
                                        ob1.free_up_memory();
                                        cout<<endl;
                                        break;
				case 3:
					ob1.free_up_memory();
                                        ob1.read_file();
                                        ob1.delete_entire_stock_item();
                                        ob1.free_up_memory();
                                        cout<<endl;
                                        break;
				case 4:
					ob1.free_up_memory();
                                        ob1.read_file();
                                        ob1.delete_stocks_for_max_profit(W);
                                        ob1.free_up_memory();
                                        cout<<endl;
                                        break;
				case 5:
					ob1.free_up_memory();
                                        ob1.read_file();
                                        ob1.delete_a_given_stock();
					ob1.input_stock_items();
                                        ob1.free_up_memory();
                                        cout<<endl;
                                        break;
				case 6:
					ob1.free_up_memory();
                                        ob1.read_file();
                                        ob1.delete_a_given_stock();
                                        ob1.free_up_memory();
                                        cout<<endl;
                                        break;
				case 7:
					cout<<"thank you"<<endl;
                                        ob1.free_up_memory();
                                        cout<<endl;
					exit(2);
                                        break;
				default:
					cout<<"Thank You"<<endl;
					break;
			}
		}
	}
}
