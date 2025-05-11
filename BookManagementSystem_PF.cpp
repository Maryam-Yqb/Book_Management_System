#include<iostream>
#include<fstream>
#include<string>
#include <iomanip> // For formatting output

using namespace std;

// Book structure 

 struct Book {
    int B_id;
    string B_name;
    string B_author;
    int B_price;

 };
 
 // Function declarations
 void add_record();
 void view_record();
 void search_record();
 void delete_record();
 void edit_record();
 bool duplicate(int id);


int main()
{
    int choice;
     do
     {
     	// Display the main menu
        cout << "\n============================================ Book Management System ============================================\n" << endl;
        cout << "1. Add Record" << endl;
        cout << "2. View All Records" << endl;
        cout << "3. Search Record" << endl;
        cout << "4. Delete Record" << endl;
        cout << "5. Edit Record" << endl;
        cout << "6. Exit" << endl<<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout<<endl<<endl;
        
         // Call the appropriate function based on user choice
        switch(choice)
        {
        	case 1:
        	//calling add function
        	add_record();
        	cout<<endl<<endl;
        	break;
        	case 2:
        	//calling view function
			view_record();
			cout<<endl<<endl;
        	break;
        	case 3:
        	//calling search function
			search_record();
			cout<<endl<<endl;
        	break;
        	case 4:
       	    //calling delete function
			delete_record();
			cout<<endl<<endl;
 	        break;
 	        case 5:
        	//calling edit function
			edit_record();
			cout<<endl<<endl;
        	break;
       		case 6: cout << "Exiting the program." << endl; break;
        	default: cout << "Invalid choice. Please try again!" << endl;
        }
    }
    while(choice!=6);
	return 0;
}

// Function to add a new book
void add_record()
{
	Book a[50];
    int n,b=0;
    ofstream outfile("ProjectProgramming.txt" , ios::app);
    if (!outfile) 
	{
        cout << "Error: Could not open file." << endl;
        return;
    }
    do
    {
        cout << "Enter Book ID: ";
        cin >> a[b].B_id;
        cin.ignore();
        while(duplicate(a[b].B_id) )
		{
			cout<<"\nThis ID Is Already Present\n"<<endl;
			cout<<"Enter New ID: "<<endl;
			cin>>a[b].B_id;
			cin.ignore();
        }
        
        // Get book details from the user
        cout << "Enter Book Name: ";
		getline(cin, a[b].B_name);
		cout << "Enter Book Author: ";
        getline(cin, a[b].B_author);
        cout << "Enter Book Price: ";
		cin>> a[b].B_price;
		cin.ignore();
		
		// Writing details to the file
        outfile << a[b].B_id << "\t" << a[b].B_name << "\t" << a[b].B_author << "\t" << a[b].B_price << endl;
        cout<<"\nPress 1 to Continue \nPress 0 to Exit \n";
        cin>>n;
        cin.ignore();
        cout<<endl<<endl;
        b++;
    }
	while (n!=0);
    outfile.close();
}

// Using Duplicate Function 
bool duplicate(int id)
{
	ifstream file;
	file.open("ProjectProgramming.txt");
	Book temporary;
	while(file >> temporary.B_id>>temporary.B_name>>temporary.B_author>>temporary.B_price)
	if(temporary.B_id==id)
	{
		file.close();
        return true;
    }
	file.close();
	return false;
}

// Function to view all books
void view_record()
{
	Book a[50];
	int b=0;
	ifstream infile("ProjectProgramming.txt");
	if (!infile)
	{
    	cout << "Error: Could not open file." << endl;
        return;
    }
    cout << "-----------------------------------------------------------------" << endl;
    cout << left << setw(10) << "Book ID"<< setw(20) << "Book Name"<< setw(20) << "Author"<< setw(10) << "Price" << endl;
    cout << "-----------------------------------------------------------------\n" << endl;
    while(infile>>a[b].B_id)
    {
    	infile.ignore();
    	getline(infile, a[b].B_name,'\t');
        getline(infile, a[b].B_author,'\t');
        infile >> a[b].B_price;
        infile.ignore();
        cout <<left <<setw(10) << a[b].B_id << setw(20) << a[b].B_name << setw(20) << a[b].B_author << setw(10) << a[b].B_price <<"\n";
        b++;
    }
    cout << "-----------------------------------------------------------------" << endl;
    infile.close();
}

// Function to search for a book by ID
void search_record()
{
	Book a[50];
	int n,b=0,search_id;
	bool found = false;
	do
	{
		// Get the ID to search
		cout<<"Enter Book ID: ";
		cin>>search_id;
		cout<<endl<<endl;
		ifstream infile("ProjectProgramming.txt");
		if (!infile)
		{
        	cout << "Error: Could not open file." << endl;
        	return;
        }
    	cout << "-----------------------------------------------------------------" << endl;
    	cout << left << setw(10) << "Book ID" << setw(20) << "Book Name" << setw(20) << "Author" << setw(10) << "Price" << endl;
    	cout << "-----------------------------------------------------------------\n" << endl;
    	
    	  // Search for the record
		while(infile>>a[b].B_id)
        {
        	infile.ignore();
    		getline(infile, a[b].B_name,'\t');
        	getline(infile, a[b].B_author,'\t');
        	infile >> a[b].B_price;
        	infile.ignore();
        	if(a[b].B_id==search_id)
        	{
        		cout <<left <<setw(10) << a[b].B_id << setw(20) << a[b].B_name << setw(20) << a[b].B_author << setw(10) << a[b].B_price <<"\n";
        		cout << "-----------------------------------------------------------------" << endl;
				cout << "\n\t\t=====Record Found=====\n";
				found = true;
			}
			b++;
		}
		if (!found)
		{
        	cout << "\t\t\tRecord not found." << endl;
        }
        cout<<"\n\nPress 1 to Continue \nPress 0 to Exit \n";
        cin>>n;
        cin.ignore();
    }
	while(n!=0);
}
   
   // Function to delete the book
void delete_record()
{
    Book a[50];
    int b=0,n, delete_id;
    bool found=false;
    do
    {
    	// Get the ID to delete
    	cout<<"Enter Book ID To Delete: ";
		cin>>delete_id;
		cout<<endl<<endl;
		ifstream infile("ProjectProgramming.txt");
		ofstream secfile("secT.txt");
		if(!infile || !secfile)
		{
			cout << "Error: Could not open file." << endl;
        	return;
		}
		// Delete the record
		
		while(infile>>a[b].B_id)
        {
        	infile.ignore();
    		getline(infile, a[b].B_name,'\t');
        	getline(infile, a[b].B_author,'\t');
        	infile >> a[b].B_price;
        	infile.ignore();
        	if(a[b].B_id==delete_id)
        	{
        		cout << "\t=====Record Deleted Successfully!=====\t" << endl;
        		found=true;
        	}
			else
			{
			secfile << a[b].B_id << "\t" << a[b].B_name << "\t" << a[b].B_author << "\t" << a[b].B_price << endl;
			}
		}
		infile.close();
		secfile.close();
		remove("ProjectProgramming.txt"); // Delete the original file
    	rename("secT.txt", "ProjectProgramming.txt");   // Rename the temporary file
    	if (!found)
		{
        	cout << "Record not found." << endl;
        }
		cout<<"Press 1 to Continue \nPress 0 to Exit \n";
        cin>>n;
        cin.ignore();
	}
	while(n!=0);
}

// Function to edit a book
void edit_record()
{
	Book a[50];
    int b=0,n, edit_id;
    bool found=false;
    do
    {
    	// Get the ID to edit
    	cout<<"Enter Book ID To Edit: ";
		cin>>edit_id;
		cin.ignore();
		ifstream infile("ProjectProgramming.txt");
		ofstream secfile("secT.txt");
		if(!infile || !secfile)
		{
			cout << "Error: Could not open file." << endl;
        	return;
		}
		// Edit the record
		
		while(infile>>a[b].B_id)
        {
	        infile.ignore();
	    	getline(infile, a[b].B_name,'\t');
	        getline(infile, a[b].B_author,'\t');
	        infile >> a[b].B_price;
	        infile.ignore();
	        if(a[b].B_id==edit_id)
	        {
	        	found=true;
	        	cout << "Enter Book Name: ";
				getline(cin, a[b].B_name);
	    		cout << "Enter Book Author: ";
	        	getline(cin, a[b].B_author);
	        	cout << "Enter Book Price: ";
	   			cin>> a[b].B_price;
	        	secfile << a[b].B_id << "\t" << a[b].B_name << "\t" << a[b].B_author << "\t" << a[b].B_price << endl;
	        }
			else
			{
				secfile << a[b].B_id << "\t" << a[b].B_name << "\t" << a[b].B_author << "\t" << a[b].B_price << endl;
			}
		}
        infile.close();
		secfile.close();
		remove("ProjectProgramming.txt"); // Delete the original file
    	rename("secT.txt", "ProjectProgramming.txt");   // Rename the temporary file
    	if (found)
		{
			cout << "Record With ID " << edit_id << " Edited Successfully!" << endl;
        }
    	cout<<"Press 1 to Continue \n Press 0 to Exit ";
        cin>>n;
        cin.ignore();
	}
	while(n!=0);
}
