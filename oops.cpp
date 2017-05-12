#include <iostream>
#include <cstring>
#include <list>
#include <fstream>
#include <cctype>
using namespace std;

//-----------------------------------------------------------------------------------
// Class Declarations begins
//-----------------------------------------------------------------------------------
class person
{
	public:
		char name[50], phone[15]; 
};
//--------------------------------------------------------------------------------
class coordinator: public person
{
	
};
//--------------------------------------------------------------------------------
class parti : public person 										// Derived class representing event participants
{
	public:
		char college[100], eventname[50], edufield[30]; 			// a participant has a college, field of education
		int team;													// Number of members in the team, if this is team participation
		friend ofstream &operator<<(ofstream &stream, parti p); 	// Persisting the set of participants in a csv file format
		friend ifstream &operator>>(ifstream &stream, parti &p); 	// Retrieving set of participants from a csv file
};

list <parti> participants; 											//linked list of participants using STL
//---------------------------------------------------------------------------------
class event
{
	protected:														//encapsulation
		char description[200], location[50];
		char timeslot[20], date[20];
		coordinator StudentCoord, FacultyCoord, Judge;
		int prize;
		int noinateam;												// No of team members required for this event
	public:
		char flag, name[50];
		int registration, numberofparticipants;
		virtual bool validatepart(int numofpart, int amtpaid, char *edufield ){}
		friend ostream &operator<<(ostream &stream, event e);
		friend ifstream &operator>>(ifstream &stream, event &e);
		friend ofstream &operator<<(ofstream &stream, event e);						// polymorphism by operator overloading
		virtual void display(){}													// Implemented in derived classes
		friend void edit(event &e);													// friend function that enables event to be edited
		 template<typename placeholder> friend placeholder input(placeholder c);
};
//-------------------------------------------------------------------------------
class cultural : public event
{
	public:
		bool validatepart(int numofpart, int amtpaid, char *edufield)
		{
			if(numofpart==noinateam && numofpart*100==amtpaid) //is a valid participant if they have paid the right amount (each individual must pay 100)
			//And if the number of participants in the team do not exceed the max allowed
			{
				cin.clear();
				fflush (stdin); 
				cout<<"\nYou have successfully registered!\n";
				return true; //if the correct registertion amount is paid, participant is valid
			}
			else
			{
				cout<<"\nRegistration failed!!!!\n";
				return false;
			}
				
		}
		void display();
		
}; 
list <cultural> clist; //list of cultural events
//------------------------------------------------------------------------------
void cultural:: display()
{
	cout<<"\nC u l t u r a l   E v e n t s\n";
	cout<<"Number of events: "<< clist.size() << "\n";
	list<cultural>::iterator C= clist.begin();
	while(C!=clist.end())
	{
		cout << "\t" << C->name << endl;
		C++;
	}
	cout << endl;
}
//--------------------------------------------------------------------------------------------
// Template function capable in searching in lists of cultural, technical and Proshow events
template <typename placeholder>
void search(list<placeholder> &list1, char *eventname) //generic function to search a list
{
	typename list<placeholder>::iterator c= list1.begin();
	while(c!=list1.end())
	{
		if(!strcmp(c->name,eventname))
		{
			placeholder C=*c;
			cout<<"\nHere are the event details:\n--------------------------\n" << C;
			return;
		}
		c++;
	}
	cout<<"\nThis event does not exist!!\nPlease refer list of events.\n";
	return;
	
}
//--------------------------------------------------------------------------------------
class technical : public event
{
	public:
		bool validatepart(int numofpart, int amtpaid, char *edufield)
		{
			if(numofpart==noinateam && numofpart*100==amtpaid && (strcmp(edufield, "ENG")|| strcmp(edufield, "SCI"))) 
			// Assumed that only engineering or science students are allowed to participate in technical events
			// Thus, validation logic is different in different subclasses of event
			{
				cout<<"\nRegistration successful!\n";
				return true;
				//if correct registration is paid & participant is either an engineer or a science student, is valid
			}
			else
			{
				cout<<"\nRegistration failed!\n";
				return false;
			 } 
		}
		void display();
}; 
list <technical> tlist;
//------------------------------------------------------------------------------------------
void technical:: display()
{
	cout<<"\nT e c h n i c a l   E v e n t s\n";
	cout<<"Number of events: "<<tlist.size() << "\n";
	list<technical>::iterator T= tlist.begin();
	while(T!=tlist.end())
	{
		cout << "\t" << T->name << "\n";
		T++;
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------------------------
class proshows : public event
{
	public:
		bool validatepart(int numofpart, int amtpaid, char *edufield)
		{
			cout<<"\nNo registration is required or allowed for Proshow events!!\n";
			return false; //no participant can exist for proshows
		}
		void display();
}; 
list <proshows> plist;
//---------------------------------------------------------------------------------
void proshows:: display()
{
	cout<<"\nP r o s h o w s\n";
	cout<<"Number of proshows: "<<plist.size() << "\n";
	list<proshows>::iterator C= plist.begin();
	while(C!=plist.end())
	{
		cout<< "\t" << C->name << "\n";
		C++;
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------------
// Read the event details from a csv file represented by ifstream
ifstream &operator>> (ifstream &stream, event &e)
{
	char str[100];
	if(stream.good())
	{
		stream.getline(str, 100, ',');
		strcpy(e.name, str);
		stream.getline(str,100, ',');
		strcpy(e.description, str);
		stream.getline(str,100, ',');
		sscanf(str, "%d" , &e.prize);
		stream.getline(str,100, ',');
		strcpy(e.timeslot, str);
		stream.getline(str,100, ',');
		strcpy(e.date, str);
		stream.getline(str,100, ',');
		strcpy(e.location, str);
		stream.getline(str,100, ',');
		strcpy(e.StudentCoord.name, str);
		stream.getline(str,100, ',');
		strcpy(e.StudentCoord.phone, str);
		stream.getline(str,100, ',');
		strcpy(e.FacultyCoord.name, str);
		stream.getline(str,100, ',');
		strcpy(e.FacultyCoord.phone, str);
		stream.getline(str,100, ',');
		strcpy(e.Judge.name, str);
		stream.getline(str,100, ',');
		strcpy(e.Judge.phone, str);
		stream.getline(str,100, ',');
		sscanf(str, "%d" , &e.registration);
		stream.getline(str,100, ',');
		sscanf(str, "%d" , &e.noinateam);
		stream.getline(str,100, ',');
		sscanf(str, "%d", &e.numberofparticipants);
	}
	return stream;
}
//--------------------------------------------------------------------------------------
// Display event details on the console
ostream &operator<<(ostream &stream, event e)
{
		char ch;
	stream<<"Event: "<<e.name<<"\nEvent Description: "<<e.description<<"\nCoordinator: "<<e.StudentCoord.name<<" ("<<e.StudentCoord.phone<<")\nPrize money: ";
	stream<<e.prize<<"\nNumber of members allowed in a team: "<< e.noinateam<<"\nDate and Time: "<<e.timeslot<<", "<<e.date;
	stream<<"\nLocation: "<<e.location<<"\n";
	stream<<"For further information, enter Y\n";
	cin.clear();
	fflush (stdin);
	cin>>ch;
	if(ch=='Y' || ch == 'y')
	{
		stream<<"\nFaculty coordinator details: "<<e.FacultyCoord.name<<" ("<<e.FacultyCoord.phone<<")";
		stream<<"\nJudge details: "<<e.Judge.name<< " ("<<e.Judge.phone<<")";
		stream<<"\nRegistration amount collected so far: "<<e.registration;
		stream<<"\nNumber of teams already registered: "<<e.numberofparticipants;
		stream<<"\n";
	}
	
	return stream;

}
//-----------------------------------------------------------------------------------------
// Persist event into a csv file
ofstream &operator<<(ofstream &stream, event e)
{
	stream<<e.flag<<","<<e.name<<","<<e.description<<","<<e.prize<<","<<e.timeslot<<","<<e.date<<","<<e.location<<","<<e.StudentCoord.name<<","<<e.StudentCoord.phone<<",";
	stream<<e.FacultyCoord.name<<","<<e.FacultyCoord.phone<<","<<e.Judge.name<<","<<e.Judge.phone<<","<<e.registration<<","<<e.noinateam<<",";
	stream<<e.numberofparticipants<<",\n";
	return stream;
}
//------------------------------------------------------------------------------------------------------
// Persist participant into a csv file
ofstream &operator<<(ofstream &stream, parti p)
{
	stream<<p.name<<","<<p.phone<<","<<p.eventname<<","<<p.edufield<<","<<p.college<<","<<p.team<<",\n";
	return stream;
}
//----------------------------------------------------------------------------------------------------
// Read participant from a csv file
ifstream &operator>>(ifstream &stream, parti &p)
{
	char str[100];
	stream.getline(str,100, ',');
	strcpy(p.name, str);
	stream.getline(str,100, ',');
	strcpy(p.phone, str);
	stream.getline(str,100, ',');
	strcpy(p.eventname, str);
	stream.getline(str,100, ',');
	strcpy(p.edufield, str);
	stream.getline(str,100, ',');
	strcpy(p.college, str);
	stream.getline(str,100, ',');
	sscanf(str, "%d", &p.team);
	return stream;
}
//----------------------------------------------------------------------------------------------
// Traverse through the lists of culturak, technical and proshow events and persist them in a file
void updateevents()
{
	ofstream rewriteevents("event.csv");
	list<cultural>::iterator c= clist.begin();
	while(c!=clist.end())
		{
			cultural C=*c;
			rewriteevents<<C;
			c++;
		}
	list<technical>::iterator t= tlist.begin();
	while(t!=tlist.end())
		{
			technical T=*t;
			rewriteevents<<T;
			t++;
		}
	list<proshows>::iterator p= plist.begin();
	while(p!=plist.end())
	{
		proshows P=*p;
		rewriteevents<<P;
		p++;
	}
	rewriteevents.close();
	return;
}
//----------------------------------------------------------------
// Traverse the participants list in order to persist them into a csv file
void updateparticipants()
{
	ofstream updatepart("Participants.csv");
					list<parti>::iterator pa= participants.begin();
					while(pa!=participants.end())
					{
						parti temp=*pa;
						updatepart<<temp;
						pa++;
					}
					updatepart.close();
}
//-----------------------------------------------------------------------------
void readevents()
{
	char flag[2];
	ifstream filereader("event.csv");
	
	if (!filereader) {
		cout << "Error!!";
		return;
	}
		
	while(filereader)
	{
		if (filereader.peek() == '\n')
			filereader.ignore();
		if (filereader.peek() == EOF) break;
		
		filereader.getline(flag, 2, ','); //read if cultural or technical event and place in flag
		
		if(!strcmp(flag,"t"))
		{
			technical t;
			t.flag='t';
			filereader>>t;
			tlist.push_back(t);
			
		}
		else if(!strcmp(flag, "c"))
		{
			cultural c;
			c.flag='c';
			filereader>>c;
			clist.push_back(c);

		}
		else if(!strcmp(flag, "p"))
		{
			proshows p;
			p.flag= 'p';
			filereader>>p;
			plist.push_back(p);
		}
	}
	filereader.close();
}
//-------------------------------------------------------------
void readparticipants()
{
	ifstream readpart("Participants.csv");
	if(!readpart)
	{
		return;
	}
	else
	{
		while(readpart)
	{
		if (readpart.peek() == '\n')
			readpart.ignore();
		if (readpart.peek() == EOF) break;
		parti P;
		readpart>>P;
		participants.push_back(P);
	}
}
	return;
	
}
//-----------------------------------------------------------
// Find the user specified event in order to edit it
void editevent(char *s)
{
		list<cultural>::iterator c= clist.begin();
	while(c!=clist.end())
		{
			if(!strcmp(c->name, s))
			{
				edit(*c);
				break;
				
			}
			c++;
		}
	list<technical>::iterator t= tlist.begin();
	while(t!=tlist.end())
		{
			if(!strcmp(t->name, s))
			{
				edit(*t);
				break;
				}
			t++;
		}
	list<proshows>::iterator pr= plist.begin();
	while(pr!=plist.end())
		{
			if(!strcmp(pr->name, s))
			{
					edit(*pr);
					break;
				}
			pr++;	
	}
	return;	
}
//------------------------------------------------------
// Ask event details from user and update in event class
void edit(event &e)
{
	char ch;
	cout<<"You have chosen to edit "<<e.name;
	cout<<"\nEnter student co-ordinator's name and number: ";
	cin.getline(e.StudentCoord.name, 100);
	cin>>e.StudentCoord.phone;
	cout<<"\nEnter faculty co-ordinator's name ";
	cin.clear();
	fflush (stdin);
	cin.getline(e.FacultyCoord.name, 100);
	cout<<"\nEnter faculty co-ordinator's number: ";
	cin.clear();
	fflush (stdin); 
	cin>>e.FacultyCoord.phone;
	cout<<"\nDo you wish to enter the judge for the event?Y/N ";
	cin.clear();
	fflush (stdin); 
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
		cout<<"\nEnter judge's name and contact number: ";
		cin.getline(e.Judge.name, 100);
		cin>e.Judge.phone;
	}
	cout<<"\nMaximum number of participants per team?\n";
	cin>>e.noinateam;
	return;
}
//--------------------------------------------------------------------------------------
// Add a new participant
void addpart()
{
	parti p;
	int amount;
	cout<<"\nEnter your name: ";
	cin.clear();
	fflush (stdin); 
	cin.getline(p.name, 50);
	cout<<"\nEnter phone number: ";
	cin>>p.phone;
	cout<<"\nEnter college name: ";
	cin.clear();
	fflush (stdin);
	cin.getline(p.college, 100);
	cout<<"\nEnter event name: ";
	cin.clear();
	fflush (stdin);
	cin.getline(p.eventname, 50);
	cout<<"\nSelect education field: 1.ENGineering\n2.SCIence\n3.MEDical\n4.LAW\n5.COMmerce\n";
	cin>>p.edufield;
	cout<<"\nEnter number of participants in the team: ";
	cin>>p.team;
	cout<<"\nRegistration amount is 100 per participant.\nEnter the amount you have paid: ";
	cin>>amount;
	list<cultural>::iterator c= clist.begin();
	while(c!=clist.end())
		{
			if(!strcmp(c->name, p.eventname))
			{
				cultural C=*c;
				if(C.validatepart(p.team,amount, p.edufield) )
				{
					participants.push_back(p);
					c->registration+=amount;
					c->numberofparticipants+=1;
					return;
					
				}
			}
			c++;
		}
	list<technical>::iterator t= tlist.begin();
	while(t!=tlist.end())
		{
			if(!strcmp(t->name, p.eventname))
			{
				technical T=*t;
				if(T.validatepart(p.team,amount, p.edufield) )
				{
					participants.push_back(p);
					t->registration+=amount;
					t->numberofparticipants+=1;
					return;
				}
			}
			t++;
		}

	return;
} 
//----------------------------------------------------------------------------------------
// Add a new event
void addevent()
{
	int n;
	cout<<"\nChoose type of event: 1. Cultural, 2. Technical 3. Proshow\n";
	cin>>n;
	switch(n)
	{
		case 1: {
				cultural c;
				c.flag='c';
				c=input(c);
				clist.push_back(c);
				break;}
		case 2: {
				technical t;
				t.flag= 't';
				t=input(t);
				tlist.push_back(t);
				break;}
		case 3:{
				 proshows p;
				p.flag='p';
				p=input(p);
				plist.push_back(p);
				break;}
				
	}
}
//--------------------------------------------------------------------------------------------------
// Template function that accepts user inputs to create any of three types of events
template<typename placeholder>
placeholder input(placeholder c)
{
	char ch;
	cout<<"Enter event name: "; 
	cin.clear();
	fflush (stdin);
	cin.getline( c.name, 50);
	cout<<"Enter event description: ";
	cin.clear();
	fflush (stdin);
	cin.getline(c.description, 100);
	cout<<"Enter prize money for the event: ";
	cin.clear();
	fflush (stdin);
	 cin>>c.prize;
	cout<<"Enter date of the event: ";
	cin.clear();
	fflush (stdin);
	cin.getline(c.date, 50);
	cout<<"Enter time slot: ";
	cin.clear();
	fflush (stdin);
	 cin.getline(c.timeslot, 50);
	cout<<"Enter number of participants in a team: ";
	cin.clear();
	fflush (stdin);
	 cin>>c.noinateam;
	cin.clear();
	fflush (stdin);
	cout<<"Enter student co-ordinator's name and number: ";
	cin.getline(c.StudentCoord.name, 100);
	cin>>c.StudentCoord.phone;
	cout<<"Enter faculty co-ordinator's name ";
	cin.clear();
	fflush (stdin);
	cin.getline(c.FacultyCoord.name, 100);
	cout<<"Enter faculty co-ordinator's number: ";
	cin.clear();
	fflush (stdin); 
	cin>>c.FacultyCoord.phone;
	cout<<"Do you wish to enter the judge for the event?Y/N ";
	cin.clear();
	fflush (stdin); 
	cin>>ch;
	if(ch=='Y'||ch=='y')
	{
		cout<<"Enter judge's name and contact number: ";
		cin.clear();
		fflush (stdin); 
		cin.getline(c.Judge.name, 100);
		cin>c.Judge.phone;
	}
	cin.clear();
	fflush (stdin); 
	cout<<"Enter location: "; cin.getline(c.location, 50);
	c.registration=0;
	c.numberofparticipants=0;
	return c;
		
}
//------------------------------------------------------------------------------------------------------------------
int main()
{
	system("color 2");
	readevents();
	readparticipants();
	int ch, n;
	cout<<"A N A A D Y A N T A   2 0 1 7\n";
	while(1)
	{
		system("color 2");
		cout<<"\n MAIN MENU\n1. Display All Events\n2. Display Details of Event\n3. Edit details of an event\n4. Register for an event\n5. Add a new event\n6. Save and Exit\nChoose Action:"<<endl;
		cin>>ch;
		switch(ch)
		{
			case 1: system("color 3");
					cout<<"\n1.Cultural events\n2.Technical Events\n3.Proshows\nChoose Event type to display:";
					cin>>n;
					if(n==1) {
						cultural c;
						c.display();
					}
					else if(n==2)
					{
						technical t;
						t.display();
					}
					else
					{
						proshows p;
						p.display();
					}
					break;
			case 2: system("color 3");
					cout<<"\n1.Cultural events\n2.Technical Events\n3.Proshows\nSelect Event Type:";
					cin>>n;
					char name[40];
					cout<<"\nEnter name of the event you are looking for: \n";
					cin.clear();
					fflush (stdin); 
					cin.getline (name, 40, '\n');
					if(n==1) search(clist, name);
					else if(n==2) search(tlist, name);
					else search(plist, name);
					
					break;
			case 3: system("color 3");
					cout<<"\nEnter name of the event you wish to edit: \n";
					cin.clear();
					fflush (stdin); 
					cin.getline (name, 40, '\n');
					editevent(name);
					break;
			case 4:	system("color 3");
					addpart();
					break;
			case 5: system("color 3");
					addevent();
					break;
			case 6: updateevents();
					updateparticipants();
					return 0;
				
		}
	}
	
	return 0;
}

