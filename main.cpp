#include <bits/stdc++.h>
#include <cstdio>
#include <conio.h>

using namespace std;

class Administration
{
private:
    string admin_username="admin";
    string admin_password="admin123";

public:
    bool login(const string& user,const string& pass)
    {
        return (user==admin_username && pass==admin_password);
    }

    void createUser()
    {
        char username[50], password[50];
        cout<<"Enter new username: ";cin>>username;
        cout<<"Enter new password: ";cin>>password;

        FILE *file=fopen("users.csv", "a");
        if(file==NULL)
        {
            cout<<"Error opening file!"<<"\n";
            return;
        }

        fprintf(file,"%s,%s\n",username,password);
        fclose(file);

        cout<<"User created successfully and saved to users.csv."<<"\n";
    }

    void modifyUser()
    {
        char username[50], newPassword[50], line[100];
        cout << "Enter the username to modify: ";cin >> username;
        cout << "Enter new password: ";cin >> newPassword;

        FILE *file=fopen("users.csv","r");
        FILE *tempFile=fopen("temp.csv","w");
        if(file==NULL || tempFile==NULL)
        {
            cout<<"Error opening file!"<<"\n";
            return;
        }

        bool userFound=false;

        while(fgets(line, sizeof(line), file))
        {
            char storedUser[50],storedPass[50];
            sscanf(line,"%[^,],%s",storedUser,storedPass);

            if(strcmp(storedUser,username)==0)
            {
                fprintf(tempFile,"%s,%s\n",username,newPassword);
                userFound=true;
            }
            else
            {
                fputs(line,tempFile);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("users.csv");
        rename("temp.csv","users.csv");

        if(userFound)
        {
            cout<<"Password updated successfully for user: "<<username<<"\n";
        }
        else
        {
            cout<<"User not found."<<"\n";
        }
    }

    void deleteUser()
    {
        char username[50],line[100];
        cout<<"Enter the username to delete: ";cin>>username;

        FILE *file=fopen("users.csv","r");
        FILE *tempFile=fopen("temp.csv","w");
        if(file==NULL || tempFile==NULL)
        {
            cout<<"Error opening file!"<<"\n";
            return;
        }

        bool userFound=false;

        while(fgets(line,sizeof(line),file))
        {
            char storedUser[50],storedPass[50];
            sscanf(line,"%[^,],%s",storedUser,storedPass);

            if(strcmp(storedUser,username) !=0)
            {
                fputs(line,tempFile);
            }
            else
            {
                userFound=true;
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("users.csv");
        rename("temp.csv","users.csv");

        if(userFound)
        {
            cout<<"User deleted successfully."<<"\n";
        }
        else
        {
            cout<<"User not found."<<"\n";
        }
    }

    void viewUsers()
    {
        FILE *file=fopen("users.csv","r");
        if(file==NULL)
        {
            cout<< "Error opening file or no users found!"<<"\n";
            return;
        }

        char line[100];
        fgets(line,sizeof(line),file);

        cout<<"\n--- List of Users ---"<<"\n";
        while(fgets(line, sizeof(line), file))
        {
            char storedUser[50],storedPass[50];
            sscanf(line, "%[^,],%s",storedUser,storedPass);
            cout<<"Username: "<<storedUser<<"\n";
        }

        fclose(file);
    }
};


void input_login(string &username,string &password)
{
    cout<<"Enter Username: ";cin>>username;
    cout<<"Enter Password: ";
    char ch;
    password="";

    while(true)
    {
        ch= _getch();

        if(ch=='\r' || ch=='\n')
        {
            cout<<"\n";
            break;
        }
        else if(ch=='\b')
        {
            if(!password.empty())
            {
                cout<<"\b \b";
                password.erase(password.size() - 1);
            }
        }
        else
        {
            password.push_back(ch);
            cout << '*';
        }
    }
}

int administrator(const string &user,const string &pass)
{
    FILE *file=fopen("users.csv","r");
    if (file==NULL) {
        cout<<"Error opening file!"<<"\n";
        return 0;
    }

    char line[100];
    bool userFound=false;

    while (fgets(line,sizeof(line),file))
    {
        char storedUser[50],storedPass[50];
        sscanf(line,"%[^,],%s",storedUser,storedPass);

        if (user==storedUser)
        {
            userFound=true;
            if (pass==storedPass)
            {
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    return 0;
}


void login_pannel()
{
    bool login=false;
    string username,password;

    while(!login)
        {
        input_login(username,password);
        login =administrator(username,password);
        if (login)
        {
            cout<<"Login Successful. Welcome to Hospital Management System, You are logged in as "<<username<<"\n";
        }
        else
        {
            cout<<"Login Failed. Bad Password or Username. Try again or contact admin."<<"\n";
        }
    }
}

int main() {
    login_pannel();

    Administration admin;
    string username,password;
    int choice;

    cout<<"Enter Unique Credential: ";cin>>username;
    cout<<"Enter Default password: ";
        char ch;
    password = "";

    while (true)
    {
        ch = _getch();
        if(ch=='\r' || ch=='\n')
        {
            cout << endl;
            break;
        }
        else if (ch == '\b')
        {
            if (!password.empty())
            {
                cout << "\b \b";
                password.erase(password.size() - 1);
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }


    if(admin.login(username, password))
        {
        cout << "Admin login successful!" << endl;

        do
        {
            try {
                cout << "\nMenu:\n";
                cout << "1. Create User\n";
                cout << "2. Modify User\n";
                cout << "3. Delete User\n";
                cout << "4. View Users\n";
                cout << "5. Exit\n";
                cout << "Choose an option: ";

                if (!(cin >> choice))
                {
                    throw invalid_argument("Input must be a number.");
                }

                switch (choice)
                {
                    case 1:
                        admin.createUser();
                        break;
                    case 2:
                        admin.modifyUser();
                        break;
                    case 3:
                        admin.deleteUser();
                        break;
                    case 4:
                        admin.viewUsers();
                        break;
                    case 5:
                        cout << "Exiting admin panel." << endl;
                        break;
                    default:
                        cout << "Invalid option. Please try again." << endl;
                }

            }
            catch (const invalid_argument &e)
            {
                cout << "Error: " << e.what() << endl;

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

        }
        while (choice != 5);
    }
    else
    {
        cout<<"Login failed! Incorrect username or password."<<"\n";
    }

    return 0;
}
