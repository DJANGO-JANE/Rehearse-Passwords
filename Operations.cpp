/*
*
*		Description: Password Memorising Helper Application
*		Written by: DJANGO JANE
*		Date: 2/09/2020
*
***************************************************/
#define _CRT_SECURE_NO_WARNINGS
#ifdef _WIN32
#include <direct.h>
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h""
#define cwd getcwd
#define cd chdir
#endif


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <corecrt_io.h>
#include "Operations.h"


const std::string TOP_BORDER = "\t====================================================================";


std::string djane::Operations::getPasswordHint()
{

    std::string value;
    std::ifstream in("data.dat");
    if (in.is_open())
    {
        std::string line;
        while (getline(in, line))
        {
            value = line.substr(0,line.find(" "));
        }
    }
    else
    {
        std::cerr << "\t\t>> Error occurred while trying to read from file.\n";
    }
    return value;
}

bool djane::Operations::checkPassword(std::string passString, std::string value)
{
    bool truthValue = false;
    std::ifstream in("data.dat", std::ios::binary);
    if (in.is_open())
    {
        std::string line, domain;
        while (getline(in, line))
        {
            int firstSpace = line.find(" ");
            domain = line.substr(0,firstSpace);
            if (domain == passString)
            {
                std::string remainingDT,pass;
                remainingDT = line.substr(firstSpace + 1);
                
                //TODO: Salt and hash password
                pass= remainingDT.substr(0,remainingDT.find(" "));
                if (pass==SecureChannel->EncryptData(value))
                {
                    truthValue = true;
                    break;
                }
            }
        }
                return truthValue;
    }
    return truthValue;
}

bool djane::Operations::addRecordToFile(std::string account, std::string pass)
{
    std::ofstream record("data.dat", std::ios::app);
    if (record.is_open())
    {
        //TODO: Salt and hash password
        record << account << " " << SecureChannel->EncryptData(pass) <<" "<<0<<" "<<0<<std::endl;
        return true;
    }
    return false;
}

void djane::Operations::WriteToRecord(std::string account,int point,int attempt)
{
    std::stringstream rowText;

    std::ifstream row("data.dat");
    std::ofstream newFile("temp.dat",std::ios::app);

    if (row.good())
    {
        std::string line;
        while (getline(row,line,'\n') && !row.eof())
        {
            if (newFile.fail())
            {
                std::cout << ">> Error occurred while writing to temp file\n";
                break;
            }
            std::string domain = line.substr(0, line.find(' '));
            
            if ((domain != account) && (newFile.good()))
            {
                newFile << line<<std::endl;
            }
            else if(newFile.good() && domain==(account))
            {
                line.erase(std::remove(line.begin(), line.end(), '\0'), line.end());

                rowText << line;
                std::string word, a, b;
                int c, d;

                rowText >> word; a = word; 
                rowText >> word; b = word; 
                rowText >> word; c = stoi(word); c += point;
                rowText >> word; d = stoi(word); d += attempt;

                std::vector<std::string> courier{ account,"<HIDDEN>",std::to_string(c),std::to_string(d) };

                //Display user progress. NOTE: setting the argument to false means not to display the actual password
                if (point == 1)
                {
                    /*
                        // Implement decryption operation later when I can devise one
                        //  So that decrypted password can be displayed after user has correctly entered
                        //  A password for the account.

                        courier[1] = SecureChannel->DecryptData(b); 
                    */

                    ProgressReport(true, courier);
                }
                else
                {
                    ProgressReport(false, courier);
                }
                newFile << a << " " << b << " " << (c) << " " << (d) << std::endl;
                    rowText.clear();
                    continue;
            }
        }
    newFile.close();
    }

    row.close();
    remove("data.dat");
    rename("temp.dat", "data.dat");
}

int djane::Operations::GetFileSize(std::string path)
{
    FILE* p_file = NULL;
    p_file = fopen(path.c_str(), "rb");
    fseek(p_file, 0, SEEK_END);
    int size = ftell(p_file);
    fclose(p_file);

    return size;
}

void djane::Operations::WorkingDirectoryCheck(std::string ndir)
{
    char* buf = {};
    std::string temp;
        temp = cwd(buf, sizeof buf);//Store the current working directory in a string

        //Check if current working directory (cwd) is the same as newly specified directory
        if(temp!=ndir)
        {
            _mkdir(ndir.c_str());
            SetFileAttributes(ndir.c_str(), FILE_ATTRIBUTE_HIDDEN);
            cd(ndir.c_str());

            //Copy work files from VS default working directory to new directory.
            std::string lines, olddir= temp.append("\\data.dat"),
                newdir= ndir.append("\\data.dat");
            std::ifstream getFile(olddir, std::ios::in);
            std::ofstream putFile(newdir, std::ios::app);

            //TODO: Compare file sizes then copy files if olddir
            //      size is bigger than newdir
            //if (getFile.good())
            //{
            //    if (djane::Operations::GetFileSize(olddir) > djane::Operations::GetFileSize(newdir))
            //    {
            //        if (putFile.good() && getFile.is_open())
            //        {
            //            while (getline(getFile, lines))
            //            {
            //                putFile << lines << std::endl;
            //            }
            //        }
            //    }
            //}
        }
    std::cout << "Working Directory: [" <<cwd(buf, sizeof buf)<<"]\n";
}

bool djane::Operations::RemoveAppFile()
{
    char* buf = {};
    std::string temp;
    temp = cwd(buf, sizeof buf);
    temp.append("\\data.dat");
    if (remove(temp.c_str()) == 0)
    {
        std::cout << "\n\t\t\t\t>> FILES HAVE BEEN DELETED.\n";
        return true;
    }
    else
    {
        std::cout << "\n\t\t\t\t>> ERROR OCCURRED: Delete files manually.\n";
        return false;
    }
}

void djane::Operations::ProgressReport(bool showOrNot, std::vector<std::string> courier)
{
    if (showOrNot)
    {
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Domain: " << courier[0] << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Password: " << courier[1] << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Progress: " << (courier[2]) << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Attempts: " << (courier[3]) << std::endl;
    }
    else
    {
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Domain: " << courier[0] << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Password: " << courier[1] << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Progress: " << (courier[2]) << std::endl;
        std::cout << "\t\t\t\t\t" << std::left << std::setw(20) << std::setfill(' ') << "Attempts: " << (courier[3]) << std::endl;
    }
}

