#include <bits/stdc++.h>
#include <cstdio>
#include <conio.h>

using namespace std;

class Administration
{
private:
    string admin_username[5]={"admin", "ADMIN", "Admin", "adminUser", "adminTester"};
    string admin_password[5]={"admin123", "ADMIN123", "Admin123", "password123", "pass123"};

public:
    bool login(const string& user, const string& pass)
    {
        for (int i=0;i<5;i++)
        {
            if (user==admin_username[i] && pass==admin_password[i])
            {
                return true;
            }
        }
        return false;
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


bool isAdmin(const string& user, const string& pass)
{
    FILE *file=fopen("users.csv", "r");
    if (file==NULL)
    {
        cout<<"Error opening file!"<<"\n";
        return false;
    }

    char line[100];
    char username[50],password[50];
    bool userFound=false;

    while (fgets(line,sizeof(line),file))
    {
        sscanf(line,"%[^,],%s", username,password);

        if (strcmp(username,user.c_str())==0)
        {
            userFound=true;
            if (strcmp(password, pass.c_str())==0)
            {
                fclose(file);
                return true;
            }
        }
    }
    fclose(file);
    return false;
}


void receptionist_database()
{
    cout << "\nAll Receptionist Information.\n\n";

    FILE *rdata;
    rdata=fopen("receptionist_database.csv","r");
    if(rdata==NULL)
    {
        cout<<"Error opening file!"<<"\n";
        return;
    }
    char rdetails[200];
    while(fgets(rdetails,sizeof(rdetails),rdata) !=NULL)
    {
        cout << rdetails;
    }
    fclose(rdata);
}


void searchReceptionist(const char *receptionistName)
{
    FILE *rdata=fopen("receptionist_database.csv","r");
    if(rdata==NULL)
    {
        cout<<"Error opening file!"<<"\n";
        return;
    }
    char details[200];
    bool found = false;

    while(fgets(details,sizeof(details), rdata) != NULL)
    {
        char *n=strtok(details," \n");
        while(n !=NULL)
        {
            if(strcmp(n,receptionistName)==0)
            {
                cout<<"\nReceptionist's Information:\n"<<"\n";
                cout<<details;

                while (fgets(details,sizeof(details),rdata) !=NULL && strcmp(details,"\n") !=0)
                {
                    cout << details;
                }
                found = true;
                break;
            }
            n = strtok(NULL, " \n");
        }
        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        cout<<"\nReceptionist with name '"<<receptionistName<<"' not found."<<"\n";
        cout<<"Please search again with the correct name."<<"\n";
    }

    fclose(rdata);
}


void addReceptionist()
{
    string username, password;

    cout << "\nTo add a new Receptionist, verify your login." << "\n";
    input_login(username, password);

    if (isAdmin(username,password))
    {
        string name,designation,department;
        string contact;

        getchar();
        cout<<"Enter name: ";getline(cin,name);
        cout<<"Enter designation: ";getline(cin,designation);
        cout<<"Enter department: ";getline(cin,department);
        cout<<"Enter contact: ";getline(cin,contact);

        FILE *rdata=fopen("receptionist_database.csv","a");
        if(rdata==NULL)
        {
            cout<<"Error opening file!"<<"\n";
            return;
        }

        fprintf(rdata,"Name: %s\nDesignation: %s\nDepartment: %s\nContact: %s\n\n",
                name.c_str(),designation.c_str(),department.c_str(),contact.c_str());

        fclose(rdata);
        cout<<"Receptionist '"<<name<<"' added successfully."<<"\n";
    }
    else
    {
        cout<<"Only admin can add a receptionist. Contact the admin."<<"\n";
    }
}


void deleteReceptionist()
{
    string username,password;

    cout<<"\nTo delete a Receptionist, verify your login."<<"\n";
    input_login(username, password);

    if(isAdmin(username,password))
    {
        string receptionistName;
        cout<<"Enter the Full Name of the receptionist to be deleted: ";cin>>receptionistName;

        FILE *rdata=fopen("receptionist_database.csv","r");
        if(rdata==NULL)
        {
            cout<<"No file found."<<"\n";
            return;
        }

        FILE *tempData=fopen("temp_receptionist_data.csv","w");
        if (tempData==NULL)
        {
            cout<<"No new file found."<<"\n";
            fclose(rdata);
            return;
        }

        char line[200];
        bool found=false;
        bool deleteMode=false;
        string currentLine;

        while(fgets(line,sizeof(line),rdata) !=NULL)
        {
            currentLine=line;

            if(currentLine.find("Name: ") !=string::npos && currentLine.find(receptionistName) !=string::npos)
            {
                found=true;
                deleteMode=true;
            }
            if(!deleteMode)
            {
                fprintf(tempData,"%s",line);
            }

            if (deleteMode && line[0]=='\n')
            {
                deleteMode=false;
            }
        }
        fclose(rdata);
        fclose(tempData);

        remove("receptionist_database.csv");
        rename("temp_receptionist_data.csv","receptionist_database.csv");

        if(found)
        {
            cout <<"Receptionist '"<<receptionistName<<"' deleted successfully."<<"\n";
        }
        else
        {
            cout<<"Receptionist '"<<receptionistName<<"' not found."<<"\n";
        }
    }
    else
    {
        cout << "Only admin can delete a receptionist. Contact the admin." <<"\n";
    }
}


void nurse_database()
{
    cout<<"\nAll Nurse's Information.\n\n";
    FILE *ndata=fopen("nurses_database.csv","r");

    if(!ndata)
    {
        cout<<"Error opening file!\n";
        return;
    }
    char fdetails[250];
    while (fgets(fdetails,sizeof(fdetails),ndata) !=NULL)
    {
        cout<<fdetails;
    }
    fclose(ndata);
    cout << "\n";
}


void searchNurse(const string& department)
{
    FILE *ndata=fopen("nurses_database.csv","r");

    if(!ndata)
    {
        cout<<"Error opening file!\n";
        return;
    }

    char ndetails[250];
    bool found=false;

    while(fgets(ndetails,sizeof(ndetails),ndata) !=NULL)
    {
        string line(ndetails);
        if(line.find(department) !=string::npos)
        {
            cout<<"\nNurse's Information:\n\n"<<line;
            found=true;
        }
    }

    if (!found)
    {
        cout << "\nNurse in department '" << department << "' not found.\n";
        cout << "Please search again.\n";
    }

    fclose(ndata);
}


void addNurse()
{
    string username,password;

    cout<<"\nTo add a new Nurse, verify your login.\n";
    input_login(username,password);

    if(isAdmin(username,password))
    {
        string name,designation,department,contact,availableTime,offDay;

        getchar();
        cout<<"Enter name: ";getline(cin,name);
        cout<<"Enter designation: ";getline(cin,designation);
        cout<<"Enter department: ";getline(cin,department);
        cout<<"Enter contact: ";getline(cin,contact);
        cout<<"Enter available time: ";getline(cin,availableTime);
        cout<<"Enter off day: ";getline(cin,offDay);

        FILE *ndata=fopen("nurses_database.csv","a");
        if(!ndata)
        {
            cout<<"Error opening file!\n";
            return;
        }

        fprintf(ndata,"Name: %s\nDesignation: %s\nDepartment: %s\nContact: %s\nAvailable Time: %s\nOff Day: %s\n\n",
                name.c_str(),designation.c_str(),department.c_str(),contact.c_str(),availableTime.c_str(),offDay.c_str());

        fclose(ndata);
        cout<< "Nurse '"<< name <<"' added successfully.\n";
    }
    else
    {
        cout<<"Only admin can add a nurse. Contact the admin.\n";
    }
}


void deleteNurse()
{
    string username,password;

    cout<<"\nTo delete a Nurse, verify your login.\n";
    input_login(username,password);

    if(isAdmin(username,password))
    {
        string nurseName;
        cout<<"Enter the Full Name of the nurse to be deleted: ";cin>>nurseName;

        FILE *ndata=fopen("nurses_database.csv","r");
        if(!ndata)
        {
            cout<<"No file found.\n";
            return;
        }

        FILE *tempData=fopen("temp_nurse_data.csv","w");
        if(!tempData)
        {
            cout<<"Error opening new file.\n";
            fclose(ndata);
            return;
        }

        char line[250];
        bool found=false;
        bool deleteMode=false;

        while(fgets(line,sizeof(line),ndata) !=NULL)
        {
            string currentLine(line);

            if(currentLine.find("Name: ") !=string::npos && currentLine.find(nurseName) !=string::npos) {
                found = true;
                deleteMode = true;
            }

            if(!deleteMode)
            {
                fputs(line,tempData);
            }

            if(deleteMode && currentLine=="\n")
            {
                deleteMode=false;
            }
        }

        fclose(ndata);
        fclose(tempData);

        remove("nurses_database.csv");
        rename("temp_nurse_data.csv", "nurses_database.csv");

        if(found)
        {
            cout<<"Nurse '" <<nurseName<<"' deleted successfully.\n";
        }
        else
        {
            cout<<"Nurse '"<<nurseName<<"' not found.\n";
        }
    }
    else
    {
        cout<<"Only admin can delete a nurse. Contact the admin.\n";
    }
}


void support_staff()
{
    cout<<"\nAll Support Staff's Information\n\n";
    FILE *sdata=fopen("support_staff_database.csv","r");

    if(!sdata)
    {
        cout<<"Error opening file!\n";
        return;
    }
    char sdetails[250];
    while(fgets(sdetails,sizeof(sdetails),sdata) !=NULL) {
        cout<<sdetails;
    }

    fclose(sdata);
    cout << "\n";
}


void searchSupport_staff(const string &department)
{
    FILE *sdata=fopen("support_staff_database.csv","r");
    if (!sdata)
    {
        cout<<"Error opening file!\n";
        return;
    }
    char sdetails[250];
    bool found=false;

    while(fgets(sdetails,sizeof(sdetails),sdata) !=NULL)
    {
        string line(sdetails);
        if(line.find(department) !=string::npos)
        {
            cout <<"\nSupport Staff Information:\n\n"<<line;
            found=true;
        }
    }
    if(!found)
    {
        cout <<"\nSupport Staff in department '"<< department<<"' not found.\n";
        cout<<"Please search again.\n";
    }
    fclose(sdata);
}


void addSupport_staff() {
    string username, password;

    cout << "\nTo add a new Support Staff, verify your login.\n";
    input_login(username, password);

    if (isAdmin(username, password)) {
        string name,designation,department,contact,availableTime,offDay;

        getchar();
        cout<<"Enter name: ";getline(cin,name);
        cout<<"Enter designation: ";getline(cin,designation);
        cout<<"Enter department: ";getline(cin,department);
        cout<<"Enter contact: ";getline(cin,contact);
        cout<<"Enter available time: ";getline(cin,availableTime);
        cout<<"Enter off day: ";getline(cin,offDay);

        FILE *sdata=fopen("support_staff_database.csv","a");
        if(!sdata)
        {
            cout<<"Error opening file!\n";
            return;
        }

        fprintf(sdata,"Name: %s\nDesignation: %s\nDepartment: %s\nContact: %s\nAvailable Time: %s\nOff Day: %s\n\n",
                name.c_str(),designation.c_str(),department.c_str(),contact.c_str(),availableTime.c_str(),offDay.c_str());

        fclose(sdata);
        cout<<"Support Staff '"<<name<<"' added successfully.\n";
    }
    else
    {
        cout<<"Only admin can add a support staff. Contact the admin.\n";
    }
}


void deleteSupport_staff()
{
    string username,password;

    cout<<"\nTo delete a Support Staff, verify your login.\n";
    input_login(username,password);

    if(isAdmin(username,password))
    {
        string StaffName;
        cout<<"Enter the Full Name of the support staff to be deleted: ";getline(cin,StaffName);

        FILE *sdata=fopen("support_staff_database.csv","r");
        if(!sdata)
        {
            cout<<"No file found.\n";
            return;
        }

        FILE *tempData=fopen("temp_support_staff_data.csv","w");
        if(!tempData)
        {
            cout<<"Error opening new file.\n";
            fclose(sdata);
            return;
        }
        char line[250];
        bool found=false;
        bool deleteMode=false;

        while(fgets(line,sizeof(line),sdata) !=NULL)
        {
            string currentLine(line);

            if(currentLine.find("Name: ") !=string::npos && currentLine.find(StaffName) !=string::npos)
            {
                found=true;
                deleteMode=true;
            }
            if (!deleteMode)
            {
                fputs(line,tempData);
            }

            if (deleteMode && currentLine=="\n")
            {
                deleteMode=false;
            }
        }
        fclose(sdata);
        fclose(tempData);

        remove("support_staff_database.csv");
        rename("temp_support_staff_data.csv","support_staff_database.csv");

        if (found)
        {
            cout<<"Support Staff '"<<StaffName<<"' deleted successfully.\n";
        }
        else
        {
            cout<<"Support Staff '"<<StaffName<<"' not found.\n";
        }
    }
    else
    {
        cout<<"Only admin can delete a support staff. Contact the admin.\n";
    }
}


void doctors_info()
{
    cout<<"\nAll Doctor's Information\n\n";
    FILE *data=fopen("doctors_data_base.csv","r");

    if(!data)
    {
        cout<<"Error: Unable to open file!\n";
        return;
    }

    char details[250];
    while(fgets(details,sizeof(details),data) !=NULL)
    {
        cout<<details;
    }
    fclose(data);
    cout<<"\n";
}


void searchDoctor(const char *doctorName)
{
    FILE *data=fopen("doctors_data_base.csv","r");

    if(!data)
    {
        cout<<"Error: Unable to open file!\n";
        return;
    }
    char details[250];
    bool found=false;

    while(fgets(details,sizeof(details),data) !=NULL)
    {
        if(strncmp(details,"Name: ",6)==0)
        {
            if(strstr(details, doctorName))
            {
                cout<<"Doctor's Information:\n"<<details;
                while(fgets(details,sizeof(details),data) !=NULL && strncmp(details,"\n",1) !=0)
                {
                    cout<<details;
                }
                found=true;
                break;
            }
        }
    }
    if (!found)
    {
        cout<<"Doctor with name '"<<doctorName<<"' not found.\nPlease search again.\n";
    }
    fclose(data);
}


void addDoctor()
{
    string username,password;

    cout<<"\nTo add a new Doctor, verify your login.\n";
    input_login(username,password);

    if(isAdmin(username,password))
    {
        string name,designation,department,qualification,speciality,chamberFloor;
        string chamberRoom,chamberTime,offDay,contact;
        getchar();
        cout<<"Enter name: ";getline(cin,name);
        cout<<"Enter designation: "; getline(cin,designation);
        cout<<"Enter department: "; getline(cin,department);
        cout<<"Enter qualification: "; getline(cin,qualification);
        cout<<"Enter speciality: "; getline(cin,speciality);
        cout<<"Enter chamber floor: ";getline(cin,chamberFloor);
        cout<<"Enter chamber room: ";getline(cin,chamberRoom);
        cout<<"Enter chamber time: ";getline(cin,chamberTime);
        cout<<"Enter off day: ";getline(cin,offDay);
        cout<<"Enter contact: ";getline(cin,contact);

        FILE *data=fopen("doctors_data_base.csv","a");
        if (!data)
        {
            cout<<"Error: Unable to open file for writing!\n";
            return;
        }

        fprintf(data,"\nName: %s\nDesignation: %s\nDepartment: %s\nQualification: %s\nSpeciality: %s\nChamber Floor: %s\nChamber Room: %s\nChamber Time: %s\nOff Day: %s\nContact: %s\n",
                name.c_str(),designation.c_str(),department.c_str(),qualification.c_str(),speciality.c_str(),chamberFloor.c_str(),chamberRoom.c_str(),chamberTime.c_str(),
                offDay.c_str(), contact.c_str());

        fclose(data);
        cout<<"Doctor '"<< name<<"' added successfully.\n";
    }
    else
    {
        cout<<"Only admin can add a doctor. Contact the admin.\n";
    }
}


void deleteDoctor()
{
    string username,password;

    cout<<"\nTo delete a Doctor, verify your login.\n";
    input_login(username,password);

    if (isAdmin(username, password))
    {
        string doctorName;
        cout<<"Enter the Full Name of the doctor to be deleted: ";
        cin.ignore();
        getline(cin,doctorName);

        FILE *data=fopen("doctors_data_base.csv","r");
        if (!data)
        {
            cout<<"Error: No file found.\n";
            return;
        }

        FILE *tempData=fopen("temp_data.csv","w");
        if (!tempData)
        {
            cout<<"Error: Unable to create temp file.\n";
            fclose(data);
            return;
        }

        char line[250];
        bool found=false;
        bool deleteMode=false;

        while (fgets(line,sizeof(line),data) !=NULL) {
            if (strncmp(line,"Name: ",6)== 0 && strstr(line,doctorName.c_str()))
            {
                found=true;
                deleteMode=true;
            }
            if(!deleteMode)
            {
                fputs(line,tempData);
            }

            if (deleteMode && line[0]=='\n')
            {
                deleteMode=false;
            }
        }
        fclose(data);
        fclose(tempData);

        remove("doctors_data_base.csv");
        rename("temp_data.csv","doctors_data_base.csv");

        if (found)
        {
            cout<<"Doctor '"<<doctorName<<"' deleted successfully.\n";
        }
        else
        {
            cout<<"Doctor '"<<doctorName<<"' not found.\n";
        }
    }
    else
    {
        cout<<"Only admin can delete a doctor. Contact the admin.\n";
    }
}


string current_dateTime()
{
    time_t t;
    time(&t);

    char buffer[20];
    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",localtime(&t));

    return string(buffer);
}

struct Patient {
    int id;
    string name;
    string age;
    string blood_grp;
    string guardian_name;
    string guardian_relation;
    string mobile;
    string problem;
    string refDoctor;
    string date_time;
    float totalBill;
    float paidAmount;
    Patient* next;
};

Patient *createPatient()
{
    return new Patient();
}

int LastPatientIdFromFile()
{
    FILE* file=fopen("patients.csv","r");
    if (!file)
    {
        return 1000;
    }

    int last_id=1000;
    char line[250];

    while(fgets(line,sizeof(line),file))
    {
        if (strncmp(line,"ID: ",4)==0)
        {
            sscanf(line, "ID: %d", &last_id);
        }
    }
    fclose(file);
    return last_id + 1;
}


void addBilling(Patient* patient)
{
    cout<<"Billing for patient ID: "<<patient->id<<"\n";

    cout<<"Enter total billing amount: $";cin>>patient->totalBill;
    patient->paidAmount=0;

    cout<<"Total billing amount for patient "<<patient->name<<" (ID: "<<patient->id << ") is $"<<patient->totalBill<<"\n";
}

void admitPatient(Patient* &head1)
{
    Patient* newPatient = createPatient();

    cout<<"Enter patient details:\n";
    getchar();
    cout<<"Name: ";getline(cin,newPatient->name);
    cout<<"Age: ";getline(cin,newPatient->age);
    cout<<"Blood Group: ";getline(cin,newPatient->blood_grp);
    cout<<"Guardian Name: ";getline(cin,newPatient->guardian_name);
    cout<<"Guardian Relation: ";getline(cin,newPatient->guardian_relation);
    cout<<"Mobile: ";getline(cin,newPatient->mobile);
    cout<<"Problem Details: ";getline(cin,newPatient->problem);
    cout<<"Referred By: ";getline(cin,newPatient->refDoctor);

    newPatient->date_time = current_dateTime();
    newPatient->id = LastPatientIdFromFile();

    addBilling(newPatient);

    newPatient->next = head1;
    head1 = newPatient;

    FILE* patientsFile = fopen("patients.csv", "a");
    if (patientsFile) {
        fprintf(patientsFile,
                "ID: %d\nName: %s\nAge: %s\nBlood Group: %s\nGuardian Name: %s\nGuardian Relation: %s\nContact: %s\nProblem Details: %s\nAdmitting Date & Time: %s\nReferred Doctor: %s\n\n",
                newPatient->id, newPatient->name.c_str(), newPatient->age.c_str(),
                newPatient->blood_grp.c_str(), newPatient->guardian_name.c_str(),
                newPatient->guardian_relation.c_str(), newPatient->mobile.c_str(),
                newPatient->problem.c_str(), newPatient->date_time.c_str(),
                newPatient->refDoctor.c_str());
        fclose(patientsFile);

        cout << "Patient admitted successfully. Patient ID: "
             << newPatient->id << "\nAdmission Date & Time: "
             << newPatient->date_time << "\n\n";
    } else {
        cerr << "Error: Could not open patients.csv file for writing!" << endl;
    }
}

Patient* findPatientByID(Patient* head, int id)
{
    Patient* current=head;
    while (current !=NULL)
    {
        if (current->id==id)
        {
            return current;
        }
        current=current->next;
    }
    return NULL;
}

void searchPatientDetails(int patientID)
{
    FILE* file=fopen("patients.csv","r");
    if (!file)
    {
        cerr<<"Error: Could not open patients.csv file!"<<"\n";
        return;
    }

    char line[250];
    bool found=false;

    while (fgets(line,sizeof(line),file))
    {
        if (strncmp(line,"ID: ",4)==0)
        {
            int id_in_file;
            sscanf(line,"ID: %d",&id_in_file);

            if (id_in_file==patientID)
            {
                found = true;
                cout << "Patient Details:\n";
                cout << line;
                for (int i=0;i<9;i++)
                {
                    fgets(line,sizeof(line),file);
                    cout << line;
                }
                break;
            }
        }
    }
    fclose(file);
    if(!found)
    {
        cout<<"Patient with ID "<<patientID<<" not found."<<"\n";
    }
}



void payBill(Patient* &head1,int patientID)
{
    Patient*patient=findPatientByID(head1,patientID);

    if(!patient)
    {
        cout<<"Patient with ID "<<patientID<<" not found."<<"\n";
        return;
    }

    cout<<"Patient found. Current bill: $"<<patient->totalBill<<"\n";
    cout<<"Paid amount so far: $"<<patient->paidAmount<<"\n";

    float payment;
    cout<<"Enter payment amount: $";
    cin>>payment;

    if (payment<0)
    {
        cout<<"Payment amount cannot be negative."<<"\n";
        return;
    }

    patient->paidAmount+=payment;
    cout <<"Updated paid amount: $"<<patient->paidAmount<<"\n";

    FILE* tempFile=fopen("temp_patients.csv","w");
    FILE* origFile=fopen("patients.csv","r");

    if(origFile && tempFile)
    {
        char line[250];
        while(fgets(line,sizeof(line),origFile))
        {
            if(strncmp(line,"ID: ",4)==0)
            {
                int id_in_file;
                sscanf(line,"ID: %d",&id_in_file);

                if (id_in_file == patient->id) {
                    fprintf(tempFile,
                            "ID: %d\nName: %s\nAge: %s\nBlood Group: %s\nGuardian Name: %s\nGuardian Relation: %s\nContact: %s\nProblem Details: %s\n"
                            "Admitting Date & Time: %s\nReferred Doctor: %s\nTotal Bill: %.2f\nPaid Amount: %.2f\n\n",
                            patient->id, patient->name.c_str(), patient->age.c_str(),patient->blood_grp.c_str(), patient->guardian_name.c_str(),
                            patient->guardian_relation.c_str(), patient->mobile.c_str(),patient->problem.c_str(), patient->date_time.c_str(),patient->refDoctor.c_str(),
                            patient->totalBill, patient->paidAmount);

                    for (int i=0; i<10;i++)
                    {
                        fgets(line,sizeof(line),origFile);
                    }
                }
                else
                {
                    fprintf(tempFile,"%s",line);
                }
            }
            else
            {
                fprintf(tempFile,"%s",line);
            }
        }
        fclose(origFile);
        fclose(tempFile);

        remove("patients.csv");
        rename("temp_patients.csv", "patients.csv");

        cout << "Bill updated successfully." << "\n";
    } else {
        cerr << "Error updating the bill!" << "\n";
        if (origFile) fclose(origFile);
        if (tempFile) fclose(tempFile);
    }
}



void releasePatient(Patient* &head1,int patientID)
{
    Patient* patient=findPatientByID(head1,patientID);

    if(!patient)
    {
        cout<<"Patient with ID "<<patientID<<" not found."<<"\n";
        return;
    }

    cout<<"Releasing patient with ID: "<<patientID<<"\n";

    if(patient->totalBill>patient->paidAmount)
    {
        cout<<"Outstanding bill: $"<<(patient->totalBill-patient->paidAmount)
             <<". Please pay the remaining amount to release the patient."<<"\n";
        return;
    }
    Patient* current=head1;
    Patient* prev=NULL;

    while(current)
    {
        if(current==patient)
            {
            if(prev)
            {
                prev->next=current->next;
            }
            else
            {
                head1=current->next;
            }
            break;
        }
        prev=current;
        current=current->next;
    }

    FILE* tempFile=fopen("temp_patients.csv","w");
    FILE* origFile=fopen("patients.csv","r");

    if(origFile && tempFile)
    {
        char line[250];
        while(fgets(line,sizeof(line),origFile))
        {
            if(strncmp(line, "ID: ",4)==0)
            {
                int id_in_file;
                sscanf(line,"ID: %d",&id_in_file);
                if (id_in_file == patient->id)
                {
                    for (int i=0;i<10;i++)
                    {
                        fgets(line, sizeof(line), origFile);
                    }
                }
                else
                {
                    fprintf(tempFile,"%s",line);
                }
            }
            else
            {
                fprintf(tempFile,"%s",line);
            }
        }
        fclose(origFile);
        fclose(tempFile);

        remove("patients.csv");
        rename("temp_patients.csv","patients.csv");
        cout<<"Patient "<<patientID<<" released successfully."<<"\n";
    }
    else
    {
        cerr<<"Error: Could not open files for patient release!"<<"\n";
        if(origFile) fclose(origFile);
        if(tempFile) fclose(tempFile);
    }
    delete patient;
}




int main() {
    Patient* head = NULL;
    Administration admin;
    string username, password;
    int choice;
    int loginAttempts = 0;

    cout<<"\t\t Welcome to Hospital Management System! Be healthy and keep smiling!!"<<"\n\n";

    while (loginAttempts < 5) {
        cout << "Enter Unique Credential: "; cin >> username;
        cout << "Enter Default password: ";
        char ch;
        password = "";

        while (true) {
            ch = _getch();
            if (ch == '\r' || ch == '\n') {
                cout << "\n";
                break;
            } else if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.erase(password.size() - 1);
                }
            } else {
                password.push_back(ch);
                cout << '*';
            }
        }

        if (admin.login(username,password))
        {
            cout<<"Admin login successful!"<<"\n\n";

            do {
                try {
                    cout<<"\nAdmin Menu:\n";
                    cout<<"1. Create User\n";
                    cout<<"2. Modify User\n";
                    cout<<"3. Delete User\n";
                    cout<<"4. View Users\n";
                    cout<<"5. Manage Receptionists\n";
                    cout<<"6. Manage Nurses\n";
                    cout<<"7. Manage Support Staff\n";
                    cout<<"8. Manage Doctor\n";
                    cout<<"9. Manage Patient\n";
                    cout<<"10. Logout\n";
                    cout<<"Choose an option: ";

                    if(!(cin>>choice))
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
                            {
                            int choice;
                            do {
                                try {
                                    cout<<"Receptionist Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout <<"4. Delete" <<"\n";
                                    cout <<"5. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addReceptionist();
                                            break;
                                        case 2:
                                            receptionist_database();
                                            break;
                                        case 3: {
                                            string Rname;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, Rname);
                                            searchReceptionist(Rname.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteReceptionist();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." << "\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 6:
                            {
                            int choice;
                            do {
                                try {
                                    cout<< "Nurses Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"5. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addNurse();
                                            break;
                                        case 2:
                                            nurse_database();
                                            break;
                                        case 3: {
                                            string dept;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, dept);
                                            searchNurse(dept.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteNurse();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 7:
                            {
                            int choice;
                            do {
                                try {
                                    cout<< "Support Staff Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"5. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addSupport_staff();
                                            break;
                                        case 2:
                                            support_staff();
                                            break;
                                        case 3: {
                                            string dept;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, dept);
                                            searchSupport_staff(dept.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteSupport_staff();
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 8:
                            {
                            int choice;
                            do {
                                try {
                                    cout << "Doctors Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"5. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin>>choice))
                                    {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice)
                                    {
                                        case 1:
                                            addDoctor();
                                            break;
                                        case 2:
                                            doctors_info();
                                            break;
                                        case 3: {
                                            string name;
                                            cin.ignore();
                                            cout<<"Enter Name to Search: ";
                                            getline(cin, name);
                                            searchDoctor(name.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteDoctor();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout<<"Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch(const invalid_argument &e)
                                {
                                    cout<<"Error: "<<e.what() <<"\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                }
                            } while (choice != 5);
                        }
                        case 9:
                            {
                            int choice;
                            do {
                                try {
                                    cout<<"Patient Menu" << "\n";
                                    cout<<"1. Admit Patient"<<"\n";
                                    cout<<"2. Add Billing"<<"\n";
                                    cout<<"3. Pay Bill"<<"\n";
                                    cout<<"4. Search Patient"<< "\n";
                                    cout<<"5. Release Patient"<<"\n";
                                    cout<<"6. Exit to Menu"<<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice))
                                    {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice)
                                    {
                                        case 1:
                                            admitPatient(head);
                                            break;
                                        case 2: {
                                            int patientID;
                                            cout << "Enter Patient ID to add billing: ";
                                            cin >> patientID;
                                            Patient* patient = findPatientByID(head, patientID);

                                            if (patient) {
                                                addBilling(patient);
                                            } else {
                                                cout << "Patient with ID " << patientID << " not found." << "\n";
                                            }
                                            break;
                                        }
                                        case 3: {
                                            int patientID;
                                            cout << "Enter Patient ID to pay the bill: ";
                                            cin >> patientID;
                                            payBill(head, patientID);
                                            break;
                                        }
                                        case 4: {
                                            int patientID;
                                            cout << "Enter Patient ID to search: ";
                                            cin >> patientID;
                                            searchPatientDetails(patientID);
                                            break;
                                        }
                                        case 5: {
                                            int patientID;
                                            cout << "Enter Patient ID to release: ";
                                            cin >> patientID;
                                            releasePatient(head, patientID);
                                            break;
                                        }
                                        case 6:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." << "\n";
                                    }
                                }
                                catch (const invalid_argument &e)
                                {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                } while (choice != 6);
                            }
                        case 10:
                            cout << "Exiting admin panel."<<"\n";
                            break;
                        default:
                            cout<<"Invalid option. Please try again."<<"\n";
                    }
                } catch (const invalid_argument &e)
                {
                    cout<<"Error: "<<e.what()<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }

            }
            while(choice != 10);
            break;
        }
        else if(!admin.login(username,password))
        {
            cout<<"Login successful! You are logged in as "<<username<<"\n";
            do {
                try {
                    cout<<"\nUser Menu:\n";
                    cout<<"1. Manage Receptionists\n";
                    cout<<"2. Manage Nurses\n";
                    cout<<"3. Manage Support Staff\n";
                    cout<<"4. Manage Doctor\n";
                    cout<<"5. Manage Patient\n";
                    cout<<"6. Logout\n";
                    cout<<"Choose an option: ";

                    if(!(cin>>choice))
                    {
                        throw invalid_argument("Input must be a number.");
                    }

                    switch (choice)
                    {
                        case 1:
                            {
                            int choice;
                            do {
                                try {
                                    cout<<"Receptionist Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"4. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addReceptionist();
                                            break;
                                        case 2:
                                            receptionist_database();
                                            break;
                                        case 3: {
                                            string Rname;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, Rname);
                                            searchReceptionist(Rname.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteReceptionist();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." << "\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 2:
                            {
                            int choice;
                            do {
                                try {
                                    cout << "Nurses Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"4. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addNurse();
                                            break;
                                        case 2:
                                            nurse_database();
                                            break;
                                        case 3: {
                                            string dept;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, dept);
                                            searchNurse(dept.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteNurse();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 3:
                            {
                            int choice;
                            do {
                                try {
                                    cout << "Support Staff Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"4. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice)) {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice) {
                                        case 1:
                                            addSupport_staff();
                                            break;
                                        case 2:
                                            support_staff();
                                            break;
                                        case 3: {
                                            string dept;
                                            cin.ignore();
                                            cout << "Enter Name to Search: ";
                                            getline(cin, dept);
                                            searchSupport_staff(dept.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteSupport_staff();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch (const invalid_argument &e) {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                            } while (choice != 5);
                        }
                        case 4:
                            {
                            int choice;
                            do {
                                try {
                                    cout << "Doctors Menu" <<"\n";
                                    cout<<"1. Add" <<"\n";
                                    cout<<"2. View" <<"\n";
                                    cout<<"3. Search" <<"\n";
                                    cout<<"4. Delete" <<"\n";
                                    cout<<"4. Exit to Menu" <<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin>>choice))
                                    {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice)
                                    {
                                        case 1:
                                            addDoctor();
                                            break;
                                        case 2:
                                            doctors_info();
                                            break;
                                        case 3: {
                                            string name;
                                            cin.ignore();
                                            cout<<"Enter Name to Search: ";
                                            getline(cin, name);
                                            searchDoctor(name.c_str());
                                            break;
                                        }
                                        case 4:
                                            deleteDoctor();
                                            break;
                                        case 5:
                                            cout<<"Exiting to Main Menu"<<"\n";
                                            break;
                                        default:
                                            cout<<"Invalid option. Please try again." <<"\n";
                                    }
                                }
                                catch(const invalid_argument &e)
                                {
                                    cout<<"Error: "<<e.what() <<"\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                }
                            } while (choice != 5);
                        }
                        case 5:
                            {
                            int choice;
                            do {
                                try {
                                    cout<<"Patient Menu" << "\n";
                                    cout<<"1. Admit Patient"<<"\n";
                                    cout<<"2. Add Billing"<<"\n";
                                    cout<<"3. Pay Bill"<<"\n";
                                    cout<<"4. Search Patient"<< "\n";
                                    cout<<"5. Release Patient"<<"\n";
                                    cout<<"6. Exit"<<"\n";
                                    cout<<"Enter your choice: ";

                                    if (!(cin >> choice))
                                    {
                                        throw invalid_argument("Input must be a number.");
                                    }

                                    switch (choice)
                                    {
                                        case 1:
                                            admitPatient(head);
                                            break;
                                        case 2: {
                                            int patientID;
                                            cout << "Enter Patient ID to add billing: ";
                                            cin >> patientID;
                                            Patient* patient = findPatientByID(head, patientID);

                                            if (patient) {
                                                addBilling(patient);
                                            } else {
                                                cout << "Patient with ID " << patientID << " not found." << "\n";
                                            }
                                            break;
                                        }
                                        case 3: {
                                            int patientID;
                                            cout << "Enter Patient ID to pay the bill: ";
                                            cin >> patientID;
                                            payBill(head, patientID);
                                            break;
                                        }
                                        case 4: {
                                            int patientID;
                                            cout << "Enter Patient ID to search: ";
                                            cin >> patientID;
                                            searchPatientDetails(patientID);
                                            break;
                                        }
                                        case 5: {
                                            int patientID;
                                            cout << "Enter Patient ID to release: ";
                                            cin >> patientID;
                                            releasePatient(head, patientID);
                                            break;
                                        }
                                        case 6:
                                            cout << "Exiting the system." << "\n";
                                            break;
                                        default:
                                            cout << "Invalid option. Please try again." << "\n";
                                    }
                                }
                                catch (const invalid_argument &e)
                                {
                                    cout << "Error: " << e.what() << "\n";
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                }
                                } while (choice != 6);
                            }
                        case 6:
                            cout << "Exiting User panel."<<"\n";
                            break;
                        default:
                            cout<<"Invalid option. Please try again."<<"\n";
                    }
                } catch (const invalid_argument &e)
                {
                    cout<<"Error: "<<e.what()<<"\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                }

            }
            while(choice != 6);
            break;
        }



        else
        {
            loginAttempts++;
            cout << "Login failed! Incorrect username or password." << "\n";
            if (loginAttempts < 5)
            {
                cout << "Please try again. Attempts remaining: " << (5 - loginAttempts) <<"\n";
            }
            else
            {
                cout << "Maximum login attempts reached. Exiting." <<"\n";
            }
        }
    }


    Patient* current = head;
    while (current) {
        Patient* toDelete = current;
        current = current->next;
        delete toDelete;
    }

    return 0;
}
